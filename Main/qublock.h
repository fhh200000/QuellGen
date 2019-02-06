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
    void initAtlas(QPixmap&,QPixmap&,QPixmap&);
private:
    Ui::QuBlock *ui;
};

#endif // QUBLOCK_H
