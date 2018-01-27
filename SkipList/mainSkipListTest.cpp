#include <iostream>
#include "SkipList.h"

int main()
{
	SkipList ls;
	ls.insert(10, 10);
	ls.insert(20, 20);
	ls.insert(30, 30);
	ls.insert(40, 40);
	ls.insert(25, 25);
	ls.printAllLevels();

	std::cout << ls.find(25)<<'\n';
	std::cout << ls.remove(25) << '\n';

	ls.printAllLevels();
	std::cout << '\n';

	ls.insert(5, 5);
	ls.printAllLevels();

	std::cout << '\n';
	ls.insert(45, 45);
	ls.printAllLevels();
	return 0;
}