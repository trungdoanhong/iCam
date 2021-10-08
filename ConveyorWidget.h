#ifndef CONVEYORWIDGET_H
#define CONVEYORWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "VariableTree.h"

class ConveyorWidget : public QLabel
{
    Q_OBJECT
public:
    ConveyorWidget(QWidget *parent = 0);
    void SetObjectVariableTree(VariableTree* objectVarTree);
    void DrawingRectangle(QRect rec);
    void DrawingRectangle(int x, int y, int w, int l, float angle, bool update = false);
    void DrawingTiltRectangle(QVector<QPoint> points);
    ~ConveyorWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QPixmap drawingArea;
    QVector<QRect> rectangles;
    VariableTree* ObjectVariableTree;

    void drawObjectFromVariableTree();
};

#endif // CONVEYORWIDGET_H
