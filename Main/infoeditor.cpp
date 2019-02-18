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
    temp = QString::number(MainWindow::self->steps);
    ui->lineEdit_2->setText(temp);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(destroy()));
}

InfoEditor::~InfoEditor()
{
    destroy();
    delete ui;
}
void InfoEditor::destroy()
{
    delete MainWindow::self->name;
    QByteArray ba = ui->lineEdit->text().toLatin1();
    MainWindow::self->name = new char[32];
    char* tmp = ba.data();
    for(int i=0;i<ba.length();i++)
    {
        MainWindow::self->name[i] = tmp[i];
    }
    MainWindow::self->name[ba.length()] = '\0';
    MainWindow::self->steps = ui->lineEdit_2->text().toInt();
}
