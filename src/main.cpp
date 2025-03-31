#include <QApplication>

#include "MainObject.h"

int main(int argc, char* argv[])
{
    QApplication::setDoubleClickInterval(300);  // 双击间隔时间
    QApplication app{argc, argv};
    MainObject*  obj{new MainObject{}};

    app.exec();
}
