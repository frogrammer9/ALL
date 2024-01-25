#include"all.hpp"
#include<ctime>

int main()
{
	ALL_LOG.setColors(ALL_DEFAULT, ALL_BLUE, ALL_DEFAULT, ALL_DEFAULT);

	ALL_ENT("test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 4, 5);
	ALL_INF("test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 4, 5);
	ALL_WAR("test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 4, 5);
	ALL_ERR("test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 4, 5);
	ALL_ENT("test {00}, {0}, { , {0}, { } haha {0}", 2, 3, 4, 5);


	system("PAUSE");
	return 0;
}