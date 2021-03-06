#include "ChooseDlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(_buttons[0] = new QPushButton("电脑先下"));
    lay->addWidget(_buttons[1] = new QPushButton("玩家先下"));

    for(int i=0; i<2; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<2; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_sel = i;
            break;
        }
    }
    accept();
}

ChooseDlg::~ChooseDlg()
{

}
