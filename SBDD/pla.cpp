#include <fstream>
#include <ostream>

#include "pla.h"

bool PLA::setData(const std::string &fileName)
{
	// TODO: ChernyshovSV - здесь необходимо унифицировать парсинг, для возможности работы с любыми pla или почти с любыми.
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		clear();
		return false;
	}
	std::string word;
	
	if (file.eof()) {
		clear();
		return false;
	}
	file >> word;
	size_t size = 0;
	while (word[0] == '.') {
		if (word == ".i") {
			file >> i_;
			file >> word;
		}
		if (word == ".o") {
			file >> o_;
			file >> word;
		}
		if (word == ".p") {
			file >> p_;
			file >> word;
		}
		if (file.eof()) {
			clear();
			return false;
		}
	}
	int i = 0;
	while (word != ".e" && i < p_) {
		StrPLA str;
		str.input = word;
		if (file.eof()) {
			clear();
			return false;
		}
		file >> word;
		str.output = word;
		if (file.eof()) {
			clear();
			return false;
		}
		file >> word;
		cubes_.push_back(str);
		++i;
	}
	file.close();
	return true;
}

void PLA::show(std::ostream &stream)
{
	stream << "PLA:\n";
	stream << ".p " << p_ << "\n";
	stream << ".i " << i_ << "\n";
	stream << ".o " << o_ << "\n\n";
	
	auto iter = cubes_.begin();
	auto end = cubes_.end();
	for (; iter != end; ++iter) {
		stream << iter->input << " " << iter->output << "\n";
	}

	stream << ".e\n\n";
}