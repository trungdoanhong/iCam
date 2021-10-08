# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindow.ui'
##
## Created by: Qt User Interface Compiler version 5.15.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

from CameraWidget import CameraWidget

import resource_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(800, 677)
        icon = QIcon()
        icon.addFile(u":/icon/icons8_lens_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setStyleSheet(u"")
        self.actionSave_Image = QAction(MainWindow)
        self.actionSave_Image.setObjectName(u"actionSave_Image")
        self.actionStart = QAction(MainWindow)
        self.actionStart.setObjectName(u"actionStart")
        self.actionStop = QAction(MainWindow)
        self.actionStop.setObjectName(u"actionStop")
        self.actionSave_Video = QAction(MainWindow)
        self.actionSave_Video.setObjectName(u"actionSave_Video")
        self.actionSave_Image_2 = QAction(MainWindow)
        self.actionSave_Image_2.setObjectName(u"actionSave_Image_2")
        self.actionSave_Video_2 = QAction(MainWindow)
        self.actionSave_Video_2.setObjectName(u"actionSave_Video_2")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout = QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.pbConnectCamera = QPushButton(self.centralwidget)
        self.pbConnectCamera.setObjectName(u"pbConnectCamera")
        font = QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pbConnectCamera.setFont(font)
        self.pbConnectCamera.setStyleSheet(u"")

        self.horizontalLayout.addWidget(self.pbConnectCamera)

        self.cbCameraList = QComboBox(self.centralwidget)
        self.cbCameraList.setObjectName(u"cbCameraList")
        self.cbCameraList.setMinimumSize(QSize(200, 0))

        self.horizontalLayout.addWidget(self.cbCameraList)

        self.pbRefresh = QPushButton(self.centralwidget)
        self.pbRefresh.setObjectName(u"pbRefresh")
        icon1 = QIcon()
        icon1.addFile(u":/icon/icons8_replay_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRefresh.setIcon(icon1)

        self.horizontalLayout.addWidget(self.pbRefresh)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.pbShotImage = QPushButton(self.centralwidget)
        self.pbShotImage.setObjectName(u"pbShotImage")
        self.pbShotImage.setEnabled(False)
        icon2 = QIcon()
        icon2.addFile(u":/icon/icons8_google_images_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbShotImage.setIcon(icon2)

        self.horizontalLayout.addWidget(self.pbShotImage)

        self.pbShotVideo = QPushButton(self.centralwidget)
        self.pbShotVideo.setObjectName(u"pbShotVideo")
        self.pbShotVideo.setEnabled(False)
        icon3 = QIcon()
        icon3.addFile(u":/icon/icons8_play_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon3.addFile(u":/icon/icons8_pause_48px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbShotVideo.setIcon(icon3)
        self.pbShotVideo.setCheckable(True)

        self.horizontalLayout.addWidget(self.pbShotVideo)

        self.pbRecord = QPushButton(self.centralwidget)
        self.pbRecord.setObjectName(u"pbRecord")
        self.pbRecord.setEnabled(False)
        icon4 = QIcon()
        icon4.addFile(u":/icon/icons8_record_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRecord.setIcon(icon4)
        self.pbRecord.setCheckable(True)

        self.horizontalLayout.addWidget(self.pbRecord)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")

        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.scrollArea = QScrollArea(self.centralwidget)
        self.scrollArea.setObjectName(u"scrollArea")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.scrollArea.sizePolicy().hasHeightForWidth())
        self.scrollArea.setSizePolicy(sizePolicy)
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 435, 579))
        sizePolicy1 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.scrollAreaWidgetContents.sizePolicy().hasHeightForWidth())
        self.scrollAreaWidgetContents.setSizePolicy(sizePolicy1)
        self.horizontalLayout_4 = QHBoxLayout(self.scrollAreaWidgetContents)
        self.horizontalLayout_4.setSpacing(0)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.widget = QWidget(self.scrollAreaWidgetContents)
        self.widget.setObjectName(u"widget")
        sizePolicy1.setHeightForWidth(self.widget.sizePolicy().hasHeightForWidth())
        self.widget.setSizePolicy(sizePolicy1)
        self.widget.setMinimumSize(QSize(0, 0))
        self.verticalLayout_2 = QVBoxLayout(self.widget)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.frame = QFrame(self.widget)
        self.frame.setObjectName(u"frame")
        self.frame.setMinimumSize(QSize(0, 30))
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_6 = QHBoxLayout(self.frame)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.frame1 = QFrame(self.frame)
        self.frame1.setObjectName(u"frame1")
        self.horizontalLayout_8 = QHBoxLayout(self.frame1)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.horizontalLayout_8.setContentsMargins(0, 0, 0, 0)
        self.fImageCounter = QFrame(self.frame1)
        self.fImageCounter.setObjectName(u"fImageCounter")
        self.fImageCounter.setStyleSheet(u"QFrame\n"
"{\n"
"	background-color: rgb(225, 225, 225);\n"
"}")
        self.horizontalLayout_5 = QHBoxLayout(self.fImageCounter)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalLayout_5.setContentsMargins(10, 0, 10, 0)
        self.tbResetImageCounter = QToolButton(self.fImageCounter)
        self.tbResetImageCounter.setObjectName(u"tbResetImageCounter")
        icon5 = QIcon()
        icon5.addFile(u":/icon/icons8_reset_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbResetImageCounter.setIcon(icon5)

        self.horizontalLayout_5.addWidget(self.tbResetImageCounter)

        self.label_12 = QLabel(self.fImageCounter)
        self.label_12.setObjectName(u"label_12")

        self.horizontalLayout_5.addWidget(self.label_12)

        self.lbImageCounter = QLabel(self.fImageCounter)
        self.lbImageCounter.setObjectName(u"lbImageCounter")
        self.lbImageCounter.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.horizontalLayout_5.addWidget(self.lbImageCounter)


        self.horizontalLayout_8.addWidget(self.fImageCounter)

        self.fResolution = QFrame(self.frame1)
        self.fResolution.setObjectName(u"fResolution")
        self.fResolution.setMinimumSize(QSize(0, 0))
        self.fResolution.setStyleSheet(u"background-color: rgb(225, 225, 225);")
        self.fResolution.setFrameShape(QFrame.StyledPanel)
        self.fResolution.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_7 = QHBoxLayout(self.fResolution)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(10, 0, 10, 0)
        self.label_17 = QLabel(self.fResolution)
        self.label_17.setObjectName(u"label_17")

        self.horizontalLayout_7.addWidget(self.label_17)

        self.lbResolution = QLabel(self.fResolution)
        self.lbResolution.setObjectName(u"lbResolution")

        self.horizontalLayout_7.addWidget(self.lbResolution)


        self.horizontalLayout_8.addWidget(self.fResolution)

        self.fResolution_2 = QFrame(self.frame1)
        self.fResolution_2.setObjectName(u"fResolution_2")
        self.fResolution_2.setMinimumSize(QSize(0, 0))
        self.fResolution_2.setStyleSheet(u"background-color: rgb(225, 225, 225);")
        self.fResolution_2.setFrameShape(QFrame.StyledPanel)
        self.fResolution_2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.fResolution_2)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(10, 0, 10, 0)
        self.label_18 = QLabel(self.fResolution_2)
        self.label_18.setObjectName(u"label_18")

        self.horizontalLayout_9.addWidget(self.label_18)

        self.lbDisplayRatio = QLabel(self.fResolution_2)
        self.lbDisplayRatio.setObjectName(u"lbDisplayRatio")

        self.horizontalLayout_9.addWidget(self.lbDisplayRatio)


        self.horizontalLayout_8.addWidget(self.fResolution_2)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_8.addItem(self.horizontalSpacer_2)


        self.horizontalLayout_6.addWidget(self.frame1)


        self.verticalLayout_2.addWidget(self.frame)

        self.lbCameraDisplay = CameraWidget(self.widget)
        self.lbCameraDisplay.setObjectName(u"lbCameraDisplay")
        sizePolicy1.setHeightForWidth(self.lbCameraDisplay.sizePolicy().hasHeightForWidth())
        self.lbCameraDisplay.setSizePolicy(sizePolicy1)
        self.lbCameraDisplay.setMinimumSize(QSize(0, 0))
        self.lbCameraDisplay.setStyleSheet(u"background-color: rgb(255, 255, 255);")

        self.verticalLayout_2.addWidget(self.lbCameraDisplay)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_2)


        self.horizontalLayout_4.addWidget(self.widget)

        self.scrollArea.setWidget(self.scrollAreaWidgetContents)

        self.horizontalLayout_2.addWidget(self.scrollArea)

        self.scrollArea_2 = QScrollArea(self.centralwidget)
        self.scrollArea_2.setObjectName(u"scrollArea_2")
        sizePolicy1.setHeightForWidth(self.scrollArea_2.sizePolicy().hasHeightForWidth())
        self.scrollArea_2.setSizePolicy(sizePolicy1)
        self.scrollArea_2.setMinimumSize(QSize(0, 0))
        self.scrollArea_2.setMaximumSize(QSize(345, 16777215))
        self.scrollArea_2.setWidgetResizable(True)
        self.scrollAreaWidgetContents_2 = QWidget()
        self.scrollAreaWidgetContents_2.setObjectName(u"scrollAreaWidgetContents_2")
        self.scrollAreaWidgetContents_2.setGeometry(QRect(0, -81, 320, 2000))
        sizePolicy1.setHeightForWidth(self.scrollAreaWidgetContents_2.sizePolicy().hasHeightForWidth())
        self.scrollAreaWidgetContents_2.setSizePolicy(sizePolicy1)
        self.scrollAreaWidgetContents_2.setMinimumSize(QSize(0, 2000))
        self.scrollAreaWidgetContents_2.setMaximumSize(QSize(320, 16777215))
        self.verticalLayout_3 = QVBoxLayout(self.scrollAreaWidgetContents_2)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.groupBox_3 = QGroupBox(self.scrollAreaWidgetContents_2)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.groupBox_3.setMinimumSize(QSize(0, 50))
        font1 = QFont()
        font1.setPointSize(8)
        font1.setBold(False)
        font1.setItalic(False)
        font1.setWeight(50)
        self.groupBox_3.setFont(font1)
        self.gridLayout_3 = QGridLayout(self.groupBox_3)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.leSaveFolder = QLineEdit(self.groupBox_3)
        self.leSaveFolder.setObjectName(u"leSaveFolder")
        self.leSaveFolder.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_3.addWidget(self.leSaveFolder, 5, 1, 1, 1)

        self.pbCalculatePeriod = QPushButton(self.groupBox_3)
        self.pbCalculatePeriod.setObjectName(u"pbCalculatePeriod")
        self.pbCalculatePeriod.setMinimumSize(QSize(0, 0))

        self.gridLayout_3.addWidget(self.pbCalculatePeriod, 2, 0, 1, 1)

        self.label_8 = QLabel(self.groupBox_3)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setMinimumSize(QSize(100, 0))

        self.gridLayout_3.addWidget(self.label_8, 1, 0, 1, 1)

        self.leShootingArea = QLineEdit(self.groupBox_3)
        self.leShootingArea.setObjectName(u"leShootingArea")
        sizePolicy2 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.leShootingArea.sizePolicy().hasHeightForWidth())
        self.leShootingArea.setSizePolicy(sizePolicy2)
        self.leShootingArea.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_3.addWidget(self.leShootingArea, 1, 1, 1, 1)

        self.label_5 = QLabel(self.groupBox_3)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_3.addWidget(self.label_5, 3, 2, 1, 1)

        self.lePeriod = QLineEdit(self.groupBox_3)
        self.lePeriod.setObjectName(u"lePeriod")
        sizePolicy2.setHeightForWidth(self.lePeriod.sizePolicy().hasHeightForWidth())
        self.lePeriod.setSizePolicy(sizePolicy2)
        self.lePeriod.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_3.addWidget(self.lePeriod, 3, 1, 1, 1)

        self.cbSaveImage = QCheckBox(self.groupBox_3)
        self.cbSaveImage.setObjectName(u"cbSaveImage")
        self.cbSaveImage.setChecked(True)

        self.gridLayout_3.addWidget(self.cbSaveImage, 4, 1, 1, 1)

        self.label_7 = QLabel(self.groupBox_3)
        self.label_7.setObjectName(u"label_7")

        self.gridLayout_3.addWidget(self.label_7, 0, 2, 1, 1)

        self.label_10 = QLabel(self.groupBox_3)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setMinimumSize(QSize(100, 0))

        self.gridLayout_3.addWidget(self.label_10, 4, 0, 1, 1)

        self.label_4 = QLabel(self.groupBox_3)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setMinimumSize(QSize(100, 0))

        self.gridLayout_3.addWidget(self.label_4, 3, 0, 1, 1)

        self.label_9 = QLabel(self.groupBox_3)
        self.label_9.setObjectName(u"label_9")

        self.gridLayout_3.addWidget(self.label_9, 1, 2, 1, 1)

        self.label_6 = QLabel(self.groupBox_3)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setMinimumSize(QSize(100, 0))

        self.gridLayout_3.addWidget(self.label_6, 0, 0, 1, 1)

        self.leConveyorSpeed = QLineEdit(self.groupBox_3)
        self.leConveyorSpeed.setObjectName(u"leConveyorSpeed")
        sizePolicy2.setHeightForWidth(self.leConveyorSpeed.sizePolicy().hasHeightForWidth())
        self.leConveyorSpeed.setSizePolicy(sizePolicy2)
        self.leConveyorSpeed.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_3.addWidget(self.leConveyorSpeed, 0, 1, 1, 1)

        self.tbOpenSaveFolder = QToolButton(self.groupBox_3)
        self.tbOpenSaveFolder.setObjectName(u"tbOpenSaveFolder")
        self.tbOpenSaveFolder.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)

        self.gridLayout_3.addWidget(self.tbOpenSaveFolder, 5, 2, 1, 1)

        self.pbCaptureAndSave = QPushButton(self.groupBox_3)
        self.pbCaptureAndSave.setObjectName(u"pbCaptureAndSave")
        self.pbCaptureAndSave.setMinimumSize(QSize(0, 40))
        self.pbCaptureAndSave.setIcon(icon2)
        self.pbCaptureAndSave.setIconSize(QSize(32, 32))

        self.gridLayout_3.addWidget(self.pbCaptureAndSave, 6, 0, 1, 1)

        self.pbRunAutoShotting = QPushButton(self.groupBox_3)
        self.pbRunAutoShotting.setObjectName(u"pbRunAutoShotting")
        self.pbRunAutoShotting.setMinimumSize(QSize(0, 40))
        icon6 = QIcon()
        icon6.addFile(u":/icon/icons8_camcorder_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRunAutoShotting.setIcon(icon6)
        self.pbRunAutoShotting.setIconSize(QSize(32, 32))
        self.pbRunAutoShotting.setCheckable(True)

        self.gridLayout_3.addWidget(self.pbRunAutoShotting, 6, 1, 1, 1)

        self.pbImageFolder = QPushButton(self.groupBox_3)
        self.pbImageFolder.setObjectName(u"pbImageFolder")
        self.pbImageFolder.setMinimumSize(QSize(0, 40))
        icon7 = QIcon()
        icon7.addFile(u":/icon/icons8_folder_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbImageFolder.setIcon(icon7)

        self.gridLayout_3.addWidget(self.pbImageFolder, 6, 2, 1, 1)

        self.label_11 = QLabel(self.groupBox_3)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setMinimumSize(QSize(100, 0))

        self.gridLayout_3.addWidget(self.label_11, 5, 0, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox_3)

        self.groupBox = QGroupBox(self.scrollAreaWidgetContents_2)
        self.groupBox.setObjectName(u"groupBox")
        self.groupBox.setEnabled(True)
        self.gridLayout = QGridLayout(self.groupBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.label_35 = QLabel(self.groupBox)
        self.label_35.setObjectName(u"label_35")

        self.gridLayout.addWidget(self.label_35, 15, 0, 1, 1)

        self.cbCorner2 = QComboBox(self.groupBox)
        self.cbCorner2.addItem("")
        self.cbCorner2.addItem("")
        self.cbCorner2.addItem("")
        self.cbCorner2.addItem("")
        self.cbCorner2.setObjectName(u"cbCorner2")

        self.gridLayout.addWidget(self.cbCorner2, 6, 0, 1, 1)

        self.leYCalibPoint2Position = QLineEdit(self.groupBox)
        self.leYCalibPoint2Position.setObjectName(u"leYCalibPoint2Position")
        sizePolicy1.setHeightForWidth(self.leYCalibPoint2Position.sizePolicy().hasHeightForWidth())
        self.leYCalibPoint2Position.setSizePolicy(sizePolicy1)
        self.leYCalibPoint2Position.setMinimumSize(QSize(20, 0))
        self.leYCalibPoint2Position.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leYCalibPoint2Position, 20, 2, 1, 1)

        self.label_13 = QLabel(self.groupBox)
        self.label_13.setObjectName(u"label_13")

        self.gridLayout.addWidget(self.label_13, 1, 0, 1, 1)

        self.cbSelectedPoint = QComboBox(self.groupBox)
        self.cbSelectedPoint.addItem("")
        self.cbSelectedPoint.addItem("")
        self.cbSelectedPoint.setObjectName(u"cbSelectedPoint")

        self.gridLayout.addWidget(self.cbSelectedPoint, 16, 2, 1, 1)

        self.label_19 = QLabel(self.groupBox)
        self.label_19.setObjectName(u"label_19")

        self.gridLayout.addWidget(self.label_19, 4, 1, 1, 1)

        self.label_26 = QLabel(self.groupBox)
        self.label_26.setObjectName(u"label_26")

        self.gridLayout.addWidget(self.label_26, 17, 1, 1, 1)

        self.cbCorner3 = QComboBox(self.groupBox)
        self.cbCorner3.addItem("")
        self.cbCorner3.addItem("")
        self.cbCorner3.addItem("")
        self.cbCorner3.addItem("")
        self.cbCorner3.setObjectName(u"cbCorner3")

        self.gridLayout.addWidget(self.cbCorner3, 7, 0, 1, 1)

        self.leCorner4X = QLineEdit(self.groupBox)
        self.leCorner4X.setObjectName(u"leCorner4X")
        sizePolicy1.setHeightForWidth(self.leCorner4X.sizePolicy().hasHeightForWidth())
        self.leCorner4X.setSizePolicy(sizePolicy1)
        self.leCorner4X.setMinimumSize(QSize(20, 0))
        self.leCorner4X.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner4X, 8, 1, 1, 1)

        self.leXCalibPoint2Position = QLineEdit(self.groupBox)
        self.leXCalibPoint2Position.setObjectName(u"leXCalibPoint2Position")
        sizePolicy1.setHeightForWidth(self.leXCalibPoint2Position.sizePolicy().hasHeightForWidth())
        self.leXCalibPoint2Position.setSizePolicy(sizePolicy1)
        self.leXCalibPoint2Position.setMinimumSize(QSize(20, 0))
        self.leXCalibPoint2Position.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leXCalibPoint2Position, 20, 1, 1, 1)

        self.leYCalibPoint1Location = QLineEdit(self.groupBox)
        self.leYCalibPoint1Location.setObjectName(u"leYCalibPoint1Location")
        sizePolicy1.setHeightForWidth(self.leYCalibPoint1Location.sizePolicy().hasHeightForWidth())
        self.leYCalibPoint1Location.setSizePolicy(sizePolicy1)
        self.leYCalibPoint1Location.setMinimumSize(QSize(20, 0))
        self.leYCalibPoint1Location.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leYCalibPoint1Location, 14, 2, 1, 1)

        self.leYCalibPoint1Position = QLineEdit(self.groupBox)
        self.leYCalibPoint1Position.setObjectName(u"leYCalibPoint1Position")
        sizePolicy1.setHeightForWidth(self.leYCalibPoint1Position.sizePolicy().hasHeightForWidth())
        self.leYCalibPoint1Position.setSizePolicy(sizePolicy1)
        self.leYCalibPoint1Position.setMinimumSize(QSize(20, 0))
        self.leYCalibPoint1Position.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leYCalibPoint1Position, 18, 2, 1, 1)

        self.pbPointTool = QPushButton(self.groupBox)
        self.pbPointTool.setObjectName(u"pbPointTool")
        self.pbPointTool.setMinimumSize(QSize(0, 0))
        icon8 = QIcon()
        icon8.addFile(u":/icon/icons8_select_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbPointTool.setIcon(icon8)

        self.gridLayout.addWidget(self.pbPointTool, 27, 1, 1, 1)

        self.label_21 = QLabel(self.groupBox)
        self.label_21.setObjectName(u"label_21")

        self.gridLayout.addWidget(self.label_21, 12, 1, 1, 1)

        self.label_15 = QLabel(self.groupBox)
        self.label_15.setObjectName(u"label_15")

        self.gridLayout.addWidget(self.label_15, 2, 2, 1, 1)

        self.pbWarpPerspective = QPushButton(self.groupBox)
        self.pbWarpPerspective.setObjectName(u"pbWarpPerspective")
        self.pbWarpPerspective.setMinimumSize(QSize(0, 40))
        icon9 = QIcon()
        icon9.addFile(u":/icon/icons8_opacity_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbWarpPerspective.setIcon(icon9)
        self.pbWarpPerspective.setIconSize(QSize(32, 32))

        self.gridLayout.addWidget(self.pbWarpPerspective, 9, 0, 1, 2)

        self.label_14 = QLabel(self.groupBox)
        self.label_14.setObjectName(u"label_14")

        self.gridLayout.addWidget(self.label_14, 2, 0, 1, 1)

        self.label_31 = QLabel(self.groupBox)
        self.label_31.setObjectName(u"label_31")

        self.gridLayout.addWidget(self.label_31, 14, 0, 1, 1)

        self.pbGetCalibPointTool = QPushButton(self.groupBox)
        self.pbGetCalibPointTool.setObjectName(u"pbGetCalibPointTool")
        self.pbGetCalibPointTool.setMinimumSize(QSize(0, 0))
        icon10 = QIcon()
        icon10.addFile(u":/icon/icons8_target_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbGetCalibPointTool.setIcon(icon10)

        self.gridLayout.addWidget(self.pbGetCalibPointTool, 16, 1, 1, 1)

        self.leCorner4Y = QLineEdit(self.groupBox)
        self.leCorner4Y.setObjectName(u"leCorner4Y")
        self.leCorner4Y.setMinimumSize(QSize(20, 0))
        self.leCorner4Y.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner4Y, 8, 2, 1, 1)

        self.label_34 = QLabel(self.groupBox)
        self.label_34.setObjectName(u"label_34")

        self.gridLayout.addWidget(self.label_34, 25, 0, 1, 1)

        self.label_30 = QLabel(self.groupBox)
        self.label_30.setObjectName(u"label_30")

        self.gridLayout.addWidget(self.label_30, 12, 0, 1, 1)

        self.leCorner3X = QLineEdit(self.groupBox)
        self.leCorner3X.setObjectName(u"leCorner3X")
        sizePolicy1.setHeightForWidth(self.leCorner3X.sizePolicy().hasHeightForWidth())
        self.leCorner3X.setSizePolicy(sizePolicy1)
        self.leCorner3X.setMinimumSize(QSize(20, 0))
        self.leCorner3X.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner3X, 7, 1, 1, 1)

        self.pbLineTool = QPushButton(self.groupBox)
        self.pbLineTool.setObjectName(u"pbLineTool")
        self.pbLineTool.setMinimumSize(QSize(0, 0))
        icon11 = QIcon()
        icon11.addFile(u":/icon/icons8_line_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLineTool.setIcon(icon11)

        self.gridLayout.addWidget(self.pbLineTool, 26, 1, 1, 1)

        self.pbFindChessboard = QPushButton(self.groupBox)
        self.pbFindChessboard.setObjectName(u"pbFindChessboard")
        self.pbFindChessboard.setMinimumSize(QSize(0, 40))
        icon12 = QIcon()
        icon12.addFile(u":/icon/icons8_chessboard_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFindChessboard.setIcon(icon12)
        self.pbFindChessboard.setIconSize(QSize(32, 32))

        self.gridLayout.addWidget(self.pbFindChessboard, 3, 0, 1, 2)

        self.pbMapping = QPushButton(self.groupBox)
        self.pbMapping.setObjectName(u"pbMapping")
        self.pbMapping.setMinimumSize(QSize(0, 40))
        icon13 = QIcon()
        icon13.addFile(u":/icon/icons8_grid_3_48px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbMapping.setIcon(icon13)
        self.pbMapping.setIconSize(QSize(32, 32))

        self.gridLayout.addWidget(self.pbMapping, 24, 0, 1, 2)

        self.lineEdit_4 = QLineEdit(self.groupBox)
        self.lineEdit_4.setObjectName(u"lineEdit_4")
        sizePolicy1.setHeightForWidth(self.lineEdit_4.sizePolicy().hasHeightForWidth())
        self.lineEdit_4.setSizePolicy(sizePolicy1)
        self.lineEdit_4.setMinimumSize(QSize(20, 0))
        self.lineEdit_4.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.lineEdit_4, 2, 1, 1, 1)

        self.cbCorner1 = QComboBox(self.groupBox)
        self.cbCorner1.addItem("")
        self.cbCorner1.addItem("")
        self.cbCorner1.addItem("")
        self.cbCorner1.addItem("")
        self.cbCorner1.setObjectName(u"cbCorner1")

        self.gridLayout.addWidget(self.cbCorner1, 5, 0, 1, 1)

        self.leXCalibPoint1Location = QLineEdit(self.groupBox)
        self.leXCalibPoint1Location.setObjectName(u"leXCalibPoint1Location")
        sizePolicy1.setHeightForWidth(self.leXCalibPoint1Location.sizePolicy().hasHeightForWidth())
        self.leXCalibPoint1Location.setSizePolicy(sizePolicy1)
        self.leXCalibPoint1Location.setMinimumSize(QSize(20, 0))
        self.leXCalibPoint1Location.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leXCalibPoint1Location, 14, 1, 1, 1)

        self.lineEdit_3 = QLineEdit(self.groupBox)
        self.lineEdit_3.setObjectName(u"lineEdit_3")
        sizePolicy3 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.lineEdit_3.sizePolicy().hasHeightForWidth())
        self.lineEdit_3.setSizePolicy(sizePolicy3)
        self.lineEdit_3.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.lineEdit_3, 1, 2, 1, 1)

        self.leXCalibPoint2Location = QLineEdit(self.groupBox)
        self.leXCalibPoint2Location.setObjectName(u"leXCalibPoint2Location")
        sizePolicy1.setHeightForWidth(self.leXCalibPoint2Location.sizePolicy().hasHeightForWidth())
        self.leXCalibPoint2Location.setSizePolicy(sizePolicy1)
        self.leXCalibPoint2Location.setMinimumSize(QSize(20, 0))
        self.leXCalibPoint2Location.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leXCalibPoint2Location, 15, 1, 1, 1)

        self.label_32 = QLabel(self.groupBox)
        self.label_32.setObjectName(u"label_32")

        self.gridLayout.addWidget(self.label_32, 26, 0, 1, 1)

        self.label_23 = QLabel(self.groupBox)
        self.label_23.setObjectName(u"label_23")

        self.gridLayout.addWidget(self.label_23, 17, 0, 1, 1)

        self.label_33 = QLabel(self.groupBox)
        self.label_33.setObjectName(u"label_33")

        self.gridLayout.addWidget(self.label_33, 27, 0, 1, 1)

        self.leCorner2X = QLineEdit(self.groupBox)
        self.leCorner2X.setObjectName(u"leCorner2X")
        sizePolicy1.setHeightForWidth(self.leCorner2X.sizePolicy().hasHeightForWidth())
        self.leCorner2X.setSizePolicy(sizePolicy1)
        self.leCorner2X.setMinimumSize(QSize(20, 0))
        self.leCorner2X.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner2X, 6, 1, 1, 1)

        self.leCorner1X = QLineEdit(self.groupBox)
        self.leCorner1X.setObjectName(u"leCorner1X")
        sizePolicy1.setHeightForWidth(self.leCorner1X.sizePolicy().hasHeightForWidth())
        self.leCorner1X.setSizePolicy(sizePolicy1)
        self.leCorner1X.setMinimumSize(QSize(70, 0))
        self.leCorner1X.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner1X, 5, 1, 1, 1)

        self.cbCorner4 = QComboBox(self.groupBox)
        self.cbCorner4.addItem("")
        self.cbCorner4.addItem("")
        self.cbCorner4.addItem("")
        self.cbCorner4.addItem("")
        self.cbCorner4.setObjectName(u"cbCorner4")

        self.gridLayout.addWidget(self.cbCorner4, 8, 0, 1, 1)

        self.label_20 = QLabel(self.groupBox)
        self.label_20.setObjectName(u"label_20")

        self.gridLayout.addWidget(self.label_20, 4, 2, 1, 1)

        self.label_36 = QLabel(self.groupBox)
        self.label_36.setObjectName(u"label_36")

        self.gridLayout.addWidget(self.label_36, 20, 0, 1, 1)

        self.leCorner2Y = QLineEdit(self.groupBox)
        self.leCorner2Y.setObjectName(u"leCorner2Y")
        self.leCorner2Y.setMinimumSize(QSize(20, 0))
        self.leCorner2Y.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner2Y, 6, 2, 1, 1)

        self.lineEdit_2 = QLineEdit(self.groupBox)
        self.lineEdit_2.setObjectName(u"lineEdit_2")
        sizePolicy1.setHeightForWidth(self.lineEdit_2.sizePolicy().hasHeightForWidth())
        self.lineEdit_2.setSizePolicy(sizePolicy1)
        self.lineEdit_2.setMinimumSize(QSize(20, 0))
        self.lineEdit_2.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.lineEdit_2, 1, 1, 1, 1)

        self.leCorner3Y = QLineEdit(self.groupBox)
        self.leCorner3Y.setObjectName(u"leCorner3Y")
        self.leCorner3Y.setMinimumSize(QSize(20, 0))
        self.leCorner3Y.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner3Y, 7, 2, 1, 1)

        self.label_27 = QLabel(self.groupBox)
        self.label_27.setObjectName(u"label_27")

        self.gridLayout.addWidget(self.label_27, 17, 2, 1, 1)

        self.leYCalibPoint2Location = QLineEdit(self.groupBox)
        self.leYCalibPoint2Location.setObjectName(u"leYCalibPoint2Location")
        sizePolicy1.setHeightForWidth(self.leYCalibPoint2Location.sizePolicy().hasHeightForWidth())
        self.leYCalibPoint2Location.setSizePolicy(sizePolicy1)
        self.leYCalibPoint2Location.setMinimumSize(QSize(20, 0))
        self.leYCalibPoint2Location.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leYCalibPoint2Location, 15, 2, 1, 1)

        self.label = QLabel(self.groupBox)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 0, 1, 1, 2)

        self.checkBox = QCheckBox(self.groupBox)
        self.checkBox.setObjectName(u"checkBox")

        self.gridLayout.addWidget(self.checkBox, 25, 1, 1, 1)

        self.label_29 = QLabel(self.groupBox)
        self.label_29.setObjectName(u"label_29")

        self.gridLayout.addWidget(self.label_29, 18, 0, 1, 1)

        self.leXCalibPoint1Position = QLineEdit(self.groupBox)
        self.leXCalibPoint1Position.setObjectName(u"leXCalibPoint1Position")
        sizePolicy1.setHeightForWidth(self.leXCalibPoint1Position.sizePolicy().hasHeightForWidth())
        self.leXCalibPoint1Position.setSizePolicy(sizePolicy1)
        self.leXCalibPoint1Position.setMinimumSize(QSize(20, 0))
        self.leXCalibPoint1Position.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leXCalibPoint1Position, 18, 1, 1, 1)

        self.label_2 = QLabel(self.groupBox)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout.addWidget(self.label_2, 4, 0, 1, 1)

        self.label_22 = QLabel(self.groupBox)
        self.label_22.setObjectName(u"label_22")

        self.gridLayout.addWidget(self.label_22, 12, 2, 1, 1)

        self.leCorner1Y = QLineEdit(self.groupBox)
        self.leCorner1Y.setObjectName(u"leCorner1Y")
        self.leCorner1Y.setMinimumSize(QSize(70, 0))
        self.leCorner1Y.setMaximumSize(QSize(70, 16777215))

        self.gridLayout.addWidget(self.leCorner1Y, 5, 2, 1, 1)

        self.pbAutoCalibration = QPushButton(self.groupBox)
        self.pbAutoCalibration.setObjectName(u"pbAutoCalibration")
        self.pbAutoCalibration.setMinimumSize(QSize(0, 40))
        icon14 = QIcon()
        icon14.addFile(u":/icon/icons8_3d_model_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbAutoCalibration.setIcon(icon14)
        self.pbAutoCalibration.setIconSize(QSize(32, 32))

        self.gridLayout.addWidget(self.pbAutoCalibration, 28, 0, 1, 2)

        self.cbWarpPerspectiveAuto = QCheckBox(self.groupBox)
        self.cbWarpPerspectiveAuto.setObjectName(u"cbWarpPerspectiveAuto")

        self.gridLayout.addWidget(self.cbWarpPerspectiveAuto, 9, 2, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(self.scrollAreaWidgetContents_2)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setEnabled(True)
        self.gridLayout_2 = QGridLayout(self.groupBox_2)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.lePythonScript = QLineEdit(self.groupBox_2)
        self.lePythonScript.setObjectName(u"lePythonScript")

        self.gridLayout_2.addWidget(self.lePythonScript, 10, 0, 1, 3)

        self.pbRunDetecting = QPushButton(self.groupBox_2)
        self.pbRunDetecting.setObjectName(u"pbRunDetecting")
        self.pbRunDetecting.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.pbRunDetecting, 7, 0, 1, 1)

        self.leScriptPath = QLineEdit(self.groupBox_2)
        self.leScriptPath.setObjectName(u"leScriptPath")

        self.gridLayout_2.addWidget(self.leScriptPath, 0, 1, 1, 1)

        self.label_3 = QLabel(self.groupBox_2)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.label_3, 6, 0, 1, 1)

        self.label_25 = QLabel(self.groupBox_2)
        self.label_25.setObjectName(u"label_25")
        self.label_25.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.label_25, 1, 0, 1, 1)

        self.leYolovModel = QLineEdit(self.groupBox_2)
        self.leYolovModel.setObjectName(u"leYolovModel")

        self.gridLayout_2.addWidget(self.leYolovModel, 6, 1, 1, 1)

        self.teTermiteScreen = QTextEdit(self.groupBox_2)
        self.teTermiteScreen.setObjectName(u"teTermiteScreen")

        self.gridLayout_2.addWidget(self.teTermiteScreen, 9, 0, 1, 3)

        self.tbOpenScript = QToolButton(self.groupBox_2)
        self.tbOpenScript.setObjectName(u"tbOpenScript")
        self.tbOpenScript.setIcon(icon7)

        self.gridLayout_2.addWidget(self.tbOpenScript, 0, 2, 1, 1)

        self.label_16 = QLabel(self.groupBox_2)
        self.label_16.setObjectName(u"label_16")
        self.label_16.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.label_16, 0, 0, 1, 1)

        self.label_24 = QLabel(self.groupBox_2)
        self.label_24.setObjectName(u"label_24")
        self.label_24.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.label_24, 8, 0, 1, 1)

        self.tbOpenModelFolder = QToolButton(self.groupBox_2)
        self.tbOpenModelFolder.setObjectName(u"tbOpenModelFolder")
        self.tbOpenModelFolder.setIcon(icon7)

        self.gridLayout_2.addWidget(self.tbOpenModelFolder, 6, 2, 1, 1)

        self.pbExecuteScript = QPushButton(self.groupBox_2)
        self.pbExecuteScript.setObjectName(u"pbExecuteScript")
        self.pbExecuteScript.setMinimumSize(QSize(100, 0))

        self.gridLayout_2.addWidget(self.pbExecuteScript, 3, 0, 1, 1)

        self.cbIpParaOnOff = QCheckBox(self.groupBox_2)
        self.cbIpParaOnOff.setObjectName(u"cbIpParaOnOff")
        self.cbIpParaOnOff.setChecked(True)

        self.gridLayout_2.addWidget(self.cbIpParaOnOff, 2, 0, 1, 1)

        self.leScriptParas = QLineEdit(self.groupBox_2)
        self.leScriptParas.setObjectName(u"leScriptParas")

        self.gridLayout_2.addWidget(self.leScriptParas, 1, 1, 1, 1)

        self.leIPPara = QLineEdit(self.groupBox_2)
        self.leIPPara.setObjectName(u"leIPPara")
        self.leIPPara.setReadOnly(True)

        self.gridLayout_2.addWidget(self.leIPPara, 2, 1, 1, 2)


        self.verticalLayout_3.addWidget(self.groupBox_2)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_3.addItem(self.verticalSpacer)

        self.scrollArea_2.setWidget(self.scrollAreaWidgetContents_2)

        self.horizontalLayout_2.addWidget(self.scrollArea_2)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"iCam- Industry Camera Code Example", None))
        self.actionSave_Image.setText(QCoreApplication.translate("MainWindow", u"Save Image", None))
        self.actionStart.setText(QCoreApplication.translate("MainWindow", u"Start", None))
        self.actionStop.setText(QCoreApplication.translate("MainWindow", u"Stop", None))
        self.actionSave_Video.setText(QCoreApplication.translate("MainWindow", u"Save Video", None))
        self.actionSave_Image_2.setText(QCoreApplication.translate("MainWindow", u"Save Image", None))
        self.actionSave_Video_2.setText(QCoreApplication.translate("MainWindow", u"Save Video", None))
        self.pbConnectCamera.setText(QCoreApplication.translate("MainWindow", u"Connect", None))
        self.pbRefresh.setText("")
        self.pbShotImage.setText(QCoreApplication.translate("MainWindow", u"Single Shot", None))
        self.pbShotVideo.setText(QCoreApplication.translate("MainWindow", u"Continious Shot", None))
        self.pbRecord.setText(QCoreApplication.translate("MainWindow", u"Record", None))
        self.tbResetImageCounter.setText("")
        self.label_12.setText(QCoreApplication.translate("MainWindow", u"Images:", None))
        self.lbImageCounter.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.label_17.setText(QCoreApplication.translate("MainWindow", u"Resolution:", None))
        self.lbResolution.setText(QCoreApplication.translate("MainWindow", u"0 x 0", None))
        self.label_18.setText(QCoreApplication.translate("MainWindow", u"Display:", None))
        self.lbDisplayRatio.setText(QCoreApplication.translate("MainWindow", u"50%", None))
        self.lbCameraDisplay.setText("")
        self.groupBox_3.setTitle(QCoreApplication.translate("MainWindow", u"Capture and Save", None))
        self.leSaveFolder.setText(QCoreApplication.translate("MainWindow", u"C:\\Users\\Admin\\Desktop\\XCam - Save", None))
        self.pbCalculatePeriod.setText(QCoreApplication.translate("MainWindow", u"Calculate", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"Shooting Area", None))
        self.leShootingArea.setText(QCoreApplication.translate("MainWindow", u"200", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"ms", None))
        self.lePeriod.setText(QCoreApplication.translate("MainWindow", u"4000", None))
        self.cbSaveImage.setText("")
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"mm/s", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"Save Images", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"Period", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"Conveyor Speed", None))
        self.leConveyorSpeed.setText(QCoreApplication.translate("MainWindow", u"50", None))
