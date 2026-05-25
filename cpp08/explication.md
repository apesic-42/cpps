# CPP Module 08 — Explication detaillee du code
note perso : ce module introduit enfin la STL (containers, iterators, algorithms). Tout ce qu'on a appris avant (templates, orthodox canonical form) est utilise ici avec les outils standard du C++.

## Vue d'ensemble du module

Le module 08 porte sur **les conteneurs templates de la STL, les iterateurs et les algorithmes**. C'est le premier module ou l'utilisation de la STL est autorisee (et meme obligatoire). Le but est d'apprendre a utiliser les outils que le C++ fournit nativement pour manipuler des collections de donnees.

| Concept | Description |
|---------|-------------|
| Conteneur STL | Structure de donnees template fournie par le standard (vector, list, stack, deque, etc.) |
| Iterateur | Objet qui pointe vers un element d'un conteneur et permet de le parcourir — c'est le "pont" entre conteneurs et algorithmes |
| Algorithme STL | Fonction template qui opere sur des plages d'iterateurs (find, sort, min_element, etc.) |
| Adaptateur de conteneur | Conteneur qui en encapsule un autre et limite son interface (stack, queue, priority_queue) |

Chaque exercice monte en difficulte :
- ex00 → utiliser `std::find` sur un conteneur generique (function template + algorithme STL)
- ex01 → creer une classe qui encapsule un `std::vector` et utilise des algorithmes STL (sort, adjacent_difference, min/max_element)
- ex02 → heriter de `std::stack` pour lui ajouter des iterateurs (comprendre les adaptateurs de conteneur)

**Regle importante du sujet** : il faut utiliser au maximum les conteneurs et algorithmes standards. Reimplementer a la main ce que la STL fournit deja serait penalise.

---

# Exercice 00 — Easy find

## Objectif du sujet

Ecrire un function template `easyfind`, template sur un type `T`, qui prend :
1. Un conteneur `T` (qui contient des `int`)
2. Un `int` a chercher

La fonction doit trouver la **premiere occurrence** du second parametre dans le conteneur. Si l'element n'est pas trouve, il faut gerer l'erreur (exception ou valeur de retour d'erreur).

## Le header (easyfind.hpp)

```cpp
#ifndef EASYFIND_H
# define EASYFIND_H

# include <algorithm>

template<typename T>
typename T::iterator    easyfind(T &elems, int el)
{
    return std::find(elems.begin(), elems.end(), el);
}

#endif
```

### Pourquoi `typename T::iterator` ?

- `T::iterator` est un **type dependant** : il depend du parametre template `T`. En C++, le compilateur ne sait pas si `T::iterator` est un type ou une variable membre. Le mot-cle `typename` lui dit explicitement "c'est un type".
- Sans `typename`, le compilateur refuse de compiler. C'est une regle fondamentale des templates en C++.

### Pourquoi tout mettre dans le header ?

Les templates doivent etre visibles au moment de l'instanciation. Ici, la declaration et l'implementation sont directement dans le `.hpp`. C'est l'approche la plus simple — une alternative serait de separer l'implementation dans un fichier `.tpp` inclus a la fin du header (comme en cpp07), mais ici tout est regroupe dans un seul fichier.

### `std::find` — l'algorithme central

`std::find` est un algorithme STL defini dans `<algorithm>`. Il prend :
1. Un iterateur de debut (`elems.begin()`)
2. Un iterateur de fin (`elems.end()`)
3. La valeur a chercher (`el`)

Il parcourt la plage `[begin, end)` element par element et retourne un iterateur vers le premier element egal a `el`. Si aucun element n'est trouve, il retourne `end()`.

C'est exactement le pattern standard : on compare le retour a `end()` pour savoir si l'element a ete trouve. C'est comme ca que tous les algorithmes de recherche STL fonctionnent.

### Pourquoi retourner un iterateur plutot que jeter une exception ?

