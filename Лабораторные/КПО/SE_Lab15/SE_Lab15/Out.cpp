#define _CRT_SECURE_NO_WARNINGS
#include "Out.h"
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

	void WriteLine(OUT out, char* c, ...)
	{
		for (char** c_ptr = &c; **c_ptr; c_ptr++)
		{
			*out.stream << *c_ptr;
		}
	}

	void Close(OUT out)
	{
		(*out.stream).close();
		delete out.stream;
	}
}