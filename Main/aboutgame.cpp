#include "aboutgame.h"
#include "ui_aboutgame.h"

AboutGame::AboutGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutGame)
{
    ui->setupUi(this);
    QString location = QCoreApplication::applicationDirPath()+ "/Resources/ftg-logo.png";
    QPixmap *logo = new QPixmap(location);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*logo);
}

AboutGame::~AboutGame()
{
    delete ui;
}
