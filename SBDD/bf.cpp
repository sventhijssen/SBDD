#include <fstream>

#include "bf.h"

std::vector<std::string> split(const std::string &line, char sym)
{
	std::vector<std::string> result;
	size_t size = line.size();
	std::string var;
	for (size_t i = 0; i < size; ++i) {
		if (line[i] == sym) {
			result.push_back(var);
			var = "";
		}
		else
		{
			var.push_back(line[i]);
		}
	}
	result.push_back(var);
	return result;
}

bool BoolFormula::setData(const std::string &fileName)
{
	variables_.clear();
	functions_.clear();
	numVar_ = 0;

	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		return false;
	}
	std::string word;

	while (!file.eof()) {
		file >> word;
		std::vector<std::string> function = split(word, '=');
		formulaToDNF(function[0], function[1]);
	}

	file.close();
	return true;
}

void BoolFormula::show(std::ostream &stream)
{
	stream << "BF:\n";
	stream << "Indexes of variables:\n";
	auto iter = variables_.begin();
	auto end = variables_.end();
	for (; iter != end; ++iter) {
		stream << iter->first << " -> " << iter->second << "\n";
	}
	stream << "\n";

	auto iterF = functions_.begin();
	auto endF = functions_.end();
	for (; iterF != endF; ++iterF) {
		stream << iterF->first << ":\n";
		DNF dnf = iterF->second;
		size_t sizeC = dnf.dnf_.size();
		for (size_t i = 0; i < sizeC; ++i) {
			size_t sizeV = dnf.dnf_[i].size();
			for (size_t j = 0; j < sizeV; ++j) {
				stream << dnf.dnf_[i][j];
				if (j != sizeV - 1) {
					stream << "*";
				}
			}
			if (i != sizeC - 1) {
				stream << "+";
			}
		}
		stream << "\n";
	}
	stream << "\n";
}

void BoolFormula::formulaToDNF(const std::string &nameF, std::string &formul)
{
	DNF dnf;
	std::vector<std::string> cons = split(formul, '+');
	size_t size = cons.size();
	for (size_t i = 0; i < size; ++i) {
		std::vector<std::string> invVars = split(cons[i], '*');
		dnf.dnf_.push_back(std::vector<std::string>());
		size_t rang = invVars.size();
		for (size_t j = 0; j < rang; ++j) {
			std::string var;
			if (invVars[j][0] == '!') {
				var = invVars[j].substr(1, invVars[j].size() - 1);
			}
			else {
				var = invVars[j];
			}
			if (!variables_.count(var)) {
				variables_.insert(std::pair<std::string, int>(var, numVar_));
				numVar_++;
			}
			dnf.dnf_[i].push_back(invVars[j]);
		}
	}
	functions_.insert(std::pair<std::string, DNF>(nameF, dnf));
}