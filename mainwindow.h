#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigECamera.h>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

#include <MvCameraControl.h>

#include <iostream>

#include <QLabel>
#include <qtimer.h>
#include <QResizeEvent>
#include <QFileDialog>
#include <QSettings>
#include <QDesktopServices>

#include "xcammanager.h"
#include "ImageUnity.h"

#define MAX_BUF_SIZE    (1920*1200*3)

using namespace Pylon;
using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void TestBaslerCameraExampleCode();
    void TestHikCameraExampleCode();
    void UpdateLabelImage(cv::Mat mat, QLabel* label);

    Mat* openCvImage = NULL;

    QTimer* CameraDisplayUpdatingTimer;
    QTimer* AutoShootingTimer;

    cv::VideoWriter cvVideoCreator;

    int CameraInterval = 20;

    XCamManager IndustryCamera;

    QSettings Settings;

    void resizeEvent(QResizeEvent* event);

private slots:

    void CaptureCamera();
    void CaptureAndSave();
    void UpdateCameraDisplay();

    void on_pbRefresh_clicked();
    void on_pbShotImage_clicked();

    void on_pbConnectCamera_clicked();

    void on_pbShotVideo_clicked();

    void on_cbCameraList_currentIndexChanged(int index);

    void on_pbCaptureAndSave_clicked();

    void on_pbRecord_clicked();

    void on_pbCalib_clicked();

    void on_pbCalculatePeriod_clicked();

    void on_pbRunAutoShotting_clicked();

    void on_tbOpenSaveFolder_clicked();

    void on_tbResetImageCounter_clicked();

    void on_pbImageFolder_clicked();

private:
    int imageName = 0;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
