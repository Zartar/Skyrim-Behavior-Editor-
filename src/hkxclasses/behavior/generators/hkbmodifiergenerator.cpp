#include "hkbmodifiergenerator.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/behaviorfile.h"
/*
 * CLASS: hkbModifierGenerator
*/

uint hkbModifierGenerator::refCount = 0;

QString hkbModifierGenerator::classname = "hkbModifierGenerator";

hkbModifierGenerator::hkbModifierGenerator(HkxFile *parent, long ref)
    : hkbGenerator(parent, ref),
      userData(0)
{
    setType(HKB_MODIFIER_GENERATOR, TYPE_GENERATOR);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
    name = "hkbModifierGenerator"+QString::number(refCount);
}

QString hkbModifierGenerator::getClassname(){
    return classname;
}

QString hkbModifierGenerator::getName() const{
    return name;
}

int hkbModifierGenerator::getIndexToInsertIcon(HkxObject *child) const{
    if (modifier.constData() == child){
        return 0;
    }else if (generator.constData() == child){
        return 1;
    }
    return -1;
}

bool hkbModifierGenerator::setChildAt(HkxObject *newChild, ushort index){
    if (index == 0 && (!newChild || newChild->getType() == TYPE_GENERATOR)){
        generator = HkxObjectExpSharedPtr(newChild);
        return true;
    }else if (index == 1 && (!newChild || newChild->getType() == TYPE_MODIFIER)){
        modifier = HkxObjectExpSharedPtr(newChild);
        return true;
    }else{
        return false;
    }
}

bool hkbModifierGenerator::wrapObject(DataIconManager *objToInject, DataIconManager *childToReplace){
    if (generator.data() == childToReplace && childToReplace->getType() == TYPE_GENERATOR){
        if (!objToInject->setChildAt(generator.data())){
            return false;
        }
        generator = HkxObjectExpSharedPtr(objToInject);
        return true;
    }else if (modifier.data() == childToReplace && childToReplace->getType() == TYPE_MODIFIER){
        if (!objToInject->setChildAt(modifier.data())){
            return false;
        }
        modifier = HkxObjectExpSharedPtr(objToInject);
        return true;
    }
    return false;
}

bool hkbModifierGenerator::appendObject(DataIconManager *objToAppend){
    if (objToAppend->getType() == TYPE_GENERATOR){
        generator = HkxObjectExpSharedPtr(objToAppend);
    }else if (objToAppend->getType() == TYPE_MODIFIER){
        modifier = HkxObjectExpSharedPtr(objToAppend);
    }
    return true;
}

bool hkbModifierGenerator::removeObject(DataIconManager *objToRemove, bool removeAll){
    bool b = false;
    if (removeAll){
        if (generator.data() == objToRemove){
            generator = HkxObjectExpSharedPtr();
            b = true;
        }
        if (modifier.data() == objToRemove){
            modifier = HkxObjectExpSharedPtr();
            b = true;
        }
        return b;
    }else{
        if (generator.data() == objToRemove){
            generator = HkxObjectExpSharedPtr();
            return true;
        }
        if (modifier.data() == objToRemove){
            modifier = HkxObjectExpSharedPtr();
            return true;
        }
    }
    return false;
}

bool hkbModifierGenerator::hasChildren() const{
    if (generator.data()){
        return true;
    }
    if (modifier.data()){
        return true;
    }
    return false;
}

int hkbModifierGenerator::addChildrenToList(QList<DataIconManager *> & list, bool reverseOrder){
    int objectChildCount = 0;
    if (reverseOrder){
        if (generator.data()){
            list.append(static_cast<DataIconManager *>(generator.data()));
            objectChildCount++;
        }
        if (modifier.data()){
            list.append(static_cast<DataIconManager *>(modifier.data()));
            objectChildCount++;
        }
    }else{
        if (modifier.data()){
            list.append(static_cast<DataIconManager *>(modifier.data()));
            objectChildCount++;
        }
        if (generator.data()){
            list.append(static_cast<DataIconManager *>(generator.data()));
            objectChildCount++;
        }
    }
    return objectChildCount;
}

bool hkbModifierGenerator::readData(const HkxXmlReader &reader, long index){
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
        }else if (text == "modifier"){
            if (!modifier.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'modifier' reference!\nObject Reference: "+ref);
            }
        }else if (text == "generator"){
            if (!generator.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'generator' reference!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbModifierGenerator::write(HkxXMLWriter *writer){
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
        if (modifier.data()){
            refString = modifier.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("modifier"), refString);
        if (generator.data()){
            refString = generator.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("generator"), refString);
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (variableBindingSet.data() && !variableBindingSet.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'variableBindingSet'!!!", true);
        }
        if (modifier.data() && !modifier.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'modifier'!!!", true);
        }
        if (generator.data() && !generator.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'generator'!!!", true);
        }
    }
    return true;
}

bool hkbModifierGenerator::link(){
    if (!getParentFile()){
        return false;
    }
    if (!static_cast<DataIconManager *>(this)->linkVar()){
        writeToLog(getClassname()+": link()!\nFailed to properly link 'variableBindingSet' data field!\nObject Name: "+name);
    }
    HkxObjectExpSharedPtr *ptr;
    ptr = static_cast<BehaviorFile *>(getParentFile())->findModifier(modifier.getReference());
    if (ptr){
        if ((*ptr)->getType() != TYPE_MODIFIER){
            writeToLog(getClassname()+": link()!\n'modifier' data field is linked to invalid child!\nObject Name: "+name);
            setDataValidity(false);
        }
        modifier = *ptr;
    }
    ptr = static_cast<BehaviorFile *>(getParentFile())->findGenerator(generator.getReference());
    if (!ptr){
        writeToLog(getClassname()+": link()!\nFailed to properly link 'generator' data field!\nObject Name: "+name);
        setDataValidity(false);
    }else if ((*ptr)->getType() != TYPE_GENERATOR || (*ptr)->getSignature() == BS_BONE_SWITCH_GENERATOR_BONE_DATA || (*ptr)->getSignature() == HKB_STATE_MACHINE_STATE_INFO || (*ptr)->getSignature() == HKB_BLENDER_GENERATOR_CHILD){
        writeToLog(getClassname()+": link()!\n'generator' data field is linked to invalid child!\nObject Name: "+name);
        setDataValidity(false);
        generator = *ptr;
    }else{
        generator = *ptr;
    }
    return true;
}

void hkbModifierGenerator::unlink(){
    HkDynamicObject::unlink();
    modifier = HkxObjectExpSharedPtr();
    generator = HkxObjectExpSharedPtr();
}

bool hkbModifierGenerator::evaulateDataValidity(){
    if (!HkDynamicObject::evaulateDataValidity()){
        return false;
    }else if (modifier.data() && modifier.data()->getType() != HkxObject::TYPE_MODIFIER){
    }else if (!generator.data() || generator.data()->getType() != HkxObject::TYPE_GENERATOR){
    }else if (name == ""){
    }else{
        setDataValidity(true);
        return true;
    }
    setDataValidity(false);
    return false;
}

hkbModifierGenerator::~hkbModifierGenerator(){
    refCount--;
}