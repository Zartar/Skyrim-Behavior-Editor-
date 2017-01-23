#ifndef STATEUI_H
#define STATEUI_H

#include <QGroupBox>

class HkxObject;
class BehaviorGraphView;
class PointerWidget;
class StringWidget;
class IntWidget;
class TransitionsUI;
class hkbStateMachineStateInfo;
class QVBoxLayout;
class TableWidget;
class QTableWidgetItem;
class SpinBox;
class QLineEdit;
class ComboBox;
class QPushButton;
class QHBoxLayout;
class QSignalMapper;
class DoubleSpinBox;
class QCheckBox;
class QStackedLayout;
class HkTransition;
class hkbStateMachineEventPropertyArray;
class hkbStateMachine;
class GenericTableWidget;

class StateUI: public QGroupBox
{
    Q_OBJECT
    friend class HkDataUI;
    friend class StateMachineUI;
public:
    StateUI();
    virtual ~StateUI(){}
    void loadData(HkxObject *data);
    //void setGeneratorTable(GenericTableWidget *genTable);
signals:
    void stateNameChanged(const QString & newName, int index);
    void toParentStateMachine();
    void viewTransition(hkbStateMachine *parent, HkTransition *transition);
    void viewGeneratorTable(int index);
private slots:
    void setName();
    void setGenerator(int index);
    void setStateId();
    void setProbability();
    void setEnable();
    void addEnterEvent();
    void setEnterEventAt(int index);
    void setEnterEventPayloadAt(int index);
    void removeEnterEvent();
    void addExitEvent();
    void setExitEventAt(int index);
    void setExitEventPayloadAt(int index);
    void removeExitEvent();
    void addTransition();
    void removeTransition();
    void transitionSelected(int row, int column);
    void viewGenerators();
private:
    void appendEnterEventTableRow(int index, hkbStateMachineEventPropertyArray *enterEvents, const QStringList &eventList);
    void appendExitEventTableRow(int index, hkbStateMachineEventPropertyArray *exitEvents, const QStringList &eventList);
    void addEventToLists(const QString & name);
    void removeEventFromLists(int index);
    void renameEventInLists(const QString & newName, int index);
private:
    static QStringList headerLabels1;
    static QStringList headerLabels2;
    static QStringList headerLabels3;
    GenericTableWidget *generatorTable;
    BehaviorGraphView *behaviorView;
    hkbStateMachineStateInfo *bsData;
    QVBoxLayout *lyt;
    TableWidget *table;
    QPushButton *returnPB;
    QLineEdit *name;
    QPushButton *generator;
    SpinBox *stateId;
    DoubleSpinBox *probability;
    QCheckBox *enable;
    TableWidget *enterNotifyEvents;
    TableWidget *exitNotifyEvents;
    TableWidget *transitions;
    QPushButton *addEnterEventPB;
    QPushButton *removeEnterEventPB;
    ComboBox *typeEnterEventCB;
    QSignalMapper *enterEventSignalMapper;
    QSignalMapper *enterEventPayloadSignalMapper;
    QHBoxLayout *enterEventButtonLyt;
    QPushButton *addExitEventPB;
    QPushButton *removeExitEventPB;
    ComboBox *typeExitEventCB;
    QSignalMapper *exitEventSignalMapper;
    QSignalMapper *exitEventPayloadSignalMapper;
    QHBoxLayout *exitEventButtonLyt;
    QPushButton *addTransitionPB;
    QPushButton *removeTransitionPB;
    ComboBox *typeTransitionCB;
    QHBoxLayout *transitionButtonLyt;
};

#endif // STATEUI_H
