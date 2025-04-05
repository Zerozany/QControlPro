_Pragma("once");

#include <QObject>
#include <QToolButton>

#include "MainWidget.h"

class MainObject : public QObject
{
    Q_OBJECT
public:
    explicit(true) MainObject(QObject* _parent = nullptr);
    ~MainObject() = default;

private:
    std::map<QString, QWidget*> m_objectsmap{
        {"NO1_min", new QToolButton},
        {"NO1_normal", new QToolButton},
        {"NO1_close", new QToolButton},
    };

    MainWidget w{m_objectsmap};
};
