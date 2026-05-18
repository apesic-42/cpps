
#include "Interpreter.hpp"

Interpreter::Interpreter(std::string const &value):
	str(value), type(BadType)
{
	for (int i = 0; i < 4; i++)
		this->status[i] = 0;
	this->parse();
	if (this->type != BadType)
	{
		this->convert();
		if (this->hasFlag(TypeInt, this->notPossible)
			|| this->ivalue > 127 || this->ivalue < 0)
			this->setFlag(TypeChar, this->notPossible);
		if (!std::isprint(this->cvalue))
			this->setFlag(TypeChar, this->notDisplayable);
	}
	else
	{
		this->setFlag(TypeInt, this->notPossible);
		this->setFlag(TypeFloat, this->notPossible);
		this->setFlag(TypeDouble, this->notPossible);
		this->setFlag(TypeChar, this->notPossible);
	}
}

Interpreter::Interpreter(Interpreter const &other):
	str(other.str), type(other.type),
	ivalue(other.ivalue), fvalue(other.fvalue),
	dvalue(other.dvalue), cvalue(other.cvalue)
{
	for (int i = 0; i < 4; i++)
		this->status[i] = other.status[i];
}

Interpreter::~Interpreter()
{
}

void Interpreter::parse(void)
{
	std::stringstream ss; // stream, we push value in it
	size_t length = this->str.length();
	size_t i = 0;

	if (length == 1 && !std::isdigit(this->str[0])) // case 0
	{
		this->type = TypeChar;
		this->cvalue = this->str[0];
		return ;
	}
	if (this->str[0] == '+' || this->str[0] == '-') // + or -
		ss << str[i++];
	this->type = TypeInt;
	for ( ; i < length; i++)
	{
		if (this->str[i] == '.' && this->type != TypeDouble)
		{
			this->type = TypeDouble;
			ss << str[i];
		}
		else if (this->str[i] == 'e' && i < length - 1  // scientific number ?
			&& (this->str[i + 1] == '-'
				|| this->str[i + 1] == '+'
				|| std::isdigit(this->str[i + 1])))
		{
			ss << str[i] << str[i + 1];
			i++;
			this->type = TypeDouble;
		}
		else if (this->str[i] == 'f' && i == length - 1 && this->type == TypeDouble) // float ?
			this->type = TypeFloat;
		else if (!std::isdigit(this->str[i])) // other than number ?
		{
			this->type = BadType;
			i = length;
		}
		else
			ss << str[i];
	}
	if (this->type == TypeFloat) // now push in the stream the value depending on the type
		ss >> this->fvalue;
	else if (this->type == TypeDouble)
		ss >> this->dvalue;
	else if (this->type == TypeInt)
	{
		long lvalue;
		ss >> lvalue;
		this->ivalue = lvalue;
		if (ss.fail()
			|| lvalue > std::numeric_limits<int>::max()
			|| lvalue < std::numeric_limits<int>::min())
			this->type = BadType;
	}
	else if (this->type == BadType)
	{
		if (this->str == "inff" || this->str == "-inff" || this->str == "+inff"
			|| this->str == "nanf") // special ieee 754 cases
		{
			this->fvalue = atof(this->str.c_str());
			this->type = TypeFloat;
		}
		else if (this->str == "inf" ||  this->str == "-inf" || this->str == "+inf"
				|| this->str == "nan")
		{
			this->dvalue = atof(this->str.c_str());
			this->type = TypeDouble;
		}
	}
}

void Interpreter::convert(void)
{
	switch (this->type)
	{
	case TypeInt:
		this->fromInt();
		break;
	case TypeFloat:
		this->fromFloat();
		break;
	case TypeDouble:
		this->fromDouble();
		break;
	case TypeChar:
		this->fromChar();
		break;
	}
}

void Interpreter::fromInt(void)
{
	this->fvalue = static_cast<float>(this->ivalue);
	this->dvalue = static_cast<double>(this->ivalue);
	this->cvalue = static_cast<char>(this->ivalue);
}

