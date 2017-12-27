#pragma once

#include <map>
#include <vector>

#include "TableStr.h"

class SBDD;

class BDD
{
	friend SBDD;
public:
	// Если constant = false, то будет создан SBDD = 0, иначе 1.
	BDD(bool constant = false);
	BDD(const BDD &bdd);

	void show(std::ostream &stream);

private:
	std::map<int, TableStr> table_;
	std::string fName_;
	int fRoot_;
	int nextNum_;
};