#ifndef QUBLOCK_H
#define QUBLOCK_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
namespace Ui
{
    class QuBlock;
}

class QDESIGNER_WIDGET_EXPORT QuBlock : public QWidget
{
    Q_OBJECT

public:
    explicit QuBlock(QWidget *parent = nullptr);
    ~QuBlock();
    void initAtlas(QPixmap&,QPixmap&,QPixmap&);

    Ui::QuBlock *ui;
};

#endif // QUBLOCK_H
