#include "mainwindow.h"
#include "ui_mainwindow.h"

static const uint32_t c_countOfImagesToGrab = 1000000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //--------- Init variable ----------

    QString saveFolder = Settings.value("CaptureAndSave/SaveFolder", "C:/Users/Admin/Desktop/XCam - Save").toString();
    ui->leSaveFolder->setText(saveFolder);

    QString pythonFile = Settings.value("ObjectDetecting/ScriptPath", "C:/Users/Admin/Desktop").toString();
    ui->leScriptPath->setText(pythonFile);

    QString imageFolder = Settings.value("AI/DatasetImageFolder", "C:/Users/Admin/Desktop").toString();
    ui->leDatasetImageFolder->setText(imageFolder);

    QString labelFolder = Settings.value("AI/DatasetLabelFolder", "C:/Users/Admin/Desktop").toString();
    ui->leDatasetLabelFolder->setText(labelFolder);

    initWidgetPointers();

    getPerspectiveSettings();

    InitTreeVariables();

    RobotObject = new Robot();
    RobotObject->SetInputWidget(ui->dsbRobotX, ui->dsbRobotY, ui->dsbRobotZ, ui->dsbRobotW, ui->dsbRobotU, ui->dsbRobotV);

    Encoder1 = new COMDevice();
    Encoder1->DefaultBaudrate = 115200;
    connect(Encoder1, SIGNAL(FinishedReadLine(QString)), this, SLOT(ReceiveConveyorResponse(QString)));
    ConveyorVelocityTimer = new QTimer();
    connect(ConveyorVelocityTimer, SIGNAL(timeout()), this, SLOT(UpdateConveyorVelocity()));

    Conveyor1 = new COMDevice();
    connect(Conveyor1, SIGNAL(FinishedReadLine(QString)), this, SLOT(ReceiveConveyorResponse(QString)));

    connect(RobotObject->RobotCOMPort, SIGNAL(FinishedReadLine(QString)), this, SLOT(ReceiveRobotResponse(QString)));

//    //---- Init timer -------
    CameraDisplayUpdatingTimer = new QTimer();
    connect(CameraDisplayUpdatingTimer, SIGNAL(timeout()), this, SLOT(CaptureCameraAndDisplay()));

    AutoShootingTimer = new QTimer();
    connect(AutoShootingTimer, SIGNAL(timeout()), this, SLOT(CaptureAndSave()));

//    //---- Init camera ------
    connect(ui->lbCameraDisplay, SIGNAL(MousePositionChanged(int, int)), this, SLOT(UpdateMousePosition(int, int)));
    connect(ui->lbCameraDisplay, SIGNAL(CalibPointSelected(int, int)), this, SLOT(UpdateCalibPointPosition(int, int)));
    connect(ui->lbCameraDisplay, SIGNAL(MappingPointSelected(int, int)), this, SLOT(DisplayMappingPoint(int, int)));
    //    //----- Init Pylon ------
//    FindBaslerCameraList();
//    //---- Init Mat-----
//    openCvImage = new Mat();

