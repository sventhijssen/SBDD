#pragma once

#include <string>
#include <vector>
#include <map>

class PLA;

class BoolFunction
{
public:
	std::vector<std::string> cubes_;

	bool isZero();
	bool isOne();
};

class UniData
{
public:
	UniData() {}

	void fromPLA(const PLA &pla);
	
	std::map<std::string, BoolFunction> functions() const { return functions_; }
	BoolFunction function(const std::string &fName);

	void show(std::ostream &stream);
	
private:
	std::map<std::string, BoolFunction> functions_;
};