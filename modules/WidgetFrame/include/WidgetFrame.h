_Pragma("once");
#include <QPainter>
#include <QPainterPath>
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

Q_SIGNALS:
    auto titleHeightChanged() -> void;

protected:
    virtual auto paintEvent(QPaintEvent* _event) -> void;

    virtual auto mousePressEvent(QMouseEvent* _event) -> void;

    virtual auto mouseMoveEvent(QMouseEvent* _event) -> void;

    virtual auto mouseReleaseEvent(QMouseEvent* _event) -> void;

    virtual auto mouseDoubleClickEvent(QMouseEvent* _event) -> void;

private:
    quint8       m_titleHeight{Height}; /*标题栏高度*/
    widgetsMap&  m_widgetsMap;          /*控件集*/
    MouseHandle* m_mouseHandle{new MouseHandle{this}};
    TitleWidget* m_titleWidget{new TitleWidget{this, 30, TitleWidget::SystemStyle::WIN, this}};

private:
    inline static constexpr quint8 Height{30}; /*标题栏默认高度*/
};
