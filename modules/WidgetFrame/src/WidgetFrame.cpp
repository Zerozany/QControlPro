#include "WidgetFrame.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <functional>

#include "MouseHandle.h"
#include "TitleWidget.h"

WidgetFrame::WidgetFrame(widgetsMap& _widgetsMap, QWidget* _parent)
    : QWidget{_parent}, m_widgetsMap{_widgetsMap}
{
    Q_ASSERT_X(this->m_widgetsMap.size() > 0, "WidgetFrame", "Arguments _widgetsMap is empty!");
    std::invoke(&WidgetFrame::setWindowConfig, this);
    std::invoke(&WidgetFrame::setFrameLayout, this);
    std::invoke(&WidgetFrame::conncetSignalsToSlots, this);
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
    emit titleHeightChanged(this->titleHeight());
}

auto WidgetFrame::setLayout(QLayout* _layout) noexcept -> void
{
    if (m_globabLayout->count() >= 2)
    {
        delete m_globabLayout->takeAt(m_globabLayout->count() - 1);
    }
    m_globabLayout->addLayout(_layout);
}

auto WidgetFrame::setWindowConfig() noexcept -> void
{
    /// @brief 开启鼠标活动监听
    this->setMouseTracking(true);
    /// @brief 移除窗口的系统默认边框和标题栏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    /// @brief 设置窗口背景完全透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    /// @brief 设置基础大小
    this->setBaseSize(800, 600);

    m_mouseHandle = new MouseHandle{m_titleHeight, this};
    m_titleWidget = new TitleWidget{m_titleHeight, this};
}

auto WidgetFrame::conncetSignalsToSlots() noexcept -> void
{
    connect(this, &WidgetFrame::titleHeightChanged, m_mouseHandle, &MouseHandle::resetHeight, Qt::QueuedConnection);
    connect(this, &WidgetFrame::titleHeightChanged, m_titleWidget, &TitleWidget::resetHeight, Qt::QueuedConnection);
    connect(m_mouseHandle, &MouseHandle::resizeWidget, m_titleWidget, &TitleWidget::setTitleStatus, Qt::DirectConnection);
}

auto WidgetFrame::setFrameLayout() noexcept -> void
{
    QHBoxLayout* titleLayout{new QHBoxLayout{}};
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(0);
    titleLayout->addWidget(m_titleWidget);
    m_globabLayout->setContentsMargins(0, 0, 0, 0);
    m_globabLayout->addLayout(titleLayout, Qt::AlignTop);
    m_globabLayout->addStretch();
}

auto WidgetFrame::paintEvent(QPaintEvent* _event) -> void
{
    QPainter painter{this};
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    // 1. 绘制圆角背景
    QPainterPath path{};
    // 10px圆角
    path.addRoundedRect(this->rect(), 10, 10);
    // 填充背景色（替代样式表中的background-color）
    painter.fillPath(path, QColor("#FFFFFF"));
    // 2. 绘制边框（替代样式表中的border, 1px灰色边框
    painter.setPen(QPen(QColor("#CCCCCC"), 1));

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
    std::invoke(&MouseHandle::mouseDoubleClick, this->m_mouseHandle, _event);
}
