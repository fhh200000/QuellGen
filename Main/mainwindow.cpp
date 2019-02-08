#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include "quellblock.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("就绪",-1);
    this->ui->pushButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    pop->removeMap(5);
}

void MainWindow::on_pushButton_clicked()
{
     pop = new ItWorksPop(this);
     pop->setModal(false);
     //pop->setFixedWidth(1000);
     //pop->setFixedHeight(800);
     int layer1[] = {14,15,132,163,174,25,14,14,14,14};
     int layer2[] = {0,23,0,0,0,23,23,0,0,0};
     int layer3[] = {155,0,0,155,0,0,0,156,0,0};
     pop->initMap(2,5,layer1,layer2,layer3);
     pop->show();
}
