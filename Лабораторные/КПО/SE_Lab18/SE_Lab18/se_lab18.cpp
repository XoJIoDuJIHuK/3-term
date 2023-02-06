#include <iostream>
#include <string>
using namespace std;

struct stack
{
	char value;
	stack* prev = nullptr;
};

stack zeroItem;
stack* head = &zeroItem;
char operators[] = { '+', '-', '*', '/', '(', ')' };
int priorities[] = { 2, 2, 3, 3, 1, 1 };

void push(char str)
{
	stack* st = new stack;
	st->value = str;
	st->prev = head;
	head = st;
}

char pop()
{
	char ret = head->value;
	stack* temp = head;
	head = head->prev;
	delete temp;
	return ret;
}

bool stackIsEmpty()
{
	if (head->prev == nullptr) return true;
	else return false;
}

bool isLetter(char ch)
{
	if ((int)ch >= 65 && (int)ch <= 122) return true;
	//if ('A' <= ch <= 'z') return true;
	else return false;
}

bool isDigit(char ch)
{
	if ((int)ch >= 48 && (int)ch <= 57) return true;
	else return false;
}

bool isOperator(char ch)
{
	for (int i = 0; i < sizeof(operators) / sizeof(char); i++)
	{
		if (operators[i] == ch) return true;
	}
	return false;
}

int priority(char ch)
{
	for (int i = 0; i < sizeof(operators) / sizeof(char); i++)
	{
		if (ch == operators[i]) return priorities[i];
	}
	return 0;
}

bool polishNotationalizer(string str)
{
	string resString = "";
	bool waitsForInstruction = 1;
	bool waitsForOperand = 1;
	bool waitsForOperator = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			i++;
			continue;
		}
		if (isLetter(str[i]))//рассматриваем идентификатор
		{
			while (isLetter(str[i + 1]) || isDigit(str[i + 1]))
			{
				resString += str[i++];
			}
			resString += str[i];
			resString += ' ';
		}
		else if (str[i] == '.')//рассматриваем число с плавающей точкой без нулевой целой части
		{
			if (isDigit(str[i + 1]))
			{
				resString += "0.";
				i++;
				while (isDigit(str[i + 1]))
				{
					resString += str[i++];
				}
				resString += str[i];
				resString += ' ';
			}
			else
			{
				cout << "Invalid float number\n";
				return false;
			}
		}
		else if (isDigit(str[i]))//рассматриваем число
		{
			int numOfDots = 0;
			while (isDigit(str[i + 1]) || str[i + 1] == '.')
			{
				if (str[i] == '.')
				{
					if (0 <= numOfDots <= 1) numOfDots++;
					else
					{
						cout << "Too many dots\n";
						return false;
					}
				}
				resString += str[i++];
			}
			resString += str[i];
			resString += ' ';
		}
		else if (isOperator(str[i]))//рассматриваем операцию
		{
			if (stackIsEmpty() || str[i] == '(' || priority(head->value) < priority(str[i]))
			{
				push(str[i]);
			}
			else if (str[i] == ')')
			{
				bool isOpenBracket = false;
				while (head->value != '(' && !stackIsEmpty())
				{
					resString += pop();
					resString += ' ';
				}
				if (head->value == '(') pop();
				else
				{
					cout << "Missing opening bracket\n";
					return false;
				}
			}
			else if (priority(str[i]) <= priority(head->value))
			{
				while (priority(str[i]) <= priority(head->value) && !stackIsEmpty())
				{
					resString += pop();
					resString += ' ';
				}
				push(str[i]);
			}
		}
	}
	while (!stackIsEmpty())
	{
		resString += pop();
		resString += ' ';
	}
	cout << "Resulting string:\n" << resString << endl;
	return true;
}

void main()
{
	string str;
	cout << "Enter string to polishNotationalize\n";
	getline(cin, str);
	if (polishNotationalizer(str))
	{
		cout << "true\n";
	}
	else
	{
		cout << "false\n";
	}
}