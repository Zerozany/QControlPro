#include "TitleWidget.h"

TitleWidget::TitleWidget(QWidget* _widget, quint8 _height, const SystemStyle& _systemStyle, QWidget* _parent)
    : QLabel{_parent}, m_widget{_widget}, m_height{_height}, m_systemStyle{_systemStyle}
{
    this->setParent(_parent);
    std::invoke(&TitleWidget::setTitleConfig, this);
}

auto TitleWidget::setTitleConfig() noexcept -> void
{
    // QToolButton* btn{new QToolButton{this}};
    // btn->setText("Click");
    // this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setStyleSheet("background-color: #00FF00; border-top-right-radius: 10px;border-top-left-radius: 10px");
}