//    TestBaslerCameraExampleCode();
    //TestHikCameraExampleCode();

    on_pbRefresh_clicked();

    // ------- TCP Connection ------
    TcpServer = new QTcpServer();
    connect(TcpServer, SIGNAL(newConnection()), this, SLOT(GetSocketFromPython()));
    bool result = OpenServer("localhost", 7337);

    ExternalSoftwareTcpClient = new QTcpSocket();
    connect(ExternalSoftwareTcpClient, SIGNAL(readyRead()), this, SLOT(ReadDataFromPython()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestBaslerCameraExampleCode()
{
    Pylon::PylonAutoInitTerm autoInitTerm;
        try
        {
                     // Create a camera object (the first recognized camera)
            CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
                     // print the name of the camera
            std::cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
                     // Get camera node mapping to get camera parameters
            GenApi::INodeMap& nodemap = camera.GetNodeMap();
                     //turn on camera
            camera.Open();
                     // Get camera imaging width and height
            GenApi::CIntegerPtr width = nodemap.GetNode("Width");
            GenApi::CIntegerPtr height = nodemap.GetNode("Height");

                     // Set the camera maximum buffer, the default is 10
            camera.MaxNumBuffer = 5;
                     // Create a new pylon ImageFormatConverter object.
            CImageFormatConverter formatConverter;
                     // Determine the output pixel format
            formatConverter.OutputPixelFormat = PixelType_BGR8packed;
                     // Create a Pylonlmage that will be used to create OpenCV images
            CPylonImage pylonImage;

                     // Declare an integer variable used to count the captured image, and create a file name index
            int grabbedlmages = 0;

                     // Create a new OpenCV video creator object.
            VideoWriter cvVideoCreator;

                     // Create a new OpenCV image object.
            Mat openCvImage;

                     // video file name
            std::string videoFileName = "openCvVideo.avi";

                     // Define the video frame size
            cv::Size frameSize = Size((int)width->GetValue(), (int)height->GetValue());

                     // Set the video encoding type and frame rate, there are three options
                     // The frame rate must be less than or equal to the camera imaging frame rate

                     // Start crawling c_countOfImagesToGrab images.
                     // Camera default settings continuous crawl mode
            camera.StartGrabbing(1, GrabStrategy_LatestImageOnly);

                     // Grab the result data pointer
            CGrabResultPtr ptrGrabResult;

                     // Camera.StopGrabbing() when c_countOfImagesToGrab images get recovered successfully
                     // is automatically called by the RetrieveResult () method to stop crawling

            if (camera.IsGrabbing())
            {
                             // Waiting to receive and restore images, the timeout is set to 5000 ms.
                camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

                             // If the image is successfully captured
                if (ptrGrabResult->GrabSucceeded())
                {
                                     // Get image data
                    cout <<"SizeX: "<<ptrGrabResult->GetWidth()<<endl;
                    cout <<"SizeY: "<<ptrGrabResult->GetHeight()<<endl;

                                     // Convert the captured buffer data into pylon image.
                    formatConverter.Convert(pylonImage, ptrGrabResult);

                                     // Convert pylon image to OpenCV image.
                    openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

                    // Display timely images.
                    imshow("OpenCV Display Window", openCvImage);

                    // Define a timeout for customer's input in
                    // '0' means indefinite, i.e. the next image will be displayed after closing the window.
                    // '1' means live stream
                    waitKey(1);

                }

            }

        }
        catch (GenICam::GenericException &e)
        {
            // Error handling.
            cerr << "An exception occurred." << endl
                << e.GetDescription() << endl;
        }
        return;

}

void MainWindow::TestHikCameraExampleCode()
{
    int nRet = -1;
    void* m_handle = NULL;

    // enumerate all devices corresponding to the specified transport protocol in the subnet
    unsigned int nTLayerType = MV_GIGE_DEVICE;
    //unsigned int nTLayerType = MV_USB_DEVICE;
    MV_CC_DEVICE_INFO_LIST m_stDevList = { 0 };
    nRet = MV_CC_EnumDevices(nTLayerType, &m_stDevList);
    if (nRet != 0)
    {
        printf("error: EnumDevices fail [%x]\n", nRet);
    }

    if (m_stDevList.nDeviceNum == 0)
    {
        printf("no camera found!\n");
    }

     // Select the first online device found, create a device handle
    int nDeviceIndex = 0;

    MV_CC_DEVICE_INFO m_stDevInfo = { 0 };

    memcpy(&m_stDevInfo, m_stDevList.pDeviceInfo[nDeviceIndex], sizeof(MV_CC_DEVICE_INFO));

    nRet = MV_CC_CreateHandle(&m_handle, &m_stDevInfo);

    if (nRet != 0)
    {
        printf("error: CreateHandle fail [%x]\n", nRet);
    }



     //Connect the device
    unsigned int nAccessMode = MV_ACCESS_Exclusive;
    unsigned short nSwitchoverKey = 0;
    nRet = MV_CC_OpenDevice(m_handle, nAccessMode, nSwitchoverKey);
    if (nRet != 0)
    {
        printf("error: OpenDevice fail [%x]\n", nRet);
    }
     //...other processing

     // Start collecting images
    nRet = MV_CC_StartGrabbing(m_handle);
    if (nRet != 0)
    {
        printf("error: StartGrabbing fail [%x]\n", nRet);
    }

     // Get the size of a frame of data
    MVCC_INTVALUE stIntvalue = { 0 };
    nRet = MV_CC_GetIntValue(m_handle, "PayloadSize", &stIntvalue);
    if (nRet != 0)
    {
        printf("Get PayloadSize failed! nRet [%x]\n", nRet);
    }
     //int nBufSize = stIntvalue.nCurValue; //One frame data size
    int nBufSize = MAX_BUF_SIZE;
    unsigned int    nTestFrameSize = 0;
    unsigned char*  pFrameBuf = NULL;
    pFrameBuf = (unsigned char*)malloc(nBufSize);

    MV_FRAME_OUT_INFO_EX stInfo;
    memset(&stInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));


     // The upper application needs to control the frequency of calling the interface according to the frame rate.
     // This code is for reference only, the actual application suggests another thread to capture and process image frames
    while (1)
    {
        if (nTestFrameSize > 50)
        {
            break;
        }
        nRet = MV_CC_GetImageForBGR(m_handle, pFrameBuf, nBufSize, &stInfo, 1000);
        if (nRet != 0)
        {
            cout << "error:GetImageForRGB:" << setbase(16) << nRet << endl;
            break;
        }
        else
        {
             //...Image data processing
            cout << "imagetype:" << setbase(16) << stInfo.enPixelType << endl;

            int width = stInfo.nWidth;
            int height = stInfo.nHeight;

            if (stInfo.enPixelType == PixelType_Gvsp_BGR8_Packed)
            {
                cv::Mat pImg(height, width, CV_8UC3, pFrameBuf);
                cv::imshow("1", pImg);
                cv::waitKey(10);
            }

            nTestFrameSize++;
        }
    }

     //...other processing

     // Stop collecting images
    nRet = MV_CC_StopGrabbing(m_handle);
    if (nRet != 0)
    {
        printf("error: StopGrabbing fail [%x]\n", nRet);
    }

     // Close the device, release resources
    nRet = MV_CC_CloseDevice(m_handle);
    if (nRet != 0)
    {
        printf("error: CloseDevice fail [%x]\n", nRet);
    }

     // Destroy the handle, release resources
    nRet = MV_CC_DestroyHandle(m_handle);
    if (nRet != 0)
    {
        printf("error: DestroyHandle fail [%x]\n", nRet);
    }
    system("pause");
}

void MainWindow::UpdateLabelImage(Mat mat, QLabel *label)
{
    QImage img = ImageTool::cvMatToQImage(mat);
    int width1 = label->parentWidget()->geometry().width();
    int width2 = label->parentWidget()->parentWidget()->geometry().width();
    int width3 = label->parentWidget()->parentWidget()->parentWidget()->geometry().width();

    int ratio = (float)width3/mat.cols * 100;

    ui->lbDisplayRatio->setText(QString::number(ratio) + "%");

    label->setPixmap(QPixmap::fromImage(img).scaledToWidth(width3));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (IndustryCamera.IsOpen() == false)
        return;

    CaptureCameraAndDisplay();
    DrawingCameraAndDisplay();
}

void MainWindow::CaptureCamera()
{
    uint8_t* imageData = IndustryCamera.Capture();
    if (openCvImage != NULL)
        delete openCvImage;

    int h = IndustryCamera.Height();
    int w = IndustryCamera.Width();

    openCvImage = new Mat(h, w, CV_8UC3, imageData);

    openCvDrawingImage = openCvImage->clone();

    QString width = QString::number(openCvImage->cols);
    QString height = QString::number(openCvImage->rows);
    ui->lbResolution->setText(width + " x " + height);
}

void MainWindow::CaptureAndSave()
{
    CaptureCameraAndDisplay();

    if (!ui->cbSaveImage->isChecked())
        return;

    QString path = ui->leSaveFolder->text();
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");

    cv::imwrite((path + "/" + QString::number(imageName) + ".jpg").toStdString(), *openCvImage);

    ui->lbImageCounter->setText(QString::number(imageName));

    imageName++;
}

void MainWindow::CaptureCameraAndDisplay()
{    
    CaptureCamera();

    if (ui->cbWarpPerspectiveAuto->isChecked())
    {
        on_pbWarpPerspective_clicked();

        QElapsedTimer timer;
        timer.start();
        SendCameraImageToExternal();
        qDebug() << timer.elapsed() << "ms";
    }
    else
    {
        UpdateLabelImage(*openCvImage, ui->lbCameraDisplay);
    }

    //cvVideoCreator.write(*openCvImage);
}

void MainWindow::DrawingCameraAndDisplay()
{
    if (openCvWarpImage.empty())
        return;

    openCvDrawingImage = openCvWarpImage.clone();

    QString text1 = QString("P1(x: %1, y: %2)").arg(ui->leXCalibPoint1Location->text()).arg(ui->leYCalibPoint1Location->text());
    QString text2 = QString("P2(x: %1, y: %2)").arg(ui->leXCalibPoint2Location->text()).arg(ui->leYCalibPoint2Location->text());

    int x1Mat = ui->leXCalibPoint1Position->text().toInt();
    int y1Mat = ui->leYCalibPoint1Position->text().toInt();

    int x2Mat = ui->leXCalibPoint2Position->text().toInt();
    int y2Mat = ui->leYCalibPoint2Position->text().toInt();

    circle(openCvDrawingImage, Point(x1Mat, y1Mat), 2, Scalar(255, 0, 0), 2);
    putText(openCvDrawingImage, text1.toStdString(), Point(x1Mat + 10, y1Mat), cv::FONT_HERSHEY_SIMPLEX, 1.0f, Scalar(0, 255, 0), 2, cv::LINE_AA);
    circle(openCvDrawingImage, Point(x2Mat, y2Mat), 2, Scalar(255, 0, 0), 2);
    putText(openCvDrawingImage, text2.toStdString(), Point(x2Mat + 10, y2Mat), cv::FONT_HERSHEY_SIMPLEX, 1.0f, Scalar(0, 255, 0), 2, cv::LINE_AA);

    UpdateLabelImage(openCvDrawingImage, ui->lbCameraDisplay);
}

void MainWindow::UpdateMousePosition(int x, int y)
{
    QString debug = QString("x:%1, y:%2").arg(x).arg(y);
    ui->statusbar->showMessage(debug);
}

void MainWindow::UpdateCalibPointPosition(int x, int y)
{
    const QPixmap* pix = ui->lbCameraDisplay->pixmap();

    float ratio = (float)openCvImage->cols/pix->width();

    int xMat = x * ratio;
    int yMat = y * ratio;

    QString text;

    if (ui->cbSelectedPoint->currentIndex() == 0)
    {

        ui->leXCalibPoint1Position->setText(QString::number(xMat));
        ui->leYCalibPoint1Position->setText(QString::number(yMat));
    }
    else
    {
        text = QString("P2(x: %1, y: %2)").arg(ui->leXCalibPoint2Location->text()).arg(ui->leYCalibPoint2Location->text());

        ui->leXCalibPoint2Position->setText(QString::number(xMat));
        ui->leYCalibPoint2Position->setText(QString::number(yMat));
    }

    DrawingCameraAndDisplay();
}

void MainWindow::DisplayMappingPoint(int x, int y)
{
    if (openCvWarpImage.empty())
        return;

    const QPixmap* pix = ui->lbCameraDisplay->pixmap();

    float ratio = (float)openCvImage->cols/pix->width();

    int xMat = x * ratio;
    int yMat = y * ratio;

    QPoint newPoint = Mapping(QPoint(xMat, yMat));

    openCvDrawingImage = openCvWarpImage.clone();

    QString text = QString("(x: %1mm, y: %2mm)").arg(newPoint.x()).arg(newPoint.y());

    putText(openCvDrawingImage, text.toStdString(), Point(xMat + 10, yMat), cv::FONT_HERSHEY_SIMPLEX, 1.0f, Scalar(0, 255, 0), 2, cv::LINE_AA);
    circle(openCvDrawingImage, Point(xMat, yMat), 2, Scalar(0, 0, 255), 2);

    UpdateLabelImage(openCvDrawingImage, ui->lbCameraDisplay);
}

QPoint MainWindow::Mapping(QPoint p)
{
    return mappingMatrix.map(p);
}

void MainWindow::ProcessInfoFromPython(QString info)
{
    if (info.contains("="))
    {
        QStringList infos = info.split(";");

        foreach(QString var, infos)
        {
            if (var.contains("="))
            {
                QStringList keyvalue = var.split('=');
                QString name = keyvalue[0];
                QString value = keyvalue[1];
                GlobalVariable->UpdateChildVariable(name, value);
            }
        }
    }

    QString consoleScreen = ui->teTermiteScreen->toPlainText();
    ui->teTermiteScreen->setPlainText(consoleScreen + info);
}

bool MainWindow::OpenServer(QString ip, int p)
{
    return TcpServer->listen(QHostAddress(ip), p);
}

void MainWindow::SendCameraImageToExternal()
{
    if (PythonTcpClient == NULL)
        return;

    char* pos = (char*)openCvWarpImage.data;

    int colByte = openCvWarpImage.cols*openCvWarpImage.channels() * sizeof(uchar);
    for (int i = 0; i < openCvWarpImage.rows; i++)
    {
        char* data = (char*)openCvWarpImage.ptr<uchar>(i); //first address of the i-th line
        int sedNum = 0;
        char buf[1024] = { 0 };

        while (sedNum < colByte)
        {
            int sed = (1024 < colByte - sedNum) ? 1024 : (colByte - sedNum);
            memcpy(buf, &data[sedNum], sed);
            int SendSize = PythonTcpClient->write(buf, sed);

            if (SOCKET_ERROR == SendSize)
                return;
            sedNum += SendSize;
        }
    }
}

void MainWindow::ProcessInfoFromExternalSoftware(QString info)
{
    if (info.contains("="))
    {
        QStringList infos = info.split(";");

        foreach(QString var, infos)
        {
            if (var.contains("="))
            {
                QStringList keyvalue = var.split('=');
                QString name = keyvalue[0];
                QString value = keyvalue[1];
                GlobalVariable->UpdateChildVariable(name, value);
            }
        }
    }
}

void MainWindow::ReceiveConveyorResponse(QString response)
{
    if (response.at(0) == "P")
    {
        Conveyor1Position = response.mid(1).toFloat();
        ui->lbConveyor1Position->setText(QString::number(Conveyor1Position));
    }
}

void MainWindow::ReceiveRobotResponse(QString response)
{
    QString termiteDisplay = ui->teRobotTermiteReceiver->toPlainText();
    termiteDisplay += "\nRobot >> " + response;
    ui->teRobotTermiteReceiver->setPlainText(termiteDisplay);
}

void MainWindow::UpdateConveyorVelocity()
{
    float velocity = 0;
    static float lastPosition = 0;
    static float currentPosition = 0;
    float encoderPeriod = ui->leEncoder1Period->text().toFloat();

    currentPosition = ui->lbConveyor1Position->text().toFloat();
    velocity = (currentPosition - lastPosition) / (encoderPeriod / 1000);
    lastPosition = currentPosition;

    ui->lbConveyor1Velocity->setText(QString::number(velocity));
}

void MainWindow::GetSocketFromPython()
{
    PythonTcpClient = TcpServer->nextPendingConnection();

    connect(PythonTcpClient, SIGNAL(readyRead()), this, SLOT(ReadDataFromPython()));

    PythonTcpClient->write("python\n");
}

void MainWindow::ReadDataFromPython()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (socket)
    {
        while (socket->canReadLine())
        {
            QString receiveLines = socket->readLine();
            QStringList receiveLineList = receiveLines.split("\n");
            foreach(QString line, receiveLineList)
            {
                if (line == "")
                    continue;

                ProcessInfoFromPython(line);
            }
        }
    }
}

