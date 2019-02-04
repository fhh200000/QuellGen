#include "itworkspop.h"
#include "ui_itworkspop.h"
#include <QDesktopWidget>
#include "quellblock.h"
#include "qublock.h"
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
void ItWorksPop::initMap(void){
    QuBlock *qu = new QuBlock();
    this->ui->gridLayout->setAlignment(Qt::AlignTop);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPixmap* atlasp = QuellBlock::atlasp;
    qu->initAtlas(atlasp[132],atlasp[22],atlasp[151]);
    /*QSize size = QSize(48,48);
    QLabel* map[3];
    map[0] = new QLabel();
    map[1] = new QLabel();
    map[2] = new QLabel();
    map[0]->setScaledContents(true);
    map[1]->setScaledContents(true);
    map[2]->setScaledContents(true);
    map[0]->setPixmap(atlasp[132]);
    map[0]->setSizePolicy(sizePolicy);
    printf("layer 0 loaded with atlas 131.\n");
    map[1]->setPixmap(atlasp[22]);
    map[1]->setSizePolicy(sizePolicy);
    printf("layer 1 loaded with atlas 22.\n");
    map[2]->setPixmap(atlasp[151]);
    map[2]->setSizePolicy(sizePolicy);
    printf("layer 2 loaded with atlas 151.\n");
    map[0]->setMaximumSize(size);
    map[1]->setMaximumSize(size);
    map[2]->setMaximumSize(size);
    this->ui->gridLayout->addWidget(map[0],0,0,1,1);
    this->ui->gridLayout->addWidget(map[1],1,0,1,1);
    this->ui->gridLayout->addWidget(map[2],1,0,1,1);
    map[0]->show();
    map[1]->show();
    map[2]->show();*/
    ui->gridLayout->addWidget(qu,0,0,1,1);
    qu->show();
    qu->first.show();
    qu->second.show();
    qu->third.show();
    printf("%d\n",qu->first.pixmap()->depth());
    ui->bg->resize(256,256);
    ui->bg->setPixmap(atlasp[132]);
    ui->bg->setVisible(false);
}
