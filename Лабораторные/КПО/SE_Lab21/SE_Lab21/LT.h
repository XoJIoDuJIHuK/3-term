#pragma once

#include <iostream>
#include "Error.h"
#include "In.h"
#include "Out.h"
#include "Log.h"
#include "IT.h"

#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_ID
#define LEX_LITERAL
#define LEX_FUNCTION
#define LEX_DECLARE
#define LEX_RETURN
#define LEX_PRINT
#define LEX_SEMICOLON
#define LEX_COMMA
#define LEX_LEFTBRACE
#define LEX_BRACELET
#define LEX_LEFTHESIS
#define LEX_RIGHTHESIS
#define LEX_PLUS
#define LEX_MINUS
#define LEX_STAR
#define LEX_DIRSLASH

namespace LT
{
	struct Entry
	{
		char lexema;
		int sn;
		int idxTI;
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