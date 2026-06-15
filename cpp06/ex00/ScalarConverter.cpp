
#include "ScalarConverter.hpp"
#include <cstdlib> // pour atof() (fonction C) qui sait lire "inf" et "nan"

// les 4 fonctions de la forme canonique, definies mais en private donc inutilisables
// (void)other = on ignore le param, juste pour eviter un warning -Wunused
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const &other) { (void)other; }
ScalarConverter::~ScalarConverter() {}
ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) { (void)other; return (*this); }

// enum = des etiquettes pour le type detecte
// les valeurs (0,1,2,3) servent aussi d'index dans status[4]
enum Type {
	TypeChar,   // 0
	TypeInt,    // 1
	TypeFloat,  // 2
	TypeDouble, // 3
	TypeLong,   // 4  declare mais pas utiliser
	BadType     // 5  = parsing rate
};

// detectType = le parseur, c'est le coeur de l'ex00
// fonction static locale (pas une methode de classe), visible que dans ce .cpp
// elle scanne la string et remplit la bonne variable passee par reference (&)
// retourne le type detecte (le tag pour la suite)
static int	detectType(std::string const &str, int &ivalue, float &fvalue, double &dvalue, char &cvalue)
{
	std::stringstream ss; // on accumule les caracteres valides ici pour les extraire apres
	size_t length = str.length();
	size_t i = 0;
	int type;

	// cas 1 : un seul caractere ET pas un chiffre => c'est un char (genre 'a')
	if (length == 1 && !std::isdigit(str[0]))
	{
		cvalue = str[0];
		return (TypeChar);
	}
	// cas 2 : signe au debut, on le copie et on avance (gere "-42" / "+4.2f")
	if (str[0] == '+' || str[0] == '-')
		ss << str[i++];
	type = TypeInt; // hypothese de depart : on suppose que c'est un int
	for ( ; i < length; i++)
	{
		// un point => on monte en double. type != TypeDouble bloque le double point "1.2.3"
		if (str[i] == '.' && type != TypeDouble)
		{
			type = TypeDouble;
			ss << str[i];
		}
		// 'e' = notation scientifique, on verifie qu'il reste un signe ou chiffre apres
		else if (str[i] == 'e' && i < length - 1
			&& (str[i + 1] == '-'
				|| str[i + 1] == '+'
				|| std::isdigit(str[i + 1])))
		{
			ss << str[i] << str[i + 1]; // on pousse le 'e' ET le caractere suivant
			i++; // on saute pour pas re-traiter le signe a la prochaine iteration
			type = TypeDouble;
		}
		// 'f' tout a la fin et seulement si on est deja en double => c'est un float
		// le 'f' n'est PAS ajoute au stream car stringstream sait pas le lire
		else if (str[i] == 'f' && i == length - 1 && type == TypeDouble)
			type = TypeFloat;
		// autre non-chiffre => string invalide, on sort de la boucle
		else if (!std::isdigit(str[i]))
		{
			type = BadType;
			i = length; // force la sortie de la boucle
		}
		else
			ss << str[i]; // chiffre normal, on l'empile
	}
	// extraction : on lit le stream nettoye dans la bonne variable
	if (type == TypeFloat)
		ss >> fvalue;
	else if (type == TypeDouble)
		ss >> dvalue;
	else if (type == TypeInt)
	{
		// on lit d'abord en long (plus large que int) pour detecter l'overflow
		long lvalue;
		ss >> lvalue;
		ivalue = lvalue;
		// si ss.fail() ou la valeur depasse les bornes d'un int => impossible
		if (ss.fail()
			|| lvalue > std::numeric_limits<int>::max()
			|| lvalue < std::numeric_limits<int>::min())
			type = BadType;
	}
	// cas 5 : filet de rattrapage pour les pseudo-literals (nan/inf) que la boucle rejette
	else if (type == BadType)
	{
		if (str == "inff" || str == "-inff" || str == "+inff"
			|| str == "nanf")
		{
			fvalue = atof(str.c_str()); // atof (fonction C) sait lire "inf" et "nan"
			type = TypeFloat; // on promeut de BadType vers float pour la suite
		}
		else if (str == "inf" || str == "-inf" || str == "+inf"
				|| str == "nan")
		{
			dvalue = atof(str.c_str());
			type = TypeDouble;
		}
	}
	return (type);
}

