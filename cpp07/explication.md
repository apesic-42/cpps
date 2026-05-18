# CPP Module 07 — Explication detaillee du code
note perso : ce module est court mais il faut bien comprendre la mecanique des templates, c'est la base de la programmation generique en C++

## Vue d'ensemble du module

Le module 07 porte sur **les templates en C++**. Les templates permettent d'ecrire du code **generique** : une seule fois le code, et le compilateur genere automatiquement une version pour chaque type utilise. C'est le mecanisme qui fait tourner toute la STL (vector, map, etc.).

| Concept | Description |
|---------|-------------|
| Function template | Fonction dont le type est un parametre — le compilateur genere une version par type utilise |
| Class template | Classe dont les membres dependent d'un type parametre |
| Instanciation | Le moment ou le compilateur genere le code concret pour un type donne |
| Deduction | Le compilateur deduit `T` automatiquement a partir des arguments passes |

Chaque exercice monte en difficulte :
- ex00 → function templates simples (swap, min, max)
- ex01 → function template avec pointeur de fonction en parametre (iter)
- ex02 → class template complete avec gestion memoire (Array)

**Regle importante du sujet** : les templates doivent etre definis dans les headers (`.hpp`). C'est normal — le compilateur a besoin de voir le corps du template pour l'instancier. Pas de `.cpp` pour les templates.

---

# Exercice 00 — A few functions

## Objectif du sujet

Ecrire 3 function templates dans `whatever.hpp` :
- `swap` : echange les valeurs de deux arguments, ne retourne rien.
- `min` : compare deux arguments, retourne le plus petit. **Si egaux, retourne le second**.
- `max` : compare deux arguments, retourne le plus grand. **Si egaux, retourne le second**.

Les fonctions doivent marcher avec **n'importe quel type** qui supporte les operateurs de comparaison.

## Le header (whatever.hpp)

```cpp
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
T const &min(T const &a, T const &b)
{
    return (a < b) ? a : b;
}

template <typename T>
T const &max(T const &a, T const &b)
{
    return (a > b) ? a : b;
}

#endif
```

### Decomposition de `swap`

```cpp
template <typename T>
void swap(T &a, T &b)
```

- `template <typename T>` : declare un parametre de type `T`. Le compilateur remplacera `T` par le type reel a l'appel (int, string, etc.).
- Les parametres sont des **references** (`T &`) : on modifie directement les variables de l'appelant, pas des copies.
- L'algorithme classique en 3 etapes : sauvegarde dans `tmp`, ecrase `a` avec `b`, ecrase `b` avec `tmp`.

### Decomposition de `min` et `max`

```cpp
template <typename T>
T const &min(T const &a, T const &b)
{
    return (a < b) ? a : b;
}
```

