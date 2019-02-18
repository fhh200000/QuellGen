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
private slots:
    void destroy();
};

#endif // INFOEDITOR_H