void MainWindow::ReadDataFromExternalSoftware()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (socket)
    {
        while (socket->canReadLine())
        {
            QString receiveLines = socket->readLine();

            //ui->teExternalSoftwareReceiver->setText(receiveLines);

            QStringList receiveLineList = receiveLines.split("\n");
            foreach(QString line, receiveLineList)
            {
                if (line == "")
                    continue;

                ProcessInfoFromExternalSoftware(line);
            }
        }
    }
}


void MainWindow::on_pbRefresh_clicked()
{
    ui->cbCameraList->addItems(IndustryCamera.FindCameraList());
}

void MainWindow::on_pbShotImage_clicked()
{
    CaptureCameraAndDisplay();
}

void MainWindow::on_pbConnectCamera_clicked()
{
    bool result = IndustryCamera.ConnectCamera(ui->cbCameraList->currentIndex());

    if (result == true)
    {
        ui->pbShotImage->setEnabled(true);
        ui->pbShotVideo->setEnabled(true);

        on_pbShotImage_clicked();
    }
}

void MainWindow::on_pbShotVideo_clicked()
{
    if (ui->pbShotVideo->isChecked() == true)
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Input"), tr("Period (ms)"), QLineEdit::Normal, "50", &ok);
        if (ok && !text.isEmpty())
        {
            int inputValue = text.toInt();
            if (inputValue > 0)
                CameraInterval = inputValue;

            ui->lbFPS->setText(QString::number((float)1000/CameraInterval));

            CameraDisplayUpdatingTimer->start(CameraInterval);
            ui->pbShotVideo->setText("Stop");

            ui->cbCameraList->setEnabled(false);
        }
        else
        {
            ui->pbShotVideo->setChecked(false);
        }

    }
    else
    {
        CameraDisplayUpdatingTimer->stop();
        ui->pbShotVideo->setText("Continious Shot");
        ui->cbCameraList->setEnabled(true);

        ui->lbFPS->setText("0");
    }
}

