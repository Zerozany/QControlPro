_Pragma("once");
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QToolButton>
#include <QWidget>
#include <ranges>

#include "GlobalGeneral.h"

class TitleWidget : public QLabel
{
    Q_OBJECT
public:
    enum struct SystemStyle : std::uint8_t
    {
        WIN = 0x01,
        MAC = 0x02,
    };
    Q_ENUM(SystemStyle);

public:
    explicit(true) TitleWidget(QWidget* _widget, quint8 _height = 30, const SystemStyle& _systemStyle = SystemStyle::WIN, QWidget* _parent = nullptr);
    ~TitleWidget() = default;

    auto setButtonProperty(const char* _groupName = "propertyName", const QStringList& _propertyNames = {"min", "normal", "close"}) noexcept -> void;

    auto setButtonStyle(const QString& _filePath) noexcept -> void;

    // auto setButtonIcons(const QString& _filePath) noexcept -> void;

private:
    auto conncetSignalsToSlots() noexcept -> void;

    auto setTitleConfig(QWidget* _parent) noexcept -> void;

    auto setTitleButtonLayout() noexcept -> void;

Q_SIGNALS:
    auto buttonStyleChanged(const QString& _styleString) -> void;

private Q_SLOTS:
    auto readButtonStyle(const QString& _styleString) noexcept -> void;

private:
    QWidget*     m_widget{nullptr};
    quint8       m_height{};
    SystemStyle  m_systemStyle{};
    QHBoxLayout* m_titleLayout{new QHBoxLayout{this}};

    std::map<QString, QWidget*> m_titleButtons{
        {"min", new QToolButton{this}},
        {"normal", new QToolButton{this}},
        {"close", new QToolButton{this}},
    };

private:
    inline static constexpr quint8 BUTTONWIDTH{40};
    inline static constexpr quint8 m_border_width{BORDERWIDTH}; /*边缘感应宽度*/
};
