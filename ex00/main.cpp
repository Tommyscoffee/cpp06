#include "TypeAnalytics.hpp"
#include "utils.hpp"

int	main( int argc, char **argv )
{
	TypeAnalytics TypeAnalytics;

	try
	{
		if (argc == 1)
			throw (TypeAnalytics::EmptyInput());
		for (int i = 1; i < argc; i++)
		{
			TypeAnalytics.analyseNewInput(argv[i]);
			TypeAnalytics.printTypes();
			if (i + 1 < argc)
				std::cout << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		print_help();
	}
}