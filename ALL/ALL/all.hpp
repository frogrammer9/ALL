#ifndef ALL
#define ALL

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<fstream>
#include<chrono>

#if defined __GNUC__ || __clang__
	#define ALL_ENT(text, ...) all::Logger::getInstance().entry(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_INF(text, ...) all::Logger::getInstance().info(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_WAR(text, ...) all::Logger::getInstance().warning(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_ERR(text, ...) all::Logger::getInstance().error(text __VA_OPT__(,) __VA_ARGS__)

	#define ALL_ENT(...) all::Logger::getInstance().entry(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_INF(...) all::Logger::getInstance().info(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_WAR(...) all::Logger::getInstance().warning(text __VA_OPT__(,) __VA_ARGS__)
	#define ALL_ERR(...) all::Logger::getInstance().error(text __VA_OPT__(,) __VA_ARGS__)
#elif defined _MSC_VER
	#define ALL_ENT(text, ...) all::Logger::getInstance().entry(text, ## __VA_ARGS__)
	#define ALL_INF(text, ...) all::Logger::getInstance().info(text, ## __VA_ARGS__)
	#define ALL_WAR(text, ...) all::Logger::getInstance().warning(text, ## __VA_ARGS__)
	#define ALL_ERR(text, ...) all::Logger::getInstance().error(text, ## __VA_ARGS__)
	
	#define ALL_ENT(...) all::Logger::getInstance().entry(## __VA_ARGS__)
	#define ALL_INF(...) all::Logger::getInstance().info(## __VA_ARGS__)
	#define ALL_WAR(...) all::Logger::getInstance().warning(## __VA_ARGS__)
	#define ALL_ERR(...) all::Logger::getInstance().error(## __VA_ARGS__)
#else
	#error Supported compiler has not beed defined
#endif





namespace all {
class Logger
{
public:
	~Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator = (const Logger&) = delete;

	static Logger& getInstance()
	{ static Logger s; return s; }

	  //===============================================================================
	  // string + variables
	  //===============================================================================
	template<typename ...Types>
	void entry(std::string message, Types&& ... args)
	{

	}
	template<typename ...Types>
	void info(std::string message, Types&& ... args)
	{

	}
	template<typename ...Types>
	void warning(std::string message, Types&& ... args)
	{

	}
	template<typename ...Types>
	void error(std::string message, Types&& ... args)
	{

	}
	//===============================================================================
	// variables only
	//===============================================================================
	template<typename ...Types>
	void entry(Types&& ... args)
	{

	}
	template<typename ...Types>
	void info(Types&& ... args)
	{

	}
	template<typename ...Types>
	void warning(Types&& ... args)
	{

	}
	template<typename ...Types>
	void error(Types&& ... args)
	{

	}


private:
	Logger() {}

};
}
#endif