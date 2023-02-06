#include "LT.h"
#include "IT.h"
#include "In.h"
#include "FST.h"
#include <vector>
#include <stack>

using namespace std;

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
	void Print(LexTable table, Log::LOG log)
	{
		*log.stream << "Table of lexems | size:" << table.size << " | maxsize: " << table.maxsize << "\n";
		for (int i = 0; i < table.size; i++)
		{
			Entry e = table.table[i];
			*log.stream << i << ") " << e.lexema << " | idxTI: " << e.idxTI << " | string number: " << e.sn;
			if (e.lexema == LEX_CALLFUNC) *log.stream << " | amount of parameters: " << e.priority;
			*log.stream << '\n';
		}
	}
	bool is5CharKeyWord(string str)
	{
		if (str.length() != 5) return false;
		string arr[] = { "print" };
		int arrLength = 1;
		for (int i = 0; i < arrLength; i++)
		{
			bool wordFound = true;
			for (int j = 0; j < str.length() && wordFound; j++)
			{
				if (str[j] != arr[i][j]) wordFound = false;
			}
			if (wordFound) return true;
		}
		return false;
	}

	bool isSpecSymbol(char c)
	{
		string str = "(),{};\n=";
		for (int i = 0; i < str.length(); i++) if (str[i] == c) return true;
		return false;
	}

	void ToId(char* id, string word)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j < word.length()) id[j] = word[j];
			else id[j] = 0;
		}
		id[5] = 0;
	}

	void ToCharPtr(char** ptr, string str)
	{
		short length = str.length();
		*ptr = new char[length + 1];
		for (short i = 0; i < length; i++) (*ptr)[i] = str[i];
		(*ptr)[length] = 0;
	}

	void strcpy(char** dest, char* src)
	{
		short length = 0;
		while (src[length] != 0) length++;
		(*dest) = new char[length + 1];
		for (short i = 0; i < length; i++) (*dest)[i] = src[i];
		(*dest)[length] = 0;
	}

	bool LexAnalyze(In::IN& in, Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		vector<pair<char, FSTN::FSTsmall>> lexems =
		{
			{
				{
					'v', FSTN::FSTsmall
					{
						2,
						FSTN::NODE(4, FSTN::RELATION('+', 1), FSTN::RELATION('-', 1), FSTN::RELATION('*', 1), FSTN::RELATION('/', 1)),
						FSTN::NODE()
					}
				},
				{
					't', FSTN::FSTsmall
					{
						13,
						FSTN::NODE(2, FSTN::RELATION('i', 1), FSTN::RELATION('s', 7)),
						FSTN::NODE(1, FSTN::RELATION('n', 2)),
						FSTN::NODE(1, FSTN::RELATION('t', 3)),
						FSTN::NODE(1, FSTN::RELATION('e', 4)),
						FSTN::NODE(1, FSTN::RELATION('g', 5)),
						FSTN::NODE(1, FSTN::RELATION('e', 6)),
						FSTN::NODE(1, FSTN::RELATION('r', 12)),
						FSTN::NODE(1, FSTN::RELATION('t', 8)),
						FSTN::NODE(1, FSTN::RELATION('r', 9)),
						FSTN::NODE(1, FSTN::RELATION('i', 10)),
						FSTN::NODE(1, FSTN::RELATION('n', 11)),
						FSTN::NODE(1, FSTN::RELATION('g', 12)),
						FSTN::NODE()
					}
				},
				{
					'f', FSTN::FSTsmall
					{
						9,
						FSTN::NODE(1, FSTN::RELATION('f', 1)),
						FSTN::NODE(1, FSTN::RELATION('u', 2)),
						FSTN::NODE(1, FSTN::RELATION('n', 3)),
						FSTN::NODE(1, FSTN::RELATION('c', 4)),
						FSTN::NODE(1, FSTN::RELATION('t', 5)),
						FSTN::NODE(1, FSTN::RELATION('i', 6)),
						FSTN::NODE(1, FSTN::RELATION('o', 7)),
						FSTN::NODE(1, FSTN::RELATION('n', 8)),
						FSTN::NODE()
					}
				},
				{
					'd', FSTN::FSTsmall
					{
						8,
						FSTN::NODE(1, FSTN::RELATION('d',  1)),
						FSTN::NODE(1, FSTN::RELATION('e',  2)),
						FSTN::NODE(1, FSTN::RELATION('c',  3)),
						FSTN::NODE(1, FSTN::RELATION('l',  4)),
						FSTN::NODE(1, FSTN::RELATION('a',  5)),
						FSTN::NODE(1, FSTN::RELATION('r',  6)),
						FSTN::NODE(1, FSTN::RELATION('e',  7)),
						FSTN::NODE()
					}
				},
				{
					'r', FSTN::FSTsmall
					{
						7,
						FSTN::NODE(1, FSTN::RELATION('r',  1)),
						FSTN::NODE(1, FSTN::RELATION('e',  2)),
						FSTN::NODE(1, FSTN::RELATION('t',  3)),
						FSTN::NODE(1, FSTN::RELATION('u',  4)),
						FSTN::NODE(1, FSTN::RELATION('r',  5)),
						FSTN::NODE(1, FSTN::RELATION('n',  6)),
						FSTN::NODE()
					}
				},
				{
					'p', FSTN::FSTsmall
					{
						6,
						FSTN::NODE(1, FSTN::RELATION('p',  1)),
						FSTN::NODE(1, FSTN::RELATION('r',  2)),
						FSTN::NODE(1, FSTN::RELATION('i',  3)),
						FSTN::NODE(1, FSTN::RELATION('n',  4)),
						FSTN::NODE(1, FSTN::RELATION('t',  5)),
						FSTN::NODE()
					}
				},
				{
					'm', FSTN::FSTsmall
					{
						5,
						FSTN::NODE(1, FSTN::RELATION('m',  1)),
						FSTN::NODE(1, FSTN::RELATION('a',  2)),
						FSTN::NODE(1, FSTN::RELATION('i',  3)),
						FSTN::NODE(1, FSTN::RELATION('n',  4)),
						FSTN::NODE()
					}
				},
				{
					'l', FSTN::FSTsmall
					{
						3,
						FSTN::NODE(1, FSTN::RELATION('\'', 1)),
						FSTN::NODE(38, FSTN::RELATION('\'', 2), FSTN::RELATION(' ', 1), FSTN::RELATION('a', 1), FSTN::RELATION('b', 1), FSTN::RELATION('c', 1), FSTN::RELATION('d', 1), FSTN::RELATION('e', 1), FSTN::RELATION('f', 1), FSTN::RELATION('g', 1), FSTN::RELATION('h', 1), FSTN::RELATION('i', 1), FSTN::RELATION('j', 1), FSTN::RELATION('k', 1), FSTN::RELATION('l', 1), FSTN::RELATION('m', 1), FSTN::RELATION('n', 1), FSTN::RELATION('o', 1), FSTN::RELATION('p', 1), FSTN::RELATION('q', 1), FSTN::RELATION('r', 1), FSTN::RELATION('s', 1), FSTN::RELATION('t', 1), FSTN::RELATION('u', 1), FSTN::RELATION('v', 1), FSTN::RELATION('w', 1), FSTN::RELATION('x', 1), FSTN::RELATION('y', 1), FSTN::RELATION('z', 1), FSTN::RELATION('0', 1), FSTN::RELATION('1', 1), FSTN::RELATION('2', 1), FSTN::RELATION('3', 1), FSTN::RELATION('4', 1), FSTN::RELATION('5', 1), FSTN::RELATION('6', 1), FSTN::RELATION('7', 1), FSTN::RELATION('8', 1), FSTN::RELATION('9', 1)),
						FSTN::NODE()
					}
				},
				{
					'l', FSTN::FSTsmall
					{
						1,
						FSTN::NODE(10, FSTN::RELATION('0', 0), FSTN::RELATION('1', 0), FSTN::RELATION('2', 0), FSTN::RELATION('3', 0), FSTN::RELATION('4', 0), FSTN::RELATION('5', 0), FSTN::RELATION('6', 0), FSTN::RELATION('7', 0), FSTN::RELATION('8', 0), FSTN::RELATION('9', 0)),
					}
				},
				{
					'i', FSTN::FSTsmall
					{
						1,
						FSTN::NODE(26, FSTN::RELATION('a', 0), FSTN::RELATION('b', 0), FSTN::RELATION('c', 0), FSTN::RELATION('d', 0), FSTN::RELATION('e', 0), FSTN::RELATION('f', 0), FSTN::RELATION('g', 0), FSTN::RELATION('h', 0), FSTN::RELATION('i', 0), FSTN::RELATION('j', 0), FSTN::RELATION('k', 0), FSTN::RELATION('l', 0), FSTN::RELATION('m', 0), FSTN::RELATION('n', 0), FSTN::RELATION('o', 0), FSTN::RELATION('p', 0), FSTN::RELATION('q', 0), FSTN::RELATION('r', 0), FSTN::RELATION('s', 0), FSTN::RELATION('t', 0), FSTN::RELATION('u', 0), FSTN::RELATION('v', 0), FSTN::RELATION('w', 0), FSTN::RELATION('x', 0), FSTN::RELATION('y', 0), FSTN::RELATION('z', 0))
					}
				}
			}
		};
		int position = 0;
		int positionInLine = 0;
		int positionOut = 3;
		int lexemNumber = 0;
		int identifiersNumber = 0;
		short line = 1;
		int numOfMains = 0;
		bool functionRecentlyDeclared = false;//функци€ только что объ€влена, дл€ заполнени€ вектора параметров
		in.textOut = new unsigned char[IN_MAX_LEN_TEXT];
		std::memset(in.textOut, 0, IN_MAX_LEN_TEXT);
		in.textOut[0] = '0';
		in.textOut[1] = '1';
		in.textOut[2] = ' ';
		string pre0previousWord = "";
		string pre1previousWord = "";

		stack<string> scopeStack;
		scopeStack.push("");

		char* currentScope = new char[1];
		currentScope[0] = 0;
		short numberOfLiterals = 0;
		short parenthesesOpened = 0;
		bool waitingForParameters = false;
		bool includedFunctionScope = false;
		while (position < in.size)
		{
			string word = "";
			char* id = new char[6];
			bool wordFound = false;
			bool stringLiteral = false;
			for (int i = 0; position + i < in.size; i++)
			{
				if (!stringLiteral && (in.code[in.text[position + i]] == In::IN::S ||
					in.text[position + i] == '$')) break;
				if (in.text[position + i] == '\'') stringLiteral = !stringLiteral;
				wordFound = true;
				word += in.text[position + i];
			}
			if (!wordFound)
			{
				LT::Entry ltEntry;
				if (in.code[in.text[position]] == In::IN::S)
				{
					if (isSpecSymbol(in.text[position]))
					{
						LT::Entry e;
						e.idxTI = -1;
						e.lexema = in.text[position];
						e.sn = line;
						LT::Add(lextable, e);
						lexemNumber++;
					}
					if (in.text[position] == '{') parenthesesOpened++;
					if (in.text[position] == '}')
					{
						scopeStack.pop();
						ToCharPtr(&currentScope, scopeStack.top());
						parenthesesOpened--;
						if (parenthesesOpened == 0)
						{
							delete[] currentScope;
							currentScope = new char[1];
							currentScope[0] = 0;
						}
					}
					if (in.text[position] == '(' || in.text[position] == ')') ltEntry.priority = 1;
					if (in.text[position] == '(' && idtable.table[idtable.size - 1].idtype 
						== IT::F) waitingForParameters = true;
					if (in.text[position] == ')' && waitingForParameters) waitingForParameters = false;
					if (in.text[position] == ')' && functionRecentlyDeclared) functionRecentlyDeclared = false;
					if (in.text[position] == ')' && includedFunctionScope)
					{
						includedFunctionScope = false;
						scopeStack.pop();
						ToCharPtr(&currentScope, scopeStack.top());
					}
					if (in.text[position] == ' ')
					{
						position++;
						positionInLine++;
						continue;
					}
					else if (in.text[position] == '+' ||
						in.text[position] == '-' ||
						in.text[position] == '*' ||
						in.text[position] == '/')
					{
						switch (in.text[position])
						{
							case '+':
							case '-':
							{
								ltEntry.priority = 2;
								break;
							}
							case '*':
							case '/':
							{
								ltEntry.priority = 3;
								break;
							}
						}
						in.textOut[positionOut] = 'v';
						ltEntry.idxTI = -1;
						ltEntry.lexema = 'v';
						ltEntry.sn = line;
						Add(lextable, ltEntry);
						lexemNumber++;
					}
					else
					{
						in.textOut[positionOut] = in.text[position];
					}
					position++;
					positionOut++;
					positionInLine++;
					continue;
				}
				if (in.text[position] == '$')
				{
					line++;
					in.textOut[positionOut++] = '\n';
					in.textOut[positionOut++] = (char)(line / 10 + (int)'0');
					in.textOut[positionOut++] = (char)(line % 10 + (int)'0');
					in.textOut[positionOut++] = ' ';
					position++;
					positionInLine = 0;
					continue;
				}
			}
			else
			{
				ToId(id, word);
				position += word.length();
				positionInLine += word.length();
				bool lexemFound = false;
				for (int i = 0; i < lexems.size(); i++)
				{
					if (FSTN::execute(in, lexems[i].second, word))
					{
						if (lexems[i].first == 'm')
						{
							numOfMains++;
							delete[] currentScope;
							currentScope = new char[5];
							currentScope[0] = 'm';
							currentScope[1] = 'a';
							currentScope[2] = 'i';
							currentScope[3] = 'n';
							currentScope[4] = '\0';
							scopeStack.push("main");
						}
						LT::Entry ltEntry;
						IT::Entry itEntry;
						strcpy(&itEntry.scope, currentScope);
						lexemFound = true;
						in.textOut[positionOut++] = lexems[i].first;
						ltEntry.lexema = lexems[i].first;
						ltEntry.sn = line;
						if (lexems[i].first == 'i' || lexems[i].first == 'l')
						{
							if (is5CharKeyWord(word)) throw ERROR_THROW_IN(5, line, positionInLine); //#
							itEntry.idxfirstLE = lexemNumber;
							for (int j = 0; j < 5; j++) itEntry.id[j] = id[j];
							if (lexems[i].first == 'i')
							{
								bool identifierExists = (IT::IsId(idtable, id, currentScope) != -1);
								if (!identifierExists)
								{
									ltEntry.idxTI = idtable.size;
									//переменна€
									if (lextable.table[lextable.size - 2].lexema == 'd')
									{
										itEntry.idtype = IT::V;
										if (pre0previousWord == "integer")
										{
											itEntry.iddatatype = IT::INT;
											itEntry.value.vint = 0;
										}
										else if (pre0previousWord == "string")
										{
											itEntry.iddatatype = IT::STR;
											itEntry.value.vstr.len = TI_STR_DEFAULT;
										}
										else throw ERROR_THROW_IN(6, line, positionInLine);// #6
									}
									//функци€
									else if (lextable.table[lextable.size - 1].lexema == 'f')
									{
										if (currentScope[0] == 0)
										{
											functionRecentlyDeclared = true;
											ToCharPtr(&currentScope, word);
											scopeStack.push(word);
										}
										if (lextable.table[lextable.size - 3].lexema == LEX_DECLARE)
										{
											functionRecentlyDeclared = true;
											includedFunctionScope = true;
											scopeStack.push(word);
											ToCharPtr(&currentScope, word);
										}
										itEntry.idtype = IT::F;
										if (pre1previousWord == "integer")
										{
											itEntry.iddatatype = IT::INT;
											itEntry.value.vint = 0;
										}
										else if (pre1previousWord == "string")
										{
											itEntry.iddatatype = IT::STR;
											itEntry.value.vstr.len = TI_STR_DEFAULT;
											itEntry.value.vstr.str[0] = 0;
										}
										else throw ERROR_THROW(6, line, positionInLine);// #6
									}
									//параметр
									else if (waitingForParameters)
									{
										itEntry.idtype = IT::P;
										if (pre0previousWord == "integer")
										{
											itEntry.iddatatype = IT::INT;
											itEntry.value.vint = 0;
										}
										else if (pre0previousWord == "string")
										{
											itEntry.iddatatype = IT::STR;
											itEntry.value.vstr.len = TI_STR_DEFAULT;
											itEntry.value.vstr.str[0] = 0;
										}
										else throw ERROR_THROW_IN(8, line, positionInLine);// #8
										if (functionRecentlyDeclared)
										{
											int funcIndex = lextable.size - 2;
											while (funcIndex > -1)
											{
												if (lextable.table[funcIndex].idxTI == -1)
												{
													funcIndex--;
												}
												else
												{
													if (idtable.table[lextable.table[funcIndex].idxTI].idtype ==
														IT::F) break;
													funcIndex--;
												}
											}
											if (funcIndex == -1) cout << "funcIndex == -1\n";
											switch (itEntry.iddatatype)
											{
												case IT::INT:
												{
													lextable.table[idtable.table[lextable.
														table[funcIndex].idxTI].idxfirstLE].params.
														push_back(IT::INT);
													break;
												}
												case IT::STR:
												{
													lextable.table[idtable.table[lextable.
														table[funcIndex].idxTI].idxfirstLE].params.
														push_back(IT::STR);
													break;
												}
											}
										}
									}
									else throw ERROR_THROW_IN(7, line, positionInLine);// #7
								}
								else
								{
									int intId = IT::IsId(idtable, id, currentScope);
									ltEntry.idxTI = intId;
									itEntry.iddatatype = idtable.table[intId].iddatatype;
									if (waitingForParameters) itEntry.idtype = IT::P;
									else itEntry.idtype = idtable.table[intId].idtype;
									if (idtable.table[intId].iddatatype == IT::INT)
									{
										itEntry.value.vint = idtable.table[intId].value.vint;
									}
									else
									{
										itEntry.value.vstr.len = idtable.table[intId].value.vstr.len;
										for (int j = 0; j < itEntry.value.vstr.len; j++)
										{
											itEntry.value.vstr.str[j] = idtable.table[intId].value.vstr.str[j];
										}
									}
								}
							}
							else
							{
								int alreadyExists = -1;
								bool isString = word[0] == '\'';
								IT::IDDATATYPE type = isString ? IT::STR : IT::INT;
								for (int j = 0; j < idtable.size; j++)
								{
									IT::Entry entry = idtable.table[j];
									if (entry.idtype == IT::L && entry.iddatatype == type)
									{
										if (isString)
										{
											string strCmp = word.substr(1, word.length() - 2);
											bool stringsAreEqual = strCmp.length() == entry.value.vstr.len;
											for (int k = 0; k < strCmp.length() && stringsAreEqual; k++)
											{
												if (strCmp[k] != entry.value.vstr.str[k]) stringsAreEqual = false;
											}
											if (stringsAreEqual) alreadyExists = j;
										}
										else
										{
											if (atoi(word.c_str()) == entry.value.vint) alreadyExists = j;
										}
									}
								}
								if (numberOfLiterals > 99) throw ERROR_THROW_IN(12, line, positionInLine);
								id[0] = '_';
								id[1] = 'l';
								id[2] = isString ? 's' : 'i';
								id[3] = (numberOfLiterals % 10) + '0';
								id[4] = ((numberOfLiterals / 10) % 10) + '0';
								for (int j = 0; j < 5; j++) itEntry.id[j] = id[j];
								numberOfLiterals++;
								itEntry.idtype = IT::L;
								if (isString)
								{
									itEntry.iddatatype = IT::STR;
									char length = word.length() - 2;
									char* a = new char[length];
									for (int j = 0; j < length; j++) itEntry.value.vstr.str[j] = word[j + 1];
									itEntry.value.vstr.len = length;
								}
								else
								{
									itEntry.iddatatype = IT::INT;
									int length = word.length();
									char* a = new char[length];
									for (int j = 0; j < length; j++)
									{
										a[j] = word[j];
									}
									itEntry.value.vint = atoi(a);
								}
								if (alreadyExists != -1)
								{
									ltEntry.idxTI = alreadyExists;
								}
								else
								{
									ltEntry.idxTI = identifiersNumber;
								}
							}
							IT::Add(idtable, itEntry);
							identifiersNumber++;
						}
						else
						{
							ltEntry.idxTI = -1;
						}
						LT::Add(lextable, ltEntry);
						pre1previousWord = pre0previousWord;
						pre0previousWord = word;
						lexemNumber++;
						break;
					}
				}
				if (!lexemFound)
				{
					cout << "Unexpected lexem at position " << position << " word: " << word << endl;
					throw ERROR_THROW_IN(11, line, positionInLine);
				}
			}
			delete[] id;
		}
		if (numOfMains == 0) throw ERROR_THROW(150);
		if (numOfMains > 1) throw ERROR_THROW(151);
		LT::Entry le;
		le.idxTI = -1;
		le.lexema = '$';
		le.sn = -1;
		LT::Add(lextable, le);
		IT::Print(idtable, log);
		LT::Print(lextable, log);
	}
}