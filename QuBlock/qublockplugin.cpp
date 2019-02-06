#include "qublock.h"
#include "qublockplugin.h"

#include <QtPlugin>

QuBlockPlugin::QuBlockPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QuBlockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QuBlockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QuBlockPlugin::createWidget(QWidget *parent)
{
    return new QuBlock(parent);
}

QString QuBlockPlugin::name() const
{
    return QLatin1String("QuBlock");
}

QString QuBlockPlugin::group() const
{
    return QLatin1String("");
}

QIcon QuBlockPlugin::icon() const
{
    return QIcon(QLatin1String(":/low.png"));
}

QString QuBlockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QuBlockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QuBlockPlugin::isContainer() const
{
    return false;
}

QString QuBlockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QuBlock\" name=\"quBlock\">\n</widget>\n");
}

QString QuBlockPlugin::includeFile() const
{
    return QLatin1String("qublock.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qublock, QuBlockPlugin)
#endif // QT_VERSION < 0x050000
