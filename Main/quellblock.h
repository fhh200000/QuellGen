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
    static QPixmap* rockstyle1;
    static QPixmap* rockstyle2;
    static void loadAtlas(void);
};
typedef struct
{
    int count;
    int width;
    int index;
    int style;
}extrablock;
#endif // QUELLBLOCK_H
