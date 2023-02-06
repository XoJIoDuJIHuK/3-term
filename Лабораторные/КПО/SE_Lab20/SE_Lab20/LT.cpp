#include "LT.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable lextable;
		lextable.maxsize = size;
		lextable.table = new Entry[size];
		return lextable;
	}
	void Add(LexTable& lextable, Entry entry)
	{
		lextable.table[lextable.size++] = entry;
	}
	
	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n < 0 || n > lextable.size - 1)
		{
			throw ERROR_THROW(10);
			std::cout << "Index n in GetEntry (lextable) is out of range\n";
			Entry e;
			e.idxTI = -1;
			e.lexema = 0;
			e.sn = -1;
			return e;
		}
		return lextable.table[n];
	}
	void Delete(LexTable& lextable)
	{
		delete& lextable;
	}
	void Print(LexTable table)
	{
		std::cout << "Table of lexems | size:" << table.size << " | maxsize: " << table.maxsize << "\n";
		for (int i = 0; i < table.size; i++)
		{
			Entry e = table.table[i];
			std::cout << i << ") " << e.lexema << " | idxTI: " << e.idxTI << " | string number: " << e.sn << '\n';
		}
	}
}