#pragma once

#include <iostream>
#include <vector>
#include "Error.h"
#include "In.h"
#include "Out.h"
#include "Log.h"
#include "IT.h"

#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 't'
#define LEX_STRING 's'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/'
#define LEX_EQUALS '='
#define LEX_CALLFUNC '@'

namespace LT
{
	struct Entry
	{
		char lexema;
		int sn;
		int idxTI;
		int priority = -1;//используется для указания количества параметров при вызове функции в польской записи
		std::vector<IT::IDDATATYPE> params;
	};
	struct LexTable
	{
		int maxsize;
		int size = 0;
		Entry* table;
	};
	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	void Print(LexTable, Log::LOG log);
	bool LexAnalyze(In::IN& in, Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable);
}