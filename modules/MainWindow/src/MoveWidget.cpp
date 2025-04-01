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
        // if (m_window->isMaximized())
        // {
        //     m_window->showNormal();
        // }
        m_window->move(_event->globalPos() - m_mousePoint);
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
