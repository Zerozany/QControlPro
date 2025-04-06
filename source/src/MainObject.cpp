#include "MainObject.h"

MainObject::MainObject(QObject* _parent) : QObject{_parent}
{
    w.resize(800, 600);
    w.show();
}
