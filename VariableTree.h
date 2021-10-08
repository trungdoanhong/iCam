#ifndef VARIABLETREE_H
#define VARIABLETREE_H

#include <QObject>
#include <QVector>
#include <QTreeWidget>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include "Robot.h"

class VariableTree : public QObject
{
    Q_OBJECT
public:
    explicit VariableTree(QObject *parent = nullptr);
    void SetParentVT(VariableTree* parent);
    void AddChild(VariableTree* child);
    void UpdateChildVariable(QString name, QString value);

    VariableTree *GetChildVariable(QString name);

    QString GetValueOfChildVariable(QString name);
    QString GetFullName(QTreeWidgetItem* item);
    VariableTree *FindChildVariable(QString name);
    QString FindValueOfChildVariable(QString name);
    void Clear();
    void Delete(QString name);
    void SetName(QString name);
    void SetValue(QString value);
    void UpdateView();

    void SetDisplayWidget(QWidget* displayWidget);
    void SetDisplayWidget(QString childVarName, QWidget* displayWidget);

    VariableTree* GetVariableTree(VariableTree* varTree, QString name);

    QString Name;
    QString Value;
    QTreeWidget* TreeWidget = NULL;
    QTreeWidgetItem* TreeWidgetItem = NULL;
    QVector<QWidget*> DisplayWidgets;
    QVector<VariableTree*> ChildVariables;

public slots:
    void ChangeValue(QTreeWidgetItem* item, int col);
    void ChangeValue(QString value);
signals:
    void variableChanged(QString name, QString value);
private:
    VariableTree* parentVT;
    QObject* emittedWidget;

    void updateWidgets();
};

#endif // VARIABLETREE_H
