#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itworkspop.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString data;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void open_selected();
    void save_selected();
public:
    Ui::MainWindow *ui;
    ItWorksPop *pop=nullptr;
    int* layer0=nullptr;
    int* layer1=nullptr;
    int* layer2=nullptr;
    int steps = 0;
    unsigned int w,h;
    char* name = new char[32];
};

#endif // MAINWINDOW_H
