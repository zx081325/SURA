#include <QApplication>
#include "Board.h"
#include "ChooseDlg.h"
#include <QPushButton>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    Board board;
    board.AI_first=false;
    //board.AI_Play();

    ChooseDlg dlg;
    if(dlg.exec() != QDialog::Accepted)
        return 0;

    if(dlg._sel == 0)
    {
        board.AI_first=true;
        board.AI_Play();
    }
    else if(dlg._sel == 1)
    {
         board.AI_first=false;
    }
    board.show();
    return app.exec();
}


