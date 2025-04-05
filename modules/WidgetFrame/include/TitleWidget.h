_Pragma("once");
#include <QLabel>
#include <QToolButton>
#include <QWidget>

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

    auto setTitleConfig() noexcept -> void;

private:
    QWidget*    m_widget{nullptr};
    quint8      m_height{};
    SystemStyle m_systemStyle{};
};
