#include "MainWindow.h"

MainWindow::MainWindow(QWidget* _parent, quint16 _height) : QWidget{_parent}, m_height{_height}
{
    Q_ASSERT_X(m_height > 0, "MainWindow", "Window's titlebar height must greater zero");
    std::invoke(&MainWindow::setWindowConfig, this);
}

auto MainWindow::setWindowConfig() noexcept -> void
{
    this->setMouseTracking(true);
    /// @brief 移除窗口的系统默认边框和标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    /// @brief 设置窗口背景完全透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    /// @brief 刷新窗口尺寸变化事件
    this->resize(this->width(), this->height());
}

auto MainWindow::mousePressEvent(QMouseEvent* _event) -> void
{
    m_moveWidget->mousePress(_event);
}

auto MainWindow::mouseMoveEvent(QMouseEvent* _event) -> void
{
    m_moveWidget->mouseMove(_event);
}

auto MainWindow::mouseReleaseEvent(QMouseEvent* _event) -> void
{
    m_moveWidget->mouseRelease(_event);
}

auto MainWindow::paintEvent(QPaintEvent* _event) -> void
{
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    // 1. 绘制圆角背景
    QPainterPath path{};
    // 5px圆角
    path.addRoundedRect(rect(), 10, 10);
    // 填充背景色（替代样式表中的background-color）
    painter.fillPath(path, QColor("#FFFFFF"));
    // 2. 绘制边框（替代样式表中的border）
    painter.setPen(QPen(QColor("#CCCCCC"), 1));  // 1px灰色边框
    painter.drawPath(path);
}

auto MainWindow::resizeEvent(QResizeEvent* _event) -> void
{
    m_titleBarButton->resizeButtonLayout(_event, this, m_height);
}

auto MainWindow::mouseDoubleClickEvent(QMouseEvent* _event) -> void
{
    m_moveWidget->mouseDoubleClick(_event);
    QWidget::mouseDoubleClickEvent(_event);
}
