#ifndef ITWORKSPOP_H
#define ITWORKSPOP_H

#include <QDialog>
#include "qublock.h"
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
private:
    Ui::ItWorksPop *ui;
    QuBlock** que;
};

#endif // ITWORKSPOP_H
