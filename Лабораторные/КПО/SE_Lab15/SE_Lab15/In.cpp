#include "In.h"
#include "Error.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

namespace In
{
	IN getin(Parm::PARM parm)
	{
		try
		{
			IN in{ 0, 0, 0, nullptr, IN_CODE_TABLE };
			int col = 0;

			unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

			ifstream fin(parm.in);
			if (fin.fail()) throw ERROR_THROW(110);
			ofstream fout(parm.out);
			if (fout.fail()) throw ERROR_THROW(113);
			while (in.size < IN_MAX_LEN_TEXT)
			{

				unsigned char x = (unsigned char)fin.get();

				if (fin.eof())
				{
					text[in.size] = '\0';
					in.lines++;
					break;
				}
				if (in.code[x] == in.T)
				{
					text[in.size] = x;
					fout << x;
					in.size++;
					col++;
				}
				else if (in.code[x] == in.I)
				{
					in.ignor++;
				}
				else if (in.code[x] == in.F)
				{
					throw ERROR_THROW_IN(111, in.lines, col);
				}
				else
				{
					text[in.size] = in.code[x];
					fout << (char)in.code[x];
					in.size++;
					col++;
				}
				if (x == IN_CODE_ENDL)
				{
					in.lines++;
					col = 0;
				}
			}
			in.text = text;
			fin.close();
			fout.close();
			return in;
		}
		catch (Error::ERROR e)
		{
			Error::ErrorDisplay(e);
		}
	}
}