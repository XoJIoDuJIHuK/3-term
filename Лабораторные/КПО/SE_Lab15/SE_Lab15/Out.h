#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Out
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const OUT INITOUT{ L"", NULL };
	OUT getout(wchar_t logfile[]);
	void WriteLine(OUT log, char* c, ...);
	void Close(OUT log);
}