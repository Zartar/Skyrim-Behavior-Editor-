#ifndef HKXOBJECT_H
#define HKXOBJECT_H

#include <QSharedData>

#include "src/utility.h"

class HkxFile;
class HkxXmlReader;
class HkxSharedPtr;
class HkxXMLWriter;
class TreeGraphicsItem;
class hkbGenerator;

class HkxObject: public QSharedData
{
    friend class BehaviorFile;
    friend class ProjectFile;
    friend class CharacterFile;
    friend class SkeletonFile;
    friend class BehaviorUI;
    friend class ProjectUI;
    friend class CharacterUI;
    friend class SkeletonUI;
    friend class BSIStateManagerModifier;
public:
    enum HkxType {
        TYPE_OTHER=0,
        TYPE_GENERATOR=1,
        TYPE_MODIFIER=2
    };
public:
    virtual ~HkxObject();
    void writeToLog(const QString & message, bool isError = false);
    HkxSignature getSignature() const;
    HkxType getType() const;
    virtual bool evaluateDataValidity();
    bool isDataValid() const;
    virtual bool link() = 0;
    virtual void unlink();
    virtual bool write(HkxXMLWriter *);
    virtual bool readData(const HkxXmlReader &, long);
    virtual bool merge(HkxObject *);
    virtual void mergeEventIndex(int, int);
    virtual bool isEventReferenced(int ) const;
    virtual bool isVariableReferenced(int ) const;
    virtual void updateEventIndices(int);
    QString getReferenceString() const;
    QString getBoolAsString(bool b) const;
    HkxFile * getParentFile() const;
protected:
    HkxObject(HkxFile *parent, long ref = -1);
    void setDataValidity(bool isValid);
    void setType(HkxSignature sig, HkxType type);
    bool readMultipleVector4(const QByteArray &lineIn,  QVector <hkQuadVariable> & vectors);
    bool readReferences(const QByteArray &line, QList <HkxSharedPtr> & children);
    bool readIntegers(const QByteArray &line, QVector<int> & ints);
    bool toBool(const QByteArray &line, bool *ok);
    bool readDoubles(const QByteArray &line, QVector<qreal> & doubles);
    hkVector3 readVector3(const QByteArray &lineIn, bool *ok);
    hkQuadVariable readVector4(const QByteArray &lineIn, bool *ok);
    void setIsWritten(bool written = true);
    bool getIsWritten() const;
    void setReference(int ref);
    long getReference() const;
    bool getIsMerged() const;
    void setIsMerged(bool value);
private:
    HkxObject(const HkxObject &obj);
    HkxObject& operator=(const HkxObject&);
private:
    HkxFile *parentFile;
    long reference;
    HkxSignature signature;
    HkxType typeCheck;
    bool dataValid;
    bool isWritten;
    bool isMerged;
};

class HkxSharedPtr: public QExplicitlySharedDataPointer <HkxObject>
{
public:
    HkxSharedPtr(HkxObject *obj = nullptr, long ref = -1);
    bool operator==(const HkxSharedPtr & other) const;
    void setShdPtrReference(long ref);
    long getShdPtrReference() const;
    bool readShdPtrReference(long index, const HkxXmlReader & reader);
private:
    long reference;
};

struct hkEventPayload{
    hkEventPayload(): id(-1){}
    int id;
    HkxSharedPtr payload;
};

class HkDynamicObject: public HkxObject
{
public:
    virtual ~HkDynamicObject();
    bool linkVar();
    void unlink();
    bool evaluateDataValidity();
    void addBinding(const QString & path, int varIndex, bool isProperty = false);
    void removeBinding(const QString & path);
    void removeBinding(int varIndex);
    bool isVariableReferenced(int variableindex) const;
    bool merge(HkxObject *recessiveObject);
protected:
    HkDynamicObject(HkxFile *parent, long ref = -1);
public:
    HkxSharedPtr variableBindingSet;
private:
    HkDynamicObject& operator=(const HkDynamicObject&);
    HkDynamicObject(const HkDynamicObject &);

};

#endif // HKXOBJECT_H
