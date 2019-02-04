#ifndef QUBLOCK_H
#define QUBLOCK_H

#include <QWidget>
#include <QLabel>

class QuBlock : public QWidget
{
    Q_OBJECT

public:
    QLabel first,second,third;
    QuBlock(QWidget *parent = nullptr);
    void initAtlas(QPixmap&,QPixmap&,QPixmap&);
};

#endif
