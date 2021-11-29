#include "AI.h"

AI::AI(QObject *parent) : QObject(parent)
{

}

void AI::AddImages(QStringList files)
{
    DatasetImages.append(files);
}

void AI::AddLabels(QStringList files)
{
    DatasetLabels.append(files);
}

QString AI::GetImagePath(QString name)
{
    foreach(QString path, DatasetImages)
    {
        QString n = path.mid(path.lastIndexOf('/') + 1);
        if (n.contains(name))
            return path;
    }

    return "";
}

QString AI::GetPath(QString name, QStringList paths)
{
    foreach(QString path, paths)
    {
        QString fullName = path.mid(path.lastIndexOf('/') + 1);
        if (fullName.contains(name))
            return path;
    }

    return "";
}

QString AI::GetImageName(QString path)
{
    int last = path.lastIndexOf('.');
    int start = path.lastIndexOf('/') + 1;
    QString name = path.mid(start, last - start);
    return name;
}

cv::Mat AI::DrawBox(cv::Mat mat, QString name)
{
    QString imagePath = GetPath(name, DatasetImages);
    QString labelPath = GetPath(name, DatasetLabels);

    QFile file(labelPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return mat;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        ObjectInfo objectInfo = ObjectInfo::GetInfoFromLine(line, BoundShape);

        if (objectInfo.Points.size() == 0 && objectInfo.Direction.length() == 0)
        {
            cv::Point p1 = objectInfo.GetPoint1(mat.rows, mat.cols);
            cv::Point p2 = objectInfo.GetPoint2(mat.rows, mat.cols);

            cv::rectangle(mat, p1, p2, cv::Scalar(0, 0, 255), 2);

            int angle = objectInfo.Class * 22.5 - 90;

            cv::putText(mat, QString::number(angle).toStdString(),p1 + cv::Point(15, 15), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 3);
        }

        if (BoundShape != "Box")
        {
            if (objectInfo.Points.size() != 0)
            {
                for (int i = 0; i < objectInfo.Points.size(); i++)
                {
                    cv::Point2f p1, p2;
                    p1.x = objectInfo.Points[i].x() * mat.cols;
                    p1.y = objectInfo.Points[i].y() * mat.rows;

                    if (i + 1 < objectInfo.Points.size())
                    {
                        p2.x = objectInfo.Points[i + 1].x() * mat.cols;
                        p2.y = objectInfo.Points[i + 1].y() * mat.rows;
                    }
                    else
                    {
                        p2.x = objectInfo.Points[0].x() * mat.cols;
                        p2.y = objectInfo.Points[0].y() * mat.rows;
                    }

                    cv::line(mat, p1, p2, cv::Scalar(0, 0, 255), 2);
                }
            }
            if (objectInfo.Direction.length() != 0)
            {
                cv::Point2f p1, p2;
                p1.x = objectInfo.Direction.p1().x() * mat.cols;
                p1.y = objectInfo.Direction.p1().y() * mat.rows;

                p2.x = objectInfo.Direction.p2().x() * mat.cols;
                p2.y = objectInfo.Direction.p2().y() * mat.rows;

                cv::line(mat, p1, p2, cv::Scalar(0, 255, 0), 2);

                cv::circle(mat, p2, 10, cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    return mat;
}
