_Pragma("once");
#include <QVBoxLayout>
#include <QWidget>
#include <map>

#include "Threshold.h"

class MouseHandle;
class TitleWidget;

class WidgetFrame : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(quint8 titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)

public:
    using widgetsMap = std::map<QString, QWidget*>;

public:
    explicit(true) WidgetFrame(widgetsMap& _widgetsMap, QWidget* _parent = nullptr);
    ~WidgetFrame() = default;

    auto setWindowTitle(const QString& _title) -> void = delete;

    auto titleHeight() noexcept -> quint8;

    auto setTitleHeight(const quint8& _height) noexcept -> void;

    auto setLayout(QLayout* _layout) noexcept -> void;

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
    QVBoxLayout* m_globabLayout{new QVBoxLayout{this}};
    quint8       m_titleHeight{Height}; /*标题栏高度*/
    widgetsMap&  m_widgetsMap;          /*控件集*/
    MouseHandle* m_mouseHandle{};
    TitleWidget* m_titleWidget{};

private:
    inline static constexpr quint8 Height{TITLE_HEIGHT}; /*标题栏默认高度*/
};
