_Pragma("once");
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit(true) MainWidget(QWidget* _parent = nullptr);
    ~MainWidget() = default;
};
