#include "TitleBarButton.h"

TitleBarButton::TitleBarButton(std::map<QString, QWidget*>& _buttonsMap, const ButtonSystemStyle& _system, QObject* _parent) : QObject{_parent}, m_buttonsMap{_buttonsMap}, m_system{_system}
{
    std::invoke(&TitleBarButton::setButtonProperty, this);
    std::invoke(&TitleBarButton::setButtonStyle, this, R"(:/resources/QToolButton.css)");
}

auto TitleBarButton::setButtonProperty() noexcept -> void
{
    Q_ASSERT_X(m_buttonsMap.size() == m_propertyList.size(), "setButtonProperty", "PropertyList's size must greater three");
    auto buttons{m_buttonsMap | std::views::values};
    for (auto&& [button, property] : std::views::zip(buttons, m_propertyList))
    {
        button->setProperty("propertyName", property);
    }
}

auto TitleBarButton::setButtonStyle(const QString& _styleFilePath) noexcept -> void
{
    QFile buttonStyleFile{_styleFilePath};
    if (!buttonStyleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << _styleFilePath;
        return;
    }
    QTextStream buttonStream{&buttonStyleFile};
    QString     styleSheet{buttonStream.readAll()};
    buttonStyleFile.close();
    for (auto&& buttons : m_buttonsMap | std::views::values)
    {
        buttons->setStyleSheet(styleSheet);
    }
}

auto TitleBarButton::resizeButtonLayout(QResizeEvent* _event, QWidget* _widget, quint16 _height) noexcept -> void
{
    std::size_t count{3};
    for (auto&& buttons : m_buttonsMap | std::views::values)
    {
        buttons->setGeometry(_widget->width() - (MainSize::BUTTON_WIDTH * count), 0, MainSize::BUTTON_WIDTH, _height);
        --count;
    }
}
