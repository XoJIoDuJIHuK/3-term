#include "IT.h"
#include "Log.h"

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
	short lengthof(char* str)
	{
		short length = 0;
		while (str[length] != 0) length++;
		return length;
	}
	bool equals(char* p1, char* p2)
	{
		int length = lengthof(p1);
		if (length != lengthof(p2)) return false;
		for (int i = 0; i < length; i++) if (p1[i] != p2[i]) return false;
		return true;
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char* scope)
	{
		short length = lengthof(id);
		for (int i = 0; i < idtable.size; i++)
		{
			if (lengthof(idtable.table[i].id) != length) continue;
			for (int j = 0; j < length; j++)
			{
				char c[1] = { 0 };
				if (idtable.table[i].id[j] != id[j] || (!equals(idtable.table[i].scope, scope)
					&& !equals(idtable.table[i].scope, c))) break;
				else if (j == length - 1) return i;
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
	void Print(IdTable idtable, Log::LOG log)
	{
		*log.stream << "Table of identifiers | size:" << idtable.size << " | maxsize: " << idtable.maxsize << "\n";
		for (int i = 0; i < idtable.size; i++)
		{
			Entry e = idtable.table[i];
			*log.stream << i << ") " << e.id << " | scope: " << e.scope <<
				" | firstLE: " << e.idxfirstLE << " | ";
			switch (e.iddatatype)
			{
				case 1:
				{
					*log.stream << "INT";
					break;
				}
				case 2:
				{
					*log.stream << "STR";
					break;
				}
			}
			*log.stream << " | ";
			switch (e.idtype)
			{
				case 1:
				{
					*log.stream << "V";
					break;
				}
				case 2:
				{
					*log.stream << "F";
					break;
				}
				case 3:
				{
					*log.stream << "L/P";
					break;
				}
			}
			*log.stream << " | ";
			if (e.iddatatype == INT) *log.stream << e.value.vint;
			else *log.stream << "vstr.len: " << (int)(e.value.vstr.len) << " | vstr.str: ";
			for (int i = 0; i < e.value.vstr.len; i++) *log.stream << e.value.vstr.str[i];
			*log.stream << "\n";
		}
	}
}