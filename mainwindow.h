#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/calib3d/calib3d.hpp>

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
#include <QMatrix>
#include <qmath.h>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QElapsedTimer>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QFrame>
#include <QtOpenGL>
#include <ImageViewer.h>

#include "xcammanager.h"
#include "ImageUnity.h"

#include "VariableTree.h"
#include "ComDevice.h"

#include "AI.h"

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

    // ---- Camera Function ----
    void TestBaslerCameraExampleCode();
    void TestHikCameraExampleCode();
    void UpdateLabelImage(cv::Mat mat, QLabel* label);
    void UpdateCameraViewer(cv::Mat mat);

    // ---- Camera variables -----
    XCamManager IndustryCamera;

    Mat* openCvImage = NULL;
    Mat openCvWarpImage;
    Mat openCvDrawingImage;
    QTimer* CameraDisplayUpdatingTimer;
    int CameraInterval = 20;
    QTimer* AutoShootingTimer;

    //------ Camera Display Widget -----
    QGraphicsPixmapItem* ImageItem;

    // ---- Calibration ----
    std::vector<cv::Point> PperspectivePoints;


    // ----- Setting -----
    QSettings Settings;

    //------ Variable Manager -----
    VariableTree* GlobalVariable;

    //----- Robot ----
    Robot* RobotObject;

    //----- AI ----
    AI YolovAI;

    //------ Conveyor -----
    COMDevice* Encoder1;
    COMDevice* Conveyor1;

    float Conveyor1Position = 0;
    QTimer* ConveyorVelocityTimer;

    //----- Connection ----

    QTcpServer* TcpServer;
    QTcpSocket* PythonTcpClient = NULL;
    QTcpSocket* ExternalSoftwareTcpClient;

    //----- Measuring Timer ----
    QElapsedTimer ElapsedTimer;

    //----- Widget Event -----

    void resizeEvent(QResizeEvent* event);

private slots:
    // ----- Calibration -----
    void transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat & transMat);
    void transformPerspective(cv::Mat processMat, cv::Point2f *points, cv::Mat & transMat);
    QPoint Mapping(QPoint p);

    //------ Camera ----
    void CaptureCamera();
    void CaptureAndSave();
    void CaptureCameraAndDisplay();
    void DrawingCameraAndDisplay();

    //----- Display -----
    void UpdateMousePosition(int x, int y);
    void UpdateCalibPointPosition(int x, int y);
    void DisplayMappingPoint(int x, int y);

    // ------ Connection -----
    void GetSocketFromPython();
    void ReadDataFromPython();
    void ReadDataFromExternalSoftware();
    void ProcessInfoFromPython(QString info);
    bool OpenServer(QString ip, int p);
    void SendCameraImageToExternal();
    void ProcessInfoFromExternalSoftware(QString info);

    // ------ Response -----
    void ReceiveConveyorResponse(QString response);
    void ReceiveRobotResponse(QString response);
    void UpdateConveyorVelocity();

    // ----- Generated Slot ----

    void on_pbRefresh_clicked();
    void on_pbShotImage_clicked();

    void on_pbConnectCamera_clicked();

    void on_pbShotVideo_clicked();

    void on_cbCameraList_currentIndexChanged(int index);

    void on_pbCaptureAndSave_clicked();

    void on_pbRecord_clicked();

    void on_pbWarpPerspective_clicked();

    void on_pbCalculatePeriod_clicked();

    void on_pbRunAutoShotting_clicked();

    void on_tbOpenSaveFolder_clicked();

    void on_tbResetImageCounter_clicked();

    void on_pbImageFolder_clicked();

    void on_pbFindChessboard_clicked();

    void on_cbCorner1_currentIndexChanged(int index);

    void on_pbGetCalibPointTool_clicked();

    void on_pbLineTool_clicked();

    void on_pbPointTool_clicked();

    void on_pbAutoCalibration_clicked();

    void on_pbMapping_clicked();

    void on_lePythonScript_returnPressed();

    void on_tbOpenScript_clicked();

    void on_pbExecuteScript_clicked();

    void on_cbIpParaOnOff_toggled(bool checked);


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pbConnectEncoder1_clicked();

    void on_leStepPer100um_returnPressed();

    void on_pbConnectConveyor1_clicked();

    void on_cbConveyor1Mode_currentTextChanged(const QString &arg1);

    void on_leConveyor1DesiredValue_returnPressed();

    void on_cbConveyorMovingMode_currentTextChanged(const QString &arg1);

    void on_leConveyor1VelocityInPositionMode_returnPressed();

    void on_pbResetConveyor1Position_clicked();

    void on_pbConnectRobot_clicked();

    void on_tbClearTermite_clicked();

    void on_leRobotTermiteSender_returnPressed();

    void on_pbConnectExternalSoftware_clicked();

    void on_leExternalSoftwareSender_returnPressed();

    void on_tbOpenDatasetImageFolder_clicked();

    void on_lwDatasetImages_itemClicked(QListWidgetItem *item);

    void on_tbOpenDatasetLabelFolder_clicked();

    void on_lwDatasetImages_currentRowChanged(int currentRow);

    void on_tbClearDatasetImageList_clicked();

    void on_tbClearDatasetLabelList_clicked();

private:

    //----- Init ----
    void initWidgetPointers();
    void InitTreeVariables();

    //----- Calibration ----
    void getPerspectiveSettings();


    //----- Calibration ----
    QComboBox* cbPerspectivePoints[4];

    float D_mapping;
    float Dx_mapping;
    float Dy_mapping;
    QMatrix mappingMatrix;

    // ----- Display ----
    int imageName = 0;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
