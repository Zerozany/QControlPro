_Pragma("once");
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

#include "Threshold.h"

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

private:
    auto conncetSignalsToSlots() noexcept -> void;

    auto setTitleConfig(QWidget* _parent) noexcept -> void;

    auto setTitleButtonLayout() noexcept -> void;

Q_SIGNALS:
    auto buttonStyleChanged(const QString& _filePath) -> void;

    auto buttonPropertyChanged(const char* _groupName, const QStringList& _propertyNames) -> void;

    auto buttonIconsChanged(const QStringList& _filePath, const QSize& _size) -> void;

private Q_SLOTS:
    auto setButtonStyle(const QString& _filePath) noexcept -> void;

    auto setButtonProperty(const char* _groupName, const QStringList& _propertyNames) noexcept -> void;

    auto setButtonIcons(const QStringList& _filePath, const QSize& _size) noexcept -> void;

public Q_SLOTS:
    auto resetHeight(const quint8 _height) noexcept -> void;

    auto setTitleStatus(const bool _flag) noexcept -> void;

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
