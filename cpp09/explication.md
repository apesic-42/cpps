# CPP Module 09 — Explication detaillee du code
note perso : ce sujet est tres dure et tres technique, il porte sur la STL (Standard Template Library) et des algorithmes de tri avances. Revise bien le Ford-Johnson et les conteneurs STL.

## Vue d'ensemble du module

Le module 09 porte sur **les conteneurs STL en C++**. C'est le dernier module du tronc commun C++, et c'est la premiere fois (avec le module 08) que la STL est autorisee. Chaque exercice doit utiliser **un conteneur different**, et une fois un conteneur utilise dans un exercice, il est **interdit dans les suivants** (sauf ex02 qui en utilise deux).

| Exercice | Sujet | Conteneur(s) utilise(s) | Pourquoi ce conteneur |
|----------|-------|------------------------|----------------------|
| ex00 | Bitcoin Exchange | `std::map` | Recherche par cle (date) avec `upper_bound()` en O(log n) |
| ex01 | Reverse Polish Notation | `std::stack` | LIFO naturel pour l'evaluation d'expressions postfixees |
| ex02 | PmergeMe | `std::deque` + `std::vector` | Comparaison de performance du meme algo sur 2 conteneurs |

### Regle des conteneurs

Le sujet impose : "Once a container is used you cannot use it for the rest of the module." Donc :
- ex00 utilise `map` → `map` interdit en ex01 et ex02
- ex01 utilise `stack` → `stack` interdit en ex02
- ex02 utilise `deque` + `vector` → c'est le dernier exercice, pas de contrainte supplementaire

---

# Exercice 00 — Bitcoin Exchange

## Objectif du sujet

Ecrire un programme `./btc <fichier>` qui :
1. Charge une base de donnees CSV (`data.csv`) contenant l'historique des prix du Bitcoin (date,taux).
2. Lit un fichier d'entree contenant des lignes au format `date | valeur`.
3. Pour chaque ligne valide, affiche `date => valeur = valeur * taux_du_jour`.
4. Si la date exacte n'existe pas dans la base, utilise la **date inferieure la plus proche** (pas la superieure).
5. Gere les erreurs : date invalide, valeur negative, valeur > 1000, format incorrect.

Sortie attendue (exemples du sujet) :
```
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

## Architecture choisie

Le code definit une classe `BitcoinExchange` dans `BitcoinExchange.hpp`. Le conteneur utilise est `std::map<time_t, float>` : une map ordonnee dont les cles sont des timestamps UNIX et les valeurs sont les taux de change.

### Pourquoi `std::map` ?

`std::map` est un arbre binaire equilibre (red-black tree) qui maintient ses elements **tries par cle**. Ca offre :
- **Insertion** en O(log n)
- **Recherche** en O(log n)
- **`upper_bound(key)`** en O(log n) : retourne un iterateur vers le premier element dont la cle est **strictement superieure** a `key`. En decrementant cet iterateur, on obtient la cle inferieure ou egale la plus proche — exactement ce dont on a besoin pour trouver la date la plus proche.

Aucun autre conteneur standard n'offre cette capacite aussi naturellement. Un `vector` necessiterait un tri explicite puis une recherche binaire manuelle.

### Le header (BitcoinExchange.hpp)

```cpp
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>
# include <ctime>

class	BitcoinExchange
{
	private:
		std::map<time_t, float>	data;
	public:
		~BitcoinExchange(void);
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange &copy);
		float			get_value(time_t time);
		BitcoinExchange	&operator=(const BitcoinExchange &copy);
};
```

`#include <ctime>` est necessaire pour declarer `time_t` et `struct tm`. La classe suit l'Orthodox Canonical Form (constructeur, destructeur, copie, assignment). Le membre `data` est prive — l'encapsulation est respectee.

## La fonction `parse_date()` (BitcoinExchange.cpp:8-25)

```cpp
static bool	parse_date(const std::string &str, struct tm *t)
{
	int	year, month, day;
	char dash1, dash2;

	if (str.length() != 10)
		return (false);
	std::istringstream iss(str);
	iss >> year >> dash1 >> month >> dash2 >> day;
	if (iss.fail() || dash1 != '-' || dash2 != '-')
		return (false);
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	std::memset(t, 0, sizeof(struct tm));
	t->tm_year = year - 1900;
	t->tm_mon = month - 1;
	t->tm_mday = day;
	return (true);
}
```

