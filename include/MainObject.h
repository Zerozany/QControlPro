_Pragma("once");

#include <QObject>

#include "MainWidget.h"

class MainObject : public QObject
{
    Q_OBJECT
public:
    explicit(true) MainObject(QObject* _parent = nullptr);
    ~MainObject() = default;

private:
    MainWidget w{};
};
