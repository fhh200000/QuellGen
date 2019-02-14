#ifndef ABOUTAUTHOR_H
#define ABOUTAUTHOR_H

#include <QWidget>

namespace Ui {
class AboutAuthor;
}

class AboutAuthor : public QWidget
{
    Q_OBJECT

public:
    explicit AboutAuthor(QWidget *parent = nullptr);
    ~AboutAuthor();

private:
    Ui::AboutAuthor *ui;
};

#endif // ABOUTAUTHOR_H
