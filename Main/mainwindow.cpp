#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include "quellblock.h"
#include <QFileDialog>
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
    /*int layer1[] = {14,15,132,163,174,25};
    int layer2[] = {0,23,0,0,0,23};
    int layer3[] = {155,0,0,155,0,0};
    pop->initMap(2,3,layer1,layer2,layer3);*/
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
    //定义文件对话框类
        QFileDialog *fileDialog = new QFileDialog(this);
        //定义文件对话框标题
        fileDialog->setWindowTitle(tr("打开关卡"));
        //设置默认文件路径
        fileDialog->setDirectory(".");
        //设置文件过滤器
        fileDialog->setNameFilter(tr("Quell关卡文件(*.gmp)"));
        //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
        fileDialog->setFileMode(QFileDialog::ExistingFile);
        //设置视图模式
        fileDialog->setViewMode(QFileDialog::Detail);
        //打印所有选择的文件的路径
        QString fileName;
        if(fileDialog->exec())
        {
            fileName = fileDialog->selectedFiles().first();
        }
        qDebug()<<fileName<<endl;
        QFile *fp = new QFile(fileName);
        fp->open(QIODevice::ReadOnly | QIODevice::Text);
        data = fp->readAll();
        fp->close();
        qDebug()<<MainWindow::data<<endl;
        delete fp;
}
