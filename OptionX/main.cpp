#include "optionx.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptionX w;
    w.show();

    return a.exec();
}
