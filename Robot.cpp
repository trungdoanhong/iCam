#include "Robot.h"

Robot::Robot()
{
    RobotCOMPort = new COMDevice();
    connect(RobotCOMPort, SIGNAL(FinishedReadLine(QString)), this, SLOT(ReceiveRobotCOMPortResponse(QString)));
}

void Robot::SetStep(float step)
{
    Step = step;

    for(int i = 0; i < 6; i++)
    {
        DsbPara[i]->setSingleStep(step);
    }
}

void Robot::SetInputWidget(QDoubleSpinBox *dsbX, QDoubleSpinBox *dsbY, QDoubleSpinBox *dsbZ, QDoubleSpinBox *dsbW, QDoubleSpinBox *dsbU, QDoubleSpinBox *dsbV)
{
    DsbPara[X] = dsbX;
    DsbPara[Y] = dsbY;
    DsbPara[Z] = dsbZ;
    DsbPara[W] = dsbW;
    DsbPara[U] = dsbU;
    DsbPara[V] = dsbV;
}

void Robot::ReceiveRobotCOMPortResponse(QString response)
{

}
