#ifndef DATAICONMANAGER_H
#define DATAICONMANAGER_H

#include <QString>
#include <QList>

#include "src/hkxclasses/hkxobject.h"

class TreeGraphicsItem;
class hkbModifier;
class BehaviorFile;

class DataIconManager: public HkDynamicObject
{
    friend class GraphicsViewData;
    friend class TreeGraphicsScene;
    friend class TreeGraphicsItem;
    friend class BehaviorGraphIcon;
    friend class BehaviorGraphView;
    friend class BehaviorFile;
    friend class BSBoneSwitchGenerator;
    friend class hkbStateMachine;
    friend class hkbModifierList;
public:
    virtual QString getName() const;
    virtual bool hasChildren() const;
    bool hasIcons() const;
    void updateIconNames();
    bool hasSameSignatureAndName(const DataIconManager * other) const;
    virtual int getIndexOfObj(DataIconManager *) const;
protected:
    virtual QList <DataIconManager *> getChildren() const;
    virtual bool insertObjectAt(int , DataIconManager *);
    virtual bool removeObjectAt(int );//If index is -1 remove all...
    DataIconManager(HkxFile *parent, long ref = -1);
    void injectWhileMerging(HkxObject *recessiveobj);
    bool merge(HkxObject *recessiveObject);
private:
    void setDataInvalid();
    bool wrapObjectAt(int index, DataIconManager *obj, DataIconManager *parentObj);
    TreeGraphicsItem *reconnectToNext();
    void appendIcon(TreeGraphicsItem *icon);
    void removeIcon(TreeGraphicsItem *icon);
private:
    QList <TreeGraphicsItem *> icons;
};

#endif // DATAICONMANAGER_H
