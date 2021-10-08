#include "ConveyorWidget.h"

ConveyorWidget::ConveyorWidget(QWidget *parent) :
    QLabel(parent)
{
    drawingArea = QPixmap(QSize(parentWidget()->width(), parentWidget()->height()));

    setPixmap(drawingArea);

    DrawingRectangle(10, 20, 20, 20, 30, true);

}

void ConveyorWidget::SetObjectVariableTree(VariableTree *objectVarTree)
{
    ObjectVariableTree = objectVarTree;
}

void ConveyorWidget::DrawingRectangle(QRect rec)
{

    QPainter p(&drawingArea);

    p.begin(this);
    p.drawRect(rec);
    p.end();

    setPixmap(drawingArea);

    update();

    rectangles.push_back(rec);
}

void ConveyorWidget::DrawingRectangle(int x, int y, int w, int l, float angle, bool update)
{

    QPainter p(&drawingArea);

    p.begin(this);
    p.resetTransform();
    p.translate(y, x);
    p.rotate(angle);
    p.drawRect(- w/2, - l/2, w, l);
    p.end();
}

void ConveyorWidget::DrawingTiltRectangle(QVector<QPoint> points)
{
    QPainter p(&drawingArea);

    p.begin(this);
    p.drawLines(points);
    p.end();
}

ConveyorWidget::~ConveyorWidget()
{

}

void ConveyorWidget::mousePressEvent(QMouseEvent *event)
{

}

void ConveyorWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void ConveyorWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void ConveyorWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    //--- Draw objects from variable tree
    drawObjectFromVariableTree();
    //--- Update pixmap to widget

    setPixmap(drawingArea);
    update();
}

void ConveyorWidget::resizeEvent(QResizeEvent *event)
{
}

void ConveyorWidget::drawObjectFromVariableTree()
{
    if (ObjectVariableTree == NULL)
        return;

    drawingArea.fill();

    int objectNumber = ObjectVariableTree->GetValueOfChildVariable("Size").toInt();

    for (int i = 0; i < objectNumber; i++)
    {
        QString objectName = QString::number(i + 1);
        float x = ObjectVariableTree->FindValueOfChildVariable(QString("%1.X").arg(objectName)).toFloat();
        float y = ObjectVariableTree->FindValueOfChildVariable(QString("%1.Y").arg(objectName)).toFloat();
        float a = ObjectVariableTree->FindValueOfChildVariable(QString("%1.A").arg(objectName)).toFloat();
        float w = ObjectVariableTree->FindValueOfChildVariable(QString("%1.W").arg(objectName)).toFloat();
        float l = ObjectVariableTree->FindValueOfChildVariable(QString("%1.L").arg(objectName)).toFloat();

        DrawingRectangle(x, y, w, l, a);
    }

    setPixmap(drawingArea);
    update();
}
