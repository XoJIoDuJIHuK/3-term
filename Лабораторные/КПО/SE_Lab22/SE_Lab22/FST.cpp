#include "FST.h"
using namespace std;

FSTN::RELATION::RELATION(char c = '\0', short ns = NULL)
{
    FSTN::RELATION::symbol = c;
    FSTN::RELATION::nnode = ns;
}

FSTN::NODE::NODE()
{
    FSTN::NODE::n_relation = 0;
    FSTN::NODE::relations = nullptr;
}

FSTN::NODE::NODE(short n, RELATION rel, ...)
{
    FSTN::NODE::n_relation = n;

    const RELATION* p = &rel;
    FSTN::NODE::relations = new RELATION[n];

    for (short i = 0; i < n; i++) {
        FSTN::NODE::relations[i] = p[i];
    }
}

//FSTN::FST::FST(std::string s, short ns, NODE n, ...)
//{
//    FSTN::FST::String = s;
//    FSTN::FST::nstates = ns;
//
//    FSTN::FST::nodes = new FSTN::NODE[ns];
//    const FSTN::NODE* p = &n;
//    for (int k = 0; k < ns; k++) {
//        FSTN::FST::nodes[k] = p[k];
//    }
//
//    FSTN::FST::rstates = new short[nstates];
//    memset(FSTN::FST::rstates, 0xFF, sizeof(short) * FSTN::FST::nstates);
//    FSTN::FST::rstates[0] = 0;
//
//    FSTN::FST::position = 0;
//}
FSTN::FSTsmall::FSTsmall(short ns, NODE n, ...)
{
    FSTN::FSTsmall::nstates = ns;

    FSTN::FSTsmall::nodes = new FSTN::NODE[ns];
    const FSTN::NODE* p = &n;
    for (int k = 0; k < ns; k++) {
        FSTN::FSTsmall::nodes[k] = p[k];
    }

    FSTN::FSTsmall::rstates = new short[nstates];
    memset(FSTN::FSTsmall::rstates, 0xFF, sizeof(short) * FSTN::FSTsmall::nstates);
    FSTN::FSTsmall::rstates[0] = 0;

    FSTN::FSTsmall::position = 0;
}

//bool FSTN::step(FSTN::FST &fst, short* &rstates)
//{
//    bool rc = false;
//    std::swap(rstates, fst.rstates);
//
//    for (short i = 0; i < fst.nstates; i++)
//    {
//        if (rstates[i] == fst.position)
//        {
//            for (short j = 0; j < fst.nodes[i].n_relation; j++)
//            {
//                std::string Symbol = fst.nodes[i].relations[j].symbol;
//                if (Symbol == fst.String.substr(fst.position, Symbol.length()))
//                {
//                    fst.position += Symbol.length();
//                    fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position;
//                    rc = true;
//                    fst.lastStringLength = Symbol.length();
//                }
//            }
//        }
//    }
//
//    return rc;
//}

//bool FSTN::execute(FSTN::FST& fst)
//{
//    short* rstates = new short[fst.nstates];
//    memset(rstates, 0xFFFF, sizeof(short) * fst.nstates);
//
//    short lstring = (short)((fst.String).length());
//    bool rc = true;
//
//    while (rc && fst.position < lstring)
//    {
//        rc = step(fst, rstates);
//    }
//
//    delete[] rstates;
//    return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
//}



bool FSTN::execute(In::IN in, FSTN::FSTsmall fst, string word)
{
    fst.word = word;
    fst.position = 0;
    bool success = true;
    short* rstates = new short[fst.nstates];
    memset(rstates, 0xff, sizeof(short) * fst.nstates);
    short lstring = word.length();
    for (short i = 0; i < lstring && success; i++)
    {
        success = step(fst, rstates);
        fst.position++;
    }
    bool rc = success ? (fst.rstates[fst.nstates - 1] == lstring) : success;
    delete[] rstates;
    return rc;
}
bool FSTN::step(FSTsmall& fst, short* rstates)
{
    bool success = false;
    std::swap(rstates, fst.rstates);
    for (short i = 0; i < fst.nstates; i++)
    {
        if (rstates[i] == fst.position)
        {
            for (short j = 0; j < fst.nodes[i].n_relation; j++)
            {
                if (fst.nodes[i].relations[j].symbol == fst.word[fst.position])
                {
                    fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
                    success = true;
                }
            }
        }
    }
    return success;
}