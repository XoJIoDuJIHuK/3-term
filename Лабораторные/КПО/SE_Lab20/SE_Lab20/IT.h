#pragma once

#include "Error.h"
#include <iostream>

#define ID_MAXSIZE 6
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255
namespace IT
{
	enum IDDATATYPE { INT = 1, STR };
	enum IDTYPE { V = 1, F, P, L = 3 };

	struct Entry
	{
		int idxfirstLE;
		char id[ID_MAXSIZE] = { 0, 0, 0, 0, 0, 0};
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			int vint;
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
		} value;
	};
	struct IdTable
	{
		int maxsize = TI_MAXSIZE;
		int size = 0;
		Entry* table;
	};
	IdTable Create(int s);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);
	void Delete(IdTable& idtable);
	short GetType(std::string type);
	void Print(IdTable);
}