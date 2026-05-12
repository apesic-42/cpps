

# le but global : le module cpp05 introduit les *exceptions* (try/catch) et *classe d'exception personnaliser* et l'heritage
  - exeption : meme chose qu'en python : try/except/raise. En C++ c'est try/catch/throw, même logique :
  ```
  try {
      if (age < 0)
          throw std::invalid_argument("age négatif");
  }
  catch (const std::invalid_argument& e) {
      std::cerr << "Erreur : " << e.what() << std::endl;
  }
  catch (const std::exception& e) {
      std::cerr << "Autre erreur : " << e.what() << std::endl;
  }
  ```

  
  - classe d'exeption personnaliser : c'est un classe de type erreur. Pour la faire il faut hériter de std::exception et redéfinir what(). Dans ce sujet on imbrique la classe erreur dans la classe principale (voir ex00/Bureaucrat.hpp l 41)

  - heritage, avec "virtual", "protected", les truc de base :
    - virtual est obligatoire pour avoir du polymorphisme. En Python toutes les méthodes sont "virtuelles" par défaut. En C++, sans virtual, l'appel est résolu à la compilation selon le type statique, pas le type réel de l'objet.
    (Ajoute virtual et l'appel devient dynamique (résolu à l'exécution) alors que sinon on va chercher la valeur de la compilation)
    - = 0 rend la méthode pure virtuelle (la focntion = 0, donc pour l'utiliser on est obliger de la redefinir dans la fille), ce qui rend la classe abstraite (équivalent de ABC + @abstractmethod en Python). Le A dans AForm est la convention 42 pour signaler une classe abstraite.
    - protected = accessible par les classes filles mais pas de l'extérieur (Python a juste la convention _attribut).


# les exercices : 

### ex00 — Bureaucrat  
Créer une classe `Bureaucrat` avec :
- Un `name` constant
- Un `grade` entre **1 (le plus haut)** et **150 (le plus bas)**
- Deux exceptions internes : `GradeTooHighException` et `GradeTooLowException`, lancées si le grade sort des bornes (constructeur, increment, decrement)
- Getters `getName()`, `getGrade()`
- Surcharge de `operator<<` : `<name>, bureaucrat grade <grade>.`

Objectif pédagogique : **les exceptions C++** (try/catch, héritage de `std::exception`).

#### le code :
le code est bien, j'ai pas beacoup modifier, le main a 3 test (nombre non preciser dans le sujet)
n'oublion pas que 
Bureaucrat Sleeper1("Bernd", 1500) ; = Bureaucrat Sleeper1 = Bureaucrat("Bernd", 1500); 

### ex01 — Form
Ajouter une classe `Form` avec attributs **privés** :
- `name` constant, `signed` (bool, faux à la construction)
- `gradeToSign` constant, `gradeToExecute` constant
- Mêmes exceptions de grade (`Form::GradeTooHighException`, `Form::GradeTooLowException`)
- `beSigned(Bureaucrat const&)` : passe le formulaire à signé si le grade du bureaucrate est suffisant, sinon throw
- `Bureaucrat::signForm()` : utilise `beSigned` et affiche le résultat (succès ou échec avec raison)

Objectif : **interactions entre classes via exceptions**, encapsulation stricte.

### ex02 — AForm + classes concrètes
- Renommer `Form` en `AForm` et la rendre **abstraite** (classe de base)
- Créer 3 classes concrètes :
  - `ShrubberyCreationForm` (sign 145 / exec 137) : crée un fichier `<target>_shrubbery` avec des arbres ASCII
  - `RobotomyRequestForm` (sign 72 / exec 45) : bruit de perceuse, 50% de réussite aléatoire
  - `PresidentialPardonForm` (sign 25 / exec 5) : message de pardon par Zaphod Beeblebrox
- Méthode `execute(Bureaucrat const & executor) const` dans la base : vérifie que le formulaire est signé et que le grade est suffisant, sinon throw
- `Bureaucrat::executeForm(AForm const&)`

Objectif : **héritage, classe abstraite, polymorphisme**.

### ex03 — Intern
Créer la classe `Intern` avec une méthode :
```cpp
AForm* makeForm(std::string formName, std::string target);
```
Elle retourne un pointeur vers le bon type de formulaire selon le nom. **Interdit** d'utiliser une cascade `if/else if/else` — il faut une approche élégante (typiquement un tableau de pointeurs sur fonctions ou de `std::string` indexant des factories).

Objectif : **factory pattern, design propre**.
