#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include <QFileDialog>
#include <cstdio>
#include <iostream>
#include <aboutgame.h>
#include "aboutauthor.h"
#include "osspecificvars.h"
MainWindow* MainWindow::self;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("就绪",-1);
    this->ui->pushButton->hide();
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open_selected()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_selected()));
    connect(ui->actionGame,SIGNAL(triggered()),this,SLOT(aboutGame()));
    connect(ui->actionAuthor,SIGNAL(triggered()),this,SLOT(aboutAuthor()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(showinfo()));
    name = new char[32];
    MainWindow::self = this;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showinfo()
{
    info = new InfoEditor(this);
    info->show();
}
void MainWindow::aboutGame()
{
    AboutGame *ab = new AboutGame();
    ab->show();
}
void MainWindow::aboutAuthor()
{
    AboutAuthor *ab = new AboutAuthor();
    ab->show();
}
void MainWindow::on_pushButton_2_clicked()
{
    pop->removeMap();
    ui->detailed->setDisabled(true);
    ui->statusBar->showMessage("已清除数据");
}

void MainWindow::on_pushButton_clicked()
{
    if(!pop)
    {
        pop = new ItWorksPop(this);
        pop->setModal(false);
    }
    pop->show();
}
void  MainWindow::refresh(unsigned w, unsigned h)
{
    if(!pop)
    {
        pop = new ItWorksPop(this);
        pop->setModal(false);
    }
    pop->removeMap();
    pop->initMap(static_cast<int>(w),static_cast<int>(h),layer0,layer1,layer2);
    pop->show();
}
void MainWindow::open_selected()
{
     QFileDialog *fileDialog = new QFileDialog(this);
     fileDialog->setWindowTitle(tr("打开关卡"));
     fileDialog->setDirectory(QCoreApplication::applicationDirPath());
     fileDialog->setNameFilter(tr("Quell关卡文件(*.gmp)"));
     fileDialog->setFileMode(QFileDialog::ExistingFile);
     fileDialog->setViewMode(QFileDialog::Detail);
     QString fileName;
     if(fileDialog->exec())
     {
          fileName = fileDialog->selectedFiles().first();
     }
     qDebug()<<fileName<<endl;
     if(fileName=="")return;
     //为人类阅读而优化2333
     FILE *fp;
     fp = fopen(fileName.toStdString().data(),"r+");
     fscanf(fp,"[QuellGen level data file]\n");
     fscanf(fp,"Level name:%[^\n]",name);
     fscanf(fp,"\n");
     fscanf(fp,"Best solution:%d\n",&steps);
     /*solution = new int[static_cast<unsigned>(steps)];
     fscanf(fp,"Solution:");
     for (int i=0;i<steps;i++)
     {
        fscanf(fp,"%d",&solution[i]);
     }
     fscanf(fp,"\n");
     soludrop = new int[static_cast<unsigned>(steps)];
     fscanf(fp,"Soludrop:");
     for (int i=0;i<steps;i++)
     {
        fscanf(fp,"%d",&soludrop[i]);
     }*/
     steplist = new std::vector<step>();
     fscanf(fp,"Solution:");
     for (int i=0;i<steps;i++)
     {
         int tmpsolution;
         fscanf(fp,"%d",&tmpsolution);
         steplist->push_back(step{0,tmpsolution});
     }
     fscanf(fp,"\n");
     fscanf(fp,"Soludrop:");
     for (int i=0;i<steps;i++)
     {
         int tmpsoludrop;
         fscanf(fp,"%d",&tmpsoludrop);
         steplist->data()[i].drop=tmpsoludrop;
     }
     fscanf(fp,"\n");
     fscanf(fp,"Width:%d\n",&w);
     fscanf(fp,"Height:%d\n",&h);
     fscanf(fp,"Left space:%d\n",&lspace);
     fscanf(fp,"Right space:%d\n",&rspace);
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
     refresh(w,h);
}
void MainWindow::save_selected()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setWindowTitle(tr("保存关卡"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setDefaultSuffix("gmp");
    fileDialog->setNameFilter(tr("Quell关卡文件(*.gmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if(fileDialog->exec())
    {
         fileName = fileDialog->selectedFiles().first();
    }
    if(fileName=="")return;
    FILE *fp;
    fp = fopen(fileName.toStdString().data(),"w+");
    fprintf(fp,"[QuellGen level data file]\n");
    fprintf(fp,"Level name:%s\n",name);
    fprintf(fp,"Best solution:%d\n",steps);
    fprintf(fp,"Solution:");
    for (int i=0;i<steps;i++)
    {
        fprintf(fp,"%d ",steplist->data()[i].direction);
    }
    /*for (int i=0;i<steps;i++)
    {
       fprintf(fp,"%d ",solution[i]);
    }*/
    fprintf(fp,"\n");
    fprintf(fp,"Soludrop:");
    /*for (int i=0;i<steps;i++)
    {
       fprintf(fp,"%d ",soludrop[i]);
    }*/
    for (int i=0;i<steps;i++)
    {
        fprintf(fp,"%d ",steplist->data()[i].drop);
    }
    fprintf(fp,"\n");
     fprintf(fp,"Width:%d\n",w);
    fprintf(fp,"Height:%d\n",h);
    fprintf(fp,"Left space:%d\n",lspace);
    fprintf(fp,"Right space:%d\n",rspace);
    fprintf(fp,"Layer 0:\n");
    int k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer0[k++]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"Layer 1:\n");
    k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer1[k++]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"Layer 2:\n");
    k=0;
    for(unsigned int i=0;i<h;i++)
    {
        for(unsigned int j=0;j<w;j++)
        {
            fprintf(fp,"%d ",layer2[k++]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"[End of file]");
    fclose(fp);
}
void MainWindow::loadinfo(int x,int y)
{
    QString data = QString("选中方块(%1,%2)").arg(x).arg(y);
    ui->statusBar->showMessage(data,-1);
    ui->detailed->setEnabled(true);
    ui->l1->setCurrentIndex(layer0[x+y*static_cast<int>(w)]);
}
