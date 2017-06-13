#include "hkbclipgenerator.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/behaviorfile.h"
/*
 * CLASS: hkbClipGenerator
*/

uint hkbClipGenerator::refCount = 0;

QString hkbClipGenerator::classname = "hkbClipGenerator";

QStringList hkbClipGenerator::PlaybackMode = {"MODE_SINGLE_PLAY", "MODE_LOOPING", "MODE_USER_CONTROLLED", "MODE_PING_PONG", "MODE_COUNT"};
QStringList hkbClipGenerator::ClipFlags = {"0", "FLAG_CONTINUE_MOTION_AT_END", "FLAG_SYNC_HALF_CYCLE_IN_PING_PONG_MODE", "FLAG_MIRROR", "FLAG_FORCE_DENSE_POSE", "FLAG_DONT_CONVERT_ANNOTATIONS_TO_TRIGGERS", "FLAG_IGNORE_MOTION"};

hkbClipGenerator::hkbClipGenerator(HkxFile *parent, long ref, const QString &animationname)
    : hkbGenerator(parent, ref),
      userData(0),
      animationName(animationname),
      cropStartAmountLocalTime(0),
      cropEndAmountLocalTime(0),
      startTime(0),
      playbackSpeed(0),
      enforcedDuration(0),
      userControlledTimeFraction(0),
      animationBindingIndex(-1),
      mode(PlaybackMode.first()),
      flags(ClipFlags.first())
{
    setType(HKB_CLIP_GENERATOR, TYPE_GENERATOR);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
    name = "hkbClipGenerator"+QString::number(refCount);
}

QString hkbClipGenerator::getClassname(){
    return classname;
}

QString hkbClipGenerator::getName() const{
    return name;
}

bool hkbClipGenerator::readData(const HkxXmlReader &reader, long index){
    bool ok;
    QByteArray ref = reader.getNthAttributeValueAt(index - 1, 0);
    QByteArray text;
    while (index < reader.getNumElements() && reader.getNthAttributeNameAt(index, 1) != "class"){
        text = reader.getNthAttributeValueAt(index, 0);
        if (text == "variableBindingSet"){
            if (!variableBindingSet.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'variableBindingSet' reference!\nObject Reference: "+ref);
            }
        }else if (text == "userData"){
            userData = reader.getElementValueAt(index).toULong(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'userData' data field!\nObject Reference: "+ref);
            }
        }else if (text == "name"){
            name = reader.getElementValueAt(index);
            if (name == ""){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'name' data field!\nObject Reference: "+ref);
            }
        }else if (text == "animationName"){
            animationName = reader.getElementValueAt(index);
            if (animationName == ""){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'animationName' data field!\nObject Reference: "+ref);
            }
        }else if (text == "triggers"){
            if (!triggers.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'triggers' reference!\nObject Reference: "+ref);
            }
        }else if (text == "cropStartAmountLocalTime"){
            cropStartAmountLocalTime = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'cropStartAmountLocalTime' data field!\nObject Reference: "+ref);
            }
        }else if (text == "cropEndAmountLocalTime"){
            cropEndAmountLocalTime = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'cropEndAmountLocalTime' data field!\nObject Reference: "+ref);
            }
        }else if (text == "startTime"){
            startTime = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'startTime' data field!\nObject Reference: "+ref);
            }
        }else if (text == "playbackSpeed"){
            playbackSpeed = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'playbackSpeed' data field!\nObject Reference: "+ref);
            }
        }else if (text == "enforcedDuration"){
            enforcedDuration = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'enforcedDuration' data field!\nObject Reference: "+ref);
            }
        }else if (text == "userControlledTimeFraction"){
            userControlledTimeFraction = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'userControlledTimeFraction' data field!\nObject Reference: "+ref);
            }
        }else if (text == "animationBindingIndex"){
            animationBindingIndex = reader.getElementValueAt(index).toInt(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'animationBindingIndex' data field!\nObject Reference: "+ref);
            }
        }else if (text == "mode"){
            mode = reader.getElementValueAt(index);
            if (mode == ""){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'mode' data field!\nObject Reference: "+ref);
            }
        }else if (text == "flags"){
            flags = reader.getElementValueAt(index);
            if (flags == ""){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'flags' data field!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbClipGenerator::write(HkxXMLWriter *writer){
    if (!writer){
        return false;
    }
    if (!getIsWritten()){
        QString refString = "null";
        QStringList list1 = {writer->name, writer->clas, writer->signature};
        QStringList list2 = {getReferenceString(), getClassname(), "0x"+QString::number(getSignature(), 16)};
        writer->writeLine(writer->object, list1, list2, "");
        if (variableBindingSet.data()){
            refString = variableBindingSet.data()->getReferenceString();
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("variableBindingSet"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("userData"), QString::number(userData));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("name"), name);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("animationName"), animationName);
        if (variableBindingSet.data()){
            refString = variableBindingSet.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("triggers"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("cropStartAmountLocalTime"), QString::number(cropStartAmountLocalTime, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("cropEndAmountLocalTime"), QString::number(cropEndAmountLocalTime, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("startTime"), QString::number(startTime, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("playbackSpeed"), QString::number(playbackSpeed, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("enforcedDuration"), QString::number(enforcedDuration, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("userControlledTimeFraction"), QString::number(userControlledTimeFraction, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("animationBindingIndex"), QString::number(animationBindingIndex));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("mode"), mode);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("flags"), flags);
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (variableBindingSet.data() && !variableBindingSet.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'variableBindingSet'!!!", true);
        }
        if (triggers.data() && !triggers.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'triggers'!!!", true);
        }
    }
    return true;
}

bool hkbClipGenerator::link(){
    if (!getParentFile()){
        return false;
    }
    if (!static_cast<HkDynamicObject *>(this)->linkVar()){
        writeToLog(getClassname()+": link()!\nFailed to properly link 'variableBindingSet' data field!\nObject Name: "+name);
    }
    HkxSharedPtr *ptr = static_cast<BehaviorFile *>(getParentFile())->findHkxObject(triggers.getReference());
    if (ptr){
        if ((*ptr)->getSignature() != HKB_CLIP_TRIGGER_ARRAY){
            writeToLog(getClassname()+": link()!\n'triggers' data field is linked to invalid child!\nObject Name: "+name);
            setDataValidity(false);
        }
        triggers = *ptr;
    }
    return true;
}

void hkbClipGenerator::unlink(){
    HkDynamicObject::unlink();
    triggers = HkxSharedPtr();
}

bool hkbClipGenerator::evaulateDataValidity(){
    bool valid = true;
    QStringList list = flags.split('|');
    for (int i = 0; i < list.size(); i++){
        if (!ClipFlags.contains(list.at(i))){
            valid = false;
        }
    }
    if (!HkDynamicObject::evaulateDataValidity()){
        return false;
    }else if (!PlaybackMode.contains(mode)){
    }else if (triggers.data() && triggers.data()->getSignature() != HKB_CLIP_TRIGGER_ARRAY){
    }else if (name == ""){
    }else if (animationName == ""){
    }else if (valid){
        setDataValidity(true);
        return true;
    }
    setDataValidity(false);
    return false;
}

hkbClipGenerator::~hkbClipGenerator(){
    refCount--;
}
