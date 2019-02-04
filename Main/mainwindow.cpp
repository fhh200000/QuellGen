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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pop = new ItWorksPop(this);
    pop->setModal(false);
    //pop->setFixedWidth(1000);
    //pop->setFixedHeight(800);
    pop->initMap();
    pop->show();

}
