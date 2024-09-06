#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Level.h"
#include "OrthogonalList.h"
#include <iostream>

int main()
{
	int f[5] = { 0,1,2,3,4 };

	OrthogonalList list(8);
	list.print();

	return 0;
}