#if QT_CONFIG(tooltip)
        self.tbOpenSaveFolder.setToolTip(QCoreApplication.translate("MainWindow", u"Select Saving Folder", None))
#endif // QT_CONFIG(tooltip)
        self.tbOpenSaveFolder.setText(QCoreApplication.translate("MainWindow", u"...", None))
        self.pbCaptureAndSave.setText(QCoreApplication.translate("MainWindow", u"Capture", None))
        self.pbRunAutoShotting.setText(QCoreApplication.translate("MainWindow", u"Auto Capture", None))
#if QT_CONFIG(tooltip)
        self.pbImageFolder.setToolTip(QCoreApplication.translate("MainWindow", u"Open Image Folder", None))
#endif // QT_CONFIG(tooltip)
        self.pbImageFolder.setText("")
        self.label_11.setText(QCoreApplication.translate("MainWindow", u"Image Folder", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"Camera Calibration", None))
        self.label_35.setText(QCoreApplication.translate("MainWindow", u"Point 2 (reality)", None))
        self.cbCorner2.setItemText(0, QCoreApplication.translate("MainWindow", u"1", None))
        self.cbCorner2.setItemText(1, QCoreApplication.translate("MainWindow", u"2", None))
        self.cbCorner2.setItemText(2, QCoreApplication.translate("MainWindow", u"3", None))
        self.cbCorner2.setItemText(3, QCoreApplication.translate("MainWindow", u"4", None))

        self.cbCorner2.setCurrentText(QCoreApplication.translate("MainWindow", u"3", None))
        self.leYCalibPoint2Position.setText("")
        self.label_13.setText(QCoreApplication.translate("MainWindow", u"Dimension", None))
        self.cbSelectedPoint.setItemText(0, QCoreApplication.translate("MainWindow", u"Point 1", None))
        self.cbSelectedPoint.setItemText(1, QCoreApplication.translate("MainWindow", u"Point 2", None))

        self.label_19.setText(QCoreApplication.translate("MainWindow", u"X", None))
        self.label_26.setText(QCoreApplication.translate("MainWindow", u"X (pixel)", None))
        self.cbCorner3.setItemText(0, QCoreApplication.translate("MainWindow", u"1", None))
        self.cbCorner3.setItemText(1, QCoreApplication.translate("MainWindow", u"2", None))
        self.cbCorner3.setItemText(2, QCoreApplication.translate("MainWindow", u"3", None))
        self.cbCorner3.setItemText(3, QCoreApplication.translate("MainWindow", u"4", None))

        self.cbCorner3.setCurrentText(QCoreApplication.translate("MainWindow", u"1", None))
        self.leCorner4X.setText("")
        self.leXCalibPoint2Position.setText("")
        self.leYCalibPoint1Location.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.leYCalibPoint1Position.setText("")
        self.pbPointTool.setText("")
        self.label_21.setText(QCoreApplication.translate("MainWindow", u"X (mm)", None))
        self.label_15.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pbWarpPerspective.setText(QCoreApplication.translate("MainWindow", u"Warp Perspective", None))
        self.label_14.setText(QCoreApplication.translate("MainWindow", u"Square Size", None))
        self.label_31.setText(QCoreApplication.translate("MainWindow", u"Point 1 (reality)", None))
        self.pbGetCalibPointTool.setText("")
        self.leCorner4Y.setText("")
        self.label_34.setText(QCoreApplication.translate("MainWindow", u"Ruler", None))
        self.label_30.setText(QCoreApplication.translate("MainWindow", u"Calib Point Location", None))
        self.leCorner3X.setText("")
        self.pbLineTool.setText("")
        self.pbFindChessboard.setText(QCoreApplication.translate("MainWindow", u"Find chessboard", None))
        self.pbMapping.setText(QCoreApplication.translate("MainWindow", u"Mapping", None))
        self.lineEdit_4.setText(QCoreApplication.translate("MainWindow", u"20", None))
        self.cbCorner1.setItemText(0, QCoreApplication.translate("MainWindow", u"1", None))
        self.cbCorner1.setItemText(1, QCoreApplication.translate("MainWindow", u"2", None))
        self.cbCorner1.setItemText(2, QCoreApplication.translate("MainWindow", u"3", None))
        self.cbCorner1.setItemText(3, QCoreApplication.translate("MainWindow", u"4", None))

        self.cbCorner1.setCurrentText(QCoreApplication.translate("MainWindow", u"4", None))
        self.leXCalibPoint1Location.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.lineEdit_3.setText(QCoreApplication.translate("MainWindow", u"7", None))
        self.leXCalibPoint2Location.setText(QCoreApplication.translate("MainWindow", u"120", None))
        self.label_32.setText(QCoreApplication.translate("MainWindow", u"Line Tool", None))
        self.label_23.setText(QCoreApplication.translate("MainWindow", u"Calib Point Position", None))
        self.label_33.setText(QCoreApplication.translate("MainWindow", u"Point Tool", None))
        self.leCorner2X.setText("")
        self.leCorner1X.setText("")
        self.cbCorner4.setItemText(0, QCoreApplication.translate("MainWindow", u"1", None))
        self.cbCorner4.setItemText(1, QCoreApplication.translate("MainWindow", u"2", None))
        self.cbCorner4.setItemText(2, QCoreApplication.translate("MainWindow", u"3", None))
        self.cbCorner4.setItemText(3, QCoreApplication.translate("MainWindow", u"4", None))

        self.cbCorner4.setCurrentText(QCoreApplication.translate("MainWindow", u"2", None))
        self.label_20.setText(QCoreApplication.translate("MainWindow", u"Y", None))
        self.label_36.setText(QCoreApplication.translate("MainWindow", u"Point 2 (image)", None))
        self.leCorner2Y.setText("")
        self.lineEdit_2.setText(QCoreApplication.translate("MainWindow", u"7", None))
        self.leCorner3Y.setText("")
        self.label_27.setText(QCoreApplication.translate("MainWindow", u"Y (pixel)", None))
        self.leYCalibPoint2Location.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"Chessboard", None))
        self.checkBox.setText(QCoreApplication.translate("MainWindow", u"Display", None))
        self.label_29.setText(QCoreApplication.translate("MainWindow", u"Point 1 (image)", None))
        self.leXCalibPoint1Position.setText("")
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"Corner", None))
        self.label_22.setText(QCoreApplication.translate("MainWindow", u"Y (mm)", None))
        self.leCorner1Y.setText("")
        self.pbAutoCalibration.setText(QCoreApplication.translate("MainWindow", u"Auto Calibaration", None))
        self.cbWarpPerspectiveAuto.setText(QCoreApplication.translate("MainWindow", u"Auto", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("MainWindow", u"Object Detecting", None))
        self.lePythonScript.setText("")
        self.pbRunDetecting.setText(QCoreApplication.translate("MainWindow", u"Run", None))
        self.leScriptPath.setText(QCoreApplication.translate("MainWindow", u"C:\\Users\\Admin\\Desktop\\", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"Yolov Model", None))
        self.label_25.setText(QCoreApplication.translate("MainWindow", u"Params", None))
        self.leYolovModel.setText(QCoreApplication.translate("MainWindow", u"C:\\Users\\Admin\\Desktop\\", None))
        self.tbOpenScript.setText("")
        self.label_16.setText(QCoreApplication.translate("MainWindow", u"Python Script", None))
        self.label_24.setText(QCoreApplication.translate("MainWindow", u"Console", None))
        self.tbOpenModelFolder.setText("")
        self.pbExecuteScript.setText(QCoreApplication.translate("MainWindow", u"Execute", None))
        self.cbIpParaOnOff.setText("")
        self.leScriptParas.setText("")
        self.leIPPara.setText(QCoreApplication.translate("MainWindow", u"-ip localhost -port 7337", None))
    # retranslateUi

