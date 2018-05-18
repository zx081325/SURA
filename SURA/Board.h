#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
#include "Define.h"
#include "Searchengine.h"
#include "Generator.h"
#include <QPushButton>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    int _r,_d,set_x,set_y;
    QPoint _select;
    BYTE position[6][6];
    BYTE _Side;
    bool AI_first;
    QPushButton *button;
    CHESSMOVE move1,move2;
    void darwStone(QPainter& painter);
    QPoint center(int row,int col);
    QPoint getRowCol(QPoint pt);
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void AI_Play();
    void moveStone(CHESSMOVE move);
    bool canMove(int From_row, int From_col, int To_row, int To_col);
    void cancel();
signals:

public slots:
};

#endif // BOARD_H