void MainWindow::on_cbCameraList_currentIndexChanged(int index)
{
    IndustryCamera.SelectCamera(index);

    if (IndustryCamera.IsCameraOpen(index) == true)
    {
        ui->pbShotImage->setEnabled(true);
        ui->pbShotVideo->setEnabled(true);
    }
    else
    {
        ui->pbShotImage->setEnabled(false);
        ui->pbShotVideo->setEnabled(false);
    }
}

void MainWindow::on_pbCaptureAndSave_clicked()
{
    CaptureAndSave();
}

void MainWindow::on_pbRecord_clicked()
{
//    if (ui->pbRecord->isChecked() == true)
//    {
//        static int videoName = 0;
//        QString path = ui->leSaveFolder->text();
//        QDir dir(path);
//        if (!dir.exists())
//            dir.mkpath(".");

//        QString videoPathName = ui->leSaveFolder->text() + "/" + QString::number(videoName) + ".avi";
//        int w = IndustryCamera.Width();
//        int h = IndustryCamera.Height();
//        bool rs = cvVideoCreator.open(videoPathName.toStdString(), cv::VideoWriter::fourcc('D','I','V','X'), 10, cv::Size(w, h), true);

//        ui->pbRecord->setText("Stop");
//    }
//    else
//    {
//        cvVideoCreator.release();
//        ui->pbRecord->setText("Record");
//    }
}

