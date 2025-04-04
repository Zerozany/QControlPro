#include "MoveWidget.h"

MoveWidget::MoveWidget(quint16 _height, QWidget* _window, QObject* _parent) : QObject{_parent}, m_height{_height}, m_window{_window}
{
    Q_ASSERT(_height > 0);
    Q_ASSERT(_window != nullptr);
}

auto MoveWidget::mousePress(QMouseEvent* _event) noexcept -> void
{
    if ((_event->button() & Qt::LeftButton) && QRect{0, 0, m_window->width(), m_height}.contains(_event->pos()))
    {
        m_mouseHandle = true;
        m_mousePoint  = _event->globalPos() - m_window->pos();
    }
}

auto MoveWidget::mouseMove(QMouseEvent* _event) noexcept -> void
{
    if (m_mouseHandle)
    {
        if (m_window->isMaximized())
        {
            // 计算当前鼠标在窗口中的横向比例
            float ratio_x{static_cast<float>(_event->pos().x()) / static_cast<float>(m_window->width())};
            // 记录当前鼠标全局坐标
            QPoint current_globalpos{_event->globalPos()};
            // 取消最大化
            m_window->showNormal();
            // 计算鼠标应该对应的新窗口位置,保持垂直偏移不变
            m_window->move(current_globalpos - QPoint(static_cast<int>(ratio_x * m_window->width()), m_mousePoint.y()));
            // 更新鼠标拖动偏移
            m_mousePoint = current_globalpos - m_window->pos();
        }
        else
        {
            // 正常拖动窗口
            m_window->move(_event->globalPos() - m_mousePoint);
        }
    }
}

auto MoveWidget::mouseRelease(QMouseEvent* _event) noexcept -> void
{
    m_mouseHandle = false;
}

auto MoveWidget::mouseDoubleClick(QMouseEvent* _event) noexcept -> void
{
    if (_event->button() == Qt::LeftButton)
    {
        if (QRect{0, 0, m_window->width(), m_height}.contains(_event->pos()))
        {
            m_window->isMaximized() ? m_window->showNormal() : m_window->showMaximized();
        }
    }
}
