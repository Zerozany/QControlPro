#include "TitleWidget.h"

#include <QApplication>

#include "WidgetFrame.h"

TitleWidget::TitleWidget(quint8 _height, QWidget* _parent, const SystemStyle& _systemStyle)
    : m_widget{_parent}, m_height{_height}, m_systemStyle{_systemStyle}
{
    // this->setStyleSheet("background:blue;");
    Q_ASSERT(_parent != nullptr);
    Q_ASSERT(m_height > 0);
    std::invoke(&TitleWidget::setTitleConfig, this, _parent);
    std::invoke(&TitleWidget::conncetSignalsToSlots, this);
    std::invoke([this] { this->setButtonProperty(); });
    std::invoke([this] { this->setButtonIcons(QStringList{R"(:/resources/icons/minimize.png)", R"(:/resources/icons/maximize.png)", R"(:/resources/icons/revert.png)", R"(:/resources/icons/close.png)"}); });
    std::invoke(&TitleWidget::setButtonStyle, this, R"(:/resources/css/QToolButton.css)");
    std::invoke(&TitleWidget::setTitleButtonLayout, this);
}

auto TitleWidget::conncetSignalsToSlots() noexcept -> void
{
    connect(this, &TitleWidget::buttonStyleChanged, this, &TitleWidget::readButtonStyle, Qt::AutoConnection);
}

auto TitleWidget::setTitleConfig(QWidget* _parent) noexcept -> void
{
    this->setParent(_parent);
    this->setMouseTracking(true);
    this->setFixedHeight(m_height);
    this->setContentsMargins(0, 0, 0, 0);
}

auto TitleWidget::setButtonProperty(const char* _groupName, const QStringList& _propertyNames) noexcept -> void
{
    if (_propertyNames.size() < 3)
    {
        qWarning() << "_propertyNames's size must greator three";
        return;
    }
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

auto TitleWidget::setButtonIcons(const QStringList& _filePath, const QSize& _size) noexcept -> void
{
    if (_filePath.size() < 4)
    {
        qWarning() << "_filePath's size must greator three";
        return;
    }
    qobject_cast<QPushButton*>(m_titleButtons.at("min"))->setIcon(QIcon{_filePath.at(0)});
    qobject_cast<QPushButton*>(m_titleButtons.at("normal"))->setIcon(QIcon{_filePath.at(1)});
    qobject_cast<QPushButton*>(m_titleButtons.at("close"))->setIcon(QIcon{_filePath.at(3)});
    qobject_cast<QPushButton*>(m_titleButtons.at("min"))->setIconSize(_size);
    qobject_cast<QPushButton*>(m_titleButtons.at("normal"))->setIconSize(_size);
    qobject_cast<QPushButton*>(m_titleButtons.at("close"))->setIconSize(_size);
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

auto TitleWidget::setTitleStatus(const bool _flag) noexcept -> void
{
    if (_flag)
    {
        QEvent leaveEvent(QEvent::Leave);
        for (auto& button : m_titleButtons | std::views::values)
        {
            QApplication::sendEvent(button, &leaveEvent);
            button->update();
        }
    }
    this->setAttribute(Qt::WA_TransparentForMouseEvents, _flag);
}

auto TitleWidget::readButtonStyle(const QString& _styleString) noexcept -> void
{
    for (auto& button : m_titleButtons | std::views::values)
    {
        button->setStyleSheet(_styleString);
    }
}

auto TitleWidget::resetHeight(const quint8 _height) noexcept -> void
{
    if (m_height == _height && m_height == 0)
    {
        return;
    }
    m_height = _height;
    this->setFixedHeight(m_height);
    for (auto& button : m_titleButtons | std::views::values)
    {
        button->setFixedSize(BUTTONWIDTH, m_height);
    }
}
