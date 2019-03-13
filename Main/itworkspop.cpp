#include "itworkspop.h"
#include "ui_itworkspop.h"
#include <QDesktopWidget>
#include "qublock.h"
#include <unistd.h>
#include "osspecificvars.h"
#include "mainwindow.h"
ItWorksPop::ItWorksPop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItWorksPop)
{
    ui->setupUi(this);
    QPixmap im;
    im.load(QCoreApplication::applicationDirPath()+"/Resources/bgdefault.png");
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
            que[tmp]->setGeometry(j*BLOCKSIZE,i*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            que[tmp]->show();
            if(layer0[tmp]>175)
            {
                extrablock a={i*w+j,layer0[tmp]};
                spec.push_back(a);
            }
        }
    }
    if(spec.size())
    {
        for(std::vector<extrablock>::iterator iter = spec.begin();iter !=spec.end();iter++)
        {
            this->reloadBlock(*iter,w);
        }
    }
    this->resize(BLOCKSIZE*w,BLOCKSIZE*h);
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
void ItWorksPop::reloadBlock(extrablock in, int width)
{
    QPixmap * rock = QuellBlock::rockstyle1;
    if(MainWindow::self->lvlindex==4||MainWindow::self->lvlindex==7)
        rock = QuellBlock::rockstyle2;
    switch (in.index)
    {
        case 176:
        {
            que[in.count]->reloadAtlas(rock[2]);
            break;
        }
        case 177:
        {
            que[in.count]->reloadAtlas(rock[3]);
            break;
        }
        case 178:
        {
            que[in.count]->reloadAtlas(rock[4]);
            break;
        }
        case 179:
        {
            que[in.count]->reloadAtlas(rock[8]);
            break;
        }
        case 184:
        {
            que[in.count]->reloadAtlas(rock[1]);
            que[in.count+width]->reloadAtlas(rock[9]);
            break;
        }
        case 185:
        {
            que[in.count]->reloadAtlas(rock[16]);
            que[in.count+width]->reloadAtlas(rock[24]);
            break;
        }
        case 186:
        {
            que[in.count]->reloadAtlas(rock[41]);
            que[in.count+1]->reloadAtlas(rock[42]);
            break;
        }
        case 187:
        {
            que[in.count]->reloadAtlas(rock[43]);
            que[in.count+1]->reloadAtlas(rock[44]);
            break;
        }
        case 188:
        {
            que[in.count]->reloadAtlas(rock[5]);
            que[in.count+1]->reloadAtlas(rock[6]);
            que[in.count+width]->reloadAtlas(rock[13]);
            que[in.count+width+1]->reloadAtlas(rock[14]);
            break;
        }
        case 189:
        {
            que[in.count]->reloadAtlas(rock[7]);
            que[in.count+width]->reloadAtlas(rock[15]);
            que[in.count+width*2]->reloadAtlas(rock[23]);
            break;
        }
        case 190:
        {
            que[in.count]->reloadAtlas(rock[10]);
            que[in.count+1]->reloadAtlas(rock[11]);
            que[in.count+2]->reloadAtlas(rock[12]);
            break;
        }
        case 191:
        {
            for(int i=0;i<6;i++)
            {

                que[in.count+i]->reloadAtlas(rock[17+i]);
            }
            break;

        }
        case 192:
        {
            que[in.count]->reloadAtlas(rock[25]);
            que[in.count+width]->reloadAtlas(rock[33]);
            que[in.count+width+1]->reloadAtlas(rock[34]);
            break;
        }
        case 193:
        {
            que[in.count]->reloadAtlas(rock[29]);
            que[in.count+1]->reloadAtlas(rock[30]);
            que[in.count+width]->reloadAtlas(rock[37]);
            break;
        }
        case 194:
        {
            que[in.count]->reloadAtlas(rock[27]);
            que[in.count+1]->reloadAtlas(rock[28]);
            que[in.count+width+1]->reloadAtlas(rock[36]);
            break;
        }
        case 195:
        {
            que[in.count]->reloadAtlas(rock[32]);
            que[in.count+width-1]->reloadAtlas(rock[39]);
            que[in.count+width]->reloadAtlas(rock[40]);
            break;
        }
    }
}
void changeData(int data);
void ItWorksPop::changeBlock(int a, int b, int c)
{
    QPixmap* atlasp = QuellBlock::atlasp;
    que[MainWindow::self->pos]->changeAtlas(atlasp[a],atlasp[b],atlasp[c]);
    if(a>175)
    {
        reloadBlock({MainWindow::self->pos,a},static_cast<int>(MainWindow::self->w));
    }
    if(a>180)
        {
            changeData(a);
        }
}
void changeData(int data)
{
    switch(data)
    {
    case 184:
    {
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        break;
    }
    case 185:
    {
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        break;
    }
    case 186:
    {
        MainWindow::self->layer0[MainWindow::self->pos+1]=175;
        break;
    }
    case 187:
    {
        MainWindow::self->layer0[MainWindow::self->pos+1]=175;
        break;
    }
    case 188:
    {
        MainWindow::self->layer0[MainWindow::self->pos]=data;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)+1]=175;
        break;
    }
    case 189:
    {
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)*2]=175;
        break;
    }
    case 190:
    {
        MainWindow::self->layer0[MainWindow::self->pos+1]=175;
        MainWindow::self->layer0[MainWindow::self->pos+2]=175;
        break;
    }
    case 191:
    {
        for(int i=1;i<6;i++)
        {

            MainWindow::self->layer0[MainWindow::self->pos+i]=175;
        }
        break;

    }
    case 192:
    {
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)+1]=175;
        break;
    }
    case 193:
    {
        MainWindow::self->layer0[MainWindow::self->pos+1]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        break;
    }
    case 194:
    {
        MainWindow::self->layer0[MainWindow::self->pos+1]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)+1]=175;
        break;
    }
    case 195:
    {
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)-1]=175;
        MainWindow::self->layer0[MainWindow::self->pos+static_cast<int>(MainWindow::self->w)]=175;
        break;
    }
    }
}
