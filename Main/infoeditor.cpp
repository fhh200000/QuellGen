#include "infoeditor.h"
#include "ui_infoeditor.h"
#include "mainwindow.h"
InfoEditor::InfoEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoEditor)
{
    ui->setupUi(this);
    QString temp = QString(MainWindow::self->name);
    ui->lineEdit->setText(temp);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(destroy()));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addSteps()));
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(removeSteps()));
    char dir=0;
        for(int i=0;i<MainWindow::self->steps;i++)
        {
            switch (MainWindow::self->steplist->data()[i].direction)
            {
            case 0:
                {
                dir = 'W';
                break;
                }
            case 1:
                {
                dir = 'D';
                break;
                }
            case 2:
                {
                dir = 'S';
                break;
                }
            case 3:
                {
                dir = 'A';
                break;
                }
            }
            ui->listWidget->addItem("水滴："+QString::number(MainWindow::self->steplist->data()[i].drop)+"  方向："+QString(dir));
        }
}

InfoEditor::~InfoEditor()
{
    delete ui;
}
void InfoEditor::destroy()
{
    QByteArray ba = ui->lineEdit->text().toLatin1();
    char* tmp = ba.data();
    for(int i=0;i<ba.length();i++)
    {
        MainWindow::self->name[i] = tmp[i];
    }
    MainWindow::self->name[ba.length()] = '\0';
    MainWindow::self->steps = ui->listWidget->count();
    this->hide();
    MainWindow::self->info = nullptr;
    delete this;
}
void InfoEditor::addSteps()
{
    char tmp;
    int dir;
    tmp = ui->dirIndex->text().toLatin1().front();
    switch (tmp)
    {
    case 'W':
        {
        dir = 0;
        break;
        }
    case 'D':
        {
        dir = 1;
        break;
        }
    case 'S':
        {
        dir = 2;
        break;
        }
    case 'A':
        {
        dir = 3;
        break;
        }
    default:
        {
        QMessageBox::warning(nullptr,"提示","输入的方向无效！");
        return;
        }
    }
    MainWindow::self->steplist->push_back(step{ui->dropIndex->text().toInt(),dir});
    ui->listWidget->addItem("水滴："+ui->dropIndex->text()+"  方向："+ui->dirIndex->text());
}
void InfoEditor::removeSteps()
{
    int serial = ui->listWidget->currentRow();
    ui->listWidget->takeItem(serial);
    std::vector<step>::iterator tmp = MainWindow::self->steplist->begin()+serial;
    MainWindow::self->steplist->erase(tmp);
}
void InfoEditor::closeEvent(QCloseEvent *event)
{
    destroy();
    event->accept();
}
