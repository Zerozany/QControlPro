#include "MainWidget.h"

MainWidget::MainWidget(MainWindow* _parent) : MainWindow{_parent}
{
    m_trayIcon->setIcon(QIcon(":/resources/application/icon.ico"));  // 使用资源中的图标
    m_trayIcon->setToolTip("托盘示例");
    // 绑定退出信号
    connect(m_quitAction, &QAction::triggered, this, &MainWidget::close);
    m_quitAction->setIcon(QIcon{":/resources/application/icon.ico"});
    m_trayMenu->addAction(m_quitAction);

    // 3. 绑定菜单到托盘图标
    m_trayIcon->setContextMenu(m_trayMenu);

    // 4. 显示托盘图标
    m_trayIcon->show();
}
