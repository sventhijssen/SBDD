#include <iostream>

#include "sbdd.h"
#include "pla.h"
#include "uniData.h"

int main()
{
	PLA pla;
	pla.setData("ex1.pla");
	pla.show(std::cout);

	UniData uniData;
	uniData.fromPLA(pla);
	uniData.show(std::cout);

	sbdd::SBDD sbddG;
	sbddG.build(uniData);
	sbddG.out(std::cout);

	return 0;
}