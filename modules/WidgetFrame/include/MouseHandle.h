_Pragma("once");
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

#include "GlobalGeneral.h"

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
    explicit(true) MouseHandle(quint8 _height, QWidget* _widget, QObject* _parent = nullptr);
    ~MouseHandle() = default;

    auto mousePress(QMouseEvent* _event) noexcept -> void;

    auto mouseMove(QMouseEvent* _event) noexcept -> void;

    auto mouseRelease(QMouseEvent* _event) noexcept -> void;

    auto mouseDoubleClick(QMouseEvent* _event) noexcept -> void;

    auto mouseleave(QEvent* _event) noexcept -> void;

    auto getResizing() noexcept -> bool;

private:
    auto setCursorType(const QPoint& _pos) noexcept -> void;

    auto conncetSignalsToSlots() noexcept -> void;

Q_SIGNALS:
    auto cursorTypeChanged() -> void;

private Q_SLOTS:
    auto setCursor() noexcept -> void;

public Q_SLOTS:
    auto resetHeight(const quint8 _height) noexcept -> void;

private:
    QWidget*   m_widget{nullptr};
    quint8     m_height{};
    bool       m_resizing{false}; /*窗口伸缩句柄*/
    QPoint     m_startPoint{};    /*开启伸缩标记点*/
    QRect      m_startGeometry{}; /*当前窗口大小缓存区*/
    CursorType m_cursorType{};    /*指针图标类型*/
    bool       m_mouseHandle{};   /*鼠标移动窗口句柄*/
    QPoint     m_mousePoint{};    /*窗口移动事件鼠标缓存点*/
};
