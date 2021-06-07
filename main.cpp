#include "mainwindow.h"

#include <QApplication>

#define HIK_CAMERA
#define BASLER_CAMERA

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("iCam");
    a.setOrganizationDomain("deltaxrobot.com");
    a.setOrganizationName("DeltaXRobot");
    a.setApplicationName("iCam");
    a.setApplicationVersion("0.1");

    MainWindow w;
    w.show();
    return a.exec();
}
