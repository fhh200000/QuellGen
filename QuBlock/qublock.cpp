#include "qublock.h"

QuBlock::QuBlock(QWidget *parent) :
    QWidget(parent)
{
    QSize sz = QSize(48,48);
    this->first.setScaledContents(true);
    this->second.setScaledContents(true);
    this->third.setScaledContents(true);
    this->setMaximumSize(sz);
    this->setMaximumSize(sz);
    this->setMaximumSize(sz);

}

