#include "forms/mainwindow.h"
#include "util/util.h"
#include <QApplication>
#include <QtNetwork/QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Util::networkAccessManager = new QNetworkAccessManager();
    Util::accessToken = nullptr;
    Util::serviceURL = "http://localhost:13259";
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
