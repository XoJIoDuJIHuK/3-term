#include "Semantic.h"
#include "LT.h"
#include "IT.h"
#include <iostream>
#include <vector>

void SemAnalyze(IT::IdTable idtable, LT::LexTable lextable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		switch (lextable.table[i].lexema)
		{
			case LEX_EQUALS:
			{
				IT::IDDATATYPE type = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
				for (++i; lextable.table[i].lexema != LEX_SEMICOLON; i++)
				{
					if (lextable.table[i].idxTI == -1) continue;
					if (type != idtable.table[lextable.table[i].idxTI].iddatatype)
						throw ERROR_THROW(152);
					switch (idtable.table[lextable.table[i].idxTI].idtype)
					{
						case IT::L:
						case IT::V:
						{
							if (lextable.table[i + 1].lexema == LEX_LEFTHESIS) throw ERROR_THROW(156);
							break;
						}
						case IT::F:
						{
							if (lextable.table[i + 1].lexema != LEX_LEFTHESIS) throw ERROR_THROW(157);
							int funcIndex = i;
							i += 2;
							int paramCount = 0;
							std::vector<IT::IDDATATYPE> params = lextable.table[idtable.table[lextable.
								table[funcIndex].idxTI].idxfirstLE].params;
							for (int j = 0; lextable.table[i].lexema != LEX_RIGHTHESIS;
								i++, j++)
							{
								if (paramCount >= params.size()) 
									throw ERROR_THROW(154);
								if (lextable.table[i].lexema == LEX_COMMA) continue;
								if (params[paramCount] != idtable.table[lextable.table[i].idxTI].iddatatype)
									throw ERROR_THROW(153);
								paramCount++;
							}
							if (params.size() != paramCount)
								throw ERROR_THROW(155);
							break;
						}
					}
				}
			}
		}
	}
}