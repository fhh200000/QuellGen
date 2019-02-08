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
void ItWorksPop::initMap(int w,int h,int layer0[],int layer1[],int layer2[])
{
    int tmp = -1;
    que = new QuBlock*[w*h];
    QPixmap* atlasp = QuellBlock::atlasp;
    for(int i=0;i<h;i++)//竖排
    {
        for(int j=0;j<w;j++)//竖排
        {
            que[++tmp] = new QuBlock(this);
            que[tmp]->initAtlas(atlasp[layer0[tmp]],atlasp[layer1[tmp]],atlasp[layer2[tmp]]);
            que[tmp]->setGeometry(i*48,j*48,48,48);
            que[tmp]->show();
        }
    }
    this->resize(48*h,48*w);
}
void ItWorksPop::removeMap(int size)
{
    for(int i=0;i<size;i++)
    {
        que[i]->hide();
        delete(que[i]);
    }
    que=nullptr;
}
