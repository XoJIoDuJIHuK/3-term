#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//49-wchar_t
//50-char
//51-int
//52-uint
//53-short
//54-ushort
//55-long
//56-ulong
//57-float
//58-double
//59-bool

char* ToString(int val)
{
	int n = 1;
	while (pow(10, n) < val) n++;
	char* mas = new char[n + 1];
	mas[n] = '\0';
	for (int i = n - 1; i >= 0; i--)
	{
		mas[i] = (char)(val % 10 + 48);
		val /= 10;
	}
	return mas;
}

int main()
{
	setlocale(LC_ALL, "ru");
	fstream file("../SE_Lab4/test.txt");
	string prog = ".586P\n.MODEL FLAT, STDCALL\nincludelib kernel32.lib\nExitProcess PROTO : DWORD\n\
.STACK 4096\n.CONST\n.DATA\n\t";
	char type;
	int numOfChars = 1;
	int numOfBools = 1;
	file >> type;
	while ((int)type != -52)
	{
		switch ((int)type)
		{
			case 50:
			{
				char size[1] = { 1 };
				string sval = "char";
				char* mas = ToString(numOfChars);
				numOfChars++;
				for (int i = 0; mas[i] != '\0'; i++)
				{
					sval += mas[i];
				}
				sval += " DB \"";
				file.read(size, 1);
				char* ch = new char[(int)size];
				file.read(ch, (int)size[0]);
				for (int i = 0; i < (int)size[0]; i++)
				{
					sval += ch[i];
					cout << ch[i];
				}
				sval += "\", 0\n\t";
				prog += sval;
				cout << endl;
				break;
			}
			case 59:
			{
				bool val = false;
				char ch[1];
				string sval = "bool";
				char* mas = ToString(numOfBools);
				numOfBools++;
				for (int i = 0; mas[i] != '\0'; i++)
				{
					sval += mas[i];
				}
				sval += " DB ";
				file >> ch[0];
				if (ch[0] == 101)
				{
					val = true;
					sval += '1';
				}
				else sval += '0';
				sval += "\n\t";
				prog += sval;
				if (val) cout << "true\n";
				else cout << "false\n";
				break;
			}
			default: break;
		}
		file >> type;
	}
	file.close();
	prog += ".CODE\
\nmain PROC\n\tpush - 1\n\tcall ExitProcess\nmain ENDP\nend main";
	fstream Asm("../Asm/src.asm");
	for (int i = 0; i < prog.length(); i++) Asm << prog[i];
	Asm.close();
	return 0;
}