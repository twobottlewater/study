#include "udprecv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpRecv w;
    w.show();
    return a.exec();
}
