#include"all.hpp"
#include<ctime>



int main()
{
	//ALL_LOG.setFilePath("log.txt"); example
	ALL_LOG.setColors(ALL_DEFAULT, ALL_BLUE, ALL_DEFAULT, ALL_DEFAULT);
	std::string text = "test {0}";
	ALL_ENT(12, 69, "test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 5, 6, 7, 8);
	ALL_INF(text, 12);
	ALL_ENT(2, 3, 4, 5);

	system("PAUSE");
	return 0;
}