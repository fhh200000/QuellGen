#include "aboutauthor.h"
#include "ui_aboutauthor.h"

AboutAuthor::AboutAuthor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutAuthor)
{
    ui->setupUi(this);
}

AboutAuthor::~AboutAuthor()
{
    delete ui;
}
