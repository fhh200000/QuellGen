#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itworkspop.h"
#include <QFileDialog>
#include <cstdio>
#include <iostream>
#include <aboutgame.h>
#include "aboutauthor.h"
#include "osspecificvars.h"
#include "importaction.h"
#include "exportaction.h"
MainWindow* MainWindow::self;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStatus("就绪");
    ui->pushButton_2->hide();
    ui->pushButton->hide();
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open_selected()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_selected()));
    connect(ui->actionGame,SIGNAL(triggered()),this,SLOT(aboutGame()));
    connect(ui->actionAuthor,SIGNAL(triggered()),this,SLOT(aboutAuthor()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(showinfo()));
    connect(ui->actionImport,SIGNAL(triggered()),this,SLOT(import()));
    connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(exportxml()));
    connect(ui->submit,SIGNAL(clicked()),this,SLOT(changeData()));
    name = new char[32];
    MainWindow::self = this;
    //init data strings
    QStringList items= QStringList();
        items <<
                 "0-空区块" <<
                 "1-地图边界" <<
                 "2-左上边框，小" <<
                 "3-右上边框，小" <<
                 "4-左下边框，小" <<
                 "5-右下边框，小" <<
                 "6-右下边框" <<
                 "7-左下边框" <<
                 "8-右上边框" <<
                 "9-左上边框" <<
                 "10-上边框" <<
                 "11-左边框" <<
                 "12-下边框" <<
                 "13-右边框" <<
                 "14-砖样式1，小孔" <<
                 "15-砖样式1，中孔" <<
                 "16-砖样式1，大孔" <<
                 "17-砖样式2，小孔" <<
                 "18-砖样式2，中孔" <<
                 "19-砖样式2，大孔" <<
                 "20-砖样式3，小孔" <<
                 "21-砖样式3，中孔" <<
                 "22-砖样式3，大孔" <<
                 "23-珍珠" <<
                 "24-四面刺" <<
                 "25-刺，朝上" <<
                 "26-刺，朝下" <<
                 "27-刺，朝左" <<
                 "28-刺，朝右" <<
                 "29-旋转刺" <<
                 "30-旋转开关，朝上" <<
                 "31-旋转开关，朝下" <<
                 "32-旋转开关，朝左" <<
                 "33-旋转开关，朝右" <<
                 "34-门，未触发" <<
                 "35-门，已触发" <<
                 "36-" <<
                 "37-" <<
                 "38" <<
                 "39-" <<
                 "40-性别方块，雄" <<
                 "41-性别方块，雌" <<
                 "42-" <<
                 "43-穿越圆环，金色" <<
                 "44-穿越圆环，银色" <<
                 "45-水滴" <<
                 "46-卡关检测，1" <<
                 "47-卡关检测，2" <<
                 "48-卡关检测，3" <<
                 "49-卡关检测，4" <<
                 "50-卡关检测，5" <<
                 "51-卡关检测，6" <<
                 "52-卡关检测，水滴1" <<
                 "53-卡关检测，水滴2" <<
                 "54-卡关检测，水滴3" <<
                 "55-金色珍珠" <<
                 "56-金色砖块" <<
                 "57-木刺，朝上" <<
                 "58-木刺，朝下" <<
                 "59-木刺，朝左" <<
                 "60-木刺，朝右" <<
                 "61-有毒的水滴" <<
                 "62-玫瑰，绽放" <<
                 "63-玫瑰，闭合" <<
                 "64-冰块" <<
                 "65-绿色光线，水平" <<
                 "66-绿色光线，垂直" <<
                 "67-方块装饰，样式1" <<
                 "68-方块装饰，样式2" <<
                 "69-方块装饰，样式3" <<
                 "70-方块装饰，样式4" <<
                 "71-方块装饰，样式5" <<
                 "72-方块装饰，样式6" <<
                 "73-方块装饰，样式7" <<
                 "74-方块装饰，样式8" <<
                 "75-方块装饰，样式9" <<
                 "76-方块装饰，样式10" <<
                 "77-方块装饰，样式11" <<
                 "78-方块装饰，样式12" <<
                 "79-方块装饰，样式13" <<
                 "80-方块装饰，样式14" <<
                 "81-方块装饰，样式15" <<
                 "82-方块装饰，样式16" <<
                 "83-方块装饰，样式17" <<
                 "84-方块装饰，样式18" <<
                 "85-方块装饰，样式19" <<
                 "86-方块装饰，样式20" <<
                 "87-方块装饰，样式21" <<
                 "88-方块装饰，样式22" <<
                 "89-方块装饰，样式23" <<
                 "90-方块装饰，样式24" <<
                 "91-方块装饰，样式25" <<
                 "92-方块装饰，样式26" <<
                 "93-方块装饰，样式27" <<
                 "94-方块装饰，样式28" <<
                 "95-方块装饰，样式29" <<
                 "96-方块装饰，样式30" <<
                 "97-方块装饰，样式31" <<
                 "98-方块装饰，样式32" <<
                 "99-方块装饰，样式33" <<
                 "100-珠宝" <<
                 "101-黄色灯" <<
                 "102-蓝色灯" <<
                 "103-红色灯" <<
                 "104-绿色宝石，可推动" <<
                 "105-" <<
                 "106-灵魂" <<
                 "107-振动方块，未激活" <<
                 "108-振动方块，已激活" <<
                 "109-电闸，已关闭" <<
                 "110-电闸，已开启" <<
                 "111-黄色宝石" <<
                 "112-蓝色宝石" <<
                 "113-红色宝石" <<
                 "114-黄色宝石，可推动" <<
                 "115-蓝色宝石，可推动" <<
                 "116-红色宝石，可推动" <<
                 "117-光照/普通划分区域" <<
                 "118-" <<
                 "119" <<
                 "120-" <<
                 "121-" <<
                 "122-" <<
                 "123-" <<
                 "124-" <<
                 "125-水滴位置指示器" <<
                 "126-隐藏关卡传送圆环" <<
                 "127-时空黑洞传送圆环" <<
                 "128-破坏贴图，程度1" <<
                 "129-破坏贴图，程度2" <<
                 "130-破坏贴图，程度3" <<
                 "131-" <<
                 "132-红色糖果" <<
                 "133-绿色糖果" <<
                 "134-紫色糖果" <<
                 "135-平移器，向上" <<
                 "136-平移器，向下" <<
                 "137-平移器，向左" <<
                 "138-平移器，向右" <<
                 "139-" <<
                 "140-" <<
                 "141-" <<
                 "142-" <<
                 "143-" <<
                 "144-" <<
                 "145-" <<
                 "146-" <<
                 "147-金色圆环，可推动" <<
                 "148-银色圆环，可推动" <<
                 "149-太极方块，已激活" <<
                 "150-太极方块，未激活" <<
                 "151-太极开关，已激活" <<
                 "152-太极开关，未激活" <<
                 "153-莲花方块，已激活" <<
                 "154-莲花方块，未激活" <<
                 "155-莲花开关，已激活" <<
                 "156-莲花开关，未激活" <<
                 "157-绿色水滴" <<
                 "158-绿色珍珠" <<
                 "159-绿色灯" <<
                 "160-绿色灯，关闭" <<
                 "161-" <<
                 "162-蜡烛，青" <<
                 "163-蜡烛，蓝" <<
                 "164-蜡烛，紫" <<
                 "165-蜡烛，紫红" <<
                 "166-蜡烛，粉" <<
                 "167-蜡烛，红" <<
                 "168-蜡烛，橙" <<
                 "169-蜡烛，黄" <<
                 "170-蜡烛，淡绿" <<
                 "171-蜡烛，青" <<
                 "172-蜡烛，棕" <<
                 "173-蜡烛，灰" <<
                 "174-书信" <<
                 "175-墙砖覆盖区域"<<
                 "176-墙砖,1x1,样式1"<<
                 "177-墙砖,1x1,样式2"<<
                 "178-墙砖,1x1,样式3"<<
                 "179-墙砖,1x1,样式4"<<
                 "180-"<<
                 "181-"<<
                 "182-"<<
                 "183-"<<
                 "184-墙砖,1x2,样式1"<<
                 "185-墙砖,1x2,样式2"<<
                 "186-墙砖,2x1,样式1"<<
                 "187-墙砖,2x1,样式2"<<
                 "188-墙砖,2x2,样式1"<<
                 "189-墙砖,1x3,样式1"<<
                 "190-墙砖,3x1,样式1"<<
                 "191-墙砖,6x1,样式1"<<
                 "192-墙砖,左下折角"<<
                 "193-墙砖,左上折角"<<
                 "194-墙砖,右上折角"<<
                 "195-墙砖,右下折角"
                 ;
        ui->l1->addItems(items);
        ui->l2->addItems(items);
        ui->l3->addItems(items);
    //-------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
    if(!name)
        delete name;
    if(!layer0)
    {
        delete layer0;
        delete layer1;
        delete layer2;
    }
}


