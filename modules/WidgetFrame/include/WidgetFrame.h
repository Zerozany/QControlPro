_Pragma("once");
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <map>

#include "MouseHandle.h"
#include "TitleWidget.h"

class WidgetFrame : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(quint8 titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)

public:
    using widgetsMap = std::map<QString, QWidget*>;

public:
    explicit(true) WidgetFrame(widgetsMap& _widgetsMap, QWidget* _parent = nullptr);
    ~WidgetFrame() = default;

    auto titleHeight() noexcept -> quint8;

    auto setTitleHeight(const quint8& _height) noexcept -> void;

private:
    auto setWindowConfig() noexcept -> void;

    auto conncetSignalsToSlots() noexcept -> void;

    auto setFrameLayout() noexcept -> void;

Q_SIGNALS:
    auto titleHeightChanged(const quint8 _height) -> void;

protected:
    virtual auto paintEvent(QPaintEvent* _event) -> void;

    virtual auto mousePressEvent(QMouseEvent* _event) -> void;

    virtual auto mouseMoveEvent(QMouseEvent* _event) -> void;

    virtual auto mouseReleaseEvent(QMouseEvent* _event) -> void;

    virtual auto mouseDoubleClickEvent(QMouseEvent* _event) -> void;

private:
    quint8       m_titleHeight{Height}; /*标题栏高度*/
    widgetsMap&  m_widgetsMap;          /*控件集*/
    QVBoxLayout* m_globabLayout{new QVBoxLayout{this}};
    MouseHandle* m_mouseHandle{new MouseHandle{m_titleHeight, this}};
    TitleWidget* m_titleWidget{new TitleWidget{m_titleHeight, this}};

private:
    inline static constexpr quint8 Height{TITLE_HEIGHT}; /*标题栏默认高度*/
};
