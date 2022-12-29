#include "TypeAnalytics.hpp"

/***************************
 * constructor
 * *************************/

TypeAnalytics::TypeAnalytics( void )
{
	this->resetValues();
	std::cout << "TypeAnalytics Constructor() called. " << std::endl;
	return ;
}

TypeAnalytics::TypeAnalytics( char *arg )
{
	this->analyseNewInput( arg );
	std::cout << "TypeAnalytics Constructor( char *arg) called. " << std::endl;
	return ;
}

TypeAnalytics::TypeAnalytics( const TypeAnalytics &obj )
{
	std::cout << "TypeAnalytics Constructor( TypeAnalytics const &obj ) called. " << std::endl;
	*this = obj;
	return ;
}

TypeAnalytics::~TypeAnalytics( void )
{
	std::cout << "TypeAnalytics Destructor( void ) called. " << std::endl;
	return ;
}

TypeAnalytics &	TypeAnalytics::operator=( const TypeAnalytics &obj )
{
	std::cout << "Assignement operator for TypeAnalytics called" << std::endl;
	this->_selectedType = obj._selectedType;
	this->_charScalar = obj._charScalar;
	this->_intScalar = obj._intScalar;
	this->_floatScalar = obj._floatScalar;
	this->_doubleScalar = obj._doubleScalar;
	return *this;
}


void TypeAnalytics::analyseNewInput( char *arg )
{
	this->resetValues();
	if (arg[0] == 0)
		throw TypeAnalytics::EmptyInput();
	if (!this->getType( arg ))
		throw TypeAnalytics::CannotAnalyse();
	this->setVariable( arg );
}

void	TypeAnalytics::printTypes( void )
{
	if (this->_selectedType == TypeAnalytics::noType)
		std::cout << "No type set" << std::endl;
	this->printChar();
	this->printInt();
	this->printFloat();
	this->printDouble();
}

void	TypeAnalytics::resetValues( void )
{
	this->_selectedType = TypeAnalytics::noType;
	this->_charScalar = 0;
	this->_intScalar = 0;
	this->_floatScalar = 0;
	this->_doubleScalar = 0;
}

bool	TypeAnalytics::getType( char* input )
{
	this->_selectedType = handle_special_cases(input);
	if (this->_selectedType != TypeAnalytics::noType)
		return true;
	if ((input[0] >= '0' && input[0] <= '9') || input[0] == '-'
			|| input[0] == '.')
	{
		this->_selectedType = handle_numeric_values(input);
		if (this->_selectedType != TypeAnalytics::noType)
			return true;
	}
	if (input[1])
		return false;
	this->_selectedType = TypeAnalytics::charType;
	return true;
}

void	TypeAnalytics::setVariable( char *input )
{
	if (this->_selectedType == TypeAnalytics::charType)
	{
		std::cout << "Selected char type" << std::endl;
		this->_charScalar = input[0];
	}
	else if (this->_selectedType == TypeAnalytics::intType)
	{
		std::cout << "Selected int type" << std::endl;
		this->_intScalar = atoi(input);
	}
	else if (this->_selectedType == TypeAnalytics::floatType)
	{
		std::cout << "Selected float type" << std::endl;
		this->_floatScalar = atof(input);
	}
	else if (this->_selectedType == TypeAnalytics::doubleType)
	{
		std::cout << "Selected double type" << std::endl;
		this->_doubleScalar = atof(input);
	}
}

int		TypeAnalytics::handle_special_cases( char *input ) const
{
	const std::string	special_doubles[] =
	{
		"inf", "+inf", "-inf", "nan"
	};
	const std::string	special_floats[] =
	{
		"inff", "+inff", "-inff", "nanf"
	};

	for (int i = 0; i < 4; i++)
	{
		if (special_doubles[i] == input)
			return TypeAnalytics::doubleType;
		else if (special_floats[i] == input)
			return TypeAnalytics::floatType;
	}
	return TypeAnalytics::noType;
}

int		TypeAnalytics::handle_numeric_values( char *input ) const
{
	int	i = 0;
	int	dotCount = 0;

	if (input[0] == '-' && input[1])
		i++;
	if (input[i] == '.' && (input[i + 1] == 'f' || input[i + 1] == 0))
		return (TypeAnalytics::noType);
	while (input[i] == '.' || ft_isdigit(input[i]))
	{
		if (input[i] == '.')
			dotCount++;
		if (dotCount > 1)
			return TypeAnalytics::noType;
		i++;
	}
	if (!input[i])
	{
		if (dotCount == 1)
			return TypeAnalytics::doubleType;
		return TypeAnalytics::intType;
	}
	else if (input[i] == 'f' && !input[i + 1] && dotCount == 1)
		return TypeAnalytics::floatType;
	return TypeAnalytics::noType;
}


