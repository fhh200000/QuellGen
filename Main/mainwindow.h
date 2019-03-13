#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "quellblock.h"
#include <QMainWindow>
#include "itworkspop.h"
#include "infoeditor.h"
typedef struct
{
    int drop;
    int direction;
}step;
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
    static MainWindow* self;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void refresh(uint,uint);
    void open_selected();
    void save_selected();
    void aboutGame();
    void aboutAuthor();
    void showinfo();
    void import();
    void exportxml();
    void changeData();
public:
    InfoEditor *info=nullptr;
    Ui::MainWindow *ui;
    ItWorksPop *pop=nullptr;
    int* layer0=nullptr;
    int* layer1=nullptr;
    int* layer2=nullptr;
    int steps = 0;
    int pos;
    int layers;
    unsigned int w,h;
    int lspace,rspace;
    char* name = nullptr;
    char id[20];
    void loadinfo(int x,int y);
    int *solution,*soludrop;
    std::vector<step> *steplist;
    int lvlindex;
    void setStatus(QString in);

};
#endif // MAINWINDOW_H