- Les parametres sont des **const references** (`T const &`) : on ne copie pas, et on ne modifie pas les valeurs.
- Le retour est aussi une **const reference** : on retourne une reference vers l'un des deux arguments, pas une copie. C'est plus efficace (pas de copie d'un objet potentiellement lourd).
- **Condition `a < b`** (et pas `a <= b`) : c'est ce qui fait que quand `a == b`, la condition est fausse, et on retourne `b` (le second). C'est exactement ce que demande le sujet.
- Pour `max`, c'est `a > b` (et pas `a >= b`) pour la meme raison.

### Pourquoi `::swap`, `::min`, `::max` dans le main ?

```cpp
::swap(a, b);
::min(a, b);
```

Le `::` force la recherche dans le **namespace global**. Sans ca, le compilateur pourrait trouver `std::swap` ou `std::min` (qui existent dans `<algorithm>`) et il y aurait ambiguite. Le `::` dit explicitement "utilise MA fonction, pas celle de la STL".

### Deduction de type

Quand on ecrit `::swap(a, b)` avec `a` et `b` de type `int`, le compilateur **deduit** que `T = int` et genere :

```cpp
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
```

C'est l'**instanciation implicite** : on n'a pas besoin d'ecrire `::swap<int>(a, b)` (meme si on pourrait).

## Le main (main.cpp)

```cpp
int main(void)
{
    int a = 2;
    int b = 3;

    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
    std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
    std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

    return 0;
}
```

C'est le main **impose par le sujet**. Il teste les templates avec deux types differents :
- `int` : comparaison numerique classique.
- `std::string` : comparaison lexicographique (ordre alphabetique). `"chaine1" < "chaine2"` est vrai car le `1` est avant le `2` en ASCII.

**Sortie attendue :**
```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```

Apres `swap(a, b)`, a=3 et b=2. Donc `min(3, 2)` = 2 et `max(3, 2)` = 3.
Apres `swap(c, d)`, c="chaine2" et d="chaine1". Donc `min` retourne "chaine1" (plus petit en ordre alpha).

---

# Exercice 01 — Iter

## Objectif du sujet

Ecrire un function template `iter` qui prend 3 parametres :
1. L'adresse d'un tableau.
2. La longueur du tableau.
3. Une fonction appelee sur chaque element du tableau.

Le programme doit prouver que `iter` marche avec **n'importe quel type de tableau** et/ou avec un **function template instancie** comme 3e parametre.

## Le header (iter.hpp)

```cpp
#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T *array, size_t length, F func)
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

#endif
```

### Pourquoi deux parametres de type (`T` et `F`) ?

- `T` est le type des elements du tableau.
- `F` est le type de la fonction callback.

On pourrait ecrire `void (*func)(T &)` au lieu de `F func`, mais utiliser un parametre template `F` est **plus flexible** : ca accepte a la fois :
- Des pointeurs de fonction classiques (`void (*)(int &)`)
- Des function templates instancies (`print<int>`)
- Des foncteurs (objets avec `operator()`)

Le compilateur deduit `T` depuis le tableau et `F` depuis la fonction passee.

### Comment ca marche a la compilation

Quand on ecrit :
```cpp
int arr[] = {1, 2, 3};
::iter(arr, 3, print<int>);
```

Le compilateur :
1. Deduit `T = int` (depuis `arr` qui est un `int*`)
2. Deduit `F = void(*)(int const &)` (depuis `print<int>`)
3. Genere une version concrete de `iter` pour ces types

### Pourquoi `print<int>` et pas juste `print` ?

`print` est un template, pas une fonction. Le compilateur ne peut pas prendre l'adresse d'un template — il faut l'**instancier** d'abord en precisant le type : `print<int>`. C'est ce que le sujet appelle "an instantiated function template as a third parameter".

## Le main (main.cpp)

```cpp
template <typename T>
void print(T const &x)
{
    std::cout << x << std::endl;
}

void increment(int &x)
{
    x++;
}

void toUpper(std::string &s)
{
    for (size_t i = 0; i < s.length(); i++)
        s[i] = std::toupper(s[i]);
}
```

Trois fonctions de test :
- `print<T>` : function template qui affiche n'importe quel type. Demontre l'utilisation d'un template instancie comme callback.
- `increment` : fonction classique qui modifie l'element (prouve que `iter` peut modifier le tableau).
- `toUpper` : fonction specifique aux strings (prouve la versatilite).

Le main teste `iter` avec des `int[]`, `std::string[]`, et `double[]`, avec des callbacks variees (modification, affichage, template instancie).

---

# Exercice 02 — Array

## Objectif du sujet

Ecrire un **class template** `Array<T>` qui :
- Se construit vide (aucun element).
- Se construit avec `n` elements initialises par defaut.
- Supporte copie et assignation en **deep copy** (modifier la copie ne touche pas l'original).
- Utilise `new[]` pour l'allocation.
- Accede aux elements via `operator[]`, qui jette `std::exception` si l'index est hors limites.
- A une methode `size()` qui retourne le nombre d'elements.

## Le header (Array.hpp)

```cpp
template <typename T>
class Array
{
    private:
        T               *_array;
        unsigned int    _size;

    public:
        Array(void) : _array(NULL), _size(0) {}
        Array(unsigned int n) : _array(new T[n]()), _size(n) {}
        Array(Array const &src) : _array(NULL), _size(0) { *this = src; }
        ~Array(void) { delete[] _array; }

        Array &operator=(Array const &rhs);
        T &operator[](unsigned int index);
        T const &operator[](unsigned int index) const;
        unsigned int size(void) const;
};
```

### Les membres prives

```cpp
T               *_array;    // pointeur vers le tableau alloue dynamiquement
unsigned int    _size;      // nombre d'elements
```

C'est le minimum : un pointeur brut + la taille. Pas de capacite supplementaire (pas de "preventive allocation" comme dit le sujet).

### Le constructeur par defaut

```cpp
Array(void) : _array(NULL), _size(0) {}
```

Cree un tableau vide. `_array` est `NULL`, `_size` est 0. Le destructeur fera `delete[] NULL` ce qui est garanti safe par le standard C++.

### Le constructeur parametre

```cpp
Array(unsigned int n) : _array(new T[n]()), _size(n) {}
```

**Le detail crucial ici est les parentheses `()`** dans `new T[n]()`. C'est la **value-initialization** :
- Pour les types primitifs (int, float, etc.), ca met a **zero**. Sans les `()`, les valeurs seraient non-initialisees (garbage).
- Pour les objets (string, etc.), ca appelle le constructeur par defaut.

C'est le tip du sujet : "try to compile `int * a = new int();`, then display `*a`" — la valeur sera 0.

### Le constructeur de copie

```cpp
Array(Array const &src) : _array(NULL), _size(0)
{
    *this = src;
}
```

Initialise `_array` a `NULL` et `_size` a 0, puis delegue a `operator=`. C'est important d'initialiser `_array` a `NULL` **avant** d'appeler `operator=`, parce que celui-ci fait `delete[] _array` en premier — si `_array` n'etait pas initialise, ce serait du undefined behavior.

### L'operator= (deep copy)

```cpp
Array &operator=(Array const &rhs)
{
    if (this != &rhs)
    {
        delete[] _array;
        _size = rhs._size;
        _array = new T[_size]();
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = rhs._array[i];
    }
    return *this;
}
```

**Etapes** :
1. **Self-assignment check** (`this != &rhs`) : si on fait `a = a`, on ne veut pas detruire nos propres donnees.
2. **Libere l'ancien tableau** : `delete[] _array`.
3. **Alloue un nouveau tableau** de la meme taille.
4. **Copie element par element** : chaque `_array[i] = rhs._array[i]` utilise l'`operator=` du type `T`. Pour un `int`, c'est une simple copie. Pour un `std::string`, c'est une copie profonde de la chaine.
5. **Retourne `*this`** pour permettre le chainage (`a = b = c`).

C'est une **deep copy** : les deux tableaux sont completement independants apres l'assignation. Modifier l'un ne touche pas l'autre.

### L'operator[] (acces aux elements)

```cpp
T &operator[](unsigned int index)
{
    if (index >= _size)
        throw std::out_of_range("Array index out of bounds");
    return _array[index];
}

T const &operator[](unsigned int index) const
{
    if (index >= _size)
        throw std::out_of_range("Array index out of bounds");
    return _array[index];
}
```

Deux versions :
- **Non-const** : retourne une reference modifiable (`T &`). Permet `arr[0] = 42`.
- **Const** : retourne une reference en lecture seule (`T const &`). Utilisee quand l'Array est const.

Les deux jettent `std::out_of_range` (qui herite de `std::exception`, comme demande par le sujet) si l'index est hors limites. Le type `unsigned int` garantit qu'on ne peut pas passer un index negatif.

### La methode `size()`

```cpp
unsigned int size(void) const
{
    return _size;
}
```

Simple getter. Le `const` a la fin garantit qu'on peut appeler `size()` sur un Array const, et que la methode ne modifie pas l'objet.

### Le destructeur

```cpp
~Array(void)
{
    delete[] _array;
}
```

Libere le tableau. `delete[]` appelle le destructeur de chaque element `T`, puis libere la memoire. Si `_array` est `NULL` (Array vide), c'est un no-op.

## Le main (main.cpp)

Le main teste tous les cas requis par le sujet :

1. **Construction vide** : `Array<int> empty;` — verifie que `size()` retourne 0.
2. **Construction avec taille** : `Array<int> intArr(5);` — verifie les valeurs par defaut (0 pour int).
3. **Deep copy (constructeur)** : modifie `copy[0]`, verifie que `intArr[0]` n'a pas change.
4. **Deep copy (assignation)** : modifie `assigned[1]`, verifie que `intArr[1]` n'a pas change.
5. **Out of bounds** : `intArr[42]` jette une exception.
6. **Autre type** : `Array<std::string>` — prouve que le template marche avec des strings.
7. **Init par defaut** : `Array<int> zeros(3)` — verifie que les int sont bien a 0.

---

# Pourquoi les templates doivent etre dans les headers ?

En C++ classique, on separe declaration (`.hpp`) et implementation (`.cpp`). Mais avec les templates, **le compilateur a besoin de voir le corps de la fonction/classe au moment de l'instanciation**.

Quand `main.cpp` ecrit `Array<int> arr(5)`, le compilateur doit generer le code concret pour `Array<int>`. S'il ne voit que la declaration (dans le `.hpp`) sans le corps (dans un `.cpp` separe), il ne peut rien generer → erreur de linkage.

C'est pour ca que le sujet dit "Any function implemented in a header (except in the case of templates)" — les templates sont l'exception a la regle "pas d'implementation dans les headers".

---

# Resume

| Ex | Sujet | Concept template | Difficulte |
|----|-------|-----------------|------------|
| 00 | swap/min/max | Function templates basiques, deduction de type | Simple |
| 01 | iter | Function template avec callback template, double parametre de type | Moyen |
| 02 | Array | Class template complete, orthodox canonical form, gestion memoire | Avance |

Le fil rouge du module : on va du plus simple (3 fonctions d'une ligne) au plus complexe (une classe avec allocation dynamique, deep copy, et bounds checking), en restant toujours dans la **programmation generique** — le meme code marche pour n'importe quel type.