void MainWindow::on_pbWarpPerspective_clicked()
{
    cv::Point2f newPoints[4];

    QString order = cbPerspectivePoints[0]->currentText();

    for (int i = 0; i < 4; i++)
    {
        int id = cbPerspectivePoints[i]->currentIndex();
        newPoints[i] = PperspectivePoints[id];

        Settings.setValue(QString("CameraCalibration/PerspectivePoint/") + QString::number(i), QPoint(PperspectivePoints[i].x, PperspectivePoints[i].y));

    }

    for (int i = 1; i < 4; i++)
    {
        order += "|" + cbPerspectivePoints[i]->currentText();
    }

    Settings.setValue(QString("CameraCalibration/PerspectivePoint/order"), order);

    transformPerspective(*openCvImage, newPoints, openCvWarpImage);
    UpdateLabelImage(openCvWarpImage, ui->lbCameraDisplay);
}

void MainWindow::on_pbCalculatePeriod_clicked()
{
    float conveyorSpeed = ui->leConveyorSpeed->text().toFloat();
    float shootingArea = ui->leShootingArea->text().toFloat();
    float period = shootingArea/conveyorSpeed;

    ui->lePeriod->setText(QString::number(period * 1000));
}

void MainWindow::on_pbRunAutoShotting_clicked()
{
    if (ui->pbRunAutoShotting->isChecked() == true)
    {
        AutoShootingTimer->start(ui->lePeriod->text().toUInt());
        ui->pbRunAutoShotting->setText("Stop");
    }
    else
    {
        AutoShootingTimer->stop();
        ui->pbRunAutoShotting->setText("Auto Capture");
    }

}

void MainWindow::on_tbOpenSaveFolder_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui->leSaveFolder->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->leSaveFolder->setText(dir);

    Settings.setValue("CaptureAndSave/SaveFolder", dir);
}

void MainWindow::on_tbResetImageCounter_clicked()
{
    imageName = 0;

    ui->lbImageCounter->setText(QString::number(imageName));
}

void MainWindow::on_pbImageFolder_clicked()
{
    QDesktopServices::openUrl( QUrl::fromLocalFile(ui->leSaveFolder->text()));
}

void MainWindow::transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat & transMat)
{
    if (points.size() < 3)
        return;

    cv::Point2f inputQuad[4];

    inputQuad[0] = points[0];
    inputQuad[1] = points[1];
    inputQuad[2] = points[2];
    inputQuad[3] = points[3];

    transformPerspective(processMat, inputQuad, transMat);
}

void MainWindow::transformPerspective(Mat processMat, Point2f *points, Mat &transMat)
{
    cv::Point2f outputQuad[4];
    cv::Point2f inputQuad[4];

    inputQuad[0] = points[0];
    inputQuad[1] = points[1];
    inputQuad[2] = points[2];
    inputQuad[3] = points[3];

    // ---------Find new position-------------------
    cv::Point2f center;
    center.x = (points[0].x + points[1].x + points[2].x + points[3].x)/4;
    center.y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4;

    int maxLength = 0;

    for (int i = 0; i < 4; i++)
    {
        QLineF line;
        line.setP1(QPoint(inputQuad[i].x, inputQuad[i].y));
        if (i == 3)
        {
            line.setP2(QPoint(inputQuad[0].x, inputQuad[0].y));
        }
        else
        {
            line.setP2(QPoint(inputQuad[i + 1].x, inputQuad[i + 1].y));
        }

        int len = line.length();

        if (len > maxLength)
        {
            maxLength = len;
        }
    }

    int halfLen = maxLength / 2;

    outputQuad[0] = center + cv::Point2f(-halfLen, -halfLen);
    outputQuad[1] = center + cv::Point2f(-halfLen, halfLen);
    outputQuad[2] = center + cv::Point2f(halfLen, halfLen);
    outputQuad[3] = center + cv::Point2f(halfLen, -halfLen);

    cv:: Mat lambda = cv::Mat::zeros(processMat.rows, processMat.cols, processMat.type());

    lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);

    warpPerspective(processMat, transMat, lambda, transMat.size());
}

