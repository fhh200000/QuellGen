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
public:
    Ui::MainWindow *ui;
    ItWorksPop *pop;
};

#endif // MAINWINDOW_H
