#ifndef STONE_H
#define STONE_H


class Stone
{
public:
    Stone();
    ~Stone();

    int _row;
    int _col;
    int _id;
    int _type;
    bool _dead;

    void init(int id)
    {
        _id=id;
        _dead=false;
        if(id<12)
        {
            _type=2;
            _row=id/6;
            _col=id%6;
        }
        else
        {
            _type=1;
            _row=id/6+2;
            _col=id%6;
        }
    }
};

#endif // STONE_H
