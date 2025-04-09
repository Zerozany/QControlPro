#include "TitleWidget.h"

#include <QApplication>
#include <QFile>
#include <ranges>

#ifndef BUTTONSCSSPATH
#define BUTTONSCSSPATH R"(:/resources/css/QToolButton.css)"
#endif

TitleWidget::TitleWidget(quint8 _height, QWidget* _parent, const SystemStyle& _systemStyle)
    : m_widget{_parent}, m_height{_height}, m_systemStyle{_systemStyle}
{
    // this->setStyleSheet("background:blue;");
    Q_ASSERT(_parent != nullptr);
    Q_ASSERT(m_height > 0);
    std::invoke(&TitleWidget::conncetSignalsToSlots, this);
    std::invoke(&TitleWidget::setTitleButtonLayout, this);
    std::invoke(&TitleWidget::setTitleConfig, this, _parent);
}

auto TitleWidget::conncetSignalsToSlots() noexcept -> void
{
    connect(this, &TitleWidget::buttonPropertyChanged, this, &TitleWidget::setButtonProperty, Qt::AutoConnection);
    connect(this, &TitleWidget::buttonStyleChanged, this, &TitleWidget::setButtonStyle, Qt::AutoConnection);
    connect(this, &TitleWidget::buttonIconsChanged, this, &TitleWidget::setButtonIcons, Qt::AutoConnection);
}

auto TitleWidget::setTitleConfig(QWidget* _parent) noexcept -> void
{
    QStringList __buttonPropertyList{
        "min",
        "normal",
        "close",
    };

    QStringList __buttonIconList{
        R"(:/resources/icons/minimize.png)",
        R"(:/resources/icons/maximize.png)",
        R"(:/resources/icons/revert.png)",
        R"(:/resources/icons/close.png)",
    };

    constexpr const char* __propertyName{
        "propertyName",
    };

    QSize __buttonIconSize{12, 12};

    this->setParent(_parent);
    this->setMouseTracking(true);
    this->setFixedHeight(m_height);
    this->setContentsMargins(0, 0, 0, 0);
    Q_EMIT buttonPropertyChanged(__propertyName, __buttonPropertyList);
    Q_EMIT buttonStyleChanged(BUTTONSCSSPATH);
    Q_EMIT buttonIconsChanged(__buttonIconList, __buttonIconSize);
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
    QFile styleFile{_filePath};
    if (!styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << _filePath;
        return;
    }
    QTextStream textStream{&styleFile};
    QString     styleSheet{textStream.readAll()};
    styleFile.close();
    for (auto& button : m_titleButtons | std::views::values)
    {
        qobject_cast<QPushButton*>(button)->setStyleSheet(styleSheet);
    }
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
    for (auto& button : m_titleButtons | std::views::values)
    {
        qobject_cast<QPushButton*>(button)->setIconSize(_size);
    }
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
