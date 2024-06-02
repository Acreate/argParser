#ifndef ARGPARSER_H_H_HEAD__FILE__
#define ARGPARSER_H_H_HEAD__FILE__
#pragma once
#include <string>
#include <unordered_map>
#include "../namespace/cylStd.h"
#include <vector>
namespace cylStd {
	class ARGPARSER_EXPORT ArgParser {
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
		std::vector< std::string > getOptionValues( const std::string &option_name );
	};
}


#endif // ARGPARSER_H_H_HEAD__FILE__
