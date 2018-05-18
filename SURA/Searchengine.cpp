#include "Searchengine.h"
#include "string.h"
#include "algorithm"

Searchengine::Searchengine()
{

}

Searchengine::~Searchengine()
{

}

Generator *mg;

BYTE Searchengine:: MakeMove(CHESSMOVE *move)
{
    BYTE n_side;
    n_side = CurPosition[move->To.x][move->To.y];
    CurPosition[move->To.x][move->To.y] = CurPosition[move->From.x][move->From.y];
    CurPosition[move->From.x][move->From.y] = 0;
    player=3-player;
    return n_side;
}

void Searchengine::UnMakeMove(CHESSMOVE *move, BYTE nChessID)//恢复棋盘
{
    CurPosition[move->From.x][move->From.y] = CurPosition[move->To.x][move->To.y];
    CurPosition[move->To.x][move->To.y] = nChessID;
    player=3-player;
}


CHESSMOVE Searchengine:: SearchGoodMove(BYTE position[6][6],int nply,int side)
{
    init();
    memcpy(CurPosition,position,sizeof(CurPosition));
    bestmove = nullmove;
    player=side;Maxdepth=nply;
    ms(-20000, 20000, nply);
    return bestmove;
}

double Searchengine::ms(double alpha, double beta, int depth)
{
    double score;
    double best = -20000;
    Generator As;
    Evaluation Ev;
    if (depth == 0)
    {
        best = -Ev.Evaluate(CurPosition,3-player);
        return best;
    }
    int num = As.CreatePossibleMove(CurPosition,depth,player);
    if (num == 0)
    {
        return -10000-depth;
    }
    /*
    if(depth==Maxdepth)
    {
        for(int i=0;i<num;i++)
        {
            int type = MakeMove(CurPosition,&As.m_nMoveList[depth][i]);
            As.m_nMoveList[depth][i].Score=Ev.Evaluate(CurPosition,3-player);
            UnMakeMove(CurPosition,&As.m_nMoveList[depth][i],type);
        }
    }
    std::sort( As.m_nMoveList[depth], As.m_nMoveList[depth]+num);
    */
    for(int i=0;i<num;i++)
    {
        int type = MakeMove(&As.m_nMoveList[depth][i]);
        score=-ms(-beta,-alpha,depth-1);
        UnMakeMove(&As.m_nMoveList[depth][i],type);
        if(score>best)
        {
            best=score;
            if(depth==Maxdepth)
            {
                 bestmove=As.m_nMoveList[depth][i];
                 bestmove.Score=best;
            }
            if(score>alpha)
                alpha=score;
            if(score>beta)
                break;
        }
    }
    return best;
}
