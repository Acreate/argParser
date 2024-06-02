#include "ArgParser.h"

using namespace cylStd;
/// <summary>
/// 向内存追加一个字符，如果 index 大于或者等于 maxLen，将会扩展内存，长度为 index + maxLen
///	追加过后，下标加 1 (++index)
///	新的大小重新赋值给 maxLen
/// </summary>
/// <param name="data_ptr">追加内存</param>
/// <param name="index">字符存放的下标位置</param>
/// <param name="maxLen">最大长度</param>
/// <param name="appendChar">追加字符</param>
/// <returns>存储指针，如果是重新分配内存，那么将会是新分配的指针，否则是原始指针</returns>
inline ArgParser::Char * appendChar( ArgParser::Char *data_ptr, size_t &index, size_t &maxLen, ArgParser::Char appendChar ) {
	if( index >= maxLen ) {
		auto newMaxLen = index + maxLen;
		ArgParser::Char *newBuffPtr = new ArgParser::Char[ newMaxLen ];
		memcpy( newBuffPtr, data_ptr, index );
		delete[] data_ptr;
		data_ptr = newBuffPtr;
	}
	data_ptr[ index ] = appendChar;
	++index;
	return data_ptr;
}

/// <summary>
/// 是否等于引号
/// </summary>
/// <param name="quotation">检测字符</param>
/// <returns>true 表示等于引号</returns>
inline bool isQuotation( ArgParser::Char quotation ) {
	return quotation == '\'' || quotation == '\"';
}

/// <summary>
/// 查找引号，查找位置必须存在引号( data_ptr[ index ])，从 index+1 位置开始查找，并且返回查找到的位置
/// </summary>
/// <param name="data_ptr">目标指针</param>
/// <param name="index">引号位置</param>
/// <param name="maxLen">最大长度</param>
/// <returns>最终位置，失败返回 index == maxLen</returns>
inline size_t findNextQuotation( ArgParser::Char *data_ptr, size_t index, size_t maxLen ) {
	ArgParser::Char quotation = data_ptr[ index ];
	if( isQuotation( quotation ) )
		for( ++index; index < maxLen; ++index )
			if( quotation == data_ptr[ index ] )
				break;
	return index;
}
bool ArgParser::parser( ) {
	auto data = allArgs.data( );
	size_t index = 0;
	size_t maxLen = allArgs.length( );
	decltype(allArgs)::value_type currentChar;
	size_t maxBuffLen = maxLen + 1;
	size_t indexBuff = 0;
	ArgParser::Char *dataBuff = new ArgParser::Char[ maxBuffLen ];
	int type = 0; // 0 为 选项， 1 为参数
	std::vector< String > values;
	String option;
	for( ; index < maxLen; ++index ) {
		currentChar = data[ index ];
		if( isspace( currentChar ) ) { // 如果是空格，那就是下一个字符串
			if( type == 0 ) {
				if( indexBuff ) {
					option = String( dataBuff, indexBuff );
					indexBuff = 0;
				}
			} else {
				if( indexBuff ) {
					values.emplace_back( String( dataBuff, indexBuff ) );
					indexBuff = 0;
				}
			}
			for( ++index; index < maxLen; ++index ) // 跳过所有 空格
				if( !isspace( data[ index ] ) )
					break;
			if( index == maxLen )
				break;
			currentChar = data[ index ]; // 赋值，等待追加到缓存
			type = 1;
		}
		if( currentChar == '-' ) { // 选项
			if( type == 1 ) {
				if( indexBuff ) {
					values.emplace_back( String( dataBuff, indexBuff ) );
					indexBuff = 0;
				}
				argParser.emplace( option, values );
				values.clear( );
			}
			type = 0;
			for( ++index; index < maxLen; ++index ) // 跳过所有 -
				if( data[ index ] != '-' )
					break;
			if( index == maxLen )
				break;
			currentChar = data[ index ]; // 赋值，等待追加到缓存

		}
		if( isQuotation( currentChar ) ) {
			size_t nextQuotationIndex = findNextQuotation( data, index, maxLen );
			while( nextQuotationIndex != maxLen && data[ nextQuotationIndex - 1 ] == '\\' )
				nextQuotationIndex = findNextQuotation( data, nextQuotationIndex, maxLen );
			if( nextQuotationIndex == maxLen )
				break;
			for( ; index < nextQuotationIndex; ++index )
				dataBuff = appendChar( dataBuff, indexBuff, maxBuffLen, data[ index ] );
			currentChar = data[ index ]; // 赋值，等待追加到缓存
		}
		dataBuff = appendChar( dataBuff, indexBuff, maxBuffLen, currentChar );
	}
	if( indexBuff ) {// 返回余热
		values.emplace_back( String( dataBuff, indexBuff ) );
		indexBuff = 0;
	}
	argParser.emplace( option, values );
	delete [ ] dataBuff;
	return true;
}

ArgParser::~ArgParser( ) { }
std::shared_ptr< ArgParser > ArgParser::parser( int argc, char *argv[ ] ) {
	std::shared_ptr< ArgParser > result( new ArgParser );
	for( int index = 1; index < argc; ++index )
		result->allArgs.append( argv[ index ] ).append( " " );
	result->argParser.emplace( "", std::vector< String >( { argv[ 0 ] } ) );
	if( result->parser( ) )
		return result;
	return nullptr;
}
std::shared_ptr< ArgParser > ArgParser::parser( const std::vector< String > &argvs ) {

	size_t size = argvs.size( );
	if( size == 0 )
		return nullptr;
	std::shared_ptr< ArgParser > result( new ArgParser );
	size_t index = 1;
	for( ; index < size; ++index )
		result->allArgs.append( argvs[ index ] ).append( " " );
	auto offsetPtr = argvs[ 0 ].data( );
	for( index = 0; offsetPtr[ index ] != '\0'; ++index )
		if( !isspace( offsetPtr[ index ] ) )
			break;
	if( offsetPtr[ index ] != '-' )
		result->argParser.emplace( "", std::vector< String >( { offsetPtr + index } ) ); // 存在 - ，表示第一个是选项
	else
		result->allArgs = String( offsetPtr + index ) + " " + result->allArgs; // 不存在 -。 表示第一个是运行程序
	if( result->parser( ) )
		return result;
	return nullptr;
}
std::shared_ptr< ArgParser > ArgParser::parser( const String &argvs ) {
	std::shared_ptr< ArgParser > result( new ArgParser );
	result->allArgs = argvs;
	if( result->parser( ) )
		return result;
	return nullptr;
}
std::vector< ArgParser::String > ArgParser::getOptionValues( const String &option_name ) {
	size_t buffSize = option_name.length( );
	auto optionNameIterator = option_name.begin( ), optionNameEnd = option_name.end( );
	for( ; optionNameIterator != optionNameEnd; ++optionNameIterator )
		if( *optionNameIterator != '-' )
			break;
		else
			--buffSize;

	Char *buff = new Char[ buffSize + 1 ];
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
