_Pragma("once");
#include <QObject>
#include <QWidget>

class MainObject : public QObject
{
    Q_OBJECT
public:
    explicit(true) MainObject(QObject* _parent = nullptr);
    ~MainObject() = default;

private:
    QWidget w{};
};
