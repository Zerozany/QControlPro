#include "WidgetFrame.h"

WidgetFrame::WidgetFrame(widgetsMap& _widgetsMap, QWidget* _parent)
    : QWidget{_parent}, m_widgetsMap{_widgetsMap}
{
    Q_ASSERT_X(this->m_widgetsMap.size() > 0, "WidgetFrame", "Arguments _widgetsMap is empty!");
    std::invoke(&WidgetFrame::conncetSignalsToSlots, this);
    std::invoke(&WidgetFrame::setWindowConfig, this);
    m_titleWidget->setGeometry(1, 1, this->width() - 2, 30);
}

auto WidgetFrame::titleHeight() noexcept -> quint8
{
    return this->m_titleHeight;
}

auto WidgetFrame::setTitleHeight(const quint8& _height) noexcept -> void
{
    if (this->m_titleHeight == _height)
    {
        return;
    }
    this->m_titleHeight = _height;
    emit titleHeightChanged();
}

auto WidgetFrame::setWindowConfig() noexcept -> void
{
    /// @brief 开启鼠标活动监听
    this->setMouseTracking(true);
    /// @brief 移除窗口的系统默认边框和标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    /// @brief 设置窗口背景完全透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    /// @brief 设置基础大小
    this->setBaseSize(800, 600);
}

auto WidgetFrame::conncetSignalsToSlots() noexcept -> void
{
}

auto WidgetFrame::paintEvent(QPaintEvent* _event) -> void
{
    QPainter painter{this};
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    // 1. 绘制圆角背景
    QPainterPath path{};
    // 10px圆角
    path.addRoundedRect(rect(), 10, 10);
    // 填充背景色（替代样式表中的background-color）
    painter.fillPath(path, QColor("#FFFFFF"));
    // 2. 绘制边框（替代样式表中的border）
    painter.setPen(QPen(QColor("#CCCCCC"), 1));  // 1px灰色边框
    painter.drawPath(path);
}

auto WidgetFrame::mousePressEvent(QMouseEvent* _event) -> void
{
    std::invoke(&MouseHandle::mousePress, this->m_mouseHandle, _event);
}

auto WidgetFrame::mouseMoveEvent(QMouseEvent* _event) -> void
{
    std::invoke(&MouseHandle::mouseMove, this->m_mouseHandle, _event);
}

auto WidgetFrame::mouseReleaseEvent(QMouseEvent* _event) -> void
{
    std::invoke(&MouseHandle::mouseRelease, this->m_mouseHandle, _event);
}

auto WidgetFrame::mouseDoubleClickEvent(QMouseEvent* _event) -> void
{
}
