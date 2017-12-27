#include <iostream>

#include "sbdd.h"
#include "pla.h"
#include "uniData.h"
#include "export.h"
#include "bf.h"
#include "bdd.h"

int main()
{
	PLA pla;
	pla.setData("ex1.pla");
	pla.show(std::cout);

	BoolFormula bf;
	bf.setData("ex1.bf");
	bf.show(std::cout);

	UniData uniData;
	//uniData.fromPLA(pla);
	uniData.fromBF(bf);
	uniData.show(std::cout);

	SBDD sbddG;
	sbddG.build(uniData);
	std::string fileName = "export.txt";
	exportToFileSBDD(sbddG, fileName);
	fileName = "export.dot";
	exportToFileDOT(sbddG, fileName);
	sbddG.out(std::cout);

	BDD bdd = sbddG.bdd("A");
	bdd.show(std::cout);

	BDD bdd2 = sbddG.bdd("B");
	bdd2.show(std::cout);

	BDD res = bdd.apply(bdd2, OP::Xor);
	res.show(std::cout);

	return 0;
}