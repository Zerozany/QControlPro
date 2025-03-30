_Pragma("once");
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit(true) MainWindow(QWidget* _parent = nullptr);
    ~MainWindow() = default;
};
