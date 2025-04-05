_Pragma("once");
#include "WidgetFrame.h"

class MainWidget : public WidgetFrame
{
    Q_OBJECT
public:
    explicit(true) MainWidget(widgetsMap& _widgetsMap, QWidget* _parent = nullptr);
    ~MainWidget() = default;
};
