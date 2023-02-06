#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int alphLength = 27;
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz ";
struct symbol
{
	string code = "";
	char charSymbol = '\0';
	symbol() {}
};
struct unionOfSymbols
{
	int positionInVector = -1;
	float frequency = 0;
	vector<symbol> arrOfSymbols = {};
	int numOfSymbols = 0;
	unionOfSymbols(float fr, int n, int pos, symbol s, ...)
	{
		positionInVector = pos;
		frequency = fr;
		numOfSymbols = n;
		symbol* s_ptr = &s;
		for (int i = 0; i < n; i++)
		{
			arrOfSymbols.push_back(s_ptr[i]);
		}
	}
	unionOfSymbols() {}
};
int indexOf(char c)
{
	for (int i = 0; i < alphLength; i++)
	{
		if (ALPHABET[i] == c) return i;
	}
	return -1;
}
void Add(unionOfSymbols* b, unionOfSymbols* l)//прибавляет к большему меньшее
{
	unionOfSymbols bigger = *b;
	unionOfSymbols less = *l;
	bigger.frequency += less.frequency;
	bigger.numOfSymbols += less.numOfSymbols;
	for (int i = 0; i < less.arrOfSymbols.size(); i++)
	{
		bigger.arrOfSymbols.push_back(less.arrOfSymbols[i]);
	}
	*b = bigger;
	*l = less;
}

int main()
{
	string str = "tachyla aleh vyachaslavavich";
	//getline(cin, str);
	static bool existsInString[alphLength];
	static int amountInString[alphLength];
	int amountOfCharacters = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int index = indexOf(str[i]);
		if (index != -1)
		{
			if (!existsInString[index]) amountOfCharacters++;
			existsInString[index] = 1;
			amountInString[index]++;
		}
	}
	int lastFoundedCharacter = 0;
	vector<unionOfSymbols> Vector;
	for (int i = 0, j = 0; i < alphLength; i++)
	{
		if (existsInString[i])
		{
			symbol s;
			s.charSymbol = ALPHABET[i];
			unionOfSymbols u((float)amountInString[i] / (float)str.length(), 1, j, s);
			j++;
			cout << "\'" << s.charSymbol << "\' | " << amountInString[i] << " / " << str.length() << endl;
			Vector.push_back(u);
		}
	}
	cout << "\n\n\n\n\n";
	while (Vector.size() > 1)
	{
		unionOfSymbols minLess;
		minLess.frequency = 2;
		unionOfSymbols minBigger;
		minBigger.frequency = 2;
		for (int i = 0; i < Vector.size(); i++)//поиск минимального элемента
		{
			if (Vector[i].frequency < minLess.frequency)
			{
				minLess = Vector[i];
				minLess.positionInVector = i;
			}
		}
		for (int i = 0; i < Vector.size(); i++)//поиск второго минимального элемента
		{
			if (i == minLess.positionInVector) continue;
			if (Vector[i].frequency < minBigger.frequency)
			{
				minBigger = Vector[i];
				minBigger.positionInVector = i;
			}
		}
		if (minLess.frequency == 2 || minBigger.frequency == 2) return -2;
		for (int i = 0; i < minLess.arrOfSymbols.size(); i++)//добавление нулей и единиц 
		{
			string newString = "1";
			newString += minLess.arrOfSymbols[i].code;
			Vector[minLess.positionInVector].arrOfSymbols[i].code = newString;
		}
		for (int i = 0; i < minBigger.arrOfSymbols.size(); i++)//добавление нулей и единиц 
		{
			string newString = "0";
			newString += minBigger.arrOfSymbols[i].code;
			Vector[minBigger.positionInVector].arrOfSymbols[i].code = newString;
		}
		Add(&Vector[minBigger.positionInVector], &Vector[minLess.positionInVector]);
		auto iter = Vector.cbegin();
		Vector.erase(iter + minLess.positionInVector);
	}
	for (int i = 0; i < Vector[0].arrOfSymbols.size(); i++)
	{
		cout << "\'" << Vector[0].arrOfSymbols[i].charSymbol << "\'"
			" | " << Vector[0].arrOfSymbols[i].code << endl;
	}
	return 0;
}