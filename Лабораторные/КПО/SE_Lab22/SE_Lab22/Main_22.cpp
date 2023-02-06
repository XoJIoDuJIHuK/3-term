#include "stdafx.h"
#include "MFST.h"
#include "Polization.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Out::OUT out = Out::getout(parm.out);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm);
		Out::Close(out);
		Log::WriteIn(log, in);

		IT::IdTable idtable = IT::Create(4096);
		LT::LexTable lextable = LT::Create(4096);
		LT::LexAnalyze(in, log, lextable, idtable);

		MFST::SyntAnalize(lextable, log);

		SemAnalyze(idtable, lextable);

		if (startPolishNotation(lextable, idtable)) cout << "polish successfull\n";
		else cout << "polish unsuccessful\n";
		LT::Print(lextable, log);
		return 0;
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		Error::ErrorDisplay(e);
	}

	return 0;
}