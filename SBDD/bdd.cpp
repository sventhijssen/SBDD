#include <string>

#include "bdd.h"

BDD::BDD(bool constant)
{
	nextNum_ = 2;
	TableStr tableStr;
	tableStr.index = tableStr.left = tableStr.right = -1;
	table_.insert(std::pair<int, TableStr>(constant ? 1 : 0, tableStr));
}

BDD::BDD(const BDD &bdd)
{
	table_ = bdd.table_;
	fName_ = bdd.fName_;
	fRoot_ = bdd.fRoot_;
	nextNum_ = bdd.nextNum_;
}

void BDD::show(std::ostream &stream)
{
	stream << "BDD:\n";
	stream << fName_ << ":\n";
	auto iter = table_.begin();
	auto end = table_.end();
	for (; iter != end; ++iter) {
		stream << iter->first << " -> " << iter->second.index << "   " << iter->second.left << "   " << iter->second.right << "\n";
	}
	stream << "\n";
}