_Pragma("once");
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

#include "MainWindow.h"

class MainWidget : public MainWindow
{
    Q_OBJECT
public:
    explicit(true) MainWidget(MainWindow* _parent = nullptr);
    ~MainWidget() = default;

private:
    // QSystemTrayIcon* m_trayIcon{new QSystemTrayIcon{this}};    // 托盘图标
    // QMenu*           m_trayMenu{new QMenu{this}};              // 托盘菜单
    // QAction*         m_quitAction{new QAction{"退出", this}};  // 退出动作
};
