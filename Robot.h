#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QDoubleSpinBox>
#include <ComDevice.h>

class Robot : public QObject
{
    Q_OBJECT
public:
    Robot();
    void SetStep(float step);
    void SetInputWidget(QDoubleSpinBox* dsbX, QDoubleSpinBox* dsbY, QDoubleSpinBox* dsbZ, QDoubleSpinBox* dsbW, QDoubleSpinBox* dsbU, QDoubleSpinBox* dsbV);

    QDoubleSpinBox* DsbPara[6];
    float Step = 1;

    COMDevice* RobotCOMPort;

    enum AXIS
    {
        X = 0,
        Y,
        Z,
        W,
        U,
        V
    };

public slots:
    void ReceiveRobotCOMPortResponse(QString response);
};

#endif // ROBOT_H
