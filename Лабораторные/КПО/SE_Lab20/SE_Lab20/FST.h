#pragma once
#include "In.h"
#include <iostream>
#include <string>
#include <vector>
namespace FSTN
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char, short);
	};

	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short, RELATION, ...);
	};

	/*struct FST
	{
		std::string String;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		short lastStringLength = 0;
		FST(std::string, short, NODE, ...);
	};
	bool step(FST&, short*&);
	bool execute(FST& fst);*/

	struct FSTsmall
	{
		std::string word;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		FSTsmall(short, NODE, ...);
	};


	bool step(FSTsmall&, short*);
	bool execute(In::IN, FSTsmall, std::string);
}