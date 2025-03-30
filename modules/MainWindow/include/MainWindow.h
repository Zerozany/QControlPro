_Pragma("once");
#include <QMouseEvent>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit(true) MainWindow(QWidget* _parent = nullptr, quint16 _height = 30);
    ~MainWindow() = default;

protected:
    virtual auto mousePressEvent(QMouseEvent* _event) -> void;

    virtual auto mouseMoveEvent(QMouseEvent* _event) -> void;

    virtual auto mouseReleaseEvent(QMouseEvent* _event) -> void;

private:
    bool    m_mousehandle{};
    QPoint  m_mousepoint{};
    quint16 m_height{};
};
