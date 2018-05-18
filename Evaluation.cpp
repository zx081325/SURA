#include "Evaluation.h"
#include "string.h"

Evaluation::Evaluation()
{

}

Evaluation::~Evaluation()
{

}

double Evaluation:: Evaluate(BYTE position[6][6],int side)
{
    double value[6];
    memset(value, 0, sizeof(value));
    double P[6][6] = { {1,3,2,2,3,1}, {3,6,5,5,6,3}, {2,5,4,4,5,2}, {2,5,4,4,5,2}, {3,6,5,5,6,3}, {1,3,2,2,3,1} };
    for (int i = 0;i < 6;i++)
    {
        for (int j = 0;j < 6;j++)
        {
            if (position[i][j] == side)
            {
                value[0]++;
                value[2] += P[i][j];
            }
            if (position[i][j] == 3-side)
            {
                value[1]++;
                value[2] -= P[i][j];
            }
        }
    }
    Generator As;
    As.taking[_red] = As.taking[_black] = 0;
    int num1=As.CreatePossibleMove(position, 0, side);
    int num2=As.CreatePossibleMove(position, 0, 3-side);
    if(num1==0&&num2)
    {
        return -10000;
    }
    else if(num1&&num2==0)
    {
        return 10000;
    }
    value[3] = 30 * As.taking[side] - 30 * As.taking[3 - side];
    return (value[0]-value[1])*50 + value[2]*3  + value[3];
}