bool Interpreter::floatIsValue(void) const
{
	return (!(std::isnan(this->fvalue) || std::isinf(this->fvalue)));
}

bool Interpreter::doubleIsValue(void) const
{
	return (!(std::isnan(this->dvalue) || std::isinf(this->dvalue)));
}

void Interpreter::fromFloat(void)
{
	this->ivalue = static_cast<int>(this->fvalue);
	this->dvalue = static_cast<double>(this->fvalue);
	this->cvalue = static_cast<char>(this->fvalue);
	if (!this->floatIsValue()
		|| this->fvalue > std::numeric_limits<int>::max()
		|| this->fvalue < std::numeric_limits<int>::min())
		this->setFlag(TypeInt, this->notPossible);
}

void Interpreter::fromDouble(void)
{
	this->ivalue = static_cast<int>(this->dvalue);
	this->fvalue = static_cast<float>(this->dvalue);
	this->cvalue = static_cast<char>(this->dvalue);
	if (!this->doubleIsValue()
		|| this->dvalue > std::numeric_limits<int>::max()
		|| this->dvalue < std::numeric_limits<int>::min())
		this->setFlag(TypeInt, this->notPossible);
}

void Interpreter::fromChar(void)
{
	this->ivalue = static_cast<int>(this->cvalue);
	this->fvalue = static_cast<float>(this->cvalue);
	this->dvalue = static_cast<double>(this->cvalue);
}

void Interpreter::setFlag(int status, int flag)
{
	this->status[status] |= flag;
}

bool Interpreter::hasFlag(int status, int flag) const
{
	return (this->status[status] & flag);
}

Interpreter &Interpreter::operator=(Interpreter const &other)
{
	this->str = other.str;
	this->type = other.type;
	for (int i = 0; i < 4; i++)
		this->status[i] = other.status[i];
	this->ivalue = other.ivalue;
	this->fvalue = other.fvalue;
	this->dvalue = other.dvalue;
	this->cvalue = other.cvalue;
	return (*this);
}

int Interpreter::getAsInt(void) const
{
	return (this->ivalue);
}

float Interpreter::getAsFloat(void) const
{
	return (this->fvalue);
}

double Interpreter::getAsDouble(void) const
{
	return (this->dvalue);
}

char Interpreter::getAsChar(void) const
{
	return (this->cvalue);
}

std::string const &Interpreter::getRaw(void) const
{
	return (this->str);
}

std::ostream &operator<<(std::ostream &out, Interpreter const &pr)
{
	std::stringstream ss;
	std::string tmp;

	if (pr.hasFlag(0, Interpreter::notPossible))
		ss << "char: impossible" << '\n';
	else if (pr.hasFlag(0, Interpreter::notDisplayable))
		ss << "char: Non displayable" << '\n';
	else
		ss << "char: '" << pr.getAsChar() << "'\n";

	if (pr.hasFlag(1, Interpreter::notPossible))
		ss << "int: impossible" << '\n';
	else
		ss << "int: " << pr.getAsInt() << '\n';
	out << ss.str();
	ss.str(std::string());
	ss.clear();

	if (pr.hasFlag(2, Interpreter::notPossible))
		ss << "float: impossible" << '\n';
	else
	{
		ss << "float: " << pr.getAsFloat();
		tmp = ss.str();
		if (pr.floatIsValue() && tmp.find('.') == std::string::npos)
			ss << ".0";
		ss << "f\n";
	}
	out << ss.str();
	ss.str(std::string());
	ss.clear();

	if (pr.hasFlag(3,  Interpreter::notPossible))
		ss << "double: impossible";
	else
	{
		ss << "double: " << pr.getAsDouble();
		tmp = ss.str();
		if (pr.doubleIsValue() && tmp.find('.') == std::string::npos)
			ss << ".0";
	}
	out << ss.str() << std::endl;
	return (out);
}
