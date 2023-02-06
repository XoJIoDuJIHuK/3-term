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
void push(char* ch, int size, fstream* file)
{
	char type[] = { 50 };
	char mas_size[] = { (char)size };
	(*file).write(type, 1);
	(*file).write(mas_size, 1);
	(*file).write(ch, size);
}
void push(bool value, fstream* file)
{
	char type[] = { 59 };
	char ch[1] = { 100 };
	if (value) ch[0] = 101;
	(*file).write(&type[0], 1);
	(*file).write(&ch[0], 1);
}

int main()
{
	setlocale(LC_ALL, "ru");
	fstream file("test.txt");
	char a[] = {40, ' ', 50, ' ', 52};
	char c[] = "qwerty";
	push(a, sizeof(a), &file);
	push(true, &file);
	push(c, sizeof(c) - 1, &file);
	char eof = -52;
	file << eof;
	file.close();
	return 0;
}