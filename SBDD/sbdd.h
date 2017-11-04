#pragma once

#include <map>

namespace sbdd {

	// —труктура дл€ представлени€ строчки таблицы.
	struct TableStr {
		int index;
		int left;
		int right;

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


	private:
		std::map<int, TableStr> table_;
		int nextNum_;

	};	// class SBDD

}