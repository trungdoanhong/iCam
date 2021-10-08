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
        ObjectInfo objectInfo = ObjectInfo::GetInfoFromLine(line);
        cv::Point p1 = objectInfo.GetPoint1(mat.rows, mat.cols);
        cv::Point p2 = objectInfo.GetPoint2(mat.rows, mat.cols);

        cv::rectangle(mat, p1, p2, cv::Scalar(0, 0, 255), 2);
    }

    return mat;
}
