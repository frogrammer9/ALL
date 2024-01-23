//NOLINTBEGIN
#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<fstream>

#define ALL_LOG all::Logger::GetInstance()
#if defined __DEBUG__ || __RELEASE__
	#if defined __COMPILER_GCC__ || __COMPILER_CLANG__ || __COMPILER_CLANG_CL__
		#define ALL_ENT(text, ...) all::Log.entry(text __VA_OPT__(,) __VA_ARGS__)
		#define ALL_INF(text, ...) all::Log.info(text __VA_OPT__(,) __VA_ARGS__)
		#define ALL_WAR(text, ...) all::Log.warning(text __VA_OPT__(,) __VA_ARGS__)
		#define ALL_ERR(text, ...) all::Log.error(text __VA_OPT__(,) __VA_ARGS__)
	#elif defined __COMPILER_CL__
		#define ALL_ENT(text, ...) all::Log.entry(text, ## __VA_ARGS__)
		#define ALL_INF(text, ...) all::Log.info(text, ## __VA_ARGS__)
		#define ALL_WAR(text, ...) all::Log.warning(text, ## __VA_ARGS__)
		#define ALL_ERR(text, ...) all::Log.error(text, ## __VA_ARGS__)
	#else
		#error Compiler not supported
	#endif
#else
	#if defined __COMPILER_GCC__ || __COMPILER_CLANG__ || __COMPILER_CLANG_CL__
		#define ALL_ERR(text, ...) all::Log.error(text __VA_OPT__(,) __VA_ARGS__)
	#elif defined __COMPILER_CL__
		#define ALL_ERR(text, ...) all::Log.error(text, ## __VA_ARGS__)
	#endif
#define ALL_ENT(...)
#define ALL_INF(...)
#define ALL_WAR(...)
#endif
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
#define ALL_PROGRAM_TIME	0
#define ALL_SYSTEM_TIME		1
#define ALL_DONT_SHOW		2
#define ALL_CONSOLE			0
#define ALL_FILE			1

namespace all
{
	class Logger
	{
		static Logger s_Log;
		clock_t m_time_start;
		uint32_t m_mode;
		std::string m_colEntry;
		std::string m_colInfo;
		std::string m_colWarning;
		std::string m_colError;
		int m_timeFormat;
		std::string m_filepath;
		std::ofstream m_outf;
		std::stringstream m_msg;
		bool findToken(const std::string& s, size_t* t1, size_t* t2)
		{
			*t1 = s.find('{'); *t2 = s.find('}');
			return (*t2 - *t1 == 2);
		}
		template<typename T>
		void processToken(char c, const T& arg)
		{
			if (c == '0') m_msg << arg;
			else if (c == 'x') m_msg << std::uppercase << std::hex << arg << std::nouppercase << std::dec;
			else if (c == 'o') m_msg << std::oct << arg << std::dec;
			//else if (c == 'i') m_msg << static_cast<int>(arg);
			else if (c == 's') m_msg << std::scientific << arg << std::defaultfloat;
		}
		void processToken(char c, const std::string& arg)
		{
			if (c == '0') m_msg << arg;
		}
		void processToken(char c, const char* arg)
		{
			if (c == '0') m_msg << arg;
		}

		void output(const std::string& text)
		{ m_msg << text << '\n'; }
		template<typename T>
		void output(const std::string& text, T&& arg)
		{
			size_t t1, t2;
			if (!findToken(text, &t1, &t2))
			{
				if (t1 == std::string::npos) { m_msg << text << '\n'; return; }
				m_msg << text.substr(0, t2 + 1);
				output(text.substr(t2 + 1), std::forward<T>(arg));
				return;
			}
			m_msg << text.substr(0, t1);
			processToken(text[t1 + 1], arg);
			m_msg << text.substr(t1 + 3) << '\n';
		}
		template<typename T, typename ...Types>
		void output(const std::string& text, T&& arg, Types&& ...args)
		{
			size_t t1, t2;
			if (!findToken(text, &t1, &t2))
			{
				if (t1 == std::string::npos) { m_msg << text << '\n'; return; }
				m_msg << text.substr(0, t2 + 1);
				output(text.substr(t2 + 1), std::forward<T>(arg), std::forward<Types>(args)...);
				return; 
			} 
			m_msg << text.substr(0, t1);
			processToken(text[t1 + 1], arg);
			output(text.substr(t1 + 3), std::forward<Types>(args)...);
		}

		void showtime();
		Logger() :m_time_start(std::clock()), m_mode(0), m_colEntry(ALL_WHITE), m_colInfo(ALL_GREEN), m_colWarning(ALL_YELLOW), m_colError(ALL_RED), m_timeFormat(0) {}
	public:
		Logger(const Logger&) = delete;
		~Logger();
		void settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, uint32_t logLocation);
		void setFile(const std::string& filePath) { m_filepath = filePath; }
		static Logger& GetInstance();
		template<typename ...Types>
		void entry(std::string message, Types&& ... args)
		{
			if (m_mode == ALL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colEntry; }
			showtime();
			m_msg << "[ENT] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == ALL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
		template<typename ...Types>
		void error(std::string message, Types&& ... args)
		{
			if (m_mode == ALL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colError; }
			showtime();
			m_msg << "[ERR] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == ALL_CONSOLE) { m_msg << "\033[0m"; std::cerr << m_msg.str(); }
		}
		template<typename ...Types>
		void info(std::string message, Types&& ... args)
		{
			if (m_mode == ALL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colInfo; }
			showtime();
			m_msg << "[INF] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == ALL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
		template<typename ...Types>
		void warning(std::string message, Types&& ... args)
		{
			if (m_mode == ALL_CONSOLE) { m_msg.str(std::string()); m_msg << m_colWarning; }
			showtime();
			m_msg << "[WAR] ";
			output(message, std::forward<Types>(args)...);
			if (m_mode == ALL_CONSOLE) { m_msg << "\033[0m"; std::cout << m_msg.str(); }
		}
	};
	extern all::Logger& Log;
}

all::Logger all::Logger::s_Log;
//NOLINTEND


//