_Pragma("once");
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
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
    explicit(true) TitleWidget(quint8 _height, QWidget* _parent = nullptr, const SystemStyle& _systemStyle = SystemStyle::WIN);
    ~TitleWidget() = default;

    auto setButtonProperty(const char* _groupName = "propertyName", const QStringList& _propertyNames = {"min", "normal", "close"}) noexcept -> void;

    auto setButtonStyle(const QString& _filePath) noexcept -> void;

    auto setButtonIcons(const QStringList& _filePath, const QSize& _size = QSize{12, 12}) noexcept -> void;

    auto setTitleStatus(QWidget* _parent, QMouseEvent* _event) noexcept -> void;

private:
    auto conncetSignalsToSlots() noexcept -> void;

    auto setTitleConfig(QWidget* _parent) noexcept -> void;

    auto setTitleButtonLayout() noexcept -> void;

Q_SIGNALS:
    auto buttonStyleChanged(const QString& _styleString) -> void;

private Q_SLOTS:
    auto readButtonStyle(const QString& _styleString) noexcept -> void;

public Q_SLOTS:
    auto resetHeight(const quint8 _height) noexcept -> void;

private:
    QWidget*     m_widget{nullptr};
    quint8       m_height{};
    SystemStyle  m_systemStyle{};
    QHBoxLayout* m_titleLayout{new QHBoxLayout{this}};

    std::map<QString, QWidget*> m_titleButtons{
        {"min", new QPushButton{this}},
        {"normal", new QPushButton{this}},
        {"close", new QPushButton{this}},
    };

private:
    inline static constexpr quint8 BUTTONWIDTH{40};
};