Le sujet dit "handle the error either using an exception or using an error return value. Take ideas from how standard containers work." Les conteneurs standard retournent `end()` quand un element n'est pas trouve (comme `std::find`). On suit cette convention. C'est au code appelant de verifier si le retour est `end()` ou non.

## Le main (main.cpp)

```cpp
int main(int, char**)
{
    std::list<int>  l;

    l.push_back(42);
    l.push_back(21);
    l.push_back(1337);
    l.push_back(84);

    std::list<int>::iterator it = easyfind(l, 21);
    if (it == l.end())
        std::cout << "Can't find this element..." << std::endl;
    else
        std::cout << "Element " << *it << " found !" << std::endl;

    return 0;
}
```

Le main cree une `std::list<int>` (liste doublement chainee), y insere 4 valeurs, puis cherche `21`. Comme `21` est present, `easyfind` retourne un iterateur valide et on affiche "Element 21 found !".

**Note** : le template marche avec **n'importe quel conteneur d'int** : `std::list`, `std::vector`, `std::deque`... Car tous exposent `begin()`, `end()`, et un type `iterator`. C'est la force de la programmation generique.

---

# Exercice 01 — Span

## Objectif du sujet

Creer une classe `Span` qui :
- Stocke au maximum `N` entiers (`N` passe au constructeur comme `unsigned int`)
- Expose `addNumber(int)` pour ajouter un element (jette une exception si plein)
- Expose `shortestSpan()` et `longestSpan()` qui calculent l'ecart minimum et maximum entre tous les nombres stockes (jette une exception si 0 ou 1 element)
- Bonus : permet d'ajouter des nombres via une plage d'iterateurs (pour eviter d'appeler `addNumber` des milliers de fois)

## Le header (Span.hpp)

```cpp
class Span {
private:
    const unsigned int  _max_size;
    std::vector<int>    _elems;

public:
    Span(void);
    Span(const unsigned int max_size);
    Span(const Span &src);
    ~Span(void);
    Span    &operator =(const Span &src);

    void    addNumber(const int num);
    int     shortestSpan(void) const;
    int     longestSpan(void) const;

    template<typename InputIt>
    void    insertMany(InputIt begin, InputIt end);
    void    fillWithRandom(size_t num);

    class MaxSizeReachedException: public std::exception { /* ... */ };
    class EmptySpanException: public std::exception { /* ... */ };
};
```

### Les membres prives

- `_max_size` : le nombre maximum d'elements, `const` car il ne change jamais apres construction.
- `_elems` : un `std::vector<int>` qui stocke les elements. Le vector gere lui-meme sa memoire (pas besoin de `new`/`delete`).

### Pourquoi un `vector` ?

Le sujet dit d'utiliser les conteneurs STL. `std::vector` est le choix naturel :
- Acces aleatoire O(1)
- Tri avec `std::sort` O(n log n)
- Redimensionnement automatique
- Compatible avec tous les algorithmes STL

### Orthodox Canonical Form

```cpp
Span::Span(void) : _max_size(0) {}
Span::Span(const unsigned int max_size) : _max_size(max_size) {}
Span::Span(const Span &src) : _max_size(src._max_size) { *this = src; }
Span::~Span(void) {}
```

- Le constructeur de copie initialise `_max_size` dans la liste d'initialisation (obligatoire car c'est `const`), puis delegue a `operator=`.
- L'`operator=` ne copie que `_elems` (pas `_max_size` car il est `const`).
- Le destructeur ne fait rien : le `vector` se detruit tout seul (RAII).

## `addNumber`

```cpp
void    Span::addNumber(const int num)
{
    if (this->_elems.size() >= this->_max_size ||
        this->_elems.size() >= this->_elems.max_size())
        throw Span::MaxSizeReachedException();
    this->_elems.push_back(num);
}
```

- Verifie qu'on n'a pas atteint la limite `_max_size` ni la limite physique du vector.
- Jette `MaxSizeReachedException` si plein.
- Sinon, ajoute l'element avec `push_back`.

