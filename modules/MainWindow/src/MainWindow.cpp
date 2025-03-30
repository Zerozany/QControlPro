#include "MainWindow.h"

MainWindow::MainWindow(QWidget* _parent, quint16 _height) : QWidget{_parent}, m_height{_height}
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

auto MainWindow::mousePressEvent(QMouseEvent* _event) -> void
{
    if ((_event->button() & Qt::LeftButton) && QRect{0, 0, this->width(), m_height}.contains(_event->pos()))
    {
        m_mousehandle = true;
        m_mousepoint  = _event->globalPos() - this->pos();
    }
}

auto MainWindow::mouseMoveEvent(QMouseEvent* _event) -> void
{
    if (m_mousehandle)
    {
        this->move(_event->globalPos() - m_mousepoint);
    }
}

auto MainWindow::mouseReleaseEvent(QMouseEvent* _event) -> void
{
    m_mousehandle = false;
}
