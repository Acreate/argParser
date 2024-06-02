#ifndef ARGPARSER_H_H_HEAD__FILE__
#define ARGPARSER_H_H_HEAD__FILE__
#pragma once
#include <string>
#include <unordered_map>
#include "../namespace/cylStd.h"
#include <vector>
namespace cylStd {
	class ArgParser {
		size_t argCount; // 参数个数
		std::vector< std::string > argVar; // 参数列表
		std::unordered_map< std::string, std::vector< std::string > > argParser;
	public:
		ArgParser( int argc, char *argv[ ] );
		virtual ~ArgParser( );
		/// <summary>
		/// 获取解析选项个数
		/// </summary>
		/// <returns>选项个数</returns>
		size_t optionCoun( ) const {
			return argParser.size( );
		}
		/// <summary>
		/// 获取选项值列表
		/// </summary>
		/// <param name="option_name">选项名称</param>
		/// <returns>值列表，失败返回 空列表</returns>
		std::vector< std::string > getOptionValues( const std::string &option_name ) {
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
	};
}


#endif // ARGPARSER_H_H_HEAD__FILE__
