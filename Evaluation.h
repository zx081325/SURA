#ifndef EVALUATION_H
#define EVALUATION_H

#include "Generator.h"
#include "Define.h"

class Evaluation
{
public:
    Evaluation();
    ~Evaluation();
    double Evaluate(BYTE position[6][6],int side);
};

#endif // EVALUATION_H