void MainWindow::on_pbFindChessboard_clicked()
{
    int width = ui->lbChessSizeW->text().toInt();
    int height = ui->lbChessSizeH->text().toInt();

    Size patternsize(width, height);
    Mat gray;
    Mat mat = openCvImage->clone();

    cvtColor(*openCvImage, gray, COLOR_BGR2GRAY);

    vector<Point2f> corners;
    bool patternfound = findChessboardCorners(gray, patternsize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

    if(patternfound)
    {
      cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

      PperspectivePoints.clear();

      PperspectivePoints.push_back(cv::Point(corners[0].x, corners[0].y));
      PperspectivePoints.push_back(cv::Point(corners[width - 1].x, corners[width - 1].y));
      PperspectivePoints.push_back(cv::Point(corners[width * (height - 1)].x, corners[width * (height - 1)].y));
      PperspectivePoints.push_back(cv::Point(corners[width * height - 1].x, corners[width * height - 1].y));

      ui->leCorner1X->setText(QString::number(PperspectivePoints[0].x));
      ui->leCorner1Y->setText(QString::number(PperspectivePoints[0].y));
      ui->leCorner2X->setText(QString::number(PperspectivePoints[1].x));
      ui->leCorner2Y->setText(QString::number(PperspectivePoints[1].y));
      ui->leCorner3X->setText(QString::number(PperspectivePoints[2].x));
      ui->leCorner3Y->setText(QString::number(PperspectivePoints[2].y));
      ui->leCorner4X->setText(QString::number(PperspectivePoints[3].x));
      ui->leCorner4Y->setText(QString::number(PperspectivePoints[3].y));

      circle(mat, PperspectivePoints[0], 10, Scalar(0, 255, 0), 2);
      putText(mat, "1", PperspectivePoints[0], cv::FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 255, 0), 2, cv::LINE_AA);

      circle(mat, PperspectivePoints[1], 10, Scalar(255, 0, 0), 2);
      putText(mat, "2", PperspectivePoints[1], cv::FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 0, 0), 2, cv::LINE_AA);

      circle(mat, PperspectivePoints[2], 10, Scalar(0, 0, 255), 2);
      putText(mat, "3", PperspectivePoints[2], cv::FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 2, cv::LINE_AA);

      circle(mat, PperspectivePoints[3], 10, Scalar(255, 255, 0), 2, cv::LINE_AA);
      putText(mat, "4", PperspectivePoints[3], cv::FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 0), 2, cv::LINE_AA);


      drawChessboardCorners(mat, patternsize, Mat(corners), patternfound);

      UpdateLabelImage(mat, ui->lbCameraDisplay);
    }


}

void MainWindow::on_cbCorner1_currentIndexChanged(int index)
{

}

void MainWindow::on_pbGetCalibPointTool_clicked()
{
    //QPushButton* bt = qobject_cast<QPushButton*>(sender());

    ui->lbCameraDisplay->SelectTool(CameraWidget::CALIB_POINT_TOOL);
    ui->lbCameraDisplay->ChangeToolIconInArea(ui->pbGetCalibPointTool->icon());

    DrawingCameraAndDisplay();
}

void MainWindow::on_pbLineTool_clicked()
{
    ui->lbCameraDisplay->SelectTool(CameraWidget::LINE_TOOL);
    ui->lbCameraDisplay->ChangeToolIconInArea(ui->pbLineTool->icon());
}

void MainWindow::on_pbPointTool_clicked()
{
    ui->lbCameraDisplay->SelectTool(CameraWidget::POINT_TOOL);
    ui->lbCameraDisplay->ChangeToolIconInArea(ui->pbPointTool->icon());
}

void MainWindow::on_pbAutoCalibration_clicked()
{

}

void MainWindow::on_pbMapping_clicked()
{
    float x1 = ui->leXCalibPoint1Position->text().toFloat();
    float y1 = ui->leYCalibPoint1Position->text().toFloat();
    float x2 = ui->leXCalibPoint2Position->text().toFloat();
    float y2 = ui->leYCalibPoint2Position->text().toFloat();

    float xx1 = ui->leXCalibPoint1Location->text().toFloat();
    float yy1 = ui->leYCalibPoint1Location->text().toFloat();
    float xx2 = ui->leXCalibPoint2Location->text().toFloat();
    float yy2 = ui->leYCalibPoint2Location->text().toFloat();

    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float a2 = xx2 -xx1;
    float b2 = yy2 - yy1;

    float n1n2 = a1 * a2 + b1 * b2;
    float _n1 = qSqrt(qPow(a1, 2) + qPow(b1, 2));
    float _n2 = qSqrt(qPow(a2, 2) + qPow(b2, 2));
    float ratio = _n2/_n1;

    float _n1_n2_ = _n1 * _n2;

    float cosTheta = n1n2 / _n1_n2_;
    float sinTheta = qSqrt(1 - pow(cosTheta, 2));
    //float cosTheta = a2 / _n2;
    float tanTheta = (a1 * b2 - b1 * a2) / (a1 * a2 + b1 * b2);
    float theta = qAcos(cosTheta);

    if (cosTheta < 0)
    {
        if (tanTheta > 0)
        {
            theta = 0 - theta;
        }
    }
    else
    {
        if (tanTheta < 0)
        {
            theta = 0 - theta;
        }
    }

    QMatrix RotateMatrix(qCos(theta), -qSin(theta), qSin(theta), qCos(theta), 0, 0);
    //QMatrix RotateMatrix(cosTheta, -sinTheta, sinTheta, cosTheta, 0, 0);
    QMatrix ScaleMatrix(ratio, 0, 0, 0 - ratio, 0, 0);

    QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xx1 - (ScaleRotateMatrix.m11() * x1 + ScaleRotateMatrix.m21() * y1);
    float dy = yy1 - (ScaleRotateMatrix.m12() * x1 + ScaleRotateMatrix.m22() * y1);

    float dx2 = xx2 - (ScaleRotateMatrix.m11() * x2 + ScaleRotateMatrix.m21() * y2);
    float dy2 = yy2 - (ScaleRotateMatrix.m12() * x2 + ScaleRotateMatrix.m22() * y2);

    mappingMatrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);
}

