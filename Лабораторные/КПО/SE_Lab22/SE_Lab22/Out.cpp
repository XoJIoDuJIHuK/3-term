#define _CRT_SECURE_NO_WARNINGS
#include "Out.h"
#include <string>
namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		try
		{
			OUT struc;
			struc.stream = new(std::nothrow) std::ofstream;
			if (!struc.stream) throw ERROR_THROW(112);
			struc.stream->open(outfile);
			if (!(*(struc.stream)).is_open()) throw ERROR_THROW(112);
			wcscpy_s(struc.outfile, outfile);
			return struc;
		}
		catch (Error::ERROR e)
		{
			Error::ErrorDisplay(e);
		}
	}

	void WriteOut(In::IN in, Parm::PARM parm)
	{
		std::ofstream fout(parm.out);
		if (fout.fail()) throw ERROR_THROW(113);
		fout << in.textOut;
		fout.close();
		return;
	}

	void Close(OUT out)
	{
		(*out.stream).close();
		delete out.stream;
	}
}