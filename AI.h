#ifndef AI_H
#define AI_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/calib3d/calib3d.hpp>

class ObjectInfo
{
public:
    float CenterX = 0.5;
    float CenterY = 0.5;
    float Height = 0.2f;
    float Width = 0.2f;
    int Class = 0;

    static ObjectInfo GetInfoFromLine(QString line)
    {
        QStringList paras = line.split(' ');

        ObjectInfo info;

        if (paras.length() >= 5)
        {
            info.Class = paras[0].toInt();
            info.CenterX = paras[1].toFloat();
            info.CenterY = paras[2].toFloat();
            info.Height = paras[3].toFloat();
            info.Width = paras[4].toFloat();
        }

        return info;
    }

    cv::Point2f GetPoint1()
    {
        float x = CenterX - Width / 2;
        float y = CenterY - Height / 2;

        return cv::Point(x, y);
    }

    cv::Point2f GetPoint2()
    {
        float x = CenterX + Width / 2;
        float y = CenterY + Height / 2;

        return cv::Point(x, y);
    }

    cv::Point GetPoint1(int height, int width)
    {
        float x = CenterX - Width / 2;
        float y = CenterY - Height / 2;

        return cv::Point(x * width, y * height);
    }

    cv::Point GetPoint2(int height, int width)
    {
        float x = CenterX + Width / 2;
        float y = CenterY + Height / 2;

        return cv::Point(x * width, y * height);
    }
};

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI(QObject *parent = nullptr);

    void AddImages(QStringList files);
    void AddLabels(QStringList files);
    QString GetImagePath(QString name);
    QString GetPath(QString name, QStringList paths);
    QString GetImageName(QString path);
    cv::Mat DrawBox(cv::Mat mat, QString name);

    QStringList DatasetImages;
    QStringList DatasetLabels;

signals:

};

#endif // AI_H
