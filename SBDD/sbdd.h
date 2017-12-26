#pragma once

#include <map>
#include <vector>

#include "uniData.h"

namespace sbdd {

	// —труктура дл€ представлени€ строчки таблицы.
	struct TableStr {
		int index;
		int left;
		int right;

		TableStr(int i = -1, int l = -1, int r = -1) { index = i; left = l; right = r; }

		bool operator == (const TableStr &tableStr)
		{
			if (index == tableStr.index && left == tableStr.left && right == tableStr.right) {
				return true;
			}
			else
				return false;
		}
	};

	class SBDD
	{
	public:
		// ≈сли constant = false, то будет создан SBDD = 0, иначе 1.
		SBDD(bool constant = false);
		SBDD(const SBDD &sbdd);

		// Ѕазовые операции.
		// —уществует ли данные узел в таблице.
		bool member(const TableStr &tableStr);
		// ¬озвращает номер узла в таблице, если такого узла нет то -1.
		int lookup(const TableStr &tableStr);
		// ¬ставл€ет узел в таблицу и возвращает его номер.
		int insert(const TableStr &tableStr);
		// —оздаем и добавл€ем если можно новый узел.
		int makeNode(int index, int left, int right);

		void build(const UniData &data);

		void out(std::ostream &stream) const;

		std::map<int, TableStr> table() const { return table_; }
		std::vector<std::string> fNames() const { return fNames_; }
		std::vector<int> fRoot() const { return fRoot_; }

	private:
		void buildFunctionPrivate(const BoolFunction &function);
		int buildPrivate(BoolFunction function, int index);

		BoolFunction setZero(BoolFunction function, int index);
		BoolFunction setOne(BoolFunction function, int index);

	private:
		std::map<int, TableStr> table_;
		std::vector<std::string> fNames_;
		std::vector<int> fRoot_;
		int nextNum_;

	};	// class SBDD

}