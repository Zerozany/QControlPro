_Pragma("once");
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

class MouseHandle : public QObject
{
    Q_OBJECT
public:
    enum struct CursorType : std::uint8_t
    {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    Q_ENUM(CursorType)
public:
    explicit(true) MouseHandle(QWidget* _widget, QObject* _parent = nullptr);
    ~MouseHandle() = default;

    auto mousePress(QMouseEvent* _event) noexcept -> void;

    auto mouseMove(QMouseEvent* _event) noexcept -> void;

    auto mouseRelease(QMouseEvent* _event) noexcept -> void;

    auto mouseleave(QEvent* _event) noexcept -> void;

    auto getResizing() noexcept -> bool;

private:
    auto setCursorType(const QPoint& _pos) noexcept -> void;

    auto conncetSignalsToSlots() noexcept -> void;

Q_SIGNALS:
    auto cursorTypeChanged() -> void;

private Q_SLOTS:
    auto setCursor() noexcept -> void;

private:
    QWidget*   m_widget{nullptr};
    bool       m_resizing{false}; /*窗口伸缩句柄*/
    QPoint     m_startPoint{};    /*开启伸缩标记点*/
    QRect      m_startGeometry{}; /*当前窗口大小缓存区*/
    CursorType m_cursorType{};    /*指针图标类型*/

private:
    inline static constexpr quint8 m_border_width{5}; /*边缘感应宽度*/
};