// convert = la seule methode publique, elle orchestre tout (le sujet veut une methode statique)
void ScalarConverter::convert(std::string const &value)
{
	// les 4 variables servent de tagged union : detectType remplit que la bonne
	int		ivalue = 0;
	float	fvalue = 0;
	double	dvalue = 0;
	char	cvalue = 0;
	int		status[4] = {0, 0, 0, 0}; // flags par type, indexe par l'enum (status[TypeChar]...)

	// bitmasks : chaque flag est sur un bit different, combinables avec | et testables avec &
	static const int notPossible = 0x00000001;
	static const int notDisplayable = 0x00000010;

	int type = detectType(value, ivalue, fvalue, dvalue, cvalue); // parsing + type detecte

	if (type != BadType)
	{
		// Convert from detected type to all others
		// c'est ICI qu'on utilise static_cast : conversions numeriques propres (le cast cible de l'ex00)
		switch (type)
		{
		case TypeInt:
			fvalue = static_cast<float>(ivalue); // static_cast = conversion logique entre types lies
			dvalue = static_cast<double>(ivalue);
			cvalue = static_cast<char>(ivalue);
			break;
		case TypeFloat:
			ivalue = static_cast<int>(fvalue);
			dvalue = static_cast<double>(fvalue);
			cvalue = static_cast<char>(fvalue);
			// nan/inf ou hors bornes int => le int est impossible
			if (std::isnan(fvalue) || std::isinf(fvalue)
				|| fvalue > std::numeric_limits<int>::max()
				|| fvalue < std::numeric_limits<int>::min())
				status[TypeInt] |= notPossible; // on leve le flag avec |
			break;
		case TypeDouble:
			ivalue = static_cast<int>(dvalue);
			fvalue = static_cast<float>(dvalue);
			cvalue = static_cast<char>(dvalue);
			if (std::isnan(dvalue) || std::isinf(dvalue)
				|| dvalue > std::numeric_limits<int>::max()
				|| dvalue < std::numeric_limits<int>::min())
				status[TypeInt] |= notPossible;
			break;
		case TypeChar:
			ivalue = static_cast<int>(cvalue);
			fvalue = static_cast<float>(cvalue);
			dvalue = static_cast<double>(cvalue);
			break;
		}
		// si int impossible OU hors plage ASCII [0,127] => le char est impossible
		if ((status[TypeInt] & notPossible) || ivalue > 127 || ivalue < 0)
			status[TypeChar] |= notPossible;
		// char dans la plage mais pas imprimable (isprint) => Non displayable
		if (!(status[TypeChar] & notPossible) && !std::isprint(cvalue))
			status[TypeChar] |= notDisplayable;
	}
	else
	{
		// parsing rate => tout est impossible
		status[TypeInt] |= notPossible;
		status[TypeFloat] |= notPossible;
		status[TypeDouble] |= notPossible;
		status[TypeChar] |= notPossible;
	}

	// Print char (on teste les flags avec & avant d'afficher la valeur)
	if (status[TypeChar] & notPossible)
		std::cout << "char: impossible" << std::endl;
	else if (status[TypeChar] & notDisplayable)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << cvalue << "'" << std::endl;

	// Print int
	if (status[TypeInt] & notPossible)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << ivalue << std::endl;

	// Print float
	if (status[TypeFloat] & notPossible)
		std::cout << "float: impossible" << std::endl;
	else
	{
		// astuce : cout affiche "42f" et perd le ".0", on le rajoute a la main
		std::stringstream ss;
		ss << fvalue;
		std::string tmp = ss.str();
		bool isValue = !(std::isnan(fvalue) || std::isinf(fvalue)); // pas faire "nan.0f"
		if (isValue && tmp.find('.') == std::string::npos)
			std::cout << "float: " << fvalue << ".0f" << std::endl;
		else
			std::cout << "float: " << fvalue << "f" << std::endl;
	}

	// Print double (meme astuce du ".0" que pour le float)
	if (status[TypeDouble] & notPossible)
		std::cout << "double: impossible" << std::endl;
	else
	{
		std::stringstream ss;
		ss << dvalue;
		std::string tmp = ss.str();
		bool isValue = !(std::isnan(dvalue) || std::isinf(dvalue));
		if (isValue && tmp.find('.') == std::string::npos)
			std::cout << "double: " << dvalue << ".0" << std::endl;
		else
			std::cout << "double: " << dvalue << std::endl;
	}
}
