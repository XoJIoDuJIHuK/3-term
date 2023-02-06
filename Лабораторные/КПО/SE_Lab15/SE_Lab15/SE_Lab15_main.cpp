#include <iostream>
#include <locale>
#include <cwchar>
#include <ctime>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	//test getin

	/*cout << "------ тест In::getin ------\n\n";
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm);
		Log::LOG log = Log::getlog(parm.log);
		Out::OUT out = Out::getout(parm.out);
		cout << in.text << endl;
		cout << "Всего символов: " << in.size << endl;
		cout << "Всего строк: " << in.lines << endl;
		cout << "Пропущено: " << in.ignor << endl;
		Log::WriteLine(log, (char*)"Тест: ", (char*)" Без ошибок \n", "");
		Log::WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L" Без ошибок \n", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Out::WriteLine(out, (char*)in.text, "");
		Out::Close(out);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
		cout << "строка " << e.inext.line << " позиция " << e.inext.col << endl << endl;
	};
	system("pause");*/

	//test geterror[in]

	/*cout << "------ тест In::geterror ------\n\n";
	try { throw ERROR_THROW(100); }
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
	};

	cout << "------ тест In::geterrorin ------\n\n";
	try { throw ERROR_THROW_IN(111, 7, 7); }
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
		cout << "строка " << e.inext.line << " позиция " << e.inext.col << endl << endl;
	};
	system("pause");*/

	//test getparm

	/*cout << "------ тест Parm::getparm ------\n\n";
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
	}
	catch (Error::ERROR e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl;
	};
	system("pause");*/

	/*cout << "geterror\n";
	try
	{
		throw ERROR_THROW(100);
	}
	catch (Error::ERROR e)
	{
		cout << "Error " << e.id << ": " << e.message << endl;
	}
	cout << "geterrorin\n";
	try
	{
		throw ERROR_THROW_IN(111, 7, 7);
	}
	catch (Error::ERROR e)
	{
		cout << "Error " << e.id << ": " << e.message << ", line " << e.inext.line <<
			", column " << e.inext.col << endl;
	}*/

	/*try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		wcout << "-in: " << parm.in << ", -out: " << parm.out << ", -log: " << parm.log << endl;
	}
	catch (Error::ERROR e)
	{
		cout << "Error " << e.id << ": " << e.message << endl;
	}*/

	Log::LOG log = Log::INITLOG;
	try
	{
		char a[] = "Hello World!";
		Parm::PARM parm = Parm::getparm(argc, argv);
		Log::LOG log = Log::getlog(parm.log);
		Out::OUT out = Out::getout(parm.out);
		Log::WriteLine(log, (char*)"Тест: ", (char*)" Без ошибок \n", "");
		Log::WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L" Без ошибок \n", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm);
		Out::WriteLine(out, (char*)in.text, "");
		Out::Close(out);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}