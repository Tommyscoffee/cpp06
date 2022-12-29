#ifndef TYPEANALYTICS_HPP
#define TYPEANALYTICS_HPP

#include <iostream>
#include <stdexcept>
#include "utils.hpp"
class TypeAnalytics
{
	private:
		int		_selectedType;
		char	_charScalar;
		int		_intScalar;
		float	_floatScalar;
		double	_doubleScalar;

		void	resetValues( void );
		bool	getType( char *input );
		void	setVariable( char *input );
		int		handle_special_cases( char *input ) const;
		int		handle_numeric_values( char *input ) const;
		void	printChar( void );
		bool	canConvertToChar( double number );
		void	printInt( void );
		void	printFloat( void );
		void	printDouble( void );

		static const int noType = -1;
		static const int charType = 0;
		static const int intType = 1;
		static const int floatType = 2;
		static const int doubleType = 3;

	public:
		TypeAnalytics( void );
		TypeAnalytics( char *input );
		TypeAnalytics( const TypeAnalytics &obj );
		~TypeAnalytics( void );

		TypeAnalytics	&operator=( const TypeAnalytics &obj );

		void	analyseNewInput( char *input );
		void	printTypes( void );
		class EmptyInput : public std::exception
		{
			public:
				virtual const char* what() const throw();//throw()とは、この関数はこんな内容の例外を出しますよという指定。例外指定という。今回what()自身は例外を出さないので()
		};
		class CannotAnalyse : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif