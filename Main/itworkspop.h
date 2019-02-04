#ifndef ITWORKSPOP_H
#define ITWORKSPOP_H

#include <QDialog>

namespace Ui {
class ItWorksPop;
}

class ItWorksPop : public QDialog
{
    Q_OBJECT

public:
    explicit ItWorksPop(QWidget *parent = nullptr);
    ~ItWorksPop();
    void initMap(void);
    //QSize size;
private:
    Ui::ItWorksPop *ui;
};

#endif // ITWORKSPOP_H
