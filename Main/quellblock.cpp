#include "quellblock.h"
#include "mainwindow.h"
QPixmap* QuellBlock::atlasp;
QuellBlock::QuellBlock()
{

}
QuellBlock::~QuellBlock()
{

}
void QuellBlock::loadAtlas(void)
{
    atlasp = new QPixmap[200];
    QString location = QCoreApplication::applicationDirPath()+"/Resources/Atlas/Zen/";
    QString filelocation;
    for(int i=0;i<=174;i++)
    {
        filelocation = location + QString::number(i) + ".png";
        printf("%d of 174 atlas initalized.\n",i);
        atlasp[i].load(filelocation);            
    }
}

