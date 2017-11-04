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

}