#include "itworkspop.h"
#include "ui_itworkspop.h"
#include <QDesktopWidget>
#include "quellblock.h"
#include "qublock.h"
#include <unistd.h>
ItWorksPop::ItWorksPop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItWorksPop)
{
    ui->setupUi(this);
    QPixmap im;
    im.load("/run/media/fhh/Utilities/QuellGen/Resources/bgdefault.png");
    ui->bg->setPixmap(im);
    ui->bg->setScaledContents(true);
    move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
}

ItWorksPop::~ItWorksPop()
{
    delete ui;
}
void ItWorksPop::initMap(void)
{
    QuBlock *qu[5];
    que = qu;
    QPixmap* atlasp = QuellBlock::atlasp;
    for(int i=0;i<5;i++)
    {
        qu[i] = new QuBlock(this);
        qu[i]->initAtlas(atlasp[132],atlasp[22],atlasp[151]);
        qu[i]->setGeometry(i*48,0,48,48);
        qu[i]->show();
    }
    this->removeMap(5);
}
void ItWorksPop::removeMap(int size)
{
    sleep(1);

    for(int i=0;i<size;i++)
    {
        que[i]->hide();
        delete(que[i]);
    }
    que=nullptr;
}
