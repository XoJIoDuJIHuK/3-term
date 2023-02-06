#define _CRT_SECURE_NO_WARNINGS
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		try
		{
			LOG struc;
			struc.stream = new(std::nothrow) std::ofstream;
			if (!struc.stream) throw ERROR_THROW(112);
			struc.stream->open(logfile);
			if (!(*(struc.stream)).is_open()) throw ERROR_THROW(112);
			wcscpy_s(struc.logfile, logfile);
			return struc;
		}
		catch (Error::ERROR e)
		{
			Error::ErrorDisplay(e);
		}
	}

	void WriteLine(LOG log, char* c, ...)
	{
		for (char** c_ptr = &c; **c_ptr; c_ptr++)
		{
			*log.stream << *c_ptr;
		}
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		unsigned lineLength = 0;
		char* line = nullptr;
		unsigned int n = 0;

		for (wchar_t** c_ptr = &c; **c_ptr; c_ptr++)
		{
			lineLength = wcslen(*c_ptr);
			line = new char[lineLength + 1];
			wcstombs_s(&n, line, lineLength + 1u, *c_ptr, lineLength + 1u);
			*log.stream << line;
			delete[] line;
		}
	}

	void WriteLog(LOG log)
	{
		std::string line = "----Протокол------ ";
		time_t result = time(NULL);
		char str[26];
		ctime_s(str, sizeof str, &result);
		for (int i = 0; i < 26; i++) line += str[i];
		*log.stream << line;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];
		wcstombs(in_text, parm.in, PARM_MAX_SIZE);
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);
		*log.stream << "---- Параметры ---- \n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "\n----Исходные данные------\nКоличество символов: " << (in.size < 0 ? 0 : in.size) << std::endl <<
			"Проигнорировано: " << (in.ignor < 0 ? 0 : in.ignor) << std::endl << "Количество строк: " << 
			(in.lines < 0 ? 0 : in.lines) << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " <<
			error.inext.col << std::endl;
	}

	void Close(LOG log)
	{
		(*log.stream).close();
		delete log.stream;
	}
}