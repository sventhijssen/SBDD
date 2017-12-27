#pragma once

#include <vector>
#include <map>
#include <string>

std::vector<std::string> split(const std::string &line, char sym);

class DNF
{
public:
	std::vector<std::vector<std::string>> dnf_;
};

class BoolFormula
{
public:
	BoolFormula() { numVar_ = 0; }

	bool setData(const std::string &fileName);
	void show(std::ostream &stream);
	std::map<std::string, int> variables() const { return variables_; }
	std::map<std::string, DNF> functions() const { return functions_; }

private:
	void BoolFormula::formulaToDNF(const std::string &nameF, std::string &formul);

private:
	std::map<std::string, int> variables_;
	std::map<std::string, DNF> functions_;
	int numVar_;
};