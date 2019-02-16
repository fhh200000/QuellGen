#include "itworkspop.h"
#include "ui_itworkspop.h"
#include <QDesktopWidget>
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
    std::vector<extrablock> spec;
    int tmp = -1;
    que = new QuBlock*[static_cast<unsigned long>(w*h)];
    count = w*h;
    QPixmap* atlasp = QuellBlock::atlasp;
    for(int i=0;i<h;i++)//竖排
    {
        for(int j=0;j<w;j++)//竖排
        {
            que[++tmp] = new QuBlock(this);
            que[tmp]->initAtlas(atlasp[layer0[tmp]],atlasp[layer1[tmp]],atlasp[layer2[tmp]],j,i);
            que[tmp]->setGeometry(j*48,i*48,48,48);
            que[tmp]->show();
            if(layer0[tmp]==188)
            {
                extrablock a={i*w+j,w,188,2};
                spec.push_back(a);
            }
        }
    }
    if(spec.size())
    {
        printf("%d,%d,%d,%d\n",spec.data()[0].count,spec.data()[0].width,spec.data()[0].index,spec.data()[0].style);
        this->reloadBlock(spec.data()[0],w);
    }
    this->resize(48*w,48*h);
    this->ui->bg->hide();
}
void ItWorksPop::removeMap()
{
    if(!que)return;
    for(int i=0;i<count;i++)
    {
        que[i]->hide();
        delete(que[i]);
    }
    que=nullptr;
    //this->ui->bg->show();
}
void ItWorksPop::reloadBlock(extrablock in,int width)
{
    QPixmap * rock = (in.style==1)?QuellBlock::rockstyle1:QuellBlock::rockstyle2;
    switch (in.index) {
        case 188:
        {
            que[in.count]->reloadAtlas(rock[5]);
            que[in.count+1]->reloadAtlas(rock[6]);
            que[in.count+width]->reloadAtlas(rock[13]);
            que[in.count+width+1]->reloadAtlas(rock[14]);
        printf("%d\n",in.count);
        }
    }
}