void	TypeAnalytics::printChar( void )
{
	if (this->_selectedType == TypeAnalytics::intType)
	{
		if (this->canConvertToChar(this->_intScalar))// displayableか
			std::cout << "char: '" << static_cast<char>(this->_intScalar) << "'"
				<< std::endl;
	}
	else if (this->_selectedType == TypeAnalytics::floatType)
	{
		if (this->canConvertToChar(this->_floatScalar))
			std::cout << "char: '" << static_cast<char>(this->_floatScalar) << "'"
				<< std::endl;
	}
	else if (this->_selectedType == TypeAnalytics::doubleType)
	{
		if (this->canConvertToChar(this->_doubleScalar))
			std::cout << "char: '" << static_cast<char>(this->_doubleScalar) << "'"
				<< std::endl;
	}
	else
		std::cout << "char: " << this->_charScalar << std::endl;
}

bool	TypeAnalytics::canConvertToChar( double number )
{
	if (number - static_cast<int>(number) != 0 || number > 127 || number < 0)
		std::cout << "char: impossible" << std::endl;
	else if (number <= 31 || number == 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		return true;
	return false;
}

void	TypeAnalytics::printInt( void )
{
	if (this->_selectedType == TypeAnalytics::charType)
		std::cout << "int: " << static_cast<int>(this->_charScalar)
			<< std::endl;
	else if (this->_selectedType == TypeAnalytics::intType)
		std::cout << "int: " << this->_intScalar << std::endl;
	else if (this->_selectedType == TypeAnalytics::floatType)
	{
		if (canConvertToInt(this->_floatScalar))
			std::cout << "int: " << static_cast<int>(this->_floatScalar)
				<< std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}
	else if (this->_selectedType == TypeAnalytics::doubleType)
	{
		if (canConvertToInt(this->_doubleScalar))
			std::cout << "int: " << static_cast<int>(this->_doubleScalar)
				<< std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}
}

void	TypeAnalytics::printFloat( void )
{
	if (this->_selectedType == TypeAnalytics::charType)
		std::cout << "float: " << static_cast<float>(this->_charScalar) << ".0f"
			<< std::endl;
	else if (this->_selectedType == TypeAnalytics::intType)
		std::cout << "float: " << static_cast<float>(this->_intScalar) << ".0f"
			<< std::endl;
	else if (this->_selectedType == TypeAnalytics::floatType)
		std::cout << "float: " << this->_floatScalar
			<< printDotZero(static_cast<float>(this->_floatScalar)) << "f"
			<< std::endl;
	else if (this->_selectedType == TypeAnalytics::doubleType)
	{
		if (canConvertToFloat(this->_doubleScalar))
			std::cout << "float: " << static_cast<float>(this->_doubleScalar)
				<< printDotZero(static_cast<float>(this->_doubleScalar)) << "f"
				<< std::endl;
		else
			std::cout << "float: impossible" << std::endl;
	}
}

void	TypeAnalytics::printDouble( void )
{
	if (this->_selectedType == TypeAnalytics::charType)
		std::cout << "double: " << static_cast<double>(this->_charScalar)
			 << ".0" << std::endl;
	else if (this->_selectedType == TypeAnalytics::intType)
		std::cout << "double: " << static_cast<double>(this->_intScalar)
			<< ".0" << std::endl;
	else if (this->_selectedType == TypeAnalytics::floatType)
		std::cout << "double: " << static_cast<double>(this->_floatScalar)
			<< printDotZero(static_cast<double>(this->_floatScalar))
			<< std::endl;
	else if (this->_selectedType == TypeAnalytics::doubleType)
		std::cout << "double: " << this->_doubleScalar
			<< printDotZero(static_cast<double>(this->_doubleScalar))
			<< std::endl;
}



/***************************
 * exception class functions
 * *************************/

const char* TypeAnalytics::EmptyInput::what() const throw()
{
	return ("Please enter an input to be analysed by the converter");
}

const char* TypeAnalytics::CannotAnalyse::what() const throw()
{
	return ("The input is not a valid char, int, float or double");
}