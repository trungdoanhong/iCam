#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QtMath>
#include <QtPrintSupport/qtprintsupportglobal.h>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
    QGraphicsLineItem *item;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event){
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    }

};

#define POINT_SIZE 10

class CameraPointItem : public QObject
{
    Q_OBJECT
public:
    CameraPointItem(QPointF point = QPointF(0, 0))
    {
        this->point = point;

        size = POINT_SIZE;

        whiteLineItem = new QGraphicsEllipseItem;
        blackLineItem = new QGraphicsEllipseItem;

        whiteLineItem->setPen(QPen(Qt::white, 2));
        blackLineItem->setPen(QPen(Qt::black, 1));

        whiteLineItem->setZValue(1);
        blackLineItem->setZValue(1.1f);

        updateVisual();
    }

    ~CameraPointItem()
    {
        delete whiteLineItem;
        delete blackLineItem;
    }

    void SetValue(QPointF p)
    {
        point = p;
        updateVisual();
    }

    QPointF GetValue()
    {
        return point;
    }

    void SetThin(float value)
    {
        size = value * 6;
        whiteLineItem->setPen(QPen(Qt::white, value * 2));
        blackLineItem->setPen(QPen(Qt::black, value));

        updateVisual();
    }

    void SetScene(QGraphicsScene* scene)
    {
        scene->addItem(blackLineItem);
        scene->addItem(whiteLineItem);
    }

private:
    void updateVisual()
    {
        QRectF rect(point.x() - size/2, point.y() - size/2, size, size);

        whiteLineItem->setRect(rect);
        blackLineItem->setRect(rect);
    }

    float size;
    QPointF point;
    QGraphicsEllipseItem* whiteLineItem;
    QGraphicsEllipseItem* blackLineItem;
};

class CameraLineItem : public QObject
{
    Q_OBJECT
public:
    CameraLineItem(QLineF line = QLineF(0, 0, 0, 0))
    {
        this->line = line;

        whiteLineItem = new QGraphicsLineItem;
        blackLineItem = new QGraphicsLineItem;

        whiteLineItem->setPen(QPen(Qt::white, 2));
        blackLineItem->setPen(QPen(Qt::black, 1));

        whiteLineItem->setZValue(1);
        blackLineItem->setZValue(1.1f);

        updateVisual();
    }

    ~CameraLineItem()
    {
        delete whiteLineItem;
        delete blackLineItem;
    }

    void SetValue(QLineF l)
    {
        line = l;
        updateVisual();
    }

    QLineF GetValue()
    {
        return line;
    }

    void SetPoint1(QPointF p)
    {
        line.setP1(p);
        updateVisual();
    }

    void SetPoint2(QPointF p)
    {
        line.setP2(p);
        updateVisual();
    }

    QPointF Point1()
    {
        return line.p1();
    }

    QPointF Point2()
    {
        return line.p2();
    }

    void SetThin(float value)
    {
        whiteLineItem->setPen(QPen(Qt::white, value * 2));
        blackLineItem->setPen(QPen(Qt::black, value));

        updateVisual();
    }

    void SetScene(QGraphicsScene* scene)
    {
        scene->addItem(blackLineItem);
        scene->addItem(whiteLineItem);
    }

private:
    void updateVisual()
    {
        whiteLineItem->setLine(line);
        blackLineItem->setLine(line);
    }

    QLineF line;
    QGraphicsLineItem* whiteLineItem;
    QGraphicsLineItem* blackLineItem;
};

class CameraRectItem : public QObject
{
    Q_OBJECT
public:
    CameraRectItem(QRectF rect = QRectF(0, 0, 0, 0))
    {
        this->rect = rect;

        whiteRectItem = new QGraphicsRectItem;
        blackRectItem = new QGraphicsRectItem;

        whiteRectItem->setPen(QPen(Qt::white, 2));
        blackRectItem->setPen(QPen(Qt::black, 1));

        whiteRectItem->setZValue(1);
        blackRectItem->setZValue(1.1f);

        rectToLine();

        updateVisual();
    }

    ~CameraRectItem()
    {
        delete whiteRectItem;
        delete blackRectItem;
    }

    void SetValue(QRectF r)
    {
        rect = r;

        rectToLine();
        updateVisual();
    }