C'est une fonction statique locale (pas une methode de classe) qui parse une date `"YYYY-MM-DD"` en `struct tm`. Elle est compatible **C++98** — on n'utilise pas `std::get_time` (C++11), on parse manuellement via un `istringstream`.

**Points importants** :
- On verifie que la chaine fait exactement 10 caracteres (`YYYY-MM-DD`).
- On extrait `year`, `dash1`, `month`, `dash2`, `day` depuis le stream. Si le format est mauvais (lettres, tirets manquants...), `iss.fail()` le detecte.
- On valide les plages : mois [1-12], jour [1-31].
- **`std::memset(t, 0, sizeof(struct tm))`** est crucial : on zero-initialise TOUS les champs du `struct tm` avant de remplir ceux qui nous interessent. Sans ca, les champs `tm_sec`, `tm_min`, `tm_hour`, `tm_isdst` contiennent des valeurs poubelle, et `mktime()` produit des timestamps completement faux.
- `tm_year` attend l'annee - 1900 (convention POSIX), `tm_mon` attend le mois 0-indexe.

## Le constructeur (BitcoinExchange.cpp:27-55)

```cpp
BitcoinExchange::BitcoinExchange(void)
{
	std::ifstream	file;
	std::string		line;
	struct tm		timestrct;

	file.open("data.csv");
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		exit(1);
	}
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.length() < 12)
			continue ;
		if (!parse_date(line.substr(0, 10), &timestrct))
			continue ;
		data.insert(std::pair<time_t, float>(
			mktime(&timestrct), atof(line.substr(11).c_str())));
	}
	file.close();
}
```

Le constructeur ouvre `data.csv`, skip la premiere ligne (header `date,exchange_rate`), puis pour chaque ligne :
1. Verifie que la ligne fait au moins 12 caracteres (date + virgule + au moins 1 chiffre)
2. Parse les 10 premiers caracteres comme date via `parse_date()`
3. Convertit le `struct tm` en `time_t` via `mktime()`
4. Extrait le taux (tout apres la virgule, position 11) avec `atof()` (compatible C++98, contrairement a `std::stof` qui est C++11)
5. Insere la paire `(timestamp, taux)` dans la map

**Note** : on utilise une variable locale `struct tm timestrct` sur la pile (pas de `new`/`delete`). C'est plus simple et plus sur.

### Le constructeur de copie

```cpp
BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
	data = copy.data;
}
```

Le constructeur de copie **copie la map** depuis l'objet source. C'est le comportement attendu — on ne relit pas le fichier CSV.

## La methode `get_value()` (BitcoinExchange.cpp:63-71)

```cpp
float	BitcoinExchange::get_value(time_t time)
{
	std::map<time_t, float>::iterator	it;

	it = data.upper_bound(time);
	if (it == data.begin())
		return (-1);
	it--;
	return (it->second);
}
```

C'est la methode cle de la classe. Elle utilise `upper_bound()` pour trouver le premier element avec une date **strictement superieure** a celle demandee, puis recule d'un cran pour obtenir la date inferieure ou egale la plus proche.

**Protection `begin()`** : si la date est anterieure a toutes les entrees de la base (ex: `2008-01-01` alors que la base commence en `2009`), `upper_bound` retourne `begin()`. Decrementer `begin()` serait du undefined behavior. On retourne `-1` comme signal d'erreur, et le `main` l'affiche comme "bad input".

### Comment `upper_bound` fonctionne

Imaginons la map contient les dates : `[Jan 1, Jan 4, Jan 7, Jan 10]`

- Pour la date `Jan 3` : `upper_bound` retourne l'iterateur vers `Jan 4`, on fait `it--` → `Jan 1` (correct)
- Pour la date `Jan 4` : `upper_bound` retourne `Jan 7`, on fait `it--` → `Jan 4` (exact match, correct)
- Pour la date `Jan 10` : `upper_bound` retourne `end()`, on fait `it--` → `Jan 10` (correct)
- Pour la date `Dec 2008` : `upper_bound` retourne `begin()` → on retourne `-1` (erreur)

## Le main (main.cpp)

