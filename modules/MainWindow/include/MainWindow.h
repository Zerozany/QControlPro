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

namespace MainSize
{
    constexpr quint8 BUTTON_WIDTH{40};
}

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit(true) MainWindow(QWidget* _parent = nullptr, quint16 _height = 30);
    ~MainWindow() = default;

    virtual auto setWindowProperty() noexcept -> void;

    virtual auto setWindwoStyle(const QString& _buttonStyleString, const QString& _winStyleString) noexcept -> void;

private:
    auto statusButtonLayout() noexcept -> void;

protected:
    virtual auto mousePressEvent(QMouseEvent* _event) -> void;

    virtual auto mouseMoveEvent(QMouseEvent* _event) -> void;

    virtual auto mouseReleaseEvent(QMouseEvent* _event) -> void;

    virtual auto paintEvent(QPaintEvent* _event) -> void;

    virtual auto resizeEvent(QResizeEvent* _event) -> void;

    virtual auto mouseDoubleClickEvent(QMouseEvent* _event) -> void;

private:
    bool    m_mouseHandle{};
    QPoint  m_mousePoint{};
    quint16 m_height{};

    std::map<QString, QWidget*> m_widgetMaps{
        {"minWindow", new QToolButton{this}},
        {"normalWindow", new QToolButton{this}},
        {"closeWindow", new QToolButton{this}},
    };
};