    void SetPoint1(QPointF p)
    {
        diagonalLine.setP1(p);
        lineToRect();
        updateVisual();
    }

    void SetPoint2(QPointF p)
    {
        diagonalLine.setP2(p);
        lineToRect();
        updateVisual();
    }

    QRectF GetValue()
    {
        return rect;
    }

    void SetTopLeft(QPointF p)
    {
        rect.setTopLeft(p);
        rectToLine();
        updateVisual();
    }

    void SetBottomRight(QPointF p)
    {
        rect.setBottomRight(p);
        rectToLine();
        updateVisual();
    }

    QPointF TopLeft()
    {
        return rect.topLeft();
    }

    QPointF BottomRight()
    {
        return rect.bottomRight();
    }

    void SetThin(float value)
    {
        whiteRectItem->setPen(QPen(Qt::white, value * 2));
        blackRectItem->setPen(QPen(Qt::black, value));

        updateVisual();
    }

    void SetScene(QGraphicsScene* scene)
    {
        scene->addItem(blackRectItem);
        scene->addItem(whiteRectItem);
    }

private:
    void updateVisual()
    {
        whiteRectItem->setRect(rect);
        blackRectItem->setRect(rect);
    }

    void lineToRect()
    {
        QPointF p1 = diagonalLine.p1();
        QPointF p2 = diagonalLine.p2();

        rect.setTop(p1.y() < p2.y()? p1.y() : p2.y());
        rect.setBottom(p1.y() > p2.y()? p1.y() : p2.y());
        rect.setLeft(p1.x() < p2.x()? p1.x() : p2.x());
        rect.setRight(p1.x() > p2.x()? p1.x() : p2.x());
    }

    void rectToLine()
    {

        diagonalLine.setP1(rect.topLeft());
        diagonalLine.setP2(rect.bottomRight());
    }

    QRectF rect;
    QLineF diagonalLine;
    QGraphicsRectItem* whiteRectItem;
    QGraphicsRectItem* blackRectItem;
};

class CameraQuadangleItem : public QObject
{
    Q_OBJECT
public:
    CameraQuadangleItem()
    {
        size = POINT_SIZE;

        for (int i = 0; i < 4; i++)
        {
            whiteRectItems[i] = new QGraphicsRectItem;
            blackRectItems[i] = new QGraphicsRectItem;

            whiteRectItems[i]->setPen(QPen(Qt::white, 2));
            blackRectItems[i]->setPen(QPen(Qt::black, 1));

            whiteRectItems[i]->setZValue(1);
            blackRectItems[i]->setZValue(1.1f);

            whiteLineItems[i] = new QGraphicsLineItem;
            blackLineItems[i] = new QGraphicsLineItem;

            whiteLineItems[i]->setPen(QPen(Qt::white, 2));
            blackLineItems[i]->setPen(QPen(Qt::black, 1));

            whiteLineItems[i]->setZValue(1);
            blackLineItems[i]->setZValue(1.1f);
        }

        updateVisual();
    }

    ~CameraQuadangleItem()
    {
        for (int i = 0; i < 4; i++)
        {
            delete whiteRectItems[i];
            delete blackRectItems[i];
            delete whiteLineItems[i];
            delete blackLineItems[i];
        }
    }

    void SetValue(QPointF ps[4])
    {
        for (int i = 0; i < 4; i++)
        {
            points[i] = ps[i];
        }

        pointsToLines();
        pointsToRects();

        updateVisual();
    }

    void SetPoint(QPointF p, int i)
    {
        points[i] = p;

        pointsToLines();
        pointsToRects();

        updateVisual();
    }

    QPointF* GetValue()
    {
        return points;
    }

    bool IsOverPoint(QPointF mousePos, int i)
    {
        if (abs(points[i].x() - mousePos.x()) < size && abs(points[i].y() - mousePos.y()) < size)
        {
            return true;
        }

        return false;
    }

    void SetThin(float value)
    {
        size = POINT_SIZE * value;

        for (int i = 0; i < 4; i++)
        {
            whiteRectItems[i]->setPen(QPen(Qt::white, value * 2));
            blackRectItems[i]->setPen(QPen(Qt::black, value));

            whiteLineItems[i]->setPen(QPen(Qt::white, value * 2));
            blackLineItems[i]->setPen(QPen(Qt::black, value));
        }

        pointsToRects();

        updateVisual();
    }

