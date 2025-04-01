_Pragma("once");
#include <QMouseEvent>
#include <QObject>
#include <QPoint>
#include <QWidget>

class MoveWidget : public QObject
{
    Q_OBJECT
public:
    explicit(true) MoveWidget(quint16 _height, QWidget* _window, QObject* _parent = nullptr);
    ~MoveWidget() = default;

    auto mousePress(QMouseEvent* _event) noexcept -> void;

    auto mouseMove(QMouseEvent* _event) noexcept -> void;

    auto mouseRelease(QMouseEvent* _event) noexcept -> void;

    auto mouseDoubleClick(QMouseEvent* _event) noexcept -> void;

private:
    quint16  m_height{};
    bool     m_mouseHandle{};
    QWidget* m_window{nullptr};
    QPoint   m_mousePoint{};
};
