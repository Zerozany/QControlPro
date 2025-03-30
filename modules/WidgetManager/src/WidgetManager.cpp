#include "WidgetManager.h"

WidgetManager::WidgetManager(QMap<QString, QWidget*>& _widgetsmap, QWidget* _widget, QObject* _parent) : QObject{_parent}, m_widgetsmap{_widgetsmap}
{
    std::invoke(&WidgetManager::setParent, this, _widget);
}

auto WidgetManager::getWidget(const QString& _name) noexcept -> QWidget*
{
    if (m_widgetsmap.contains(_name))
    {
        return m_widgetsmap.value(_name, nullptr);
    }
    return nullptr;
}

auto WidgetManager::setParent(QWidget* _widget) noexcept -> void
{
    for (auto& it : m_widgetsmap)
    {
        it->setParent(_widget);
    }
}
