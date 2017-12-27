#include <iostream>

#include "sbdd.h"
#include "pla.h"
#include "uniData.h"
#include "export.h"
#include "bf.h"

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
	std::string fileName = "export.txt";
	exportToFileSBDD(sbddG, fileName);
	fileName = "export.dot";
	exportToFileDOT(sbddG, fileName);

	BoolFormula bf;
	bf.setData("ex1.bf");
	bf.show(std::cout);

	return 0;
}