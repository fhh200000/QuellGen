#ifndef ITWORKSPOP_H
#define ITWORKSPOP_H
#include "quellblock.h"
#include <QDialog>
#include "qublock.h"
#include "quellblock.h"
namespace Ui {
class ItWorksPop;
}

class ItWorksPop : public QDialog
{
    Q_OBJECT

public:
    explicit ItWorksPop(QWidget *parent = nullptr);
    ~ItWorksPop();
    void initMap(int,int,int[],int[],int[]);
    void removeMap();
    void reloadBlock(extrablock in,int width);
    void changeBlock(int a,int b,int c);
private:
    Ui::ItWorksPop *ui;
    QuBlock** que=nullptr;
    int count;
};

#endif // ITWORKSPOP_H
