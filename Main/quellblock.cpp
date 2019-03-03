#include "quellblock.h"
#include "mainwindow.h"
QPixmap* QuellBlock::atlasp;
QPixmap* QuellBlock::rockstyle1;
QPixmap* QuellBlock::rockstyle2;
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
    //Rocks style 1
    rockstyle1 = new QPixmap[49];
    location = location + "rock-style1/";
    for(int i=0;i<=48;i++)
    {
        filelocation = location + QString::number(i) + ".png";
        rockstyle1[i].load(filelocation);
        printf("%d of 48 rock-style1 initalized.\n",i);
    }
    //Rocks style 2
    rockstyle2 = new QPixmap[49];
    location = QCoreApplication::applicationDirPath()+"/Resources/Atlas/Zen/rock-style2/";
    for(int i=0;i<=48;i++)
    {
        filelocation = location + QString::number(i) + ".png";
        rockstyle2[i].load(filelocation);
        if(!rockstyle2[i].isNull())
            printf("%d of 48 rock-style2 initalized.\n",i);
    }
}

