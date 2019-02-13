#ifndef ABOUTGAME_H
#define ABOUTGAME_H

#include <QDialog>

namespace Ui {
class AboutGame;
}

class AboutGame : public QDialog
{
    Q_OBJECT

public:
    explicit AboutGame(QWidget *parent = nullptr);
    ~AboutGame();

private:
    Ui::AboutGame *ui;
};

#endif // ABOUTGAME_H
