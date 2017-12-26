#include "sbdd.h"

namespace sbdd {

	SBDD::SBDD(bool constant)
	{
		nextNum_ = 2;
		TableStr tableStr;
		tableStr.index = tableStr.left = tableStr.right = -1;
		table_.insert(std::pair<int, TableStr>(constant ? 1 : 0, tableStr));
	}

	SBDD::SBDD(const SBDD &sbdd)
	{
		nextNum_ = sbdd.nextNum_;
		table_ = sbdd.table_;
	}

	bool SBDD::member(const TableStr &tableStr)
	{
		auto iter = table_.begin();
		auto end = table_.end();
		for (; iter != end; ++iter) {
			if (iter->second == tableStr) {
				return true;
			}
		}
		return false;
	}

	int SBDD::lookup(const TableStr &tableStr)
	{
		auto iter = table_.begin();
		auto end = table_.end();
		for (; iter != end; ++iter) {
			if (iter->second == tableStr) {
				return iter->first;
			}
		}
		return -1;
	}

	int SBDD::insert(const TableStr &tableStr)
	{
		table_.insert(std::pair<int, TableStr>(nextNum_, tableStr));
		nextNum_++;
		return nextNum_ - 1;
	}

	int SBDD::makeNode(int index, int left, int right)
	{
		if (left == right) {
			return left;
		}
		else {
			int res = -1;
			res = lookup(TableStr(index, left, right));
			if (res != -1) {
				return res;
			}
			else
			{
				return insert(TableStr(index, left, right));
			}
		}
	}

	void SBDD::build(const UniData &data)
	{
		table_.clear();
		fNames_.clear();
		fRoot_.clear();
		nextNum_ = 2;
		TableStr tableStr;
		tableStr.index = tableStr.left = tableStr.right = -1;
		table_.insert(std::pair<int, TableStr>(0, tableStr));
		table_.insert(std::pair<int, TableStr>(1, tableStr));

		std::map<std::string, BoolFunction> functions = data.functions();
		auto iter = functions.begin();
		auto end = functions.end();
		for (; iter != end; ++iter) {
			fNames_.push_back(iter->first);
			buildFunctionPrivate(iter->second);
		}
	}

	void SBDD::buildFunctionPrivate(const BoolFunction &function)
	{
		int res = buildPrivate(function, 0);
		fRoot_.push_back(res);
	}

	int SBDD::buildPrivate(BoolFunction function, int index)
	{
		if (static_cast<size_t>(index) >= function.cubes_[0].size()) {
			if (function.cubes_.empty()) {
				return 0;
			}
			else {
				return 1;
			}
		}
		else {
			bool b0 = false;
			bool b1 = false;
			BoolFunction f0 = setZero(function, index);
			BoolFunction f1 = setOne(function, index);
			int v0 = -1;
			int v1 = -1;
			if (f0.isOne()) {
				v0 = 1;
				b0 = true;
			}
			if (f0.isZero()) {
				v0 = 0;
				b0 = true;
			}
			if (f1.isOne()) {
				v1 = 1;
				b1 = true;
			}
			if (f1.isZero()) {
				v1 = 0;
				b1 = true;
			}
			if (!b0) {
				v0 = buildPrivate(setZero(function, index), index + 1);
			}
			if (!b1) {
				v1 = buildPrivate(setOne(function, index), index + 1);
			}
			return makeNode(index, v0, v1);
		}
	}

	BoolFunction SBDD::setZero(BoolFunction function, int index)
	{
		int size = function.cubes_.size();
		for (int i = 0; i < size; ++i) {
			if (function.cubes_[i][index] == '0') {
				function.cubes_[i][index] = '-';
			}
			if (function.cubes_[i][index] == '1') {
				function.cubes_.erase(function.cubes_.begin() + i);
				size--;
			}
		}
		return function;
	}

	BoolFunction SBDD::setOne(BoolFunction function, int index)
	{
		int size = function.cubes_.size();
		for (int i = 0; i < size; ++i) {
			if (function.cubes_[i][index] == '1') {
				function.cubes_[i][index] = '-';
			}
			if (function.cubes_[i][index] == '0') {
				function.cubes_.erase(function.cubes_.begin() + i);
				size--;
			}
		}
		return function;
	}

	void SBDD::out(std::ostream &stream) const
	{
		stream << "SBDD:\n";
		size_t size = fNames_.size();
		for (size_t i = 0; i < size; ++i) {
			stream << fNames_[i] << " -> " << fRoot_[i] << "\n";
		}
		stream << "\n";
		auto iter = table_.begin();
		auto end = table_.end();
		for (; iter != end; ++iter) {
			stream << iter->first << "   " << iter->second.index << "   " << iter->second.left << "   " << iter->second.right << "\n";
		}
		stream << "\n";
	}

}