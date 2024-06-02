#include "ArgParser.h"

using namespace cylStd;
ArgParser::ArgParser( int argc, char *argv[ ] ) {
	for( int index = 0; index < argc; ++index )
		argVar.emplace_back( argv[ index ] );
}
ArgParser::~ArgParser( ) { }
std::vector<std::string> ArgParser::getOptionValues( const std::string &option_name ) {
	size_t buffSize = option_name.length( );
	auto optionNameIterator = option_name.begin( ), optionNameEnd = option_name.end( );
	for( ; optionNameIterator != optionNameEnd; ++optionNameIterator )
		if( *optionNameIterator != '-' )
			break;
		else
			--buffSize;

	std::string::value_type *buff = new std::string::value_type[ buffSize + 1 ];
	buffSize = 0;
	for( ; optionNameIterator != optionNameEnd; ++optionNameIterator, ++buffSize )
		if( std::isspace( *optionNameIterator ) || *optionNameIterator == '-' || *optionNameIterator == '\\' || *optionNameIterator == '/' || *optionNameIterator == '\'' || *optionNameIterator == '\"' )
			break;
		else
			buff[ buffSize ] = *optionNameIterator;
	buff[ buffSize ] = 0;

	auto iterator = argParser.begin( );
	auto end = argParser.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->first == buff ) {
			delete[] buff;
			return iterator->second;
		}
	delete[] buff;
	return { };
}
