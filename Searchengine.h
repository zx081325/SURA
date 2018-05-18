#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "Define.h"
#include "Generator.h"
#include "Evaluation.h"

class Searchengine
{
public:
    Searchengine();
    ~Searchengine();
    int player;
    int Maxdepth;
    CHESSMOVE bestmove;
    CHESSMOVE nullmove;
    BYTE CurPosition[6][6];
    BYTE MakeMove(CHESSMOVE *move);
    void UnMakeMove(CHESSMOVE *move, BYTE nChessID);
    CHESSMOVE SearchGoodMove(BYTE position[6][6],int nply,int side);
    double ms(double alpha, double beta, int depth);
    void init()
    {
        nullmove.From.x=nullmove.From.y=nullmove.To.x=nullmove.To.y=-1;
    }
};

#endif // SEARCHENGINE_H
