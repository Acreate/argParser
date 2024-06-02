#include "ArgParser.h"

using namespace cylStd;
ArgParser::ArgParser( int argc, char *argv[ ] ) {
	for( int index = 0; index < argc; ++index )
		argVar.emplace_back( argv[ index ] );
}
ArgParser::~ArgParser( ) { }
