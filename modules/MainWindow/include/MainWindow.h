_Pragma("once");
#include <QFile>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QTextStream>
#include <QToolButton>
#include <QWidget>
#include <functional>
#include <map>

#include "MoveWidget.h"
#include "TitleBarButton.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit(true) MainWindow(QWidget* _parent = nullptr, quint16 _height = 30);
    ~MainWindow() = default;

private:
    auto setWindowConfig() noexcept -> void;

protected:
    virtual auto mousePressEvent(QMouseEvent* _event) -> void;

    virtual auto mouseMoveEvent(QMouseEvent* _event) -> void;

    virtual auto mouseReleaseEvent(QMouseEvent* _event) -> void;

    virtual auto paintEvent(QPaintEvent* _event) -> void;

    virtual auto resizeEvent(QResizeEvent* _event) -> void;

    virtual auto mouseDoubleClickEvent(QMouseEvent* _event) -> void;

private:
    std::map<QString, QWidget*> m_widgetMaps{
        {"NO1_minWindow", new QToolButton{this}},
        {"NO2_normalWindow", new QToolButton{this}},
        {"NO3_closeWindow", new QToolButton{this}},
    };

    quint16         m_height{};
    MoveWidget*     m_moveWidget{new MoveWidget{m_height, this}};
    TitleBarButton* m_titleBarButton{new TitleBarButton{m_widgetMaps, ButtonSystemStyle::WIN, this}};
};
