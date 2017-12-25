#include <iostream>

#include "sbdd.h"
#include "pla.h"

int main()
{
	PLA pla;
	pla.setData("ex1.pla");
	pla.show(std::cout);

	return 0;
}