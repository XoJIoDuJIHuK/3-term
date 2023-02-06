#include "Greibach.h"
#include <string.h>

namespace GRB
{
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
	}
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, GRB::Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottomT;
		rules = new GRB::Rule[size = psize];
		GRB::Rule* p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	}
	Greibach greibachOriginal(NS('S'), TS('$'), 6,
		//S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};
		Rule(NS('S'), GRB_ERRORS_START, 4,						// Неверная структура программы	
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'),
				NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'),
				NS('E'), TS(';'), TS('}'), TS(';'))
		),
		//N -> dti; | rE; | i = E; | dtfi(F); | dti; N | rE; N | i = E; N | dtfi(F); N | pE; | pE;N
		Rule(NS('N'), GRB_ERRORS_START + 1, 10,					//Не найден список параметров функции	
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';'))
		),
		//E-> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M		Неверное выражение
		Rule(NS('E'), GRB_ERRORS_START + 2, 8,
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
		),
		//M-> vE | vEM		Неверное арифметическое выражение
		Rule(NS('M'), GRB_ERRORS_START + 3, 2,
			Rule::Chain(3, TS('v'), NS('E'), NS('M')),
			Rule::Chain(2, TS('v'), NS('E'))
		),
		//F-> ti | ti,F		Неверный список параметров
		Rule(NS('F'), GRB_ERRORS_START + 4, 2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
			Rule::Chain(2, TS('t'), TS('i'))
		),
		//W-> i | l | i,W | l,W		Неверный список аргументов
		Rule(NS('W'), GRB_ERRORS_START + 5, 4,
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(1, TS('l'))
		)
	);
	Greibach getGreibach() { return greibachOriginal; }
	short Greibach::getRule(GRBALPHABET pnn, GRB::Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	}
	GRB::Rule Greibach::getRule(short n)
	{
		GRB::Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	}
	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0;
		return b;
	}
}