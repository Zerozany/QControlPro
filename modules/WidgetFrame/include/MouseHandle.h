_Pragma("once");
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>
#include <QScreen>
#include <QWidget>

#include "Threshold.h"

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

    /// @brief 获取窗口是否正在进行伸缩状态
    auto getResizing() noexcept -> bool;

private:
    auto setCursorType(const QPoint& _pos) noexcept -> void;

    auto conncetSignalsToSlots() noexcept -> void;

Q_SIGNALS:
    auto cursorTypeChanged() -> void;

    auto resizeWidget(const bool _flag) -> void;

private Q_SLOTS:
    auto setCursor() noexcept -> void;

public Q_SLOTS:
    auto resetHeight(const quint8 _height) noexcept -> void;

private:
    QWidget*   m_widget{nullptr};
    quint8     m_height{};
    bool       m_resizing{false};                          /*窗口伸缩句柄*/
    CursorType m_cursorType{};                             /*指针图标类型*/
    bool       m_mouseHandle{};                            /*鼠标移动窗口句柄*/
    QScreen*   m_screen{QGuiApplication::primaryScreen()}; /*获取主屏幕*/
};
