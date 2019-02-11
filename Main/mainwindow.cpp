#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include "quellblock.h"
#include <QFileDialog>
#include <cstdio>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("就绪",-1);
    this->ui->pushButton->hide();
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open_selected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    pop->removeMap();
}

void MainWindow::on_pushButton_clicked()
{
     qDebug()<<MainWindow::data<<endl;
     pop = new ItWorksPop(this);
     pop->setModal(false);
     int layer1[] = {2,10,10,10,10,10,10,10,10,10,10,10,10,3,11,15,14,14,14,14,14,14,16,15,16,16,15,13,11,15,0,0,0,16,0,0,0,0,135,0,16,13,11,17,0,0,45,19,0,0,132,132,0,0,19,13,11,18,0,0,18,0,137,0,0,133,133,132,19,13,11,17,0,0,0,0,0,0,134,134,133,0,18,13,11,21,0,0,0,0,0,0,0,0,134,0,22,13,11,22,0,0,0,0,0,21,0,0,0,0,22,13,11,20,22,20,20,21,20,20,22,20,22,22,21,13,4,12,12,12,12,12,12,12,12,12,12,12,12,5};
     int layer2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,74,0,0,0,0,0,0,0,0,0,0,0,0,0,82,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,91,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100,52,0,0,0,0,0,0,0,0,0,0,0,0,0,92,0,0,0,97,98,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     int layer3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     pop->initMap(14,10,layer1,layer2,layer3);
     pop->show();
     qDebug()<<MainWindow::data<<endl;
}
void MainWindow::open_selected()
{
     QFileDialog *fileDialog = new QFileDialog(this);
     fileDialog->setWindowTitle(tr("打开关卡"));
     fileDialog->setDirectory(".");
     fileDialog->setNameFilter(tr("Quell关卡文件(*.gmp)"));
     fileDialog->setFileMode(QFileDialog::ExistingFile);
     fileDialog->setViewMode(QFileDialog::Detail);
     QString fileName;
     if(fileDialog->exec())
     {
          fileName = fileDialog->selectedFiles().first();
     }
     qDebug()<<fileName<<endl;
     int steps = 0;
     unsigned int w,h;
     //为人类阅读而优化2333
     FILE *fp;
     char* name = new char[32];
     fp = fopen(fileName.toStdString().data(),"r+");
     fscanf(fp,"[QuellGen level data file]\n");
     fscanf(fp,"Level name:%s\n",name);
     fscanf(fp,"Best solution:%d\n",&steps);
     fscanf(fp,"Width:%d\n",&w);
     fscanf(fp,"Height:%d\n",&h);
     int *layer0 = new int[w*h];
     int *layer1 = new int[w*h];
     int *layer2 = new int[w*h];
     fscanf(fp,"Layer 0:\n");
     int k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer0[k++]);
         }
         fscanf(fp,"\n");
     }
     fscanf(fp,"Layer 1:\n");
     k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer1[k++]);
         }
         fscanf(fp,"\n");
     }
     fscanf(fp,"Layer 2:\n");
     k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer2[k++]);
         }
         fscanf(fp,"\n");
     }
     fclose(fp);
     delete(fp);
     pop = new ItWorksPop(this);
     pop->setModal(false);
     pop->initMap(14,10,layer0,layer1,layer2);
     delete[] layer0;
     delete[] layer1;
     delete[] layer2;
     pop->show();
}
