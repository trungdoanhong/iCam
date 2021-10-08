QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AI.cpp \
    ComDevice.cpp \
    ConveyorWidget.cpp \
    Robot.cpp \
    VariableTree.cpp \
    camerawidget.cpp \
    main.cpp \
    mainwindow.cpp \
    xcam.cpp \
    xcambasler.cpp \
    xcamhik.cpp \
    xcammanager.cpp

HEADERS += \
    AI.h \
    ComDevice.h \
    ConveyorWidget.h \
    ImageUnity.h \
    Robot.h \
    VariableTree.h \
    camerawidget.h \
    mainwindow.h \
    xcam.h \
    xcambasler.h \
    xcamhik.h \
    xcammanager.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
$$(PYLON_DEV_DIR)/include \
$$(PYLON_DEV_DIR)/include/pylon \
"C:/Program Files (x86)/MVS/Development/Includes"

LIBS += \
-L$$(PYLON_DEV_DIR)/lib/x64

INCLUDEPATH += E:\OpenCV\opencv-4.0\build\include
LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400.lib
LIBS += E:\OpenCV\opencv-4.0\build\x64\vc15\lib\opencv_world400d.lib
LIBS += "C:\Program Files (x86)\MVS\Development\Libraries\win64\MvCameraControl.lib"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_ICONS = icons8_lens.ico

DISTFILES += \
    detect.py
