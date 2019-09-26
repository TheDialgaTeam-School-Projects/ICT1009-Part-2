#include "UI/NewMainGui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NewMainGui w;
    w.show();

    return QApplication::exec();
}
