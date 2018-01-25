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

	std::cout << ls.find(25)<<'\n';
	std::cout << ls.remove(25) << '\n';
	ls.printAllLevels();
	return 0;
}