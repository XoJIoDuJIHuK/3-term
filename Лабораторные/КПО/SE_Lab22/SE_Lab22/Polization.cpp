#include "LT.h"
#include "IT.h"
#include "Polization.h"
#include <stack>
#include <queue>

using namespace std;

void PolishNotationalize(int start, int end, LT::LexTable& lextable, IT::IdTable& idtable)
{
	LT::Entry placeholder;
	placeholder.lexema = '#';
	int length = end - start;
	stack<LT::Entry> stackPolish;
	LT::Entry* sourceArray = new LT::Entry[length];
	LT::Entry* destinationArray = new LT::Entry[length];
	for (int i = 0; i < length; i++) destinationArray[i] = placeholder;
	for (int i = start; i < end; i++) 
		sourceArray[i - start] = lextable.table[i];
	int destArrSize = 0;

	for (int i = 0; i < length; i++)
	{
		switch (sourceArray[i].lexema)//1*(z+(3/(4+z)))
		{//								0123456789abcde
			case LEX_LITERAL:
			{
				destinationArray[destArrSize] = sourceArray[i];
				destArrSize++;
				break;
			}
			case LEX_ID:
			{
				if (idtable.table[lextable.table[start + i].idxTI].idtype == IT::F)
				{
					int j = i + 2;
					int amountOfParams = 0;
					for (; lextable.table[start + j].lexema != LEX_RIGHTHESIS; j++)
					{
						if (lextable.table[start + j].lexema == LEX_COMMA) continue;
						destinationArray[destArrSize++] = lextable.table[start + j];
						amountOfParams++;
					}
					LT::Entry e;
					e.lexema = LEX_CALLFUNC;
					e.priority = amountOfParams;
					destinationArray[destArrSize++] = e;
					destinationArray[destArrSize++] = lextable.table[start + i];
					i = j;
				}
				else
				{
					destinationArray[destArrSize] = sourceArray[i];
					destArrSize++;
				}
				break;
			}
			case 'v':
			{
				while (stackPolish.size() > 0 && stackPolish.top().priority >= lextable.table[i + start].priority)
				{
					destinationArray[destArrSize] = stackPolish.top();
					destArrSize++;
					stackPolish.pop();
				}
				if (stackPolish.size() == 0 || lextable.table[i + start].priority > 
					stackPolish.top().priority)
				{
					stackPolish.push(lextable.table[i + start]);
				}
				break;
			}
			case LEX_LEFTHESIS:
			{
				stackPolish.push(lextable.table[start + i]);
				break;
			}
			case LEX_RIGHTHESIS:
			{
				while (stackPolish.size() > 0 && stackPolish.top().lexema != LEX_LEFTHESIS)
				{
					destinationArray[destArrSize] = stackPolish.top();
					destArrSize++;
					stackPolish.pop();
				}
				stackPolish.pop();
				break;
			}
			default:
			{
				break;
			}
		}
	}
	while (stackPolish.size() > 0)
	{
		destinationArray[destArrSize] = stackPolish.top();
		destArrSize++;
		stackPolish.pop();
	}
	for (int i = 0; i < length; i++) cout << sourceArray[i].lexema;
	cout << "->";
	for (int i = 0; i < length; i++) cout << destinationArray[i].lexema;
	cout << endl;
	for (int i = start; i < end; i++)
	{
		lextable.table[i] = destinationArray[i - start];
	}
	delete[] sourceArray;
	delete[] destinationArray;
}

bool startPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable)
{
	bool rc = true;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUALS ||
			lextable.table[i].lexema == LEX_RETURN)
		{
			int start = i + 1;
			while (lextable.table[i++].lexema != LEX_SEMICOLON);
			PolishNotationalize(start, i - 1, lextable, idtable);
		}
	}
	return rc;
}