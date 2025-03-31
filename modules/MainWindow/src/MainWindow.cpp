#include "MainWindow.h"

MainWindow::MainWindow(QWidget* _parent, quint16 _height) : QWidget{_parent}, m_height{_height}
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    std::invoke(&MainWindow::statusButtonLayout, this);
    std::invoke(&MainWindow::setWindowProperty, this);
    std::invoke(&MainWindow::setWindwoStyle, this, R"(:/resources/QToolButton.css)", R"(:/resources/QWidget.css)");
}

auto MainWindow::setWindowProperty() noexcept -> void
{
    this->setProperty("propertyName", "main-window");
    m_widgetMaps["minWindow"]->setProperty("propertyName", "min-normal");
    m_widgetMaps["normalWindow"]->setProperty("propertyName", "min-normal");
    m_widgetMaps["closeWindow"]->setProperty("propertyName", "close");
}

auto MainWindow::setWindwoStyle(const QString& _buttonStyleString, const QString& _winStyleString) noexcept -> void
{
    QFile   buttonStyleFile{_buttonStyleString};
    QFile   winStyleFile{_winStyleString};
    QString styleSheet{};
    if (!buttonStyleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << _buttonStyleString;
        return;
    }
    QTextStream buttonStream{&buttonStyleFile};
    styleSheet = buttonStream.readAll();
    buttonStyleFile.close();
    if (!winStyleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << _winStyleString;
        return;
    }
    QTextStream winStream{&winStyleFile};
    styleSheet += winStream.readAll();
    winStyleFile.close();
    this->setStyleSheet(styleSheet);
    m_widgetMaps["minWindow"]->setStyleSheet(styleSheet);
    m_widgetMaps["normalWindow"]->setStyleSheet(styleSheet);
    m_widgetMaps["closeWindow"]->setStyleSheet(styleSheet);
}

auto MainWindow::statusButtonLayout() noexcept -> void
{
    m_widgetMaps["closeWindow"]->setGeometry(this->width() - MainSize::BUTTON_WIDTH, 0, MainSize::BUTTON_WIDTH, m_height);
    m_widgetMaps["normalWindow"]->setGeometry(this->width() - (MainSize::BUTTON_WIDTH * 2), 0, MainSize::BUTTON_WIDTH, m_height);
    m_widgetMaps["minWindow"]->setGeometry(this->width() - (MainSize::BUTTON_WIDTH * 3), 0, MainSize::BUTTON_WIDTH, m_height);
}

auto MainWindow::mousePressEvent(QMouseEvent* _event) -> void
{
    if ((_event->button() & Qt::LeftButton) && QRect{0, 0, this->width(), m_height}.contains(_event->pos()))
    {
        m_mouseHandle = true;
        m_mousePoint  = _event->globalPos() - this->pos();
    }
}

auto MainWindow::mouseMoveEvent(QMouseEvent* _event) -> void
{
    if (m_mouseHandle)
    {
        this->move(_event->globalPos() - m_mousePoint);
    }
}

auto MainWindow::mouseReleaseEvent(QMouseEvent* _event) -> void
{
    m_mouseHandle = false;
}

auto MainWindow::paintEvent(QPaintEvent* _event) -> void
{
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    // 1. 绘制圆角背景
    QPainterPath path{};
    path.addRoundedRect(rect(), 5, 5);  // 5px圆角
    // 填充背景色（替代样式表中的background-color）
    painter.fillPath(path, QColor("#FFFFFF"));
    // 2. 绘制边框（替代样式表中的border）
    painter.setPen(QPen(QColor("#CCCCCC"), 1));  // 1px灰色边框
    painter.drawPath(path);
}

auto MainWindow::resizeEvent(QResizeEvent* _event) -> void
{
    m_widgetMaps["closeWindow"]->setGeometry(this->width() - MainSize::BUTTON_WIDTH, 0, MainSize::BUTTON_WIDTH, m_height);
    m_widgetMaps["normalWindow"]->setGeometry(this->width() - (MainSize::BUTTON_WIDTH * 2), 0, MainSize::BUTTON_WIDTH, m_height);
    m_widgetMaps["minWindow"]->setGeometry(this->width() - (MainSize::BUTTON_WIDTH * 3), 0, MainSize::BUTTON_WIDTH, m_height);
}

auto MainWindow::mouseDoubleClickEvent(QMouseEvent* _event) -> void
{
    if (_event->button() == Qt::LeftButton)
    {
        if (QRect{0, 0, this->width(), m_height}.contains(_event->pos()))
        {  // 检查是否在标题栏区域
            this->isMaximized() ? showNormal() : showMaximized();
        }
    }
    QWidget::mouseDoubleClickEvent(_event);
}
