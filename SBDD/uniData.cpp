#include <string>
#include <iostream>

#include "uniData.h"
#include "pla.h"
#include "bf.h"

bool BoolFunction::isZero()
{
	return cubes_.empty();
}

bool BoolFunction::isOne()
{
	if (cubes_.empty()) {
		return false;
	}
	else {
		size_t size = cubes_[0].size();
		std::string cube(size, '-');
		int numC = cubes_.size();
		for (int i = 0; i < numC; ++i) {
			if (cube == cubes_[i]) {
				return true;
			}
		}
	}
	return false;
}

void UniData::fromPLA(const PLA &pla)
{
	functions_.clear();
	// TODO: ChernyshovSV - ���� ����� ����� ������������� ���� ������� (1,2,3,...), ����� �������� �� �������� �����.
	std::vector<StrPLA> cubes = pla.cubes();
	int nFun = pla.o();
	int p = pla.p();
	for (int i = 0; i < nFun; ++i) {
		BoolFunction function;
		for (int j = 0; j < p; ++j) {
			if (cubes[j].output[i] == '1') {
				function.cubes_.push_back(cubes[j].input);
			}
		}
		functions_.insert(std::pair<std::string, BoolFunction>(pla.funs()[i] , function));
	}
	vars_ = pla.vars();
}

void UniData::fromBF(const BoolFormula &bf)
{
	std::map<std::string, int> variables = bf.variables();
	std::map<std::string, DNF> functions = bf.functions();
	functions_.clear();
	vars_.clear();

	auto iter = functions.begin();
	auto end = functions.end();
	for (; iter != end; ++iter) {
		BoolFunction function;
		if (iter->second.dnf_[0][0] == "1") {
			function.cubes_.push_back(std::string(variables.size(), '-'));
			functions_.insert(std::pair<std::string, BoolFunction>(iter->first, function));
			continue;
		}
		if (iter->second.dnf_[0][0] == "0") {
			functions_.insert(std::pair<std::string, BoolFunction>(iter->first, function));
			continue;
		}
		DNF dnf = iter->second;
		size_t sizeC = dnf.dnf_.size();
		for (size_t i = 0; i < sizeC; ++i) {
			std::string cube(variables.size(), '-');
			std::vector<std::string> con = dnf.dnf_[i];
			size_t sizeV = con.size();
			for (size_t j = 0; j < sizeV; ++j) {
				if (con[j][0] == '!') {
					cube[variables[con[j].substr(1, con[j].size() - 1)]] = '0';
				}
				else {
					cube[variables[con[j]]] = '1';
				}
			}
			function.cubes_.push_back(cube);
		}
		functions_.insert(std::pair<std::string, BoolFunction>(iter->first, function));
	}
	vars_ = std::vector<std::string>(variables.size());
	auto iterV = variables.begin();
	auto endV = variables.end();
	for (; iterV != endV; ++iterV) {
		vars_[iterV->second] = iterV->first;
	}
}

BoolFunction UniData::function(const std::string &fName)
{
	if (functions_.count(fName)) {
		return functions_[fName];
	}
	return BoolFunction();
}

void UniData::show(std::ostream &stream)
{
	stream << "UniData:\n";
	auto iter = functions_.begin();
	auto end = functions_.end();
	for (; iter != end; ++iter) {
		stream << "\n";
		stream << iter->first << "\n";
		BoolFunction function = iter->second;
		size_t size = function.cubes_.size();
		for (size_t i = 0; i < size; ++i) {
			stream << function.cubes_[i] << "\n";
		}
	}
	stream << "\n";
}