void MainWindow::on_lePythonScript_returnPressed()
{
    QProcess OProcess;
    QString Command;    //Contains the command to be executed
    QStringList args;   //Contains arguments of the command

    Command =  ui->lePythonScript->text();

    OProcess.start(Command); //Starts execution of command
    OProcess.waitForFinished();                       //Waits for execution to complete

    QString StdOut = OProcess.readAllStandardOutput();  //Reads standard output
    QString StdError = OProcess.readAllStandardError();   //Reads standard error

    ui->teTermiteScreen->setPlainText(StdOut);
}

void MainWindow::on_tbOpenScript_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Python Script"), ui->leScriptPath->text(), tr("Python Files (*.py)"));
    ui->leScriptPath->setText(path);

    Settings.setValue("ObjectDetecting/ScriptPath", path);
}

void MainWindow::on_pbExecuteScript_clicked()
{

    QString path = QCoreApplication::applicationDirPath();
    QString command("python");
    QStringList params = QStringList() << ui->leScriptPath->text();

    if (ui->leScriptParas->text().replace(" ", "") != "")
    {
        params << ui->leScriptParas->text().split(' ');
    }

    if (ui->cbIpParaOnOff->isChecked())
    {
        params << ui->leIPPara->text().split(' ');
    }

    QString imageParas = QString("-h %1 -w %2 -c %3").arg(openCvImage->rows).arg(openCvImage->cols).arg(openCvImage->channels());

    params << imageParas.split(' ');

    params << ui->leScriptParas->text().split(' ');

    QProcess *process = new QProcess();
    process->startDetached(command, params);
    process->waitForFinished();
    process->close();
}

void MainWindow::on_cbIpParaOnOff_toggled(bool checked)
{
    ui->leIPPara->setEnabled(checked);
}

void MainWindow::initWidgetPointers()
{
    cbPerspectivePoints[0] = ui->cbCorner1;
    cbPerspectivePoints[1] = ui->cbCorner2;
    cbPerspectivePoints[2] = ui->cbCorner3;
    cbPerspectivePoints[3] = ui->cbCorner4;
}

void MainWindow::getPerspectiveSettings()
{
    QStringList order = Settings.value("CameraCalibration/PerspectivePoint/order", "4|3|1|2").toString().split("|");

    PperspectivePoints.clear();

    for (int i = 0; i < 4; i++)
    {
        cbPerspectivePoints[i]->setCurrentText(order.at(i));

        QPoint p = Settings.value(QString("CameraCalibration/PerspectivePoint/") + QString::number(i)).toPoint();
        PperspectivePoints.push_back(cv::Point(p.x(), p.y()));
    }

    ui->leCorner1X->setText(QString::number(PperspectivePoints[0].x));
    ui->leCorner1Y->setText(QString::number(PperspectivePoints[0].y));

    ui->leCorner2X->setText(QString::number(PperspectivePoints[1].x));
    ui->leCorner2Y->setText(QString::number(PperspectivePoints[1].y));

    ui->leCorner3X->setText(QString::number(PperspectivePoints[2].x));
    ui->leCorner3Y->setText(QString::number(PperspectivePoints[2].y));

    ui->leCorner4X->setText(QString::number(PperspectivePoints[3].x));
    ui->leCorner4Y->setText(QString::number(PperspectivePoints[3].y));
}

void MainWindow::InitTreeVariables()
{
    GlobalVariable = new VariableTree(this);
    GlobalVariable->SetName("iCam");
    GlobalVariable->SetDisplayWidget(ui->twVariableTree);

    GlobalVariable->UpdateChildVariable("Robot.X", "0");
    GlobalVariable->SetDisplayWidget("Robot.X", ui->dsbRobotX);

    GlobalVariable->UpdateChildVariable("Conveyor1.Object.Size", "0");
    GlobalVariable->SetDisplayWidget("Conveyor1.Object.Size", ui->lbConveyor1ObjectNumber);

    ui->Conveyor1Widget->SetObjectVariableTree(GlobalVariable->FindChildVariable("Conveyor1.Object"));
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    RobotObject->SetStep(arg1.toFloat());
}

void MainWindow::on_pbConnectEncoder1_clicked()
{
    bool result = Encoder1->Connect();

    if (result == true)
    {
        float encoderPeriod = ui->leEncoder1Period->text().toFloat();
        ui->pbConnectEncoder1->setText("Disconnect Encoder");
        Encoder1->Send(QString("M317 T%1\n").arg(encoderPeriod));
        ConveyorVelocityTimer->start(encoderPeriod);
    }
    else
    {
        ui->pbConnectEncoder1->setText("Connect Encoder");
        ConveyorVelocityTimer->stop();
    }
}


void MainWindow::on_leStepPer100um_returnPressed()
{
    Encoder1->Send(QString("M318 S%1\n").arg(ui->leStepPer100um->text()));
}


void MainWindow::on_pbConnectConveyor1_clicked()
{
    bool result = Conveyor1->Connect();

    if (result == true)
    {
        ui->pbConnectConveyor1->setText("Disconnect Conveyor");
    }
    else
    {
        ui->pbConnectConveyor1->setText("Connect Conveyor");
    }
}


void MainWindow::on_cbConveyor1Mode_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Manual")
    {
        Conveyor1->Send("M310 0\n");
    }
    else
    {
        Conveyor1->Send("M310 1\n");

        on_leConveyor1DesiredValue_returnPressed();
    }
}


