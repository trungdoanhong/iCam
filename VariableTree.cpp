#include "VariableTree.h"

VariableTree::VariableTree(QObject *parent) : QObject(parent)
{

}

void VariableTree::SetParentVT(VariableTree *parent)
{
    parentVT = parent;
}

void VariableTree::AddChild(VariableTree *child)
{
    ChildVariables.append(child);
}

void VariableTree::UpdateChildVariable(QString name, QString value)
{
    disconnect(TreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(ChangeValue(QTreeWidgetItem*, int)));

    // ex: Object.o1.X --> [Object, o1, X]
    QStringList names = name.split('.');

    VariableTree* vt = GetChildVariable(names[0]);

    // if [Object] is not exit -> creat one
    if (vt == NULL)
    {
        // this = parent.Object.o1.X
        vt = new VariableTree();
        vt->SetParentVT(this);

        // parent.Object --> child
        vt->Name = name;
        ChildVariables.append(vt);

        // Creat and update size of child into parent.Size
        if (GetChildVariable("Size") == NULL)
        {
            UpdateChildVariable("Size", QString::number(ChildVariables.length()));
        }
        else
        {
            UpdateChildVariable("Size", QString::number(ChildVariables.length() - 1));
        }
    }

    // if name parent.Object has not child --> set value for this child variable
    if (names.size() == 1)
    {
        vt->Value = value;
        vt->UpdateView();
    }
    // if name = parent.Object.o1 --> [parent.Object] add [o1]
    else
    {

        QString parentName = names[0]; //Object
        QString subName = name.mid(names[0].length() + 1); //o1

        vt->Name = parentName;

        vt->UpdateView();

        vt->UpdateChildVariable(subName, value);
    }

    connect(TreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(ChangeValue(QTreeWidgetItem*, int)));
}

/*!
Get variable tree child (1 layer)
*/
VariableTree *VariableTree::GetChildVariable(QString name)
{    
    // name = Object or Object.o1 --> Object
    QStringList subNameList = name.split('.');

    foreach(VariableTree* vt, ChildVariables)
    {
        if (subNameList[0] == vt->Name)
        {
            return vt;
        }
    }

    return NULL;
}

QString VariableTree::GetValueOfChildVariable(QString name)
{
    VariableTree* vt = GetChildVariable(name);

    if (vt == NULL)
        return 0;
    else
        return vt->Value;
}

QString VariableTree::GetFullName(QTreeWidgetItem *item)
{
    QString fullName = item->text(0);

    QTreeWidgetItem* wi = item->parent();;

    while(wi != NULL)
    {
        fullName = wi->text(0) + "." + fullName;
        wi = wi->parent();
    }

    return fullName;
}

/*!
 * \brief Find all child and sub child variables
 * \param name
 * \return pointer of Variable Tree
 */

VariableTree *VariableTree::FindChildVariable(QString name)
{
    QStringList subNameList = name.split('.');

    foreach(VariableTree* vt, ChildVariables)
    {
        if (subNameList[0] == vt->Name)
        {
            if (subNameList.length() > 1)
            {
                return vt->FindChildVariable(name.mid(subNameList[0].length() + 1));
            }
            return vt;
        }
    }

    return NULL;
}

QString VariableTree::FindValueOfChildVariable(QString name)
{
    VariableTree* vt = FindChildVariable(name);

    if (vt == NULL)
        return 0;
    else
        return vt->Value;
}

void VariableTree::SetName(QString name)
{
    Name = name;
}

void VariableTree::SetValue(QString value)
{
    if (value != Value)
    {
        Value = value;
    }
}

/*!
Update new display to TreeWidget
*/
void VariableTree::UpdateView()
{    
    // if parent is link to TreeWidget --> update child TreeWidgetItem to TreeWidget
    if (parentVT->TreeWidget != NULL)
    {
        if (TreeWidgetItem == NULL)
        {
            TreeWidgetItem = new QTreeWidgetItem(parentVT->TreeWidget);
            TreeWidgetItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }

        TreeWidgetItem->setText(0, Name);
        TreeWidgetItem->setText(1, Value);
    }
    // if parent is link to TreeWidgetItem --> update child TreeWidgetItem to TreeWidgetItem
    else if (parentVT->TreeWidgetItem != NULL)
    {
        if (TreeWidgetItem == NULL)
        {
            TreeWidgetItem = new QTreeWidgetItem(parentVT->TreeWidgetItem);
            TreeWidgetItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }

        TreeWidgetItem->setText(0, Name);
        TreeWidgetItem->setText(1, Value);
    }

    updateWidgets();
}

void VariableTree::SetDisplayWidget(QWidget *displayWidget)
{
    DisplayWidgets.append(displayWidget);

    QString className = displayWidget->metaObject()->className();

    if (className == "QTreeWidget")
    {
        TreeWidget = qobject_cast<QTreeWidget*>(displayWidget);

        connect(TreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(ChangeValue(QTreeWidgetItem*, int)));
    }

    if (className == "QDoubleSpinBox")
    {
        QDoubleSpinBox* dsb = qobject_cast<QDoubleSpinBox*>(displayWidget);
        connect(dsb, SIGNAL(textChanged(const QString &)), this, SLOT(ChangeValue(QString)));
    }
}

void VariableTree::SetDisplayWidget(QString childVarName, QWidget *displayWidget)
{
    VariableTree* vt = FindChildVariable(childVarName);

    if (vt == NULL)
        return;

    vt->SetDisplayWidget(displayWidget);
}

VariableTree* VariableTree::GetVariableTree(VariableTree* varTree, QString name)
{
    if (varTree->Name == name)
        return varTree;

    else
    {
        foreach(VariableTree* vt, varTree->ChildVariables)
        {
            return GetVariableTree(vt, name);
        }
    }

    return NULL;
}

void VariableTree::ChangeValue(QTreeWidgetItem* item, int col)
{
    QString fullName = GetFullName(item);

    QString value = item->text(col);

    VariableTree* vt = FindChildVariable(fullName);

    if (vt == NULL)
        return;

    vt->Value = value;
    vt->updateWidgets();

    emit variableChanged(fullName, value);
}

void VariableTree::ChangeValue(QString value)
{
    Value = value;

    emittedWidget = sender();

    UpdateView();
}

/*!
Update value to all widget linked to variable except emitted widget
*/
void VariableTree::updateWidgets()
{

    foreach(QWidget* wg, DisplayWidgets)
    {
        QString wgClassName = wg->metaObject()->className();

        if (emittedWidget != NULL)
        {
            QString senderClassName = emittedWidget->metaObject()->className();
            if (senderClassName == wgClassName)
                continue;
        }

        if (wgClassName == "QDoubleSpinBox")
        {
            QDoubleSpinBox* dsb = qobject_cast<QDoubleSpinBox*>(wg);
            dsb->setValue(Value.toFloat());
        }

        if (wgClassName == "QLineEdit")
        {
            QLineEdit* le = qobject_cast<QLineEdit*>(wg);
            le->setText(Value);
        }

        if (wgClassName == "QTextEdit")
        {
            QTextEdit* te = qobject_cast<QTextEdit*>(wg);
            te->setText(Value);
        }

        if (wgClassName == "QLabel")
        {
            QLabel* lb = qobject_cast<QLabel*>(wg);
            lb->setText(Value);
        }
    }

    emittedWidget = NULL;
}
