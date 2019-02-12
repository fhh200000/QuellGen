#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include "quellblock.h"
#include <QFileDialog>
#include <cstdio>
#ifdef Q_OS_LINUX
#define SEPARATOR "\n"
#elif define Q_OS_WIN
#define SEPARATOR "\r\n"
#elif defined Q_OS_MAC
#define SEPARATOR "\r"
#endif
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("就绪",-1);
    this->ui->pushButton->hide();
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open_selected()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_selected()));
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
    if(!pop)
    {
        pop = new ItWorksPop(this);
        pop->setModal(false);
        pop->initMap(14,10,layer0,layer1,layer2);
    }
    pop->show();
    printf(SEPARATOR);
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
     //为人类阅读而优化2333
     FILE *fp;
     fp = fopen(fileName.toStdString().data(),"r+");
     fscanf(fp,"[QuellGen level data file]");
     fscanf(fp,SEPARATOR);
     fscanf(fp,"Level name:%s",name);
     fscanf(fp,SEPARATOR);
     fscanf(fp,"Best solution:%d",&steps);
     fscanf(fp,SEPARATOR);
     fscanf(fp,"Width:%d",&w);
     fscanf(fp,SEPARATOR);
     fscanf(fp,"Height:%d",&h);
     fscanf(fp,SEPARATOR);
     if(!layer0)
     {
        //释放上一次的内存
         delete[](layer0);
         delete[](layer1);
         delete[](layer2);
         printf("Previous data released.\n");
     }
     layer0 = new int[w*h];
     layer1 = new int[w*h];
     layer2 = new int[w*h];
     fscanf(fp,"Layer 0:");
     fprintf(fp,SEPARATOR);
     int k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer0[k++]);
         }
         fscanf(fp,SEPARATOR);
     }
     fscanf(fp,"Layer 1:");
     fprintf(fp,SEPARATOR);
     k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer1[k++]);
         }
         fscanf(fp,SEPARATOR);
     }
     fscanf(fp,"Layer 2:");
     fprintf(fp,SEPARATOR);
     k=0;
     for(unsigned int i=0;i<h;i++)
     {
         for(unsigned int j=0;j<w;j++)
         {
             fscanf(fp,"%d",&layer2[k++]);
         }
         fscanf(fp,SEPARATOR);
     }
     fclose(fp);
     on_pushButton_clicked();
}
void MainWindow::save_selected()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setWindowTitle(tr("打开关卡"));
    fileDialog->setDirectory(".");
    fileDialog->setDefaultSuffix("gmp");
    fileDialog->setNameFilter(tr("Quell关卡文件(*.gmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if(fileDialog->exec())
    {
         fileName = fileDialog->selectedFiles().first();
    }
    FILE *fp;
    fp = fopen(fileName.toStdString().data(),"w+");
    fprintf(fp,"[QuellGen level data file]");
    fprintf(fp,SEPARATOR);
    fprintf(fp,"Level name:%s",name);
    fprintf(fp,SEPARATOR);
    fprintf(fp,"Best solution:%d",steps);
    fprintf(fp,SEPARATOR);
    fprintf(fp,"Width:%d",w);
    fprintf(fp,SEPARATOR);
    fprintf(fp,"Height:%d",h);
    fprintf(fp,SEPARATOR);
    fscanf(fp,"Layer 0:");
    fprintf(fp,SEPARATOR);
    int k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer0[k++]);
        }
        fprintf(fp,SEPARATOR);
    }
    fprintf(fp,"Layer 1:");
    fprintf(fp,SEPARATOR);
    k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer1[k++]);
        }
        fprintf(fp,SEPARATOR);
    }
    fprintf(fp,"Layer 2:");
    fprintf(fp,SEPARATOR);
    k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer2[k++]);
        }
        fprintf(fp,SEPARATOR);
    }
    fclose(fp);
}
