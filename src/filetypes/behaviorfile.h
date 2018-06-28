#ifndef BEHAVIORFILE_H
#define BEHAVIORFILE_H

#include <mutex>
#include <condition_variable>

#include "src/filetypes/hkxfile.h"

class hkbBehaviorGraph;
class CharacterFile;
class hkbModifier;
class ProjectFile;
class SkyrimClipGeneratoData;
class hkbBehaviorReferenceGenerator;
class hkbBoneWeightArray;
class hkbStateMachine;
class DataIconManager;

class BehaviorFile: public HkxFile
{
    friend class hkbBehaviorGraphData;
    friend class BehaviorGraphView;
    friend class hkbBehaviorGraph;
    friend class MainWindow;
    friend class HkDataUI;
    friend class ProjectFile;
    friend class hkbVariableBindingSet;
public:
    BehaviorFile(MainWindow *window, ProjectFile *projectfile, CharacterFile *characterData, const QString & name);
    virtual ~BehaviorFile();
    bool doesBehaviorExist(const QString &behaviorname) const;
    void setFocusGeneratorIcon(int index);
    void setFocusModifierIcon(int index);
    HkxSharedPtr * findHkxObject(long ref);
    HkxSharedPtr * findGenerator(long ref);
    //HkxSharedPtr * findGeneratorChild(long ref);
    HkxSharedPtr * findModifier(long ref);
    HkxSharedPtr * findBehaviorGraph(long ref);
    QVector<int> removeGeneratorData();
    //QVector<int> removeGeneratorChildrenData();
    QVector<int> removeModifierData();
    QVector<int> removeOtherData();
    int getIndexOfGenerator(const HkxSharedPtr & obj) const;
    bool setGeneratorData(HkxSharedPtr & ptrToSet, int index);
    hkbGenerator * getGeneratorDataAt(int index);
    int getIndexOfModifier(const HkxSharedPtr & obj) const;
    bool setModifierData(HkxSharedPtr & ptrToSet, int index);
    hkbModifier * getModifierDataAt(int index);
    QStringList getVariableTypenames() const;
    QStringList getEventNames() const;
    int getNumberOfEvents() const;
    QStringList getVariableNames() const;
    int getNumberOfVariables() const;
    QStringList getGeneratorNames() const;
    QStringList getGeneratorTypeNames() const;
    QStringList getModifierNames() const;
    QStringList getModifierTypeNames() const;
    int getCharacterPropertyIndexFromBehavior(const QString & name) const;
    int getCharacterPropertyIndex(const QString &name) const;
    int findCharacterPropertyIndexFromCharacter(int indexOfBehaviorProperty) const;
    QStringList getCharacterPropertyNames() const;
    QStringList getCharacterPropertyTypenames() const;
    hkVariableType getCharacterPropertyTypeAt(int index) const;
    hkVariableType getVariableTypeAt(int index) const;
    bool addObjectToFile(HkxObject *obj, long ref = -1);
    QStringList getAllReferencedBehaviorFilePaths() const;
    QStringList getRagdollBoneNames() const;
    QStringList getRigBoneNames() const;
    int getNumberOfBones(bool ragdoll = false) const;
    int addCharacterProperty(int index);
    QString getVariableNameAt(int index) const;
    QString getEventNameAt(int index) const;
    QString getCharacterPropertyNameAt(int index, bool fromBehaviorFile) const;
    QStringList getAnimationNames() const;
    QString getAnimationNameAt(int index) const;
    QStringList getLocalFrameNames() const;
    QStringList getAllBehaviorFileNames() const;
    void setLocalTimeForClipGenAnimData(const QString &clipname, int triggerindex, qreal time);
    void setEventNameForClipGenAnimData(const QString &clipname, int triggerindex, int eventid);
    bool isClipGenNameTaken(const QString & name) const;
    bool isClipGenNameAvailable(const QString & name) const;
    bool addClipGenToAnimationData(const QString & name);
    bool removeClipGenFromAnimData(const QString & animationname, const QString &clipname, const QString &variablename = "");
    void setClipNameAnimData(const QString &oldclipname, const QString &newclipname);
    void setAnimationIndexAnimData(int index, const QString &clipGenName);
    void setPlaybackSpeedAnimData(const QString & clipGenName, qreal speed);
    void setCropStartAmountLocalTimeAnimData(const QString & clipGenName, qreal time);
    void setCropEndAmountLocalTimeAnimData(const QString & clipGenName, qreal time);
    void appendClipTriggerToAnimData(const QString & clipGenName);
    void removeClipTriggerToAnimDataAt(const QString & clipGenName, int index);
    QString isEventReferenced(int eventindex) const;
    void updateEventIndices(int index);
    QString isVariableReferenced(int variableindex) const;
    void updateVariableIndices(int index);
    void removeUnreferencedFiles(const hkbBehaviorReferenceGenerator *gentoignore);
    QStringList getReferencedBehaviors(const hkbBehaviorReferenceGenerator *gentoignore) const;
    void removeAllData();
    void getCharacterPropertyBoneWeightArray(const QString &name, hkbBoneWeightArray *ptrtosetdata) const;
    hkbStateMachine * findRootStateMachineFromBehavior(const QString behaviorname) const;
    qreal getAnimationDurationFromAnimData(const QString & animationname) const;
    void mergeEventIndices(int oldindex, int newindex);
    void mergeVariableIndices(int oldindex, int newindex);
    bool isNameUniqueInProject(HkxObject *object) const;
    bool existsInBehavior(HkDynamicObject *object, int startindex = 0) const;
    HkxObject * getBehaviorGraphData() const;
    QStringList getErrors() const;
protected:
    bool parse();
    bool link();
private:
    QStringList getRefedAnimations() const;
    QString detectErrorsMT(int &taskcount, std::mutex &mutex, std::condition_variable &conditionVar);
    QString detectErrors();
    QVector<DataIconManager *> merge(BehaviorFile *recessivefile, int &taskCount, std::mutex &mutex, std::condition_variable &conditionVar);
    QVector<DataIconManager *> merge(BehaviorFile *recessivefile);
    void mergeObjects(QVector<DataIconManager *> &recessiveobjects);
    void generateDefaultCharacterData();
    void generateNewBehavior();
    hkbBehaviorGraph * getBehaviorGraph() const;
    HkxObject * getRootStateMachine() const;
    //TreeGraphicsItem * getRootIcon() const;
    void write();
    void mergedWrite();
    void removeBindings(int varIndex);
    bool checkForDuplicateReferencesNumbers() const;
private:
    //std::mutex mutex;
    ProjectFile *project;
    CharacterFile *character;
    HkxSharedPtr behaviorGraph;
    HkxSharedPtr stringData;
    HkxSharedPtr variableValues;
    HkxSharedPtr graphData;
    QList <HkxSharedPtr> generators;
    QList <HkxSharedPtr> modifiers;
    QList <HkxSharedPtr> otherTypes;
    QStringList referencedBehaviors;
    long largestRef;
    QStringList errorList;
};

#endif // BEHAVIORFILE_H
