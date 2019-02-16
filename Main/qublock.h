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
    void initAtlas(QPixmap& a, QPixmap& b, QPixmap& c,int xin,int yin);
    int x,y;
    void reloadAtlas(QPixmap& a);
private:
    Ui::QuBlock *ui;
private slots:
    void clicked();
};

#endif // QUBLOCK_H