```cpp
int	main(int argc, char **argv)
{
	BitcoinExchange	db;
	// ...
	file.open(argv[1]);
	std::getline(file, line);   // skip header
	while (std::getline(file, line))
	{
		// verifie le format "date | value"
		if (line.length() < 14 || line.substr(10, 3) != " | ")
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// parse date (10 first chars)
		if (!parse_date(line.substr(0, 10), &timestrct))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// parse value (after " | " = position 13)
		std::istringstream	iss(line.substr(13));
		iss >> num;
		if (iss.fail())
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// range checks
		if (num < 0) ...
		else if (num > 1000) ...
		// compute and display
		timestamp = mktime(&timestrct);
		float rate = db.get_value(timestamp);
		if (rate < 0)       // date trop ancienne
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		std::cout << line.substr(0, 10) << " => " << num
		          << " = " << num * rate << std::endl;
	}
}
```

Le main lit le fichier d'entree ligne par ligne, verifie :
1. Le separateur ` | ` est bien present a la bonne position (longueur >= 14 et `substr(10, 3) == " | "`)
2. La date est bien parsee via `parse_date()` (sinon "bad input")
3. La valeur est un nombre valide via `istringstream` (sinon "bad input")
4. La valeur est >= 0 (sinon "not a positive number")
5. La valeur est <= 1000 (sinon "too large a number")
6. Le taux est disponible dans la base (`get_value` ne retourne pas `-1`)

Si tout est bon, il multiplie la valeur par le taux de la base et affiche le resultat.

### Le format `date | value`

Le fichier d'entree a le format `YYYY-MM-DD | value`. Le `" | "` fait 3 caracteres, donc la valeur commence a la position 13 (10 pour la date + 3 pour le separateur). C'est pour ca que le code fait `line.substr(13)`.

La verification `line.substr(10, 3) != " | "` s'assure que le separateur est bien present — ca rejette les lignes comme `2001-42-42` (pas de separateur) avant meme de parser la valeur.

---

# Exercice 01 — Reverse Polish Notation (RPN)

## Objectif du sujet

Ecrire un programme `./RPN <expression>` qui :
1. Prend une expression en notation polonaise inversee (postfixee) en argument.
2. Evalue l'expression et affiche le resultat.
3. Les nombres sont des **chiffres uniques** (< 10).
4. Les operateurs supportes sont : `+`, `-`, `*`, `/`.
5. En cas d'erreur, afficher "Error" sur **stderr**.

Exemples du sujet :
```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```

## Qu'est-ce que la notation polonaise inversee (RPN) ?

