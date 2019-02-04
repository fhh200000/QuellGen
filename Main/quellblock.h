#ifndef QUELLBLOCK_H
#define QUELLBLOCK_H
#include<QtWidgets>
class QuellBlock
{
public:
    QuellBlock();
    ~QuellBlock();
public:
    static QPixmap* atlasp;
    static void loadAtlas(void);
};

#endif // QUELLBLOCK_H
