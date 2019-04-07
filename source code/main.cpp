#include "log_in.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Log_in w; //log in page
    w.show();

    return a.exec();
}