En notation classique (infixe) : `3 + 4 * 2` (necessite des regles de priorite et des parentheses).
En notation postfixee (RPN) : `3 4 2 * +` (pas d'ambiguite, pas de parentheses).

Le principe est simple :
- Quand on rencontre un **nombre**, on le **pousse** sur la pile.
- Quand on rencontre un **operateur**, on **depile deux operandes**, on applique l'operation, et on **pousse le resultat**.
- A la fin, il doit rester **exactement un element** sur la pile : c'est le resultat.

### Exemple pas a pas : `8 9 * 9 - 9 - 9 - 4 - 1 +`

| Token | Action | Pile |
|-------|--------|------|
| `8` | push | `[8]` |
| `9` | push | `[8, 9]` |
| `*` | pop 9 et 8, push 8*9=72 | `[72]` |
| `9` | push | `[72, 9]` |
| `-` | pop 9 et 72, push 72-9=63 | `[63]` |
| `9` | push | `[63, 9]` |
| `-` | pop 9 et 63, push 63-9=54 | `[54]` |
| `9` | push | `[54, 9]` |
| `-` | pop 9 et 54, push 54-9=45 | `[45]` |
| `4` | push | `[45, 4]` |
| `-` | pop 4 et 45, push 45-4=41 | `[41]` |
| `1` | push | `[41, 1]` |
| `+` | pop 1 et 41, push 41+1=42 | `[42]` |

Resultat final : **42**.

## Pourquoi `std::stack` ?

`std::stack` est un **adaptateur de conteneur** qui expose uniquement les operations `push()`, `pop()`, `top()` et `size()`. C'est exactement le pattern LIFO (Last In, First Out) dont la RPN a besoin. Pas de recherche, pas d'acces aleatoire — juste empiler et depiler.

En interne, `std::stack` utilise par defaut un `std::deque`, mais c'est un detail d'implementation transparent.

## Le header (RPN.hpp)

```cpp
class RPN
{
	private:
		std::stack<int>	nums;
	public:
		RPN(void);
		RPN(const RPN &copy);
		~RPN(void);
		RPN	&operator=(const RPN &copy);
		void			add_num(int num);
		void			operation(char op);
		int				result(void);
};
```

La pile `nums` est privee. L'Orthodox Canonical Form est respectee (constructeur, destructeur, copie, operator=). Trois methodes metier :
- `add_num` : empile un nombre
- `operation` : depile deux nombres, applique l'operateur, empile le resultat
- `result` : verifie qu'il reste exactement un element et le retourne

## La methode `operation()` (RPN.cpp:9-37)

```cpp
void	RPN::operation(char op)
{
	int	operand1;
	int	operand2;

	if (nums.size() < 2)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	operand2 = nums.top();
	nums.pop();
	operand1 = nums.top();
	nums.pop();
	switch (op)
	{
		case '+':
			nums.push(operand1 + operand2);
			break ;
		case '-':
			nums.push(operand1 - operand2);
			break ;
		case '/':
			if (operand2 == 0)
			{
				std::cerr << "Error" << std::endl;
				exit(1);
			}
			nums.push(operand1 / operand2);
			break ;
		case '*':
			nums.push(operand1 * operand2);
			break ;
	}
}
```

**Attention a l'ordre des operandes** : `operand2` est depile en premier (c'est le top de la pile = le deuxieme operande). `operand1` est depile ensuite (c'est le premier operande). L'ordre est important pour la soustraction et la division : `8 2 -` doit donner `8 - 2 = 6`, pas `2 - 8 = -6`.

**Division par zero** : avant de diviser, on verifie que `operand2 != 0`. Sans ce test, une division entiere par zero provoquerait un SIGFPE (crash).

**Erreurs sur stderr** : le sujet dit "an error message should be displayed on the standard error". On utilise `std::cerr` (pas `std::cout`) pour toutes les erreurs.

## Le main (main.cpp)

```cpp
int	main(int argc, char **argv)
{
	std::string	arg;
	RPN			calc;
	std::string	obj;

	if (argc < 2)
	{
		std::cout << "Not enough arguments!" << std::endl;
		return (1);
	}
	arg = argv[1];
	arg.push_back(' ');           // ajoute un espace final (sentinelle)
	// skip leading whitespace
	while (arg[0] == ' ' || arg[0] == '\t')
		arg.erase(0, 1);
	while (arg.length())
	{
		obj = arg.substr(0, arg.find_first_of(" \t"));
		if (obj == "+" || obj == "-" || obj == "/" || obj == "*")
			calc.operation(obj[0]);
		else if (obj.length() != 1 || !std::isdigit(obj[0]))
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		else
			calc.add_num(obj[0] - '0');
		// skip current token
		while (arg[0] && arg[0] != ' ' && arg[0] != '\t')
			arg.erase(0, 1);
		// skip whitespace
		while (arg[0] == ' ' || arg[0] == '\t')
			arg.erase(0, 1);
	}
	std::cout << calc.result() << std::endl;
}
```

### Comment le parsing fonctionne

1. L'argument est copie dans `arg`, avec un espace ajoute a la fin (sentinelle pour que le dernier token soit correctement separe).
2. On skip les espaces initiaux.
3. On extrait chaque token (sous-chaine jusqu'au prochain espace/tab).
4. Si c'est un operateur → `calc.operation()`
5. Sinon, on verifie que c'est **exactement un chiffre** : `obj.length() != 1 || !std::isdigit(obj[0])`. Cela rejette les nombres multi-chiffres, les negatifs, et tout caractere non numerique.
6. Si c'est un chiffre valide → `calc.add_num(obj[0] - '0')` : on convertit le caractere en entier par soustraction du code ASCII de `'0'`. C'est compatible C++98 (pas besoin de `std::stoi` qui est C++11).

---

# Exercice 02 — PmergeMe (Ford-Johnson Merge-Insert Sort)

## Objectif du sujet

Ecrire un programme `./PmergeMe <sequence>` qui :
1. Prend une sequence d'entiers positifs en arguments.
2. La trie en utilisant l'algorithme **merge-insert sort** (Ford-Johnson).
3. Affiche la sequence avant et apres le tri.
4. Affiche le temps d'execution pour **deux conteneurs differents** (`std::deque` et `std::vector`).
5. Doit gerer au moins **3000 elements**.

Format de sortie :
```
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::deque  : 98 us
Time to process a range of 5 elements with std::vector : 30 us
```

## Qu'est-ce que l'algorithme Ford-Johnson (Merge-Insert) ?

C'est un algorithme de tri publie par Ford et Johnson en 1959, decrit dans "The Art of Computer Programming" de Knuth (Vol. 3, p. 184). Son objectif est de **minimiser le nombre de comparaisons** necessaires pour trier une sequence.

### Etapes de l'algorithme

L'algorithme fonctionne en 4 phases :

#### Phase 1 : Appariement (pairing)
On regroupe les elements par **paires**. Dans chaque paire, on compare les deux elements et on s'assure que le plus grand est en premiere position.

```
Input:  [3, 5, 9, 7, 4]
Paires: (5,3) (9,7) | 4 est impair, mis de cote
```

#### Phase 2 : Tri recursif des plus grands
On prend les plus grands de chaque paire et on les trie **recursivement** (en reformant des paires de paires, etc.).

```
Grands: [5, 9] → trie recursivement → [5, 9]
```

#### Phase 3 : Chaine principale
Les grands elements tries forment la "chaine principale". Le premier petit element est insere en tete (il est forcement plus petit que son grand correspondant).

```
Chaine: [3, 5, 9]   (3 est le petit de 5, insere en tete)
Pendants: [7]         (le petit de 9, a inserer)
Impair: [4]           (element sans paire)
```

#### Phase 4 : Insertion avec la sequence de Jacobsthal
Les elements restants ("pendants") sont inseres dans la chaine en utilisant une **recherche binaire**, mais dans un **ordre specifique** dicte par les **nombres de Jacobsthal**. Cet ordre est calcule pour minimiser le nombre de comparaisons en exploitant le fait qu'on connait une borne superieure pour chaque element pendant.

### Les nombres de Jacobsthal

La sequence de Jacobsthal est definie par :
```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)
```

Ce qui donne : `0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...`

L'ordre d'insertion utilise les differences entre termes consecutifs : on insere d'abord le 3eme pendant, puis le 2eme, puis le 1er, puis le 5eme, le 4eme, puis le 11eme, le 10eme, le 9eme, etc. Ce pattern contre-intuitif est prouve optimal pour minimiser les comparaisons.

### Pourquoi c'est mieux qu'un tri par insertion classique ?

Un tri par insertion classique insere les elements un par un, dans l'ordre. Chaque insertion necessite une recherche binaire dans toute la chaine existante.

Ford-Johnson est plus malin : en inserant dans l'ordre de Jacobsthal, on garantit que chaque recherche binaire se fait dans un sous-ensemble **optimal** de la chaine — on n'a jamais besoin de chercher dans plus de `2^k - 1` elements, ce qui donne exactement `k` comparaisons.

Pour n elements, Ford-Johnson utilise au plus `ceil(log2(n!)/n)` comparaisons en moyenne, tres proche de la borne theorique inferieure.

## Pourquoi `std::vector` et `std::deque` ?

Le sujet demande deux conteneurs differents pour comparer les performances.

### `std::vector`
- **Memoire contigue** (un seul bloc d'allocation)
- Acces aleatoire O(1) avec excellente localite de cache
- **Insertion au milieu O(n)** (doit deplacer tous les elements apres le point d'insertion)
- Tres bon pour les petites tailles et les patterns d'acces sequentiel

### `std::deque`
- **Memoire par blocs** (tableau de pointeurs vers des blocs de taille fixe)
- Acces aleatoire O(1) mais avec indirection (un peu plus lent)
- **Insertion aux extremites O(1)**, mais insertion au milieu aussi O(n)
- Moins bonne localite de cache que le vector

En pratique, `std::vector` est generalement plus rapide pour le tri grace a la localite de cache, et c'est ce qu'on observe dans les tests (le vector est souvent 2-3x plus rapide que le deque).

## Le header (PmergeMe.hpp)

```cpp
class	PmergeMe
{
	private:
		std::deque<int>		dq;
		std::deque<int>		dq_odd;
		std::deque<int>		dq_pend;
		struct timeval		dq_time;
		std::vector<int>	vctr;
		struct timeval		vctr_time;
		std::vector<int>	vctr_odd;
		std::vector<int>	vctr_pend;
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &copy);
		void				load_dq(char **argv);
		void				load_vctr(char **argv);
};
```

L'Orthodox Canonical Form est respectee (constructeur, destructeur, copie, operator=). Pour chaque conteneur (deque et vector), on a :
- Le conteneur principal (`dq`, `vctr`) : contient la sequence a trier
- `_odd` : stocke l'element impair (quand la taille est impaire, un element n'a pas de paire)
- `_pend` : stocke les "pendants" (les petits elements de chaque paire, en attente d'insertion)
- `_time` : pour mesurer le temps d'execution

**Note** : `dq_odd`, `dq_pend`, `vctr_odd`, `vctr_pend` sont declares comme membres de classe mais sont en fait **passes par valeur** aux fonctions templates (copies). Ils sont initialises vides et servent de point de depart.

## L'implementation (PmergeMe.cpp)

### La fonction helper `t()` (ligne 7-10)

```cpp
static int	t(int val, int nb)
{
	return (val * nb + nb - 1);
}
```

C'est une fonction d'indexation. Dans l'algorithme, on ne manipule pas des elements individuels mais des **groupes de `nb` elements**. `t(val, nb)` retourne l'index du **dernier element** du groupe numero `val`.

Par exemple, si `nb = 2` (paires) :
- `t(0, 2) = 1` : dernier element du groupe 0 (indices 0-1)
- `t(1, 2) = 3` : dernier element du groupe 1 (indices 2-3)
- `t(2, 2) = 5` : dernier element du groupe 2 (indices 4-5)

C'est crucial car l'algorithme travaille a differentes echelles : d'abord des elements individuels (nb=1), puis des paires (nb=2), puis des groupes de 4 (nb=4), etc.

### La recherche binaire `bin_search()` (lignes 12-25)

```cpp
template <class Container>
static int	bin_search(Container a, int item, int low, int high, int n)
{
	int	mid;

	if (high <= low)
		return ((item > a[t(low, n)]) ? (t(low + 1, n)) : t(low, n));
	mid = (low + high) / 2;
	if (item == a[t(mid, n)])
		return (t(mid + 1, n));
	if (item > a[t(mid, n)])
		return (bin_search(a, item, mid + 1, high, n));
	return (bin_search(a, item, low, mid - 1, n));
}
```

C'est une recherche binaire **recursive** qui trouve la position d'insertion d'un element `item` dans un conteneur `a`. La particularite est qu'elle travaille par groupes de `n` elements : elle compare `item` avec le **dernier element** de chaque groupe (via `t(mid, n)`), car dans l'algorithme Ford-Johnson, le dernier element d'un groupe est toujours le plus grand (celui qui sert de "cle" de comparaison).

Elle retourne l'**index** ou inserer le groupe, en termes d'elements individuels (pas de groupes).

### Les nombres de Jacobsthal `jacobsthaler()` (lignes 27-34)

```cpp
int	jacobsthaler(int n)
{
	if (!n)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthaler(n - 1) + 2 * jacobsthaler(n - 2));
}
```

Calcul recursif naif des nombres de Jacobsthal. `J(n) = J(n-1) + 2*J(n-2)` avec `J(0)=0`, `J(1)=1`. C'est exponentiel en temps sans memoisation, mais comme `n` reste petit en pratique (on ne depasse pas J(20) ≈ 350000), ca passe.

### La fonction `pairsort()` (lignes 124-133)

```cpp
template <class Container>
static Container	pairsort(Container cntnr, Container odd, Container pend,
                             unsigned int nb)
{
	for (unsigned int i = 0; i + nb - 1 < cntnr.size(); i += nb)
		if (cntnr[i + (nb / 2) - 1] > cntnr[i + nb - 1])
			std::swap_ranges(cntnr.begin() + i,
			                 cntnr.begin() + i + (nb / 2),
			                 cntnr.begin() + i + (nb / 2));
	if (nb * 2 > cntnr.size())
		return (insert(cntnr, odd, pend, nb / 2));
	return (pairsort(cntnr, odd, pend, nb * 2));
}
```

C'est la **phase montante** de la recursion. Elle travaille par groupes de taille `nb` :

1. **Compare les paires de groupes** : pour chaque paire de groupes adjacents (de taille `nb/2` chacun), si la premiere moitie est plus grande que la seconde, on les echange avec `std::swap_ranges`. La comparaison se fait sur le **dernier element** de chaque demi-groupe (l'element "representant").

2. **Recursion** : si on peut encore doubler la taille des groupes (`nb * 2 <= cntnr.size()`), on recurse en doublant `nb`. Sinon, on passe a la **phase d'insertion** (`insert`) en redescendant.

L'appel initial est `pairsort(cntnr, odd, pend, 2)` — on commence par des paires d'elements individuels.

### Comment la recursion fonctionne concrètement

Prenons `[3, 5, 9, 7, 4]` :

**pairsort(nb=2)** : Compare par paires d'elements :
- `(3,5)` : 3 < 5, pas d'echange → `[3, 5, 9, 7, 4]`
- `(9,7)` : 9 > 7, echange → `[3, 5, 7, 9, 4]`
- `4` est seul, ignore

`nb*2=4 <= 5`, on continue.

**pairsort(nb=4)** : Compare par paires de groupes de 2 :
- Groupe 0 = `[3, 5]`, Groupe 1 = `[7, 9]`
- On compare 5 (fin du groupe 0) vs 9 (fin du groupe 1) : 5 < 9, pas d'echange

`nb*2=8 > 5`, on passe a `insert(nb=2)`.

A partir d'ici, la phase d'insertion reconstruit la sequence triee en descendant les niveaux de recursion.

### La fonction `insert()` (lignes 53-122)

C'est la fonction la plus complexe. Elle effectue la **phase descendante** : a chaque niveau de recursion (de `nb` grand vers `nb=1`), elle :

1. **Extrait l'element impair** (lignes 60-64) : si le nombre de groupes est impair, le dernier groupe complet est retire et stocke dans `odd`.

```cpp
if (((cntnr.size() - cntnr.size() % nb) / nb) % 2)
{
	odd.insert(odd.begin(), cntnr.end() - cntnr.size() % nb - nb,
	           cntnr.end() - cntnr.size() % nb);
	cntnr.erase(cntnr.end() - cntnr.size() % nb - nb,
	            cntnr.end() - cntnr.size() % nb);
}
```

2. **Separe les pendants** (lignes 65-69) : les "petits" de chaque paire (la premiere moitie de chaque groupe de `nb*2`) sont extraits et mis dans `pend`, ne laissant que les "grands" dans `cntnr`.

```cpp
for (unsigned int i = nb * 2; i + nb - 1 < cntnr.size(); i += nb)
{
	pend.insert(pend.end(), cntnr.begin() + i, cntnr.begin() + i + nb);
	cntnr.erase(cntnr.begin() + i, cntnr.begin() + i + nb);
}
```

Note : le premier pendant (index 0) reste dans `cntnr` car il est deja a la bonne place (il est plus petit que le premier "grand", donc il va en tete de la chaine principale).

3. **Insere les pendants via Jacobsthal** (lignes 70-105) :

```cpp
jacobsthal = 3;
while (pend.size())
{
	// calcule la position dans pend selon Jacobsthal
	if (jacobsthal == 3)
		pos = 3;
	else
		pos = jacobsthaler(jacobsthal) - jacobsthaler(jacobsthal - 1);
	// si pos depasse la taille, vide pend sequentiellement
	if (pos > pend.size() / nb)
	{
		while (pend.size())
		{
			i = bin_search(cntnr, pend[nb - 1], 0, cntnr.size() / nb, nb);
			// insere au bon endroit
			cntnr.insert(cntnr.begin() + i - (nb - 1), pend.begin(), pend.begin() + nb);
			pend.erase(pend.begin(), pend.begin() + nb);
		}
		break ;
	}
	// insere dans l'ordre Jacobsthal (du pos vers 1)
	while (pos)
	{
		i = bin_search(cntnr, pend[nb * pos - 1], 0, cntnr.size() / nb, nb);
		cntnr.insert(cntnr.begin() + i - (nb - 1),
		             pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
		pend.erase(pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
		pos--;
	}
	jacobsthal++;
}
```

L'idee de l'ordre de Jacobsthal : au lieu d'inserer les pendants de gauche a droite (1, 2, 3, 4, 5...), on les insere dans l'ordre 3, 2, 1, 5, 4, 11, 10, 9, 8, 7, 6, ... Ce pattern permet de limiter la plage de recherche binaire : quand on insere le pendant numero `k`, on sait qu'il ne peut pas etre plus grand que le "grand" correspondant, donc on cherche dans un intervalle borne.

4. **Insere l'element impair** (lignes 106-116) : si un element impair avait ete mis de cote, on l'insere a sa position par recherche binaire.

5. **Recursion descendante** (lignes 119-121) :
```cpp
if (nb >= 2)
	return (insert(cntnr, odd, pend, nb / 2));
return (cntnr);
```
On redescend au niveau inferieur jusqu'a `nb=1`, ou le tri est termine.

### La mesure du temps `time_elapsed()` (lignes 135-141)

```cpp
static long	time_elapsed(struct timeval time)
{
	struct timeval	new_time;

	gettimeofday(&new_time, 0);
	return ((new_time.tv_sec - time.tv_sec) * 1000000
	        + new_time.tv_usec - time.tv_usec);
}
```

Calcule le temps ecoule en **microsecondes** entre `time` (sauvegarde au debut) et maintenant. `gettimeofday` donne une precision a la microseconde (suffisant pour ce qu'on mesure).

### `load_dq()` et `load_vctr()` (lignes 143-166)

```cpp
void	PmergeMe::load_dq(char **argv)
{
	long	time_store;

	gettimeofday(&dq_time, 0);
	for (int i = 1; argv[i]; i++)
		dq.push_back(atoi(argv[i]));
	dq = pairsort(dq, dq_odd, dq_pend, 2);
	time_store = time_elapsed(dq_time);
	std::cout << "After:";
	for (unsigned int i = 0; i < dq.size(); i++)
		std::cout << " " << dq[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << dq.size()
	          << " elements with std::deque : " << time_store << " us" << std::endl;
}
```

Chaque fonction :
1. Demarre le chronometre
2. Charge les arguments dans le conteneur via `atoi()` (compatible C++98, le parsing fait partie du temps mesure comme demande par le sujet)
3. Lance le tri Ford-Johnson via `pairsort`
4. Arrete le chronometre
5. Affiche la sequence triee et le temps

Note : seul `load_dq` affiche "After:" — `load_vctr` n'affiche que le temps. C'est correct car la sequence triee est la meme pour les deux conteneurs.

## Le main (main.cpp)

```cpp
int	main(int argc, char **argv)
{
	PmergeMe	thing;

	if (argc < 3)
	{
		std::cout << "Not enough arguments!" << std::endl;
		return (1);
	}
	for (int i = 1; argv[i]; i++)
	{
		std::string	test;
		test = argv[i];
		if (test.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cout << "Error" << std::endl;
			return (1);
		}
	}
	std::cout << "Before:";
	for (int i = 1; argv[i]; i++)
		std::cout << " " << argv[i];
	std::cout << std::endl;
	thing.load_dq(argv);
	thing.load_vctr(argv);
}
```

Le main :
1. Verifie qu'il y a au moins 2 nombres (argc >= 3 car argv[0] est le programme)
2. Valide que chaque argument ne contient que des chiffres (`find_first_not_of("0123456789")`)
3. Affiche "Before:" avec la sequence non triee
4. Lance le tri sur les deux conteneurs

**Note** : la validation rejette les nombres negatifs (le `-` n'est pas dans `"0123456789"`), ce qui est correct car le sujet demande des "positive integers".

### Remarque sur les templates

Le sujet dit "it is strongly advised to implement your algorithm for each container and thus to avoid using a generic function". Le code utilise des **templates** (`template <class Container>`) pour eviter la duplication. C'est un conseil, pas une obligation stricte. L'avantage est que l'algorithme est identique pour les deux conteneurs — le template garantit la meme logique. Mais un evaluateur strict pourrait le relever.

---

# Resume des conteneurs et leur utilisation

| Conteneur | Exercice | Caractéristique cle | Utilisation |
|-----------|----------|---------------------|-------------|
| `std::map` | ex00 | Arbre ordonne, `upper_bound()` en O(log n) | Trouver le taux de change de la date la plus proche |
| `std::stack` | ex01 | LIFO, `push()`/`pop()`/`top()` | Evaluer une expression RPN |
| `std::deque` | ex02 | Blocs memoire, insertion O(1) aux extremites | Tri Ford-Johnson (comparaison de performance) |
| `std::vector` | ex02 | Memoire contigue, meilleure localite de cache | Tri Ford-Johnson (comparaison de performance) |

## Complexite du tri Ford-Johnson

| Metrique | Complexite |
|----------|-----------|
| Comparaisons | ~n*log2(n) - 1.44*n (proche de l'optimal theorique) |
| Temps (vector) | O(n^2) a cause des insertions au milieu |
| Temps (deque) | O(n^2) meme raison |
| Espace | O(n) pour les copies des sous-sequences |

Le Ford-Johnson est optimal en **nombre de comparaisons**, mais pas en temps reel a cause des insertions dans le conteneur (deplacements memoire en O(n)). En pratique, pour de grosses sequences, un `std::sort` (introsort, O(n log n)) est bien plus rapide, mais ce n'est pas le but de l'exercice — le but est de comprendre et implementer un algorithme avance.
