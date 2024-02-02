#include"all.hpp"

int main()
{
	//ALL_LOG.setFilePath("log.txt"); example
	ALL_LOG.setColors(ALL_DEFAULT, ALL_BLUE, ALL_DEFAULT, ALL_DEFAULT);
	std::string text = "test {0}";
	std::cout << &text << "\n";
	ALL_ENT("{0}, {0}, {i}, {o}, {x} { }, {z}", 12, &text, "aa", 19, 556, 18, 18);
	ALL_INF(&text, 12);
	ALL_ENT(2, 3, 4, 5);

	all::Logger::getInstance().log(all::Logger::logMode::ent, 1);
	std::cout << 1;

	system("PAUSE");
	return 0;
}