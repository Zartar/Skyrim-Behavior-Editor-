#ifndef HKBSTATEMACHINESTATEINFO_H
#define HKBSTATEMACHINESTATEINFO_H

#include "hkbgenerator.h"

class hkbStateMachine;

class hkbStateMachineStateInfo: public hkbGenerator
{
    friend class BehaviorGraphView;
    friend class hkbStateMachine;
    friend class hkbStateMachineTransitionInfoArray;
    friend class StateMachineUI;
    friend class StateUI;
public:
    hkbStateMachineStateInfo(HkxFile *parent, hkbStateMachine *parentSM, long ref = 0);
    virtual ~hkbStateMachineStateInfo();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaulateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
private:
    hkbStateMachine * getParentStateMachine() const;
    hkbStateMachineStateInfo& operator=(const hkbStateMachineStateInfo&);
    hkbStateMachineStateInfo(const hkbStateMachineStateInfo &);
private:
    HkxObjectExpSharedPtr parentSM;
    static uint refCount;
    static QString classname;
    HkxObjectExpSharedPtr enterNotifyEvents;
    HkxObjectExpSharedPtr exitNotifyEvents;
    HkxObjectExpSharedPtr transitions;
    HkxObjectExpSharedPtr generator;
    QString name;
    ushort stateId;
    qreal probability;
    bool enable;
};

#endif // HKBSTATEMACHINESTATEINFO_H