void MainWindow::showinfo()
{
    info = new InfoEditor(this);
    info->show();
}
void MainWindow::aboutGame()
{
    AboutGame *ab = new AboutGame(this);
    ab->show();
}
void MainWindow::aboutAuthor()
{
    AboutAuthor *ab = new AboutAuthor(this);
    ab->show();
}
void MainWindow::on_pushButton_2_clicked()
{
    pop->removeMap();
    ui->detailed->setDisabled(true);
    MainWindow::setStatus("已清除数据");
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
     //fileDialog->setDirectory(QCoreApplication::applicationDirPath());
     fileDialog->setDirectory("/home/fhh/桌面/tmp");
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
     sscanf(QFileInfo(fileName).fileName().toStdString().data(),"%d",&(MainWindow::lvlindex));
     delete (fileDialog);
     //为人类阅读而优化2333
     FILE *fp;
     fp = fopen(fileName.toStdString().data(),"r+");
     fscanf(fp,"[QuellGen level data file]\n");
     fscanf(fp,"Level ID:%[^\n]",id);
     fscanf(fp,"\n");
     fscanf(fp,"Level name:%[^\n]",name);
     fscanf(fp,"\n");
     fscanf(fp,"Best solution:%d\n",&steps);
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
     fscanf(fp,"Layers:%d\n",&(MainWindow::layers));
     layers==2?ui->l3->setEnabled(false):ui->l3->setEnabled(true);
     if(layer0)
     {
        //释放上一次的内存
         delete[](layer0);
         delete[](layer1);
         delete[](layer2);
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
     ui->pushButton_4->setEnabled(true);
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
    delete(fileDialog);
    FILE *fp;
    fp = fopen(fileName.toStdString().data(),"w+");
    fprintf(fp,"[QuellGen level data file]\n");
    fprintf(fp,"Level ID:%s\n",id);
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
    fprintf(fp,"Layers:%d\n",MainWindow::layers);
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
    MainWindow::setStatus(data);
    pos = x+y*static_cast<int>(w);
    ui->detailed->setEnabled(true);
    ui->l1->setCurrentIndex(layer0[x+y*static_cast<int>(w)]);
    ui->l2->setCurrentIndex(layer1[x+y*static_cast<int>(w)]);
    ui->l3->setCurrentIndex(layer2[x+y*static_cast<int>(w)]);
}
void MainWindow::import()
{
    QString levelname,stringname,outdir;
//level data------------------------------------------------
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开关卡数据文件"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setNameFilter(tr("Quell关卡数据文件(*.txt)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         levelname = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(levelname=="")return;
    //----------------------------------------------------------
    //string data------------------------------------------------
    fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开关卡字符串文件"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setNameFilter(tr("Quell关卡字符串文件(*.xml)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         stringname = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(stringname=="")return;
    //----------------------------------------------------------
    //string savedir------------------------------------------------
    fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开关卡保存文件夹"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         outdir = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(outdir=="")return;
    outdir.append("/%d.%d.%d.gmp");
    //----------------------------------------------------------
    ImportAction::loadinfo(const_cast<char*>(levelname.toStdString().data()),\
                           const_cast<char*>(stringname.toStdString().data()),\
                           const_cast<char*>(outdir.toStdString().data()));
}
void MainWindow::exportxml()
{
    QString levelname,stringname,indir;
//level data------------------------------------------------
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开源关卡数据文件"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setNameFilter(tr("Quell关卡数据文件(*.txt)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         levelname = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(levelname=="")return;
    //----------------------------------------------------------
    //string data------------------------------------------------
    fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开源关卡字符串文件"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setNameFilter(tr("Quell关卡字符串文件(*.xml)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         stringname = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(stringname=="")return;
    //----------------------------------------------------------
    //string indir------------------------------------------------
    fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开关卡保存文件夹"));
    fileDialog->setDirectory(QCoreApplication::applicationDirPath());
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec())
    {
         indir = fileDialog->selectedFiles().first();
    }
    delete(fileDialog);
    if(indir=="")return;
    //----------------------------------------------------------
    ExportAction::saveinfo(const_cast<char*>(levelname.toStdString().data()),\
                           const_cast<char*>(stringname.toStdString().data()),\
                           const_cast<char*>(indir.toStdString().data()));
}
void MainWindow::setStatus(QString in)
{
    ui->statusBar->showMessage(in,-1);
}
void MainWindow::changeData()
{
    printf("%d:%d %d %d\n",pos,layer0[pos],layer1[pos],layer2[pos]);
    layer0[pos]=ui->l1->currentIndex();
    layer1[pos]=ui->l2->currentIndex();
    layer2[pos]=ui->l3->currentIndex();
    pop->changeBlock(layer0[pos],layer1[pos],layer2[pos]);
}
