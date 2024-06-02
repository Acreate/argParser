#ifndef ARGPARSER_H_H_HEAD__FILE__
#define ARGPARSER_H_H_HEAD__FILE__
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "../namespace/cylStd.h"
#include <vector>
namespace cylStd {
	class ARGPARSER_EXPORT ArgParser {
	public:
		using String = std::string;
		using Char = String::value_type;
	private:
		std::string allArgs; // 参数列表
		std::unordered_map< String, std::vector< String > > argParser; // 参数映射
		ArgParser( ) { }
	private: // 私有函数
		/// <summary>
		/// 对私有成员 allArgs 进行解析
		/// </summary>
		bool parser( );
	public:
		virtual ~ArgParser( );
	public: // - 静态构造函数
		/// <summary>
		/// 解析参数
		/// </summary>
		/// <param name="argc">参数个数</param>
		/// <param name="argv">参数列表</param>
		static std::shared_ptr< ArgParser > parser( int argc, char *argv[ ] );
		/// <summary>
		/// 解析参数
		/// </summary>
		/// <param name="argvs">参数列表</param>
		static std::shared_ptr< ArgParser > parser( const std::vector< String > &argvs );
		/// <summary>
		/// 解析参数
		/// </summary>
		/// <param name="argvs">参数列表</param>
		static std::shared_ptr< ArgParser > parser( const String &argvs );
	public: //- 成员函数
		/// <summary>
		/// 获取解析选项个数
		/// </summary>
		/// <returns>选项个数</returns>
		size_t optionCoun( ) const {
			return argParser.size( );
		}
		/// <summary>
		/// 获取所有选项
		/// </summary>
		/// <returns>选项列表</returns>
		std::vector< String > getKeys( ) const {
			std::vector< String > result;
			for( auto it = argParser.begin( ), en = argParser.begin( ); it != en; ++it )
				result.emplace_back( it->first );
			return result;
		}
		/// <summary>
		/// 获取映射列表
		/// </summary>
		/// <returns>映射列表</returns>
		std::unordered_map< String, std::vector< String > > getPairs( ) const {
			return argParser;
		}
		/// <summary>
		/// 获取选项值列表
		/// </summary>
		/// <param name="option_name">选项名称</param>
		/// <returns>值列表，失败返回 空列表</returns>
		std::vector< String > getOptionValues( const String &option_name );
	};
}


#endif // ARGPARSER_H_H_HEAD__FILE__