## `shortestSpan` — l'algorithme le plus interessant

```cpp
int Span::shortestSpan(void) const
{
    if (this->_elems.size() <= 1)
        throw Span::EmptySpanException();

    std::vector<int> temp = this->_elems;
    std::sort(temp.begin(), temp.end());
    std::adjacent_difference(temp.begin(), temp.end(), temp.begin());

    return *std::min_element(temp.begin() + 1, temp.end());
}
```

### Etape par etape :

1. **Verification** : si 0 ou 1 element, pas de span possible → exception.
2. **Copie** : on travaille sur une copie pour ne pas modifier le Span original (methode `const`).
3. **Tri** : `std::sort` trie en O(n log n). Apres tri, les nombres les plus proches sont voisins.
4. **Differences adjacentes** : `std::adjacent_difference` calcule la difference entre chaque paire d'elements consecutifs. Le resultat est ecrit dans le meme tableau.

**Exemple** : `[3, 6, 9, 11, 17]` apres tri → `adjacent_difference` donne `[3, 3, 3, 2, 6]`

Le premier element (index 0) reste inchange (c'est la convention de `adjacent_difference`). C'est pour ca qu'on cherche le minimum a partir de `temp.begin() + 1` — sinon on risquerait de trouver la plus petite *valeur* du tableau au lieu du plus petit *ecart*.

5. **Minimum** : `std::min_element` sur `[begin+1, end)` retourne un iterateur vers la plus petite difference. On la dereference avec `*`.

### Pourquoi `begin() + 1` est crucial

`adjacent_difference` met la premiere valeur originale a `temp[0]`. Si on fait `min_element` depuis `begin()`, on compare des differences avec une valeur brute. Par exemple avec `[3, 6, 9]` :
- Apres sort : `[3, 6, 9]`
- Apres adjacent_difference : `[3, 3, 3]`
- `min_element(begin(), end())` → 3 (correct par chance)
- Mais avec `[1, 6, 9]` → `[1, 5, 3]` → `min_element` retourne 1 (faux ! le vrai shortest span est 3)

En partant de `begin() + 1`, on ne regarde que les vraies differences : `[5, 3]` → minimum = 3 (correct).

## `longestSpan`

```cpp
int Span::longestSpan(void) const
{
    if (this->_elems.size() <= 1)
        throw Span::EmptySpanException();

    int max = *std::max_element(this->_elems.begin(), this->_elems.end());
    int min = *std::min_element(this->_elems.begin(), this->_elems.end());

    return max - min;
}
```

Beaucoup plus simple : le plus grand ecart est toujours `max - min`. Pas besoin de trier. On utilise `std::max_element` et `std::min_element` qui parcourent le conteneur en O(n).

## `insertMany` et `fillWithRandom`

```cpp
template<typename InputIt>
void    Span::insertMany(InputIt begin, InputIt end)
{
    while (begin != end)
    {
        this->addNumber(*begin);
        ++begin;
    }
}

void    Span::fillWithRandom(size_t num)
{
    srand(time(NULL));
    for (size_t cur = 0; cur < num; cur++)
        this->addNumber(rand());
}
```

- `insertMany` : repond a la demande du sujet d'ajouter des nombres via une plage d'iterateurs. C'est un function template qui accepte n'importe quel type d'iterateur (pointeurs C, iterateurs de vector, de list, etc.).
- `fillWithRandom` : methode utilitaire pour les tests avec beaucoup d'elements (le sujet demande de tester avec au moins 10000 nombres).
- Les deux reutilisent `addNumber` pour beneficier de la verification de capacite.

## Les exceptions

```cpp
class MaxSizeReachedException: public std::exception {
    virtual const char* what(void) const throw();
};

class EmptySpanException: public std::exception {
    virtual const char* what(void) const throw();
};
```

Des classes d'exception nestees dans `Span`, heritant de `std::exception`. C'est le pattern canonique en C++98 : on surcharge `what()` pour retourner un message descriptif.

## Le main

Le main teste :
1. **Resultat du sujet** : `{6, 3, 17, 9, 11}` → shortestSpan=2 (entre 9 et 11), longestSpan=14 (entre 3 et 17).
2. **Ajout a un Span de taille 0** → exception.
3. **Span/longestSpan sur Span vide** → exception.
4. **Deep copy** : modifie la copie, verifie que l'original n'est pas affecte.
5. **1 000 000 d'elements aleatoires** : prouve que ca fonctionne a grande echelle.

---

# Exercice 02 — Mutated abomination (MutantStack)

## Objectif du sujet

`std::stack` est un **adaptateur de conteneur** : il encapsule un conteneur (par defaut `std::deque`) et n'expose que `push`, `pop`, `top`, `size`, `empty`. Pas d'iterateur — on ne peut pas parcourir les elements.

Le but est de creer `MutantStack`, qui herite de `std::stack` et lui **ajoute des iterateurs**. Le resultat doit produire la meme sortie que si on utilisait un `std::list` a la place.

## Le header (MutantStack.hpp)

```cpp
template<typename T>
class MutantStack: public std::stack<T> {
public:
    MutantStack(void);
    MutantStack(const MutantStack<T> &src);
    ~MutantStack(void);
    MutantStack<T>  &operator =(const MutantStack<T> &src);

    typedef typename std::stack<T>::container_type::iterator       iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    iterator        begin(void);
    const_iterator  begin(void) const;
    iterator        end(void);
    const_iterator  end(void) const;
};
```

### Heritage public de `std::stack<T>`

```cpp
class MutantStack: public std::stack<T>
```

En heritant publiquement de `std::stack<T>`, `MutantStack` **herite de toute l'interface** de `std::stack` : `push`, `pop`, `top`, `size`, `empty`. Pas besoin de les reimplementer. C'est ce que demande le sujet : "offer all of its member functions".

### Les typedefs d'iterateurs — le coeur du sujet

```cpp
typedef typename std::stack<T>::container_type::iterator       iterator;
typedef typename std::stack<T>::container_type::const_iterator const_iterator;
```

C'est la partie la plus subtile. Decomposons :

1. `std::stack<T>` a un typedef interne `container_type` qui represente le conteneur sous-jacent (par defaut `std::deque<T>`).
2. `container_type::iterator` est le type d'iterateur de ce conteneur sous-jacent.
3. `typename` est necessaire car c'est un type dependant d'un parametre template.

On cree donc des alias `iterator` et `const_iterator` qui correspondent aux iterateurs du `deque` encapsule dans le `stack`.

### Pourquoi `std::stack` n'a pas d'iterateurs nativement ?

`std::stack` est un **adaptateur** dont le role est de **restreindre l'interface** d'un conteneur pour forcer un usage LIFO (Last In, First Out). Donner des iterateurs casserait cette abstraction — on pourrait acceder a n'importe quel element, ce qui va a l'encontre du concept de pile. Le sujet joue sur cette idee : on "butche" l'abstraction pour acceder au conteneur sous-jacent.

## L'implementation (dans MutantStack.hpp)

Comme pour easyfind, l'implementation des methodes templates est directement dans le `.hpp`, apres la declaration de la classe.

### L'operator= — attention au piege

```cpp
template<class T>
MutantStack<T>  &MutantStack<T>::operator =(const MutantStack<T> &src)
{
    if (this != &src)
        std::stack<T>::operator=(src);
    return *this;
}
```

On appelle **explicitement `std::stack<T>::operator=`** pour copier le conteneur sous-jacent. C'est important : si on ecrivait `*this = src`, ca appellerait `MutantStack::operator=`... recursivement a l'infini → stack overflow.

### Les fonctions begin/end — le membre protege `c`

```cpp
template<class T>
typename MutantStack<T>::iterator   MutantStack<T>::begin(void)
{
    return this->c.begin();
}
```

`this->c` est le **membre protege** de `std::stack` qui contient le conteneur sous-jacent. En C++98, `std::stack` a un membre `protected` nomme `c` de type `container_type` (par defaut `std::deque<T>`).

Comme `MutantStack` herite de `std::stack`, il a acces a ce membre protege. On appelle simplement `begin()` et `end()` du `deque` sous-jacent.

C'est toute la "magie" : le conteneur sous-jacent a deja des iterateurs, le stack les cache, et nous on les re-expose.

### Les 4 variantes

```cpp
iterator        begin();       // version non-const → iterateur modifiable
const_iterator  begin() const; // version const → iterateur en lecture seule
iterator        end();         // version non-const
const_iterator  end() const;   // version const
```

On fournit les versions const et non-const pour suivre la convention STL. La version const est appelee automatiquement quand l'objet est const.

## Le main

```cpp
// Bloc MutantStack
MutantStack<int>    mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;    // 17
mstack.pop();
std::cout << mstack.size() << std::endl;   // 1
mstack.push(3);
mstack.push(5);
mstack.push(737);
mstack.push(0);

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite)
{
    std::cout << *it << std::endl;
    ++it;
}
std::stack<int> s(mstack);  // copie dans un std::stack normal
```

Puis le meme code avec un `std::list` :

```cpp
std::list<int>      mstack;
mstack.push_back(5);
mstack.push_back(17);
std::cout << mstack.back() << std::endl;   // 17
mstack.pop_back();
// ... meme chose avec push_back au lieu de push
```

**Les deux blocs produisent la meme sortie** :
```
17
1
5
3
5
737
0
```

C'est exactement ce que demande le sujet : "the output should be the same as if we replaced the MutantStack with std::list".

La ligne `std::stack<int> s(mstack)` prouve que `MutantStack` est compatible avec `std::stack` — on peut le copier dans un stack normal grace a l'heritage.

---

# Les 3 piliers de la STL utilises dans ce module

## 1. Conteneurs
- `std::list` (ex00) : liste doublement chainee, insertion/suppression O(1), pas d'acces aleatoire
- `std::vector` (ex01) : tableau dynamique, acces aleatoire O(1), insertion en fin O(1) amorti
- `std::stack` (ex02) : adaptateur LIFO, encapsule un `std::deque` par defaut
- `std::deque` (ex02, implicitement) : le conteneur sous-jacent du stack

## 2. Iterateurs
- `T::iterator` : type d'iterateur d'un conteneur
- `begin()` / `end()` : bornes de la plage iterable (convention `[begin, end)`)
- `++it`, `--it`, `*it` : operations de base sur les iterateurs

## 3. Algorithmes
- `std::find` (ex00) : recherche lineaire
- `std::sort` (ex01) : tri en O(n log n)
- `std::adjacent_difference` (ex01) : calcule les differences entre elements consecutifs
- `std::min_element` / `std::max_element` (ex01) : trouve le min/max dans une plage

---

# Resume

| Ex | Sujet | Concept STL | Difficulte |
|----|-------|-------------|------------|
| 00 | easyfind | Function template + `std::find` sur conteneur generique | Simple |
| 01 | Span | Classe wrappant un `std::vector` + algorithmes STL (sort, adjacent_difference, min/max_element) | Moyen |
| 02 | MutantStack | Heritage de `std::stack` + exposition du conteneur sous-jacent via iterateurs | Avance |

Le fil rouge du module : la STL est construite sur le trio **conteneurs + iterateurs + algorithmes**. Les conteneurs stockent les donnees, les iterateurs permettent de les parcourir de facon uniforme, et les algorithmes operent sur des plages d'iterateurs independamment du conteneur. C'est cette separation qui rend la STL si puissante et extensible.