    void SetScene(QGraphicsScene* scene)
    {
        for (int i = 0; i < 4; i++)
        {
            scene->addItem(blackLineItems[i]);
            scene->addItem(whiteLineItems[i]);

            scene->addItem(blackRectItems[i]);
            scene->addItem(whiteRectItems[i]);
        }
    }

private:
    void updateVisual()
    {
        for (int i = 0; i < 4; i++)
        {
            rects[i].setHeight(size);
            rects[i].setWidth(size);

            whiteLineItems[i]->setLine(lines[i]);
            blackLineItems[i]->setLine(lines[i]);

            whiteRectItems[i]->setRect(rects[i]);
            blackRectItems[i]->setRect(rects[i]);
        }


    }

    void pointsToLines()
    {
        for (int i = 0; i < 4; i++)
        {
            lines[i].setP1(points[i]);
            lines[i].setP2(points[(i + 1) % 4]);
        }
    }

    void pointsToRects()
    {
        for (int i = 0; i < 4; i++)
        {
            rects[i].setTopLeft(points[i] - QPointF(size/2, size/2));
            rects[i].setBottomRight(points[i] + QPointF(size/2, size/2));
        }
    }

    float size;

    QPointF points[4];
    QRectF rects[4];
    QLineF lines[4];
    QGraphicsLineItem* whiteLineItems[4];
    QGraphicsLineItem* blackLineItems[4];

    QGraphicsRectItem* whiteRectItems[4];
    QGraphicsRectItem* blackRectItems[4];
};

class CameraAreaItem : public QObject
{
    Q_OBJECT
public:
    CameraAreaItem(QRectF rect = QRectF(0, 0, 0, 0))
    {
        size = POINT_SIZE;

        this->rect = rect;

        for (int i = 0; i < 2; i++)
        {
            whiteRectItems[i] = new QGraphicsRectItem;
            blackRectItems[i] = new QGraphicsRectItem;

            whiteRectItems[i]->setPen(QPen(Qt::white, 2));
            blackRectItems[i]->setPen(QPen(Qt::black, 1));

            whiteRectItems[i]->setZValue(1);
            blackRectItems[i]->setZValue(1.1f);
        }

        rectToLine();

        updateVisual();
    }

    ~CameraAreaItem()
    {
        delete whiteRectItems[0];
        delete blackRectItems[0];

        delete whiteRectItems[1];
        delete blackRectItems[1];
    }

    void SetValue(QRectF r)
    {
        rect = r;

        rectToLine();
        updateVisual();
    }

    void SetPoint1(QPointF p)
    {
        diagonalLine.setP1(p);
        lineToRect();
        updateVisual();
    }

    void SetPoint2(QPointF p)
    {
        diagonalLine.setP2(p);
        lineToRect();
        updateVisual();
    }

    QRectF GetValue()
    {
        return rect;
    }

    int OverPoint(QPointF mousePos)
    {
        if (abs(rect.topLeft().x() - mousePos.x()) < 5 && abs(rect.topLeft().y() - mousePos.y()) < 5)
        {
            return 1;
        }

        if (abs(rect.bottomRight().x() - mousePos.x()) < 5 && abs(rect.bottomRight().y() - mousePos.y()) < 5)
        {
            return 2;
        }

        return -1;
    }

    void SetTopLeft(QPointF p)
    {
        rect.setTopLeft(p);
        rectToLine();
        updateVisual();
    }

    void SetBottomRight(QPointF p)
    {
        rect.setBottomRight(p);
        rectToLine();
        updateVisual();
    }

    QPointF TopLeft()
    {
        return rect.topLeft();
    }

    QPointF BottomRight()
    {
        return rect.bottomRight();
    }

    void SetThin(float value)
    {
        size = POINT_SIZE * value;
        whiteRectItems[0]->setPen(QPen(Qt::white, value * 2));
        blackRectItems[0]->setPen(QPen(Qt::black, value));

        whiteRectItems[1]->setPen(QPen(Qt::white, value * 2));
        blackRectItems[1]->setPen(QPen(Qt::black, value));

        updateVisual();
    }

