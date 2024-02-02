#include"all.hpp" //this library is header only, you simply need to include it

/*
it includes the following headers
<iostream>
<sstream>
<fstream>
<chrono>
<vector>
<mutex>
*/


int main()
{
	//ALL_LOG; this logger is not initalized until it is being used so the time used in logger may be incorrect when it is first called later in the program, to correct it you simply need to call this

	//ALL_LOG.setFilePath("log.txt"); example (once this funcion is called the logger will log to a file instead of the console)
	ALL_LOG.setColors(ALL_DEFAULT, ALL_DEFAULT, ALL_DEFAULT, ALL_DEFAULT);
	ALL_ENT("value: {0}, in hex: {x}", 123, 123);
	ALL_INF(1, 2, 3, 4);
	ALL_WAR("{0}, {u}", 12, "abc");
	int a = 12;
	ALL_ERR("{0}, {0}", a, &a);

	/*
	 Available tokens:
	 numbers:
	 0 - default output
	 o - output in base8
	 x - output in base16
	 s - output in scientific notation
	 
	 strings:
	 0 - default output
	 
	 vectors:
	 0 - default output (not indexed in a single line)
	 i - indexed in a single line
	 s - not indexed one under the other
	 l - indexed one unther the other
	 
	 other tokens and ways to format you output will come may come in the future
	*/

	return 0;
}