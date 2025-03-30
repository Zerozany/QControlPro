#include <QApplication>

#include "MainObject.h"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    MainObject*  obj{new MainObject{}};

    app.exec();
}
