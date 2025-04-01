_Pragma("once");
#include <QFile>
#include <QObject>
#include <QPushButton>
#include <QResizeEvent>
#include <QWidget>
#include <functional>
#include <map>
#include <ranges>

namespace MainSize
{
    inline constexpr quint8 BUTTON_WIDTH{40};
}

enum struct ButtonSystemStyle : std::uint8_t
{
    WIN = 0x01,
    MAC = 0x02,
};

class TitleBarButton : public QObject
{
    Q_OBJECT
public:
    explicit(true) TitleBarButton(std::map<QString, QWidget*>& _buttonsMap, const ButtonSystemStyle& _system = ButtonSystemStyle::WIN, QObject* _parent = nullptr);
    ~TitleBarButton() = default;

    auto setButtonStyle(const QString& _styleFilePath = R"(:/resources/QToolButton.css)") noexcept -> void;

    auto resizeButtonLayout(QResizeEvent* _event, QWidget* _widget, quint16 _height) noexcept -> void;

private:
    auto setButtonProperty() noexcept -> void;

private:
    QStringList                  m_propertyList{"min", "normal", "close"};
    std::map<QString, QWidget*>& m_buttonsMap;
    ButtonSystemStyle            m_system{};
};
