#pragma once
#include <iostream>
#include <string>
namespace FSTN
{
	struct RELATION
	{
		std::string symbol;
		short nnode;
		RELATION(std::string, short);
	};
	/*struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char c = 0x00, short ns = NULL);
	};*/

	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short, RELATION, ...);
	};

	struct FST
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
	bool execute(FST& fst);
}