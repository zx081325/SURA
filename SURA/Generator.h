#ifndef GENERATOR_H
#define GENERATOR_H

#include "Define.h"

class Generator
{
public:
    Generator();
    ~Generator();
    int m_nMoveCount;
    int taking[3];
    CHESSMOVE m_nMoveList[12][200];
    void AddMove(int nFromX, int nFromY, int nToX, int nToY,int nSide, int nPly);
    int CreatePossibleMove(char position[6][6], int nPly, int nSide);
};

#endif // GENERATOR_H