void MainWindow::on_leConveyor1DesiredValue_returnPressed()
{
    if (ui->cbConveyorMovingMode->currentText() == "Speed")
    {
        Conveyor1->Send(QString("M311 %1").arg(ui->leConveyor1DesiredValue->text().toInt()));
    }
    else
    {
        on_leConveyor1VelocityInPositionMode_returnPressed();
        Conveyor1->Send(QString("M312 %1").arg(ui->leConveyor1DesiredValue->text().toInt()));        
    }

}


void MainWindow::on_cbConveyorMovingMode_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Speed")
    {
        Conveyor1->Send(QString("M311 %1").arg(ui->leConveyor1DesiredValue->text()));
        ui->leConveyor1VelocityInPositionMode->setEnabled(false);
    }
    else
    {
        on_leConveyor1VelocityInPositionMode_returnPressed();

        Conveyor1->Send(QString("M312 %1").arg(ui->leConveyor1DesiredValue->text()));
        ui->leConveyor1VelocityInPositionMode->setEnabled(true);
    }
}


void MainWindow::on_leConveyor1VelocityInPositionMode_returnPressed()
{
    Conveyor1->Send(QString("M313 %1").arg(ui->leConveyor1VelocityInPositionMode->text()));
}


void MainWindow::on_pbResetConveyor1Position_clicked()
{
    Encoder1->Send("M316 0");
    ui->lbConveyor1Position->setText("0");
}


void MainWindow::on_pbConnectRobot_clicked()
{
    bool result = RobotObject->RobotCOMPort->Connect();

    if (result == true)
    {
        ui->pbConnectRobot->setText("Disconnect");
    }
    else
    {
        ui->pbConnectRobot->setText("Connect");
    }
}


void MainWindow::on_tbClearTermite_clicked()
{
    ui->teRobotTermiteReceiver->setText("");
}


void MainWindow::on_leRobotTermiteSender_returnPressed()
{
    QString msg = ui->leRobotTermiteSender->text();
    RobotObject->RobotCOMPort->Send(msg);



    QString termiteDisplay = ui->teRobotTermiteReceiver->toPlainText();
    termiteDisplay += "\nSoftware << " + msg;
    ui->teRobotTermiteReceiver->setPlainText(termiteDisplay);

    ui->leRobotTermiteSender->setText("");
}


void MainWindow::on_pbConnectExternalSoftware_clicked()
{
    QString ip = ui->leExternalSoftwareIP->text();
    int port = ui->leExternalSoftwarePort->text().toInt();

    ExternalSoftwareTcpClient->connectToHost(ip, port);

    if (ExternalSoftwareTcpClient->isOpen())
    {
        ui->pbConnectExternalSoftware->setText("Connected");
    }
    else
    {
        ui->pbConnectExternalSoftware->setText("Connect");
    }
}


void MainWindow::on_leExternalSoftwareSender_returnPressed()
{
    QString sender = ui->leExternalSoftwareSender->text() + '\n';
    ExternalSoftwareTcpClient->write(sender.toLocal8Bit());
    ui->leExternalSoftwareSender->setText(" ");
}


void MainWindow::on_tbOpenDatasetImageFolder_clicked()
{
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Open Dataset Images"), ui->leDatasetImageFolder->text(), tr("Image Files (*.jpg)"));
    if (paths.size() == 0)
        return;

    QString path = paths[0].mid(0, paths[0].lastIndexOf('/'));
    ui->leDatasetImageFolder->setText(path);

    QStringList files;

    foreach(QString fileName, paths)
    {
        files.append(fileName.mid(paths[0].lastIndexOf('/') + 1));
    }

    ui->lwDatasetImages->addItems(files);

    YolovAI.AddImages(paths);

    Settings.setValue("AI/DatasetImageFolder", path);
}

void MainWindow::on_lwDatasetImages_itemClicked(QListWidgetItem *item)
{
    if (item == NULL)
        return;

    QString imagePath = YolovAI.GetImagePath(item->text());

    QString imageName = YolovAI.GetImageName(imagePath);

    if (openCvImage != NULL)
    {
        delete openCvImage;
    }
    QPixmap img(imagePath);
    cv::Mat mat = ImageTool::QPixmapToCvMat(img);
    openCvImage = new Mat(mat);
    YolovAI.BoundShape = ui->cbDetectBound->currentText();
    openCvDrawingImage = YolovAI.DrawBox(mat, imageName);

    UpdateLabelImage(openCvDrawingImage, ui->lbCameraDisplay);
}


void MainWindow::on_tbOpenDatasetLabelFolder_clicked()
{
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Open Dataset Labels"), ui->leDatasetImageFolder->text(), tr("Label Files (*.txt)"));
    if (paths.size() == 0)
        return;

    QString path = paths[0].mid(0, paths[0].lastIndexOf('/'));
    ui->leDatasetLabelFolder->setText(path);

    QStringList files;

    foreach(QString fileName, paths)
    {
        files.append(fileName.mid(paths[0].lastIndexOf('/') + 1));
    }

    ui->lwDatasetLabels->addItems(files);

    YolovAI.AddLabels(paths);

    Settings.setValue("AI/DatasetLabelFolder", path);
}


void MainWindow::on_lwDatasetImages_currentRowChanged(int currentRow)
{
    on_lwDatasetImages_itemClicked(ui->lwDatasetImages->item(currentRow));
}


void MainWindow::on_tbClearDatasetImageList_clicked()
{
    ui->lwDatasetImages->clear();
    YolovAI.DatasetImages.clear();
}


void MainWindow::on_tbClearDatasetLabelList_clicked()
{
    ui->lwDatasetLabels->clear();
    YolovAI.DatasetLabels.clear();
}

