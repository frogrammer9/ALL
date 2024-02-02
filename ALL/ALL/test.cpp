#include"all.hpp"

int main()
{
	//ALL_LOG.setFilePath("log.txt"); example
	ALL_LOG.setColors(ALL_DEFAULT, ALL_BLUE, ALL_DEFAULT, ALL_DEFAULT);
	std::string text = "test {0}";
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ALL_ENT("{0}, {0}, {i}, {o}, {x} {s}, {z}", 12, &text, "aa", 19, 556, vec, 18);
	ALL_INF(&text, 12);
	ALL_ENT(2, 3, 4, 5); 
	system("PAUSE");
	return 0;
}