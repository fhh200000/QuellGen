#include "aboutauthor.h"
#include "ui_aboutauthor.h"

AboutAuthor::AboutAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutAuthor)
{
    ui->setupUi(this);
    QString location = QCoreApplication::applicationDirPath()+ "/Resources/author.png";
    QPixmap *logo = new QPixmap(location);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*logo);
}

AboutAuthor::~AboutAuthor()
{
    delete ui;
}
