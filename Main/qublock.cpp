#include "qublock.h"
#include "ui_qublock.h"

QuBlock::QuBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuBlock)
{
    ui->setupUi(this);
    ui->first->setScaledContents(true);
    ui->second->setScaledContents(true);
    ui->third->setScaledContents(true);
}

QuBlock::~QuBlock()
{
    delete ui;
    printf("block (%d,%d) removed.\n",x,y);
}

void QuBlock::initAtlas(QPixmap& a, QPixmap& b, QPixmap& c,int xin,int yin)
{
    ui->first->setPixmap(a);
    ui->second->setPixmap(b);
    ui->third->setPixmap(c);
    ui->first->show();
    ui->second->show();
    ui->third->show();
    x = xin;
    y = yin;
}
