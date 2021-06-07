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

//    //---- Init timer -------
    CameraDisplayUpdatingTimer = new QTimer();
    connect(CameraDisplayUpdatingTimer, SIGNAL(timeout()), this, SLOT(UpdateCameraDisplay()));

    AutoShootingTimer = new QTimer();
    connect(AutoShootingTimer, SIGNAL(timeout()), this, SLOT(CaptureAndSave()));

//    //---- Init camera ------

//    //----- Init Pylon ------
//    FindBaslerCameraList();
//    //---- Init Mat-----
//    openCvImage = new Mat();

//    TestBaslerCameraExampleCode();
    //TestHikCameraExampleCode();

    on_pbRefresh_clicked();
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

    label->setPixmap(QPixmap::fromImage(img).scaledToWidth(width3));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (IndustryCamera.IsOpen() == false)
        return;

    UpdateCameraDisplay();
}

void MainWindow::CaptureCamera()
{
    uint8_t* imageData = IndustryCamera.Capture();
    if (openCvImage != NULL)
        delete openCvImage;

    int h = IndustryCamera.Height();
    int w = IndustryCamera.Width();

    openCvImage = new Mat(h, w, CV_8UC3, imageData);
}

void MainWindow::CaptureAndSave()
{
    UpdateCameraDisplay();

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

void MainWindow::UpdateCameraDisplay()
{    
    CaptureCamera();
    UpdateLabelImage(*openCvImage, ui->lbCameraDisplay);

    cvVideoCreator.write(*openCvImage);
}


void MainWindow::on_pbRefresh_clicked()
{
    ui->cbCameraList->addItems(IndustryCamera.FindCameraList());
}

void MainWindow::on_pbShotImage_clicked()
{
    UpdateCameraDisplay();
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
        CameraDisplayUpdatingTimer->start(CameraInterval);
        ui->pbShotVideo->setText("Stop");

        ui->cbCameraList->setEnabled(false);
    }
    else
    {
        CameraDisplayUpdatingTimer->stop();
        ui->pbShotVideo->setText("Continious Shot");
        ui->cbCameraList->setEnabled(true);
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
    if (ui->pbRecord->isChecked() == true)
    {
        static int videoName = 0;
        QString path = ui->leSaveFolder->text();
        QDir dir(path);
        if (!dir.exists())
            dir.mkpath(".");

        QString videoPathName = ui->leSaveFolder->text() + "/" + QString::number(videoName) + ".avi";
        int w = IndustryCamera.Width();
        int h = IndustryCamera.Height();
        bool rs = cvVideoCreator.open(videoPathName.toStdString(), cv::VideoWriter::fourcc('D','I','V','X'), 10, cv::Size(w, h), true);

        ui->pbRecord->setText("Stop");
    }
    else
    {
        cvVideoCreator.release();
        ui->pbRecord->setText("Record");
    }
}

void MainWindow::on_pbCalib_clicked()
{

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
