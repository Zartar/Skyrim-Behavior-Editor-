#ifndef HKXXMLREADER_H
#define HKXXMLREADER_H

#include <QByteArray>
#include <QList>
#include <QVector>

#include "src/utility.h"

class BehaviorFile;

class HkxXmlReader
{
public:
    enum HkxXmlParseLine {
        NoError = 0,
        //NullPointerArgs,
        EmptyLineEndFile = 1,
        OrphanedCharacter = 2,
        InvalidElementName = 3,
        InvalidElementValue = 4,
        //ElementValueSplitOnMutipleLines = 5,
        InvalidAttributeName = 6,
        InvalidAttributeValue = 7,
        DuplicateAttribute = 8,
        OrphanedAttribute = 9,
        OrphanedElementTag = 10,
        MalformedComment = 11,
        UnexpectedNewlineCharacter = 12,
        EmptyLine = 13,
        MalformedEndElementTag = 14,
        UnknownError = 50
    };
    HkxXmlReader(BehaviorFile *file = NULL);
    bool parse();
    virtual ~HkxXmlReader();
    void setBehaviorFile(BehaviorFile *file);
    bool atEnd() const;
    int getLastElementIndex() const;
    int getNumElements() const;
    int getNumAttributesAt(int index) const;
    QByteArray getElementNameAt(int index) const;
    QByteArray getElementValueAt(int index) const;
    QByteArray getNthAttributeNameAt(int index, int nth) const;
    QByteArray getNthAttributeValueAt(int index, int nth) const;
    HkxXmlParseLine readNextLine();
    void clear();
private:
    struct Attribute{
        Attribute(const QByteArray & elem): name(elem){}
        QByteArray name;
        QByteArray value;
    };
    struct Element{
        Element(const QByteArray & elem): name(elem), isContainedOnOneLine(false)/*, isClosed(false)*/{}
        QByteArray name;
        QByteArray value;
        QList <Attribute> attributeList;
        bool isContainedOnOneLine;
    };
    BehaviorFile *hkxXmlFile;
    QList <Element> elementList;
    bool isEOF;
    QVector <long> indexOfElemTags;
    ulong lineNumber;
};

#endif // HKXXMLREADER_H