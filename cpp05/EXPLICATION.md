# CPP05 — Exceptions, héritage, classes abstraites

> Doc de révision soutenance. Objectif du module : maîtriser les **exceptions C++**
> (try/catch/throw + classes d'exception perso) et l'**héritage / polymorphisme**
> (virtual, classe abstraite, destructeur virtuel).

---

## 1. Les exceptions

### 1.1 Le principe (try / catch / throw)
Même logique qu'en Python (`try/except/raise`), en C++ c'est `try/catch/throw` :

```cpp
try {
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException(); // on "lance" un objet
}
catch (const std::exception &e) {   // on attrape par REFERENCE const
    std::cerr << e.what() << std::endl;
}
```

Quand un `throw` part :
1. l'exécution **s'arrête** à l'endroit du throw,
2. la pile se **déroule** (stack unwinding) : tous les objets locaux déjà construits
   entre le `throw` et le `catch` sont **détruits proprement** (leurs destructeurs sont appelés),
3. on saute au premier `catch` dont le type correspond.

C'est ce déroulement qui rend les exceptions sûres : pas de fuite tant qu'on utilise le RAII
(ressources gérées par des objets, libérées dans leur destructeur).

### 1.2 Classe d'exception personnalisée
Une exception perso = une classe qui **hérite de `std::exception`** et **redéfinit `what()`**.
Dans ce module on les **imbrique** dans la classe principale (ex : `Bureaucrat::GradeTooHighException`).

```cpp
class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
};
```

Points à savoir :
- **`catch` n'est PAS lié à `std::exception`** : on peut throw/catch n'importe quel type
  (`throw 42;` est valide). On hérite de `std::exception` **par convention**, pour pouvoir
  tout attraper avec un seul `catch (const std::exception &)` et lire `e.what()`.
- **`what()`** est une méthode **virtuelle** de `std::exception`. On la redéfinit pour donner
  notre message. Elle renvoie un `const char *` (chaîne C, pas `std::string`).

### 1.3 La spécification `throw()` (C++98)
```cpp
const char *what() const throw();
```
- Le `throw()` après la signature = **spécification d'exception vide** : "cette fonction promet
  de ne JAMAIS lancer d'exception".
- Si malgré tout une exception s'échappe d'une fonction `throw()` → `std::unexpected()` →
  **`std::terminate()`** → **`abort()`** : le programme **crash brutalement** (PAS un arrêt propre,
  pas de déroulement de pile garanti).
- On met `throw()` uniquement quand on est certain que ça ne throw pas (comme `what()` qui
  ne fait que `return "..."`). En C++11+ ce serait `noexcept`.

### 1.4 Attraper par référence — IMPORTANT
On écrit **toujours** `catch (const std::exception &e)`, jamais `catch (std::exception e)`.
- Par **valeur** → on **copie** l'exception, et surtout il y a **slicing** (tranchage) :
  une `GradeTooLowException` copiée dans un `std::exception` perd sa partie dérivée → le
  `what()` polymorphe n'est plus appelé.
- Par **référence** → pas de copie, pas de slicing, le vrai type polymorphe est conservé.

### 1.5 Exceptions et constructeurs (le piège qui revient)
Quand un constructeur **throw** (ex : grade hors bornes) :
- l'objet **n'est jamais complètement construit**, donc son **destructeur n'est PAS appelé**.
- MAIS **tous les membres déjà construits** (ex : `_name` qui est une `std::string` initialisée
  dans la liste d'init AVANT le throw) **sont détruits proprement** → **pas de fuite**.
- C'est pour ça qu'on peut valider et throw dans le corps du constructeur, même après que les
  membres `const` aient été initialisés dans la liste d'init (leur valeur invalide n'a aucune
  conséquence puisque l'objet ne vivra jamais).

### 1.6 Garantie d'exception forte (strong guarantee)
Une opération qui peut throw devrait laisser l'objet **inchangé en cas d'échec** ("tout ou rien").
Exemple concret dans `incrementGrade` : on **valide la valeur visée AVANT de l'appliquer** :
```cpp
void Bureaucrat::incrementGrade() {
    if (_grade - 1 < 1)             // on teste la future valeur
        throw GradeTooHighException();
    _grade--;                       // appliqué seulement si valide
}
```
Si on faisait l'inverse (`_grade--` puis test), l'objet resterait avec un grade illégal
après le throw → garantie cassée.

---

## 2. Héritage et polymorphisme

### 2.1 `virtual`
- Sans `virtual`, l'appel d'une méthode est résolu **à la compilation** selon le **type statique**.
- Avec `virtual`, l'appel est **dynamique** (résolu à l'exécution selon le **vrai type** de l'objet) :
  c'est le polymorphisme. En Python toutes les méthodes sont virtuelles par défaut ; en C++ il
  faut le demander.

### 2.2 Méthode pure virtuelle et classe abstraite
```cpp
virtual void performAction() const = 0;   // le "= 0" la rend PURE virtuelle
```
- Une classe avec **au moins une** méthode pure virtuelle est **abstraite** : on **ne peut pas
  l'instancier** (`AForm a;` → erreur de compil "cannot declare variable to be of abstract type").
- Toute fille doit **redéfinir** la méthode pure pour devenir concrète (instanciable).
- Équivalent Python : `ABC` + `@abstractmethod`. Le **A** de `AForm` = convention 42 pour
  "Abstract".

### 2.3 Destructeur virtuel — OBLIGATOIRE pour une base polymorphe
```cpp
virtual ~AForm();
```
Si on manipule les filles via un pointeur de base (`AForm *f = new ShrubberyCreationForm(...);`)
et qu'on fait `delete f;` :
- **sans** destructeur virtuel → seul `~AForm()` est appelé, **pas** celui de la fille →
  **comportement indéfini / fuite** (la partie fille n'est pas nettoyée).
- **avec** `virtual ~AForm()` → la destruction part du bon destructeur (fille puis base).
- Règle absolue : **dès qu'une classe a des méthodes virtuelles / est destinée à l'héritage,
  son destructeur doit être virtuel.**

### 2.4 NVI — Non-Virtual Interface (design d'`AForm`)
- `execute()` est **public et non-virtuel** : il impose les conditions communes (form signé ?
  grade de l'exécuteur suffisant ?) puis délègue.
- `performAction()` est **privé et virtuel pur** : c'est la seule partie qui change selon le form.
- Subtilité : les **spécificateurs d'accès (`private`) n'empêchent PAS le `override`**. La
  résolution virtuelle est indépendante de la visibilité, donc une fille peut bien redéfinir
  une méthode privée de la base.
- Intérêt : la base **garde le contrôle** du déroulement (pré/post-conditions centralisées),
  les filles ne customisent que l'action. Code plus sûr, moins dupliqué.

### 2.5 Forward declaration vs `#include`
- `#include "Bureaucrat.hpp"` → met **toute la définition** à disposition (nécessaire si on
  utilise la taille de la classe, un membre par valeur, ou on appelle ses méthodes).
- `class Bureaucrat;` (forward declaration) → dit juste "cette classe existe". **Suffit** tant
  qu'on ne manipule que des **pointeurs / références** (cas de `beSigned(const Bureaucrat &)`).
- On l'utilise surtout pour **casser une inclusion circulaire** (A inclut B qui inclut A).
- Dans le header d'`AForm`, la forward declaration suffit ; garder `#include "Bureaucrat.hpp"`
  en plus est redondant.

---

## 3. Les exercices

### ex00 — Bureaucrat
Classe `Bureaucrat` :
- `name` **const**, `grade` entre **1 (le plus haut)** et **150 (le plus bas)**.
- 2 exceptions internes : `GradeTooHighException` (grade < 1), `GradeTooLowException` (grade > 150).
- `incrementGrade` (fait baisser le chiffre, vers 1) / `decrementGrade` (fait monter, vers 150),
  qui throw aux bornes — en **validant la future valeur avant de l'appliquer** (strong guarantee).
- Getters + `operator<<` au format `<name>, bureaucrat grade <grade>.`.

Pièges :
- `_name` est const → **pas copié** dans `operator=` (on ne copie que `_grade`).
- `Bureaucrat b("Bernd", 1500);` est strictement équivalent à `Bureaucrat b = Bureaucrat("Bernd", 1500);`.
- Sens des bornes : `grade < 1` = trop **haut**, `grade > 150` = trop **bas** (contre-intuitif).

Objectif pédagogique : **les exceptions C++**.

### ex01 — Form
Classe `Form`, attributs **tous privés** :
- `name` const, `isSigned` (bool, false au départ), `gradeToSign` const, `gradeToExecute` const.
- Mêmes exceptions de grade. **Le constructeur valide les DEUX grades** (faute classique : oublier
  `gradeToExecute`, ou inverser high/low).
- `beSigned(const Bureaucrat &)` : passe `isSigned` à true si le grade suffit (`grade <= gradeToSign`),
  sinon throw `GradeTooLowException` (jamais TooHigh : un bureaucrate a toujours un grade valide).
- `Bureaucrat::signForm()` : appelle `beSigned`, catch, et affiche succès ou échec + raison.

Détail : afficher un `bool` donne `0`/`1` ; pour `true`/`false` utiliser un ternaire ou
`std::boolalpha`.

Objectif : **interaction entre classes via exceptions**, encapsulation stricte.

### ex02 — AForm + classes concrètes
- `Form` devient `AForm`, **abstraite** (méthode pure virtuelle `performAction()`), **destructeur virtuel**.
- 3 filles concrètes :
  - `ShrubberyCreationForm` (sign 145 / exec 137) : écrit `<target>_shrubbery` (arbres ASCII via `ofstream`).
  - `RobotomyRequestForm` (sign 72 / exec 45) : bruit de perceuse, **50 % de réussite** (`rand() % 2`),
    sinon throw `RobotizationFailed`.
  - `PresidentialPardonForm` (sign 25 / exec 5) : message de pardon par Zaphod Beeblebrox.
- `execute(const Bureaucrat &) const` dans la base (modèle NVI) : throw `IsNotSignedException` si non
  signé, `GradeTooLowException` si l'exécuteur n'a pas le grade, puis appelle `performAction()`.
- `Bureaucrat::executeForm(const AForm &)`.

Fautes à surveiller : destructeur **non** virtuel (UB au delete), constructeur `AForm` qui ne valide
pas les grades.

Objectif : **héritage, classe abstraite, polymorphisme, destructeur virtuel**.

### ex03 — Intern
- Classe `Intern` (ni nom ni grade) avec :
  ```cpp
  AForm *makeForm(std::string formName, std::string target);
  ```
- Retourne un `AForm *` du bon type selon le nom, et affiche `Intern creates <form>`. Si le nom est
  inconnu → message d'erreur + `NULL`.
- **Interdit** la cascade `if / else if / else`. Approche propre ici : un **tableau de noms** parcouru
  pour trouver l'index, puis `switch` sur l'index (alternative classique : tableau de pointeurs sur
  méthodes/factories).
- L'appelant est responsable du `delete` du form retourné (alloué avec `new`) → justifie le
  **destructeur virtuel** d'`AForm`.

Objectif : **factory pattern, design propre, gestion de la durée de vie via AForm***.

---

## 4. Checklist soutenance (les questions qui tombent)
- Pourquoi `catch` par référence ? → éviter copie + **slicing**.
- Que fait `throw()` violé ? → `std::terminate()` → **crash** (pas propre).
- Si un constructeur throw, le destructeur est-il appelé ? → **non**, mais les **membres déjà
  construits sont détruits** (pas de fuite).
- Qu'est-ce qui rend `AForm` abstraite ? → la méthode **pure virtuelle** (`= 0`).
- Pourquoi `~AForm()` virtuel ? → `delete` via `AForm*` sinon **UB / fuite**.
- Forward declaration vs include ? → forward suffit pour **pointeurs/références**, casse les
  **inclusions circulaires**.
- Sens des grades ? → **1 = haut, 150 = bas** ; `< 1` = TooHigh, `> 150` = TooLow.
