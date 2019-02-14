#ifndef QUBLOCK_H
#define QUBLOCK_H

#include <QWidget>

namespace Ui {
class QuBlock;
}

class QuBlock : public QWidget
{
    Q_OBJECT

public:
    explicit QuBlock(QWidget *parent = nullptr);
    ~QuBlock();
    void initAtlas(QPixmap&,QPixmap&,QPixmap&,int,int);
    int x,y;
private:
    Ui::QuBlock *ui;
private slots:
    void clicked();
};

#endif // QUBLOCK_H
