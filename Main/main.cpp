#include "mainwindow.h"
#include "quellblock.h"
#include <QApplication>
#include "itworkspop.h"
int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    QuellBlock::loadAtlas();
    w.show();
    return a.exec();
}
