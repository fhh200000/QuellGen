#include "osspecificvars.h"
#include "qublock.h"
#include "ui_qublock.h"
#include "mainwindow.h"
QuBlock::QuBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuBlock)
{
    ui->setupUi(this);
    ui->first->setScaledContents(true);
    ui->second->setScaledContents(true);
    ui->third->setScaledContents(true);
    connect(ui->click,SIGNAL(clicked()),this,SLOT(clicked()));
    ui->first->resize(BLOCKSIZE,BLOCKSIZE);
    ui->second->resize(BLOCKSIZE,BLOCKSIZE);
    ui->third->resize(BLOCKSIZE,BLOCKSIZE);
    ui->click->resize(BLOCKSIZE,BLOCKSIZE);
    this->resize(BLOCKSIZE,BLOCKSIZE);
}

QuBlock::~QuBlock()
{
    delete ui;
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
void QuBlock::reloadAtlas(QPixmap& a)
{
    ui->first->setPixmap(a);
}
void QuBlock::clicked()
{
    MainWindow::self->loadinfo(x,y);
}
