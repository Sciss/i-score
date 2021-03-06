#include <QGridLayout>

#include "PluginSettingsPresenter.hpp"
#include "PluginSettingsView.hpp"
#include <iscore/plugins/settingsdelegate/SettingsDelegateViewInterface.hpp>

class QObject;

namespace PluginSettings
{
PluginSettingsView::PluginSettingsView(QObject* parent) :
    iscore::SettingsDelegateViewInterface {parent}
{
    auto layout = new QGridLayout(m_widget);
    m_widget->setLayout(layout);

    layout->addWidget(m_listView);
}

QWidget* PluginSettingsView::getWidget()
{
    return m_widget;
}
}
