#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include "src/filetypes/hkxfile.h"
#include "src/animData/skyrimanimdata.h"
#include "src/animSetData/skyrimanimsetdata.h"

class CharacterFile;
class BehaviorFile;
class hkbBehaviorReferenceGenerator;

class ProjectFile: public HkxFile
{
    friend class BehaviorFile;
    friend class CacheWidget;
    friend class MainWindow;
    friend class ProjectUI;
    friend class hkbProjectData;
    friend class hkRootLevelContainer;
    friend class AnimationCacheUI;
public:
    ProjectFile(MainWindow *window, const QString & name, bool autogeneratedata = false, const QString & relativecharacterfilepath = "");
    virtual ~ProjectFile();
    bool addObjectToFile(HkxObject *obj, long ref = -1);
    void write();
    //QString getRootObjectReferenceString();
    QString getCharacterFilePathAt(int index) const;
    void setCharacterFile(CharacterFile *file);
    bool isClipGenNameTaken(const QString & name) const;
    bool readAnimationData(const QString &filename, const QStringList &behaviorfilenames = QStringList());
    bool readAnimationSetData(const QString & filename);
    int getAnimationIndex(const QString & name) const;
    bool isAnimationUsed(const QString & animationname);
    QStringList getAnimationNames() const;
    QString findAnimationNameFromEncryptedData(const QString & encryptedname) const;
    bool isProjectNameTaken() const;
    QString getProjectName() const;
    qreal getAnimationDurationFromAnimData(const QString & animationname) const;
    bool appendAnimation(SkyrimAnimationMotionData *motiondata);
    SkyrimAnimationMotionData getAnimationMotionData(int animationindex) const;
private:
protected:
    bool parse();
    bool link();
    //SkyrimAnimData *getAnimData() const;
private:
    void removeUnreferencedFiles(const hkbBehaviorReferenceGenerator *gentoignore);
    bool merge(ProjectFile *recessiveproject);
    bool mergeAnimationCaches(ProjectFile *recessiveproject);
    void addProjectToAnimData();
    bool removeClipGenFromAnimData(const QString & animationname, const QString &clipname, const QString &variablename = "");
    bool removeAnimationFromAnimData(const QString & name);
    bool appendClipGeneratorAnimData(const QString & name);
    void setLocalTimeForClipGenAnimData(const QString &clipname, int triggerindex, qreal time);
    void setEventNameForClipGenAnimData(const QString &clipname, int triggerindex, const QString &eventname);
    void setClipNameAnimData(const QString &oldclipname, const QString &newclipname);
    void setAnimationIndexForClipGen(int index, const QString &clipGenName);
    void setPlaybackSpeedAnimData(const QString & clipGenName, qreal speed);
    void setCropStartAmountLocalTimeAnimData(const QString & clipGenName, qreal time);
    void setCropEndAmountLocalTimeAnimData(const QString & clipGenName, qreal time);
    void appendClipTriggerToAnimData(const QString & clipGenName, const QString & eventname);
    void removeClipTriggerToAnimDataAt(const QString & clipGenName, int index);
    AnimCacheProjectData *getProjectCacheData() const;
    void setAnimationIndexDuration(int indexofanimationlist, int animationindex, qreal duration);
    void generateAnimClipDataForProject();
    void loadEncryptedAnimationNames();
    void addEncryptedAnimationName(const QString & unencryptedname);
    void removeEncryptedAnimationName(int index);
    void deleteBehaviorFile(const QString & filename);
private:
    HkxSharedPtr * findProjectData(long ref);
    HkxSharedPtr * findProjectStringData(long ref);
private:
    CharacterFile *character;
    QList <BehaviorFile *> behaviorFiles;
    HkxSharedPtr stringData;
    HkxSharedPtr projectData;
    long largestRef;
    SkyrimAnimData *skyrimAnimData;
    SkyrimAnimSetData *skyrimAnimSetData;
    int projectIndex;
    QString projectName;
    QString projectFolderName;
    QString projectAnimationsPath;
    QStringList encryptedAnimationNames;
};

#endif // PROJECTFILE_H
