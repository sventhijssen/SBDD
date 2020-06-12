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
	pla.setData("sasao2001.pla");
	pla.show(std::cout);

	BoolFormula bf;
	bf.setData("sasao2001.bf");
	bf.show(std::cout);

	UniData uniData;
	//uniData.fromPLA(pla);
	uniData.fromBF(bf);
	uniData.show(std::cout);

	SBDD sbddG;
	sbddG.build(uniData);
	std::string fileName = "sasao2001.txt";
	exportToFileSBDD(sbddG, fileName);
	fileName = "sasao2001.dot";
	exportToFileDOT(sbddG, fileName);
	sbddG.out(std::cout);

	//BDD bdd = sbddG.bdd("A");
	//bdd.show(std::cout);

	//BDD bdd2 = sbddG.bdd("B");
	//bdd2.show(std::cout);

	//BDD res = bdd.apply(bdd2, OP::Xor);
	//res.setName("t");
	//res.show(std::cout);

	//sbddG.addBdd(res);
	//fileName = "exportWithRes.dot";
	//exportToFileDOT(sbddG, fileName);

	return 0;
}