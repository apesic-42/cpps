# CPP Module 06 — Explication détaillée du code
note perso : ce sujet est tres dure et tres chiant, le code a plein de subtiliter donc revise le 

## Vue d'ensemble du module

Le module 06 porte sur **les casts en C++**. En C, on n'a qu'un seul cast `(type)valeur` qui fait à peu près n'importe quoi sans aucune vérification. C++ introduit **4 casts spécialisés**, chacun avec un rôle précis :

| Cast | Usage | Vérification |
|------|-------|--------------|
| `static_cast<T>` | Conversions « logiques » entre types liés (numériques, hiérarchies, void*) | Compile-time |
| `dynamic_cast<T>` | Downcast sûr dans une hiérarchie polymorphique (avec RTTI) | Runtime |
| `reinterpret_cast<T>` | Réinterpréter les bits bruts (pointeur ↔ entier, pointeurs incompatibles) | Aucune — dangereux |
| `const_cast<T>` | Ajouter/retirer `const` ou `volatile` | Compile-time |

Chaque exercice cible **un cast précis** :
- ex00 → `static_cast`
- ex01 → `reinterpret_cast`
- ex02 → `dynamic_cast`

(`const_cast` n'est pas couvert dans ce module.)

---

# Exercice 00 — Scalar conversion

## Objectif du sujet

Écrire un programme `./convert <literal>` qui :
1. Prend une chaîne en argument (`"42"`, `"4.2f"`, `"a"`, `"nan"`…).
2. Détecte automatiquement à quel type scalaire elle correspond : `char`, `int`, `float` ou `double`.
3. La parse en ce type natif.
4. Convertit explicitement vers les **3 autres types**.
5. Affiche les 4 valeurs avec un formatage précis. Si une conversion est impossible (overflow, NaN→int…) ou non-affichable (char invisible), affiche `impossible` ou `Non displayable`.

Il faut aussi accepter les pseudo-literals `nan`, `nanf`, `inf`, `inff`, `-inf`, `+inf`, `-inff`, `+inff`.

## Architecture choisie

Le code définit une classe `ScalarConverter` (déclarée dans `ScalarConverter.hpp`, implémentée dans `ScalarConverter.cpp`). Cette classe **n'est pas instanciable** par l'utilisateur (constructeur/copie/destructeur/opérateur= en `private`). Elle expose une seule méthode **statique** `convert(std::string const &value)` qui fait tout le travail.

En interne, la fonction `convert` utilise une fonction statique locale `detectType()` qui joue le rôle de parseur. Les variables locales à `convert` servent de *tagged union* : un `int type` joue le rôle de tag, et des variables `ivalue`, `fvalue`, `dvalue`, `cvalue` stockent la valeur parsée.

### L'enum `Type` (ScalarConverter.cpp)

```cpp
enum Type {
    TypeChar,      // 0
    TypeInt,       // 1
    TypeFloat,     // 2
    TypeDouble,    // 3
    TypeLong,      // 4   (déclaré mais inutilisé)
    BadType    // 5
};
```

C'est juste un ensemble d'étiquettes symboliques. Les valeurs numériques (0, 1, 2…) servent aussi d'**index dans `status[4]`** : `status[TypeChar]` = flags pour char, `status[TypeInt]` = flags pour int, etc.

### Les flags (dans convert())

```cpp
static const int notPossible    = 0x00000001;
static const int notDisplayable = 0x00000010;
```

Ce sont des bitmasks (chaque flag est sur un bit différent). On peut combiner les flags sur un même `int` avec `|`, et tester avec `&`.

## La méthode statique `convert()` (ScalarConverter.cpp)

La méthode `ScalarConverter::convert()` orchestre tout le travail :
1. Déclare les variables locales (`ivalue`, `fvalue`, `dvalue`, `cvalue`, `status[4]`).
2. Appelle `detectType()` qui parse la chaîne, remplit la bonne variable, et retourne le type détecté.
3. **Si le parsing a réussi** (`type != BadType`) : convertit via `static_cast` vers les 3 autres types, puis vérifie les flags char (plage ASCII `[0, 127]` + `isprint`).
4. **Si le parsing a échoué** : tout est marqué impossible.
5. Affiche les 4 valeurs avec le formatage attendu par le sujet.

## La fonction `detectType()` (ScalarConverter.cpp)

C'est le cœur du parsing. C'est une fonction statique locale (pas une méthode de classe). Elle fait **trois choses en parallèle** pendant qu'elle scanne la chaîne caractère par caractère :
1. Détermine le type (retourné comme `int`).
2. Accumule les caractères valides dans un `std::stringstream ss`.
3. À la fin, extrait `ss` vers la bonne variable passée par référence (`ivalue`, `fvalue` ou `dvalue`).

### Cas 1 : char isolé (lignes 47-52)

```cpp
if (length == 1 && !std::isdigit(str[0]))
{
    type = TypeChar;
    cvalue = str[0];
    return ;
}
```

Si la chaîne fait **un seul caractère ET n'est pas un chiffre**, c'est un char.

### Cas 2 : signe initial (lignes 53-54)

```cpp
if (str[0] == '+' || str[0] == '-')
    ss << str[i++];
```

Si le premier caractère est `+` ou `-`, on le copie dans le stream et on avance d'une position. Ça gère les nombres négatifs comme `"-42"` ou les flottants signés `"+4.2f"`.

### Cas 3 : la boucle principale (lignes 55-81)

```cpp
type = TypeInt;       // hypothèse de départ
for ( ; i < length; i++)
{
    if (str[i] == '.' && type != TypeDouble)
    {
        type = TypeDouble;
        ss << str[i];
    }
    else if (str[i] == 'e' && i < length - 1
        && (str[i + 1] == '-'
            || str[i + 1] == '+'
            || std::isdigit(str[i + 1])))
    {
        ss << str[i] << str[i + 1];
        i++;
        type = TypeDouble;
    }
    else if (str[i] == 'f' && i == length - 1 && type == TypeDouble)
        type = TypeFloat;
    else if (!std::isdigit(str[i]))
    {
        type = BadType;
        i = length;     // sort de la boucle
    }
    else
        ss << str[i];
}
```

On démarre avec l'hypothèse `TypeInt`, puis on monte en type si on trouve des marqueurs spéciaux :

- **`.`** → promotion en `TypeDouble`. La condition `type != TypeDouble` empêche un double point comme `"1.2.3"` de passer (au deuxième `.`, on est déjà en `TypeDouble` donc on tombe dans `!isdigit` → `BadType`).
- **`e`** → notation scientifique. On vérifie qu'il reste au moins un caractère après (`i < length - 1`), et que ce caractère est un signe ou un chiffre. On pousse `e` ET le caractère suivant dans le stream d'un coup, et on saute (`i++`) pour ne pas re-traiter le signe à l'itération suivante. Promotion en `TypeDouble`.
- **`f` en toute fin de chaîne, et seulement si on est déjà en `TypeDouble`** → rétrograde en `TypeFloat`. Le `f` n'est **pas** ajouté au stream parce que `stringstream` ne sait pas le lire.
- **Autre non-chiffre** → invalide, sort immédiatement de la boucle.
- **Chiffre** → on l'empile dans le stream.

À la sortie de la boucle, le stream `ss` contient une version « nettoyée » du nombre (chiffres + signe + `.` + `e<sign>`), et `type` indique quoi en faire.

### Cas 4 : extraction finale (lignes 82-95)

```cpp
if (type == TypeFloat)
    ss >> fvalue;
else if (type == TypeDouble)
    ss >> dvalue;
else if (type == TypeInt)
{
    long lvalue;
    ss >> lvalue;
    ivalue = lvalue;
    if (ss.fail()
        || lvalue > std::numeric_limits<int>::max()
        || lvalue < std::numeric_limits<int>::min())
        type = BadType;
}
```

On lit le stream dans le bon membre. Pour les entiers, on lit d'abord en `long` (plus large que `int`) pour pouvoir **détecter un overflow** : si la valeur dépasse les bornes d'un `int`, on bascule en `BadType`. C'est ce qui permet à `./convert 99999999999` de répondre `impossible` au lieu de retourner une valeur tronquée.

### Cas 5 : pseudo-literals (lignes 96-110)

```cpp
else if (type == BadType)
{
    if (str == "inff" || str == "-inff" || str == "+inff"
        || str == "nanf")
    {
        fvalue = atof(str.c_str());
        type = TypeFloat;
    }
    else if (str == "inf" || str == "-inf" || str == "+inf"
            || str == "nan")
    {
        dvalue = atof(str.c_str());
        type = TypeDouble;
    }
}
```

Filet de rattrapage pour les valeurs spéciales IEEE 754 que le parseur principal ne sait pas reconnaître (il s'attend à des chiffres). On compare la chaîne brute aux valeurs autorisées par le sujet et on utilise `atof()` — la fonction C de `<cstdlib>` — qui, elle, **sait reconnaître `"inf"` et `"nan"`**. Le `f` final de `nanf`/`inff` est ignoré par `atof` (il s'arrête au premier caractère qu'il ne comprend pas), mais ça n'a aucune importance puisque la valeur sémantique reste la même.

Une fois extrait, on **promeut** `type` de `BadType` à `TypeFloat` ou `TypeDouble`, pour que le reste de la machinerie (convert + affichage) prenne le relais normalement.

## Les conversions dans `convert()`

Après le parsing, un `switch` sur le type détecté convertit la valeur source vers les 3 autres types via `static_cast` :

```cpp
case TypeFloat:
    ivalue = static_cast<int>(fvalue);
    dvalue = static_cast<double>(fvalue);
    cvalue = static_cast<char>(fvalue);
    if (std::isnan(fvalue) || std::isinf(fvalue)
        || fvalue > std::numeric_limits<int>::max()
        || fvalue < std::numeric_limits<int>::min())
        status[TypeInt] |= notPossible;
    break;
```

**C'est ici qu'on utilise `static_cast`**, le cast cible de cet exercice. Les conversions entre types numériques sont des conversions « logiques » bien définies par le langage, et `static_cast` est l'outil approprié (par opposition à un `(int)fvalue` à la C, sans vérification).

Le test final lève le flag `notPossible` sur `TypeInt` quand :
- La valeur source n'est pas finie (NaN ou inf), ou
- La valeur dépasse la plage d'un `int`.

## L'affichage (dans convert())

L'affichage est fait directement à la fin de `convert()` via `std::cout`. Pour chaque type cible, on vérifie le flag correspondant et on affiche soit la valeur, soit `impossible` / `Non displayable`.

Astuce d'affichage pour float/double : quand on affiche `42.0f` avec `cout`, le `.0` se perd (la sortie devient `42f`). On rajoute `.0` manuellement si le point décimal n'apparaît pas dans la chaîne formatée, **et seulement si la valeur est finie** (sinon on aurait `nan.0` ou `inf.0`).

## Le `main` (main.cpp)

```cpp
int main(int argc, char const *argv[])
{
    if (argc != 2)
        std::cout << "convert: bad arguments!" << std::endl;
    else
        ScalarConverter::convert(argv[1]);
    return (0);
}
```

Minimal : vérifie qu'il y a exactement un argument, appelle la méthode statique `convert`. Tout le travail est fait dans la classe, sans jamais l'instancier.

## Pourquoi `static_cast` est le bon choix ici

Les conversions char↔int↔float↔double sont des **conversions arithmétiques standard** : le langage sait exactement ce qu'elles signifient. `static_cast` :
- Refuserait des conversions absurdes (genre `static_cast<int>(une string)`),
- Est explicite (le lecteur du code voit qu'il y a conversion intentionnelle),
- Évite les pièges du cast C (qui peut accidentellement faire un `reinterpret_cast` ou un `const_cast` selon le contexte).

---

# Exercice 01 — Serialization

## Objectif du sujet

Implémenter une classe `Serializer` **non instanciable** avec deux méthodes **statiques** :
- `static uintptr_t serialize(Data* ptr)` : transforme un pointeur en entier.
- `static Data* deserialize(uintptr_t raw)` : retransforme l'entier en pointeur.

Le programme doit prouver qu'on retombe sur le pointeur d'origine : créer un `Data`, sérialiser, désérialiser, vérifier que le pointeur final est égal au pointeur d'origine.

## Le struct `Data` (Data.hpp)

```cpp
#pragma once
#include <string>

typedef struct s_Data
{
    std::string data;
} Data;
```

Structure minimale avec un seul champ string. Le `pragma once` empêche l'inclusion multiple. Le `typedef struct` fait que Data est un alias créé avec typedef.

## La classe `Serializer` (Serializer.hpp / Serializer.cpp)

La classe a ses constructeur/copie/destructeur/opérateur= en **private** pour empêcher l'instanciation. Les deux méthodes statiques :

```cpp
uintptr_t Serializer::serialize(Data *ptr)
{
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw)
{
    return (reinterpret_cast<Data *>(raw));
}
```

**Une seule ligne chacune.** C'est l'usage canonique de `reinterpret_cast` : il prend les **bits bruts** d'une chose et les présente comme un autre type, sans aucune conversion de valeur.

### Qu'est-ce que `uintptr_t` ?

C'est un type entier non-signé (de `<stdint.h>` / `<cstdint>`) **garanti assez grand pour stocker un pointeur**. Sur un système 64 bits, c'est typiquement un `unsigned long` 64 bits ; sur un 32 bits, un `unsigned int` 32 bits. Le standard garantit que `reinterpret_cast<uintptr_t>(ptr)` puis `reinterpret_cast<Data*>(value)` retombe sur **exactement le même pointeur**.

### Pourquoi `reinterpret_cast` et pas autre chose ?

- `static_cast<uintptr_t>(ptr)` **ne compile pas** : `static_cast` refuse les conversions entre types non liés. Un pointeur et un entier n'ont aucune relation de type.
- `(uintptr_t)ptr` en style C compilerait, mais c'est précisément ce qu'on veut éviter en C++.
- `reinterpret_cast` dit explicitement : « je sais que je fais une conversion bas niveau, je prends la responsabilité ».

## Le `main` (main.cpp)

```cpp
int main()
{
    Data        *ptr;
    Data        *new_ptr;
    uintptr_t   raw;

    ptr = new Data;
    ptr->data = "Fake Data!";

    raw = Serializer::serialize(ptr);
    new_ptr = Serializer::deserialize(raw);

    std::cout << "Data of ptr: " << ptr->data << std::endl;
    std::cout << "Data of new_ptr: " << new_ptr->data << std::endl;

    if (ptr == new_ptr)
        std::cout << "Pointers are equal!" << std::endl;

    delete ptr;
}
```

**Démonstration en 5 étapes** :
1. Crée un `Data` sur le tas avec un message connu.
2. Sérialise via `Serializer::serialize()` : récupère la valeur entière du pointeur.
3. Désérialise via `Serializer::deserialize()` : reconstruit un pointeur depuis cet entier.
4. Affiche les deux contenus — si la sérialisation est correcte, ils sont identiques.
5. Vérifie que les deux pointeurs sont bien égaux.

Note importante : `ptr` et `new_ptr` pointent vers la **même zone mémoire**, ce ne sont pas deux copies. C'est pour ça qu'on ne `delete` que `ptr` — faire `delete new_ptr` aussi serait un double-free (UB).

## Cas d'usage réel

Pourquoi on ferait ça dans la vraie vie ? Quelques scénarios :
- **Stocker un pointeur dans un type qui n'accepte que des entiers** (callbacks d'API C qui prennent un `void*` ou un `long` comme user data).
- **Passer un pointeur à travers une frontière qui efface les types** (handles opaques).
- **Hash de pointeurs** : utiliser l'adresse comme clé dans une table de hachage.

Dans ces cas, `reinterpret_cast` aller-retour est garanti par la norme C++. Mais c'est une opération à utiliser avec **précaution** : aucune vérification, aucun filet de sécurité.

---

# Exercice 02 — Identify real type

## Objectif du sujet

1. Créer une classe `Base` avec un destructeur virtuel public.
2. Créer trois classes vides `A`, `B`, `C` qui héritent publiquement de `Base`.
3. Écrire `Base* generate(void)` qui retourne aléatoirement un `A`, `B` ou `C` typé comme `Base*`.
4. Écrire `void identify(Base* p)` qui affiche `"A"`, `"B"` ou `"C"` selon le vrai type runtime.
5. Écrire `void identify(Base& p)` qui fait pareil **sans utiliser de pointeur** dans le corps.

`<typeinfo>` (et donc `typeid`) est **interdit**. Il faut donc utiliser `dynamic_cast`.

## La hiérarchie de classes

### Base.hpp / Base.cpp

```cpp
class Base {
    public:
        virtual ~Base(void);
};

Base::~Base(void) {}
```

Une classe avec **un destructeur virtuel** et rien d'autre. Pourquoi virtuel ?

1. **C'est ce qui rend la classe polymorphique** — c'est-à-dire qui force le compilateur à générer la *vtable* (table des fonctions virtuelles) et donc l'information RTTI (Run-Time Type Information). **Sans au moins une méthode virtuelle, `dynamic_cast` ne peut pas fonctionner**, le code ne compilerait même pas.
2. C'est aussi nécessaire pour pouvoir `delete base;` (où `base` est `Base*` mais pointe vers `A`/`B`/`C`) sans leak. Sinon seul `~Base()` serait appelé, et si `A` avait des ressources, elles ne seraient pas libérées.

### A.hpp / A.cpp (B et C sont identiques)

```cpp
class A : public Base {
    public:
        A(void);
        A(const A& other);
        ~A(void);
        A& operator=(const A&);
};

A::A(void) {}
A::A(const A& other) { *this = other; }
A::~A(void) {}
A& A::operator=(const A&) { return (*this); }
```

Classes vides (pas de données) mais avec l'orthodox canonical form (4 fonctions de base) par habitude — pas strictement nécessaire ici puisqu'il n'y a aucun état à gérer, mais c'est ce qu'on apprend en cpp04/cpp05.

L'héritage est **public** comme demandé par le sujet : sans ça, `dynamic_cast<A*>(base_ptr)` ne pourrait pas retrouver l'objet `A` depuis un pointeur `Base*`.

## La fonction `generate()` (main.cpp:10-23)

```cpp
Base *generate(void)
{
    int random;

    random = rand() % 3;
    if (random == 0)
        return (new A);
    if (random == 1)
        return (new B);
    if (random == 2)
        return (new C);
    else
        return (NULL);
}
```

Tire un nombre dans `[0, 2]` et retourne un nouvel objet du type correspondant. Le retour est typé `Base*`, donc **du point de vue du code appelant, on ne sait pas** quel type concret est en face — c'est exactement le problème que les `identify` doivent résoudre.

Le `else return NULL` est inatteignable (vu que `rand() % 3` ne peut donner que 0, 1 ou 2) mais évite un warning sur certains compilateurs.

`srand(time(NULL))` est appelé dans `main` pour avoir des tirages différents à chaque exécution.

## La fonction `identify(Base* p)` (main.cpp:25-33)

```cpp
void identify(Base *p)
{
    if (dynamic_cast<A* >(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B* >(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C* >(p))
        std::cout << "C" << std::endl;
}
```

**Le principe de `dynamic_cast` sur pointeurs** : il essaie de convertir le pointeur `Base*` en pointeur dérivé (`A*`, `B*`, `C*`). Si l'objet pointé est vraiment du type demandé, il retourne un pointeur non-nul. Sinon, il retourne **`NULL`** (pas d'exception).

On chaîne donc trois `if` qui testent chaque type possible. Le `if (pointer)` exploite la conversion implicite pointeur → bool : `NULL` est faux, n'importe quel autre pointeur est vrai.

**C'est `dynamic_cast` qui consulte la vtable à l'exécution** pour déterminer le vrai type — c'est pour ça qu'on a eu besoin du destructeur virtuel dans `Base`.

## La fonction `identify(Base& p)` (main.cpp:35-58)

```cpp
void identify(Base &p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return ;
    }
    catch(std::exception& e) {}
    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return ;
    }
    catch(std::exception& e) {}
    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return ;
    }
    catch(std::exception& e) {}
}
```

**La grosse différence avec la version pointeur** : `dynamic_cast` sur **références** ne peut pas retourner un « pointeur nul » (une référence ne peut pas être nulle par définition). À la place, **il lève une exception `std::bad_cast`** quand la conversion échoue.

D'où le pattern :
- On essaie le cast dans un `try`.
- Si ça réussit, on affiche et on `return`.
- Si ça échoue, le `catch` attrape l'exception silencieusement et on passe au type suivant.

Le `(void)dynamic_cast<A&>(p)` jette explicitement le résultat — on n'a pas besoin de la référence convertie, on veut juste **savoir si la conversion réussit ou pas**. Le `(void)` rend cette intention claire et évite tout warning sur une valeur ignorée.

Le `return` après chaque affichage est important : sans lui, si le vrai type est `A`, on essaierait ensuite de caster en `B&` (qui jetterait), gaspillant deux exceptions inutiles.

## Le `main` (main.cpp:60-)

```cpp
int main()
{
    Base *base;

    srand(time(NULL));
    std::cout << "Identifying with pointers\n" << std::endl;

    base = generate();
    identify(base);     // version pointeur
    delete base;
    // ... 4 autres fois ...

    std::cout << "\nIdentifying with references\n" << std::endl;

    base = generate();
    identify(*base);    // version référence (déréférencement explicite)
    delete base;
    // ... 4 autres fois ...
}
```

Génère 10 instances : 5 testées via la surcharge pointeur, 5 via la surcharge référence. La surcharge est résolue à la compilation par C++ selon le type de l'argument (`Base*` vs `Base&`).

## Pourquoi `dynamic_cast` est le seul choix valide ici

- `static_cast<A*>(base_ptr)` **compile** (parce que A hérite de Base), mais **ne vérifie rien à l'exécution** — il ferait aveuglément la conversion même si l'objet est en réalité un `B`, donnant du *undefined behavior*. C'est pour ça qu'on appelle ça un « downcast non sûr ».
- `reinterpret_cast` ferait pareil mais en pire (aucune vérification de la hiérarchie non plus).
- `dynamic_cast` est le **seul cast qui interroge le RTTI à l'exécution** pour répondre à la question « cet objet est-il vraiment un A ? ». C'est exactement ce dont on a besoin.

Le coût : `dynamic_cast` n'est pas gratuit (consultation de la vtable, parfois plusieurs niveaux d'héritage à remonter). Dans du code performance-critical, on essaie de l'éviter en architecturant différemment (visitor pattern, méthode virtuelle qui retourne un type ID…). Mais pour de l'identification ad-hoc, c'est l'outil idiomatique.

---

# Résumé des correspondances cast ↔ exercice

| Ex | Sujet | Cast utilisé | Pourquoi |
|----|-------|--------------|----------|
| 00 | Scalar conversion | `static_cast` | Conversions arithmétiques bien définies entre types numériques liés. |
| 01 | Serialization | `reinterpret_cast` | Réinterprétation des bits bruts d'un pointeur en entier — types non reliés. |
| 02 | Identify real type | `dynamic_cast` | Downcast sûr dans une hiérarchie polymorphique, avec vérification runtime. |

Et le quatrième cast, `const_cast`, n'apparaît pas dans ce module — il est plus rarement utile et concerne uniquement la gestion du qualificateur `const`.
