#ifndef QUBLOCKPLUGIN_H
#define QUBLOCKPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QLabel>
class QuBlockPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
#endif // QT_VERSION >= 0x050000

public:
    QuBlockPlugin(QObject *parent = nullptr);
    QLabel first,second,third;
    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);
    void initAtlas(QPixmap&,QPixmap&,QPixmap&);
private:
    bool m_initialized;
};

#endif
