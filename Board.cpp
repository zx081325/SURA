#include "Board.h"
#include <QPainter>
#include <QMouseEvent>


Board::Board(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(660, 500);
    setMaximumSize(660, 500);

    _select.rx()=_select.ry()=-1;
    _Side=2;//1-红棋，2-黑棋
   for(int i=0;i<6;i++)
   {
       position[0][i]=position[1][i]=2;//黑棋
       position[2][i]=position[3][i]=0;//空白
       position[4][i]=position[5][i]=1;//红棋
   }

   button = new QPushButton("悔棋",this);
   button->setGeometry(520,220,100,50); //前两个参数是位置坐标，后两个参数是按钮的尺寸。
   QObject::connect(button, &QPushButton::clicked, this , Board::cancel);
}

void Board::cancel()
{
    position[move2.To.x][move2.To.y]=move2.To_Side;
    position[move2.From.x][move2.From.y]=move2.Side;

    position[move1.To.x][move1.To.y]=move1.To_Side;
    position[move1.From.x][move1.From.y]=move1.Side;

    repaint();
}


void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    _d=45;//棋盘间距
    _r=20;//棋子半径
    set_x=140,set_y=80;//棋盘偏移量

    //画线段
    for(int i=1;i<=6;i++)
    {
        painter.drawLine(QPoint(set_x+_d,i*_d+set_y),QPoint(6*_d+set_x,i*_d+set_y));
    }
    for(int i=1;i<=6;i++)
    {
        painter.drawLine(QPoint(i*_d+set_x,set_y+_d),QPoint(i*_d+set_x,6*_d+set_y));
    }
    //画弧线
     painter.drawArc(set_x,set_y,2*_d,2*_d,0*16,270*16);
     painter.drawArc(set_x-_d,set_y-_d,4*_d,4*_d,0*16,270*16);

     painter.drawArc(set_x+5*_d,set_y,2*_d,2*_d,-90*16,270*16);
     painter.drawArc(set_x+4*_d,set_y-_d,4*_d,4*_d,-90*16,270*16);

     painter.drawArc(set_x,set_y+5*_d,2*_d,2*_d,90*16,270*16);
     painter.drawArc(set_x-_d,set_y+4*_d,4*_d,4*_d,90*16,270*16);

     painter.drawArc(set_x+5*_d,set_y+5*_d,2*_d,2*_d,180*16,270*16);
     painter.drawArc(set_x+4*_d,set_y+4*_d,4*_d,4*_d,180*16,270*16);

     //画棋子
     darwStone(painter);
}

//用行列求出坐标
QPoint Board::center(int row,int col)
{
    QPoint ret;
    ret.rx()=set_x+(col+1)*_d;
    ret.ry()=set_y+(row+1)*_d;
    return ret;
}


//画棋子
void Board::darwStone(QPainter& painter)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(position[i][j]==_red)
            {
                painter.setBrush(QBrush(QColor(255,0,0)));
                if(_select.rx()==i&&_select.ry()==j)
                    painter.setBrush(QBrush(QColor(200,0,0)));
                painter.drawEllipse(center(i,j),_r,_r);
            }
            else if(position[i][j]==_black)
            {
                painter.setBrush(QBrush(QColor(0,0,0)));
                if(_select.rx()==i&&_select.ry()==j)
                    painter.setBrush(QBrush(QColor(50,50,0)));
                painter.drawEllipse(center(i,j),_r,_r);
            }
        }
    }
}

//用坐标求出行列
QPoint Board::getRowCol(QPoint pt)
{
    QPoint ret;
    ret.ry()=(pt.rx()-_d/2-set_x)/_d;
    ret.rx()=(pt.ry()-_d/2-set_y)/_d;
    return ret;
}

//用走法生成判断移动是否合法
bool Board::canMove(int From_row,int From_col,int To_row,int To_col)
{
    if(position[From_row][From_col]==position[To_row][To_col])
    {
        _select=QPoint(To_row,To_col);//点己方另一个棋子
        return false;
    }
    Generator As;
    As.CreatePossibleMove(position,11,_Side);
    int num=As.m_nMoveCount;
    for(int i=0;i<num;i++)
    {
        if(As.m_nMoveList[11][i].From.x==From_row&&As.m_nMoveList[11][i].From.y==From_col
                &&As.m_nMoveList[11][i].To.x==To_row&&As.m_nMoveList[11][i].To.y==To_col)
            return true;
    }
    return false;
}

//落子
void Board::moveStone(CHESSMOVE move)
{
    position[move.To.x][move.To.y]=move.Side;
    position[move.From.x][move.From.y]=0;
    _Side=3-_Side;
}

//鼠标响应
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if((AI_first==true && _Side==2) || (AI_first==false && _Side==1))
    {
        return ;
    }
    QPoint pt = ev->pos();
    pt=getRowCol(pt);
    if(pt.rx()<0||pt.rx()>5||pt.ry()<0||pt.ry()>5)
        return;
    if(_select.rx()==-1&&position[pt.rx()][pt.ry()]==_Side)
    {
        _select=pt;
        repaint();
    }
    else
    {
        if(canMove(_select.rx(),_select.ry(),pt.rx(),pt.ry()))
        {
            CHESSMOVE move;
            move.From.x=_select.rx();
            move.From.y=_select.ry();
            move.To.x=pt.rx();
            move.To.y=pt.ry();
            move.Side=_Side;
            move1=move2;move2=move;
            move2.To_Side=position[move2.To.x][move2.To.y];
            moveStone(move);
            _select.rx()=_select.ry()=-1;
            repaint();
            AI_Play();
        }
        //repaint()函数会强制产生一个即时的重绘事件,而update()函数只是在Qt下一次处理事件时才调用一次绘制事件。
        repaint();
    }
}

void Board::AI_Play()
{
    Searchengine Search;
    BYTE CurPosition[6][6];
    memcpy(CurPosition,position,sizeof(position));
    move1=move2;
    move2=Search.SearchGoodMove(CurPosition,6,_Side);
    move2.To_Side=position[move2.To.x][move2.To.y];
    moveStone(move2);
}


Board::~Board()
{

}
