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
    steps = new std::vector<step>(static_cast<unsigned>(MainWindow::self->steps));
    char dir=0;
        for(int i=0;i<MainWindow::self->steps;i++)
        {
            steps->push_back(step{MainWindow::self->soludrop[i],MainWindow::self->solution[i]});
            switch (MainWindow::self->solution[i])
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
            ui->listWidget->addItem("水滴："+QString::number(MainWindow::self->soludrop[i])+"  方向:"+QString(dir));
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
    steps->clear();
    delete steps;
    steps = nullptr;
    this->hide();
    MainWindow::self->info = nullptr;
    delete this;
}
