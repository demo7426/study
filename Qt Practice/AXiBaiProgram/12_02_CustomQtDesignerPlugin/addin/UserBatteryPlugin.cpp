#include "UserBatteryPlugin.h"
#include "userbattery.h"

#include <QtPlugin>

CUserBatteryPlugin::CUserBatteryPlugin(QObject *parent)
    : QObject(parent)
{}

void CUserBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CUserBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CUserBatteryPlugin::createWidget(QWidget *parent)
{
    return new CUserBattery(parent);
}

QString CUserBatteryPlugin::name() const
{
    return QLatin1String("CUserBattery");
}

QString CUserBatteryPlugin::group() const
{
    return QLatin1String("UserWidget");
}

QIcon CUserBatteryPlugin::icon() const
{
    return QIcon(QLatin1String(":/44.ico"));
}

QString CUserBatteryPlugin::toolTip() const
{
    return QLatin1String("电池");
}

QString CUserBatteryPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CUserBatteryPlugin::isContainer() const
{
    return false;
}

QString CUserBatteryPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="CUserBattery" name="cUserBattery">
</widget>)");
}

QString CUserBatteryPlugin::includeFile() const
{
    return QLatin1String("userbattery.h");
}
