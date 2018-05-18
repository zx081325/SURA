#ifndef DEFINE_H
#define DEFINE_H


typedef char BYTE;

const int _red=1;
const int _black=2;
const int _blank = 0;

typedef struct _chessmanposition
{
    int x;
    int y;
}CHESSNAMPOS;

typedef struct _chessmove
{
    short To_Side;
    short Side;
    CHESSNAMPOS From;
    CHESSNAMPOS To;
    double Score;
    bool operator==(const _chessmove & move)
    {
        if (From.x == move.From.x && From.y == move.From.y && To.x == move.To.x && To.y == move.To.y)
            return true;
        else
            return false;

    }
    bool operator<(const _chessmove& move)const
    {
        return Score > move.Score;
    }
}CHESSMOVE;



class Define
{
public:
    Define();
    ~Define();
};

#endif // DEFINE_H