    void SetScene(QGraphicsScene* scene)
    {
        scene->addItem(blackRectItems[0]);
        scene->addItem(whiteRectItems[0]);

        scene->addItem(blackRectItems[1]);
        scene->addItem(whiteRectItems[1]);
    }

private:
    void updateVisual()
    {
        QRectF rect1;
        QRectF rect2;

        rect1.setTopLeft(rect.topLeft() - QPointF(size/2, size/2));
        rect1.setBottomRight(rect.topLeft() + QPointF(size/2, size/2));

        rect2.setTopLeft(rect.bottomRight() - QPointF(size/2, size/2));
        rect2.setBottomRight(rect.bottomRight() + QPointF(size/2, size/2));

        whiteRectItems[0]->setRect(rect1);
        blackRectItems[0]->setRect(rect1);

        whiteRectItems[1]->setRect(rect2);
        blackRectItems[1]->setRect(rect2);
    }

    void lineToRect()
    {
        QPointF p1 = diagonalLine.p1();
        QPointF p2 = diagonalLine.p2();

        rect.setTop(p1.y() < p2.y()? p1.y() : p2.y());
        rect.setBottom(p1.y() > p2.y()? p1.y() : p2.y());
        rect.setLeft(p1.x() < p2.x()? p1.x() : p2.x());
        rect.setRight(p1.x() > p2.x()? p1.x() : p2.x());
    }

    void rectToLine()
    {

        diagonalLine.setP1(rect.topLeft());
        diagonalLine.setP2(rect.bottomRight());
    }

    float size;

    QRectF rect;
    QLineF diagonalLine;
    QGraphicsRectItem* whiteRectItems[2];
    QGraphicsRectItem* blackRectItems[2];
};

class ImageViewer : public QGraphicsView
{
    Q_OBJECT
public:
    ImageViewer(QWidget *parent = 0);
    void InitParameter();
    void ZoomIn(qreal value);
    void ZoomOut(qreal value);
    void Zoom(qreal value);
    void SetImage(QPixmap pixmap);

    qreal CurrentZoom = 1;
    QGraphicsLineItem *item;

    bool IsQuadrangleEnable = false;
    bool IsCalibVisible = true;

    QGraphicsPixmapItem* ImageItem = NULL;

    CustomScene* ViewerScene;

    enum CameraTool
    {
        NO_TOOL = 0,
        RECTANGLE_TOOL,
        LINE_TOOL,
        POINT_TOOL,
        QUADRANGLE_TOOL,
        AREA_TOOL,
        MAPPING_TOOL
    };

public slots:

    void SelectRectTool();
    void SelectLineTool();
    void SelectPointTool();
    void SelectQuadrangleTool();
    void SelectAreaTool();
    void SelectMappingTool();
    void SelectNoTool();

    void DrawingAllShape();

signals:

    void clickedImage(QPoint p);
    void clickedImage(int x, int y);

protected:
    void wheelEvent(QWheelEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void changeToolIconInArea(QIcon icon);
    QPoint getMousePositionOnImage(QMouseEvent *event);
    void processRightPressEvent();
    void processQuadanglePressEvent(QPoint mousePos);
    void processAreaPressEvent(QPoint mousePos);
    void processRectPressEvent(QPoint mousePos);
    void processPointPressEvent(QPoint mousePos);
    void processLinePressEvent(QPointF mousePos);
    void processMappingPressEvent(QPoint mousePos);

    void drawQuadrangle();
    void drawArea();
    void drawLine();
    void drawPoint();
    void drawMappingPoint();
    void drawStrokeLine(QLineF line);
    void drawStrokeRect(QRect rect);
    void drawStrokeText(QString text, QPoint pos);
    void drawSolidColor(QRect rect, float alpha);
    void drawAxisSymbol();

    QPixmap lastCursorIcon;

    CameraLineItem cLine;
    CameraRectItem cRect;
    CameraPointItem cPoint;
    CameraPointItem cPoint2;
    CameraPointItem cMappingPoint;
    CameraQuadangleItem cQuadangle;
    CameraAreaItem cArea;

    QLineF mLine;
    QRect mRect;
    QPoint mPoint;
    QPoint mPoint2;
    QPoint mQuadrangle[4];
    QRect mArea;
    QPoint mMappingPoint;

    bool mousePressed;
    bool drawStarted;
    int selectedTool;
    int selectedPoint = 0;
    int lastSelectedTool;

    int transPointOrder = -1;
    int processPointOrder = -1;
};

#endif // IMAGEVIEWER_H
