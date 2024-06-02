#include <algorithm>
#include <iostream>
#include <locale>

#include "argParser/ArgParser.h"
int main( int argc, char *argv[ ] ) {
	std::locale locale( "zh_CN.UTF8" );
	std::locale::global( locale );
	std::wcout.imbue( locale );
	std::cout.imbue( locale );

	cylStd::ArgParser argParser( argc, argv );

	auto optionValues = argParser.getOptionValues( "-l\t\n2" );
	return 0;

}
