#ifndef INFOEDITOR_H
#define INFOEDITOR_H

#include <QDialog>

namespace Ui {
class InfoEditor;
}

class InfoEditor : public QDialog
{
    Q_OBJECT

public:
    explicit InfoEditor(QWidget *parent = nullptr);
    ~InfoEditor();

private:
    Ui::InfoEditor *ui;
    void closeEvent(QCloseEvent *event);
private slots:
    void destroy();
    void addSteps();
    void removeSteps();
};

#endif // INFOEDITOR_H
