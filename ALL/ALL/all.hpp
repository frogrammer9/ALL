#ifndef ALL
#define ALL

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<fstream>
#include<chrono>

#if defined __GNUC__ || __clang__
	#ifndef ALL_DISABLE_ENT
		#define ALL_ENT(first, ...) all::Logger::getInstance().log(0, first, __VA_OPT__(,) __VA_ARGS__)
	#else
		#define ALL_ENT(...)
	#endif
	#ifndef ALL_DISABLE_INF
		#define ALL_INF(first, ...) all::Logger::getInstance().log(1, first, __VA_OPT__(,) __VA_ARGS__)
	#else
		#define ALL_INF(...)
	#endif
	#ifndef ALL_DISABLE_WAR
		#define ALL_WAR(first, ...) all::Logger::getInstance().log(2, first, __VA_OPT__(,) __VA_ARGS__)
	#else
		#define ALL_WAR(...)
	#endif
	#ifndef ALL_DISABLE_ERR
		#define ALL_ERR(first, ...) all::Logger::getInstance().log(3, first, __VA_OPT__(,) __VA_ARGS__)
	#else
		#define ALL_ERR(...)
	#endif
#elif defined _MSC_VER
	#ifndef ALL_DISABLE_ENT
		#define ALL_ENT(first, ...) all::Logger::getInstance().log(0, first, ## __VA_ARGS__)
	#else
		#define ALL_ENT(...)
	#endif
	#ifndef ALL_DISABLE_INF
		#define ALL_INF(first, ...) all::Logger::getInstance().log(1, first, ## __VA_ARGS__)
	#else
		#define ALL_INF(...)
	#endif
	#ifndef ALL_DISABLE_WAR
		#define ALL_WAR(first, ...) all::Logger::getInstance().log(2, first, ## __VA_ARGS__)
	#else
		#define ALL_WAR(...)
	#endif
	#ifndef ALL_DISABLE_ERR
		#define ALL_ERR(first, ...) all::Logger::getInstance().log(3, first, ## __VA_ARGS__)
	#else
		#define ALL_ERR(...)
	#endif
#else
	#error This library only supports MSVC, Clang and GNU
#endif

#define ALL_LOG all::Logger::getInstance()

#define ALL_BLACK			"\033[0;30m"
#define ALL_DARK_GRAY		"\033[1;30m"
#define ALL_BLUE			"\033[0;34m"
#define ALL_LIGHT_BLUE		"\033[1;34m"
#define ALL_GREEN			"\033[0;32m"
#define ALL_LIGHT_GREEN		"\033[1;32m"
#define ALL_CYAN			"\033[0;36m"
#define ALL_LIGHT_CYAN		"\033[1;36m"
#define ALL_RED				"\033[0;31m"
#define ALL_LIGHT_RED		"\033[1;31m"
#define ALL_PURPLE			"\033[0;35m"
#define ALL_LIGHT_PURPLE	"\033[1;35m"
#define ALL_BROWN			"\033[0;33m"
#define ALL_YELLOW			"\033[1;33m"
#define ALL_LIGHT_GRAY		"\033[0;37m"
#define ALL_WHITE			"\033[1;37m"
#define ALL_DEFAULT			"\0"

typedef std::string all_Color;

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
	template<typename T, typename ...Types>
	void log(uint8_t mode, T first, Types&& ... args)
	{
		m_msg = std::stringstream();
		m_msg << m_colors[mode];
		m_msg << getTime() << m_type[mode];
		output(first, args...);
		m_msg << "\033[0m"; std::cout << m_msg.str() << "\n";
	}
	//===============================================================================
	// settings
	//===============================================================================
	void setColors(all_Color entryColor, all_Color infoColor, all_Color warningColor, all_Color errorColor)
	{
		m_colors[0] = (entryColor == "\0") ? ALL_WHITE : entryColor;
		m_colors[1] = (infoColor == "\0") ? ALL_GREEN : infoColor;
		m_colors[2] = (warningColor == "\0") ? ALL_YELLOW : warningColor;
		m_colors[3] = (errorColor == "\0") ? ALL_RED : errorColor;
	}
private:
	Logger() :m_timeStart(std::chrono::high_resolution_clock::now()) {}
	const std::chrono::steady_clock::time_point m_timeStart;
	const std::string m_type[4] = { "[ENT] ", "[INF] ", "[WAR] ", "[ERR] "};
	std::string m_colors[4] = { ALL_WHITE, ALL_GREEN, ALL_YELLOW, ALL_RED};
	std::stringstream m_msg;

	std::string getTime()
	{
		int time = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_timeStart).count());
		int hours = time / 3600;
		int minutes = (time - hours*3600) / 60;
		int seconds = time - hours *3600 - minutes * 60;
		std::stringstream result;
		result << "[" << std::setfill('0') << std::setw(2) << std::to_string(hours) << ":" << std::setw(2) << std::to_string(minutes) << ":" << std::setw(2) << std::to_string(seconds) << "]";
		return result.str();
	}
	//===============================================================================
	// recursive output
	//===============================================================================
	template<typename T>
	void output(T arg)
	{ m_msg << arg; }
	template<typename T, typename ...Types>
	void output(const char* t, T&& arg, Types&& ...args)			//TODO Rethink and improve these two funcions. It works for now but it is disgusting!!!
	{
		const std::string text(t);
		const size_t tlc0 = text.find("{");
		const size_t tlc1 = text.find("}");
		if (tlc0 == std::string::npos) { m_msg << text; }
		else if (tlc1 - tlc0 != 2)
		{
			m_msg << text.substr(0, tlc1 + 1);
			output(text.substr(tlc1 + 2), arg, args...);
		}
		else
		{
			m_msg << text.substr(0, tlc0);
			proccesToken(text[tlc0 + 1], arg);
			output(text.substr(tlc0 + 3), args...);
		}
	}
	template<typename T, typename ...Types>
	void output(std::string text, T&& arg, Types&& ...args)			//TODO Rethink and improve these two funcions. It works for now but it is disgusting!!!
	{
		const size_t tlc0 = text.find("{");
		const size_t tlc1 = text.find("}");
		if (tlc0 == std::string::npos) { m_msg << text; }
		else if (tlc1 - tlc0 != 2)
		{
			m_msg << text.substr(0, tlc1 + 1);
			output(text.substr(tlc1 + 2), arg, args...);
		}
		else
		{
			m_msg << text.substr(0, tlc0);
			proccesToken(text[tlc0 + 1], arg);
			output(text.substr(tlc0 + 3), args...);
		}
	}
	template<typename T, typename ...Types>
	void output(T&& arg, Types&& ...args)
	{
		m_msg << arg << ", ";
		output(args...);
	}
	//===============================================================================
	// tokens processing
	//===============================================================================
	template<typename T>
	void proccesToken(char token, T arg)
	{
		m_msg << arg;
	}

};
}
#endif