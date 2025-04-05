#include "MouseHandle.h"

MouseHandle::MouseHandle(QWidget* _widget, QObject* _parent) : QObject{_parent}, m_widget{_widget}
{
    Q_ASSERT_X(m_widget != nullptr, "MouseHandle", "_widget is nullptr");
    std::invoke(&MouseHandle::conncetSignalsToSlots, this);
}

auto MouseHandle::mousePress(QMouseEvent* _event) noexcept -> void
{
    if (_event->button() == Qt::LeftButton && m_cursorType != CursorType::None)
    {
        m_resizing      = true;
        m_startPoint    = _event->globalPos();
        m_startGeometry = m_widget->geometry();
    }
}

auto MouseHandle::mouseMove(QMouseEvent* _event) noexcept -> void
{
    if (QRect end_geometry{m_startGeometry}; m_resizing)
    {
        switch (QPoint tmp_point{_event->globalPos() - m_startPoint}; m_cursorType)
        {
            case CursorType::Top:
            {
                end_geometry.setTop(end_geometry.top() + tmp_point.y());
                break;
            }
            case CursorType::Bottom:
            {
                end_geometry.setBottom(end_geometry.bottom() + tmp_point.y());
                break;
            }
            case CursorType::Left:
            {
                end_geometry.setLeft(end_geometry.left() + tmp_point.x());
                break;
            }
            case CursorType::Right:
            {
                end_geometry.setRight(end_geometry.right() + tmp_point.x());
                break;
            }
            case CursorType::TopLeft:
            {
                end_geometry.setTop(end_geometry.top() + tmp_point.y());
                end_geometry.setLeft(end_geometry.left() + tmp_point.x());
                break;
            }
            case CursorType::TopRight:
            {
                end_geometry.setTop(end_geometry.top() + tmp_point.y());
                end_geometry.setRight(end_geometry.right() + tmp_point.x());
                break;
            }
            case CursorType::BottomLeft:
            {
                end_geometry.setBottom(end_geometry.bottom() + tmp_point.y());
                end_geometry.setLeft(end_geometry.left() + tmp_point.x());
                break;
            }
            case CursorType::BottomRight:
            {
                end_geometry.setBottom(end_geometry.bottom() + tmp_point.y());
                end_geometry.setRight(end_geometry.right() + tmp_point.x());
                break;
            }
            default:
            {
                std::unreachable();
            }
        }
        if (end_geometry.width() >= m_widget->minimumWidth() && end_geometry.height() >= m_widget->minimumHeight())
        {
            m_widget->setGeometry(end_geometry);
        }
    }
    else
    {
        this->setCursorType(_event->pos());
    }
}

auto MouseHandle::mouseRelease(QMouseEvent* _event) noexcept -> void
{
    this->m_resizing = false;
}

auto MouseHandle::mouseleave(QEvent* _event) noexcept -> void
{
    m_widget->setCursor(Qt::ArrowCursor);
}

auto MouseHandle::getResizing() noexcept -> bool
{
    return this->m_resizing;
}

auto MouseHandle::setCursorType(const QPoint& _pos) noexcept -> void
{
    const int  x{_pos.x()};
    const int  y{_pos.y()};
    const int  w{m_widget->width()};
    const int  h{m_widget->height()};
    const bool left{x < m_border_width};
    const bool right{x > w - m_border_width};
    const bool top{y < m_border_width};
    const bool bottom{y > h - m_border_width};
    CursorType tmp{};
    if (top && left)
    {
        tmp = CursorType::TopLeft;
    }
    else if (top && right)
    {
        tmp = CursorType::TopRight;
    }
    else if (bottom && left)
    {
        tmp = CursorType::BottomLeft;
    }
    else if (bottom && right)
    {
        tmp = CursorType::BottomRight;
    }
    else if (top)
    {
        tmp = CursorType::Top;
    }
    else if (bottom)
    {
        tmp = CursorType::Bottom;
    }
    else if (left)
    {
        tmp = CursorType::Left;
    }
    else if (right)
    {
        tmp = CursorType::Right;
    }
    else
    {
        tmp = CursorType::None;
    }
    if (this->m_cursorType == tmp)
    {
        return;
    }
    this->m_cursorType = tmp;
    emit cursorTypeChanged();
}

auto MouseHandle::conncetSignalsToSlots() noexcept -> void
{
    connect(this, &MouseHandle::cursorTypeChanged, this, &MouseHandle::setCursor, Qt::AutoConnection);
}

auto MouseHandle::setCursor() noexcept -> void
{
    switch (this->m_cursorType)
    {
        case CursorType::Top:
        {
            [[fallthrough]];
        }
        case CursorType::Bottom:
        {
            m_widget->setCursor(Qt::SizeVerCursor);
            break;
        }
        case CursorType::Left:
        {
            [[fallthrough]];
        }
        case CursorType::Right:
        {
            m_widget->setCursor(Qt::SizeHorCursor);
            break;
        }
        case CursorType::TopLeft:
        {
            [[fallthrough]];
        }
        case CursorType::BottomRight:
        {
            m_widget->setCursor(Qt::SizeFDiagCursor);
            break;
        }
        case CursorType::TopRight:
        {
            [[fallthrough]];
        }
        case CursorType::BottomLeft:
        {
            m_widget->setCursor(Qt::SizeBDiagCursor);
            break;
        }
        default:
        {
            m_widget->setCursor(Qt::ArrowCursor);
            break;
        }
    }
}
