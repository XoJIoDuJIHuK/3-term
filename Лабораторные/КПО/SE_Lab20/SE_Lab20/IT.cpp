#include "IT.h"

namespace IT
{
	IdTable Create(int s)
	{
		IdTable obj;
		if (s > TI_MAXSIZE) throw ERROR_THROW(3);
		obj.maxsize = s;
		obj.table = new Entry[s];
		return obj;
	}
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size++] = entry;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n < 0 || n > idtable.size - 1)
		{
			throw ERROR_THROW(9);
			std::cout << "Index n in GetEntry (idtable) is out of range\n";
			Entry e;
			e.id[0] = 0;
			e.iddatatype = INT;
			e.idtype = V;
			e.idxfirstLE = -1;
			e.value.vint = -1;
			return e;
		}
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			for (int j = 0; j < ID_MAXSIZE; j++)
			{
				if (idtable.table[i].id[j] != id[j]) break;
				else if (j == 4) return i;
			}
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable)
	{
		delete &idtable;
	}
	short GetType(std::string type)
	{
		std::string arr[] = { "integer", "string" };
		for (int i = 0; i < sizeof(arr) / sizeof(std::string); i++) if (type == arr[i]) return i + 1;
		return 0;
	}
	void Print(IdTable idtable)
	{
		std::cout << "Table of identifiers | size:" << idtable.size << " | maxsize: " << idtable.maxsize << "\n";
		for (int i = 0; i < idtable.size; i++)
		{
			Entry e = idtable.table[i];
			std::cout << i << ") " << e.id << " | firstLE: " << e.idxfirstLE << " | ";
			switch (e.iddatatype)
			{
				case 1:
				{
					std::cout << "INT";
					break;
				}
				case 2:
				{
					std::cout << "STR";
					break;
				}
			}
			std::cout << " | ";
			switch (e.idtype)
			{
				case 1:
				{
					std::cout << "V";
					break;
				}
				case 2:
				{
					std::cout << "F";
					break;
				}
				case 3:
				{
					std::cout << "L/P";
					break;
				}
			}
			std::cout << " | ";
			if (e.iddatatype == INT) std::cout << e.value.vint;
			else std::cout << "vstr.len: " << (int)(e.value.vstr.len) << " | vstr.str: ";
			for (int i = 0; i < e.value.vstr.len; i++) std::cout << e.value.vstr.str[i];
			std::cout << "\n";
		}
	}
}