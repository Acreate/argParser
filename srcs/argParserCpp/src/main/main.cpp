#include <algorithm>
#include <iostream>
#include <locale>

#include "argParser/ArgParser.h"
int main( int argc, char *argv[ ] ) {
	std::locale locale( "zh_CN.UTF8" );
	std::locale::global( locale );
	std::wcout.imbue( locale );
	std::cout.imbue( locale );
	std::cout << u8"=====================" << std::endl;
	for( int index = 0; index < argc; ++index )
		std::cout << u8"参数 : " << argv[ index ] << std::endl;
	std::cout << u8"=====================" << std::endl;
	//    "args": [ "-l", "ads", "--c", "dddd" ]
	auto argParser = cylStd::ArgParser::parser( argc, argv );
	if( !argParser )
		return -1;
	auto optionValues = argParser->getOptionValues( "-l\t\n2" );
	auto map = argParser->getPairs( );
	auto it = map.begin( );
	auto end = map.end( );
	for( ; it != end; ++it ) {
		std::cout << u8"名称 : " << it->first << std::endl;
		for( auto &key : *it->second )
			std::cout << u8"\t值 : " << key << std::endl;
	}
	return 0;

}
