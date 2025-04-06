#include "TitleWidget.h"

TitleWidget::TitleWidget(QWidget* _widget, quint8 _height, const SystemStyle& _systemStyle, QWidget* _parent)
    : QLabel{_parent}, m_widget{_widget}, m_height{_height}, m_systemStyle{_systemStyle}
{
    std::invoke(&TitleWidget::conncetSignalsToSlots, this);
    std::invoke(&TitleWidget::setTitleConfig, this, _parent);
    std::invoke([this] { setButtonProperty(); });
    std::invoke(&TitleWidget::setTitleButtonLayout, this);
    std::invoke(&TitleWidget::setButtonStyle, this, R"(:/resources/QToolButton.css)");
}

auto TitleWidget::conncetSignalsToSlots() noexcept -> void
{
    connect(this, &TitleWidget::buttonStyleChanged, this, &TitleWidget::readButtonStyle, Qt::AutoConnection);
}

auto TitleWidget::setTitleConfig(QWidget* _parent) noexcept -> void
{
    this->setParent(_parent);
    // this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

auto TitleWidget::setButtonProperty(const char* _groupName, const QStringList& _propertyNames) noexcept -> void
{
    m_titleButtons.at("min")->setProperty(_groupName, _propertyNames.at(0));
    m_titleButtons.at("normal")->setProperty(_groupName, _propertyNames.at(1));
    m_titleButtons.at("close")->setProperty(_groupName, _propertyNames.at(2));
}

auto TitleWidget::setButtonStyle(const QString& _filePath) noexcept -> void
{
    QFile filePath{_filePath};
    if (!filePath.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << _filePath;
        return;
    }
    QTextStream textStream{&filePath};
    QString     styleSheet{textStream.readAll()};
    filePath.close();
    emit buttonStyleChanged(styleSheet);
}

auto TitleWidget::setTitleButtonLayout() noexcept -> void
{
    for (auto& button : m_titleButtons | std::views::values)
    {
        button->setFixedSize(BUTTONWIDTH, m_height);
    }
    m_titleLayout->setSpacing(0);
    m_titleLayout->setContentsMargins(0, 0, 0, 0);
    m_titleLayout->addStretch();
    m_titleLayout->addWidget(m_titleButtons.at("min"), Qt::AlignTop);
    m_titleLayout->addWidget(m_titleButtons.at("normal"), Qt::AlignTop);
    m_titleLayout->addWidget(m_titleButtons.at("close"), Qt::AlignTop);
}

auto TitleWidget::readButtonStyle(const QString& _styleString) noexcept -> void
{
    for (auto&& buttons : m_titleButtons | std::views::values)
    {
        buttons->setStyleSheet(_styleString);
    }
}
