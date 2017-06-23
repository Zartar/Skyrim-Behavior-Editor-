#ifndef EXPRESSIONDATAARRAYUI_H
#define EXPRESSIONDATAARRAYUI_H

#include <QGroupBox>

#include "src/hkxclasses/behavior/hkbexpressiondataarray.h"

class QGridLayout;
class QLineEdit;
class BehaviorFile;
class ComboBox;
class TableWidget;

class ExpressionDataArrayUI: public QGroupBox
{
    Q_OBJECT
    friend class EvaluateExpressionModifierUI;
public:
    ExpressionDataArrayUI();
    void loadData(BehaviorFile *parentFile, hkbExpressionDataArray::hkExpression *exp);
    //QSize sizeHint() const Q_DECL_OVERRIDE;
    //QSize minimumSizeHint() const Q_DECL_OVERRIDE;
signals:
    void viewEvents(int index);
    void viewVariables(int index);
    void returnToParent();
private slots:
    void setExpression();
    void setAssignmentVariableIndex(int index, const QString &name);
    void setAssignmentEventIndex(int index, const QString &name);
    void setEventMode(int index);
    void viewSelectedChild(int row, int column);
private:
    void connectSignals();
    void disconnectSignals();
    void eventRenamed(const QString & name, int index);
    void variableRenamed(const QString & name, int index);
private:
    static QStringList EventModeUI;
    static QStringList headerLabels;
    BehaviorFile *file;
    hkbExpressionDataArray::hkExpression *bsData;
    QGridLayout *topLyt;
    QPushButton *returnPB;
    TableWidget *table;
    QLineEdit *expression;
    ComboBox *eventMode;
};

#endif // EXPRESSIONDATAARRAYUI_H
