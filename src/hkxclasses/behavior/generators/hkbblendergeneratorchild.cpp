#include "hkbblendergeneratorchild.h"
#include "hkbblendergenerator.h"
#include "hkbposematchinggenerator.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/behaviorfile.h"
/*
 * CLASS: hkbBlenderGeneratorChild
*/

uint hkbBlenderGeneratorChild::refCount = 0;

QString hkbBlenderGeneratorChild::classname = "hkbBlenderGeneratorChild";

hkbBlenderGeneratorChild::hkbBlenderGeneratorChild(HkxFile *parent, hkbGenerator *parentBG, long ref)
    : hkbGenerator(parent, ref),
      weight(1),
      worldFromModelWeight(1),
      parentBG(parentBG)
{
    setType(HKB_BLENDER_GENERATOR_CHILD, TYPE_GENERATOR);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
    if (parentBG && (parentBG->getSignature() != HKB_BLENDER_GENERATOR && parentBG->getSignature() != HKB_POSE_MATCHING_GENERATOR)){
        CRITICAL_ERROR_MESSAGE("hkbBlenderGeneratorChild::hkbBlenderGeneratorChild: parentBG is incorrect type!!!");
    }
}

QString hkbBlenderGeneratorChild::getClassname(){
    return classname;
}

hkbGenerator * hkbBlenderGeneratorChild::getParentGenerator() const{
    if (parentBG.data() && (parentBG.data()->getSignature() == HKB_BLENDER_GENERATOR || parentBG.data()->getSignature() == HKB_POSE_MATCHING_GENERATOR)){
        return reinterpret_cast<hkbGenerator *>(parentBG.data());
    }
    return nullptr;
}

bool hkbBlenderGeneratorChild::readData(const HkxXmlReader &reader, long index){
    bool ok;
    QByteArray ref = reader.getNthAttributeValueAt(index - 1, 0);
    QByteArray text;
    while (index < reader.getNumElements() && reader.getNthAttributeNameAt(index, 1) != "class"){
        text = reader.getNthAttributeValueAt(index, 0);
        if (text == "variableBindingSet"){
            if (!variableBindingSet.readShdPtrReference(index, reader)){
                LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": readData()!\nFailed to properly read 'variableBindingSet' reference!\nObject Reference: "+ref);
            }
        }else if (text == "generator"){
            if (!generator.readShdPtrReference(index, reader)){
                LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": readData()!\nFailed to properly read 'generator' reference!\nObject Reference: "+ref);
            }
        }else if (text == "boneWeights"){
            if (!boneWeights.readShdPtrReference(index, reader)){
                LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": readData()!\nFailed to properly read 'boneWeights' reference!\nObject Reference: "+ref);
            }
        }else if (text == "weight"){
            weight = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": readData()!\nFailed to properly read 'weight' data field!\nObject Reference: "+ref);
            }
        }else if (text == "worldFromModelWeight"){
            worldFromModelWeight = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": readData()!\nFailed to properly read 'worldFromModelWeight' data field!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbBlenderGeneratorChild::write(HkxXMLWriter *writer){
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
        if (generator.data()){
            refString = generator.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("generator"), refString);
        if (boneWeights.data()){
            refString = boneWeights.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("boneWeights"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("weight"), QString::number(weight, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("worldFromModelWeight"), QString::number(worldFromModelWeight, char('f'), 6));
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (variableBindingSet.data() && !variableBindingSet.data()->write(writer)){
            LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": write()!\nUnable to write 'variableBindingSet'!!!");
        }
        if (generator.data() && !generator.data()->write(writer)){
            LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": write()!\nUnable to write 'generator'!!!");
        }
        if (boneWeights.data() && !boneWeights.data()->write(writer)){
            LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": write()!\nUnable to write 'boneWeights'!!!");
        }
    }
    return true;
}

bool hkbBlenderGeneratorChild::isParametricBlend() const{
    if (parentBG.constData() && parentBG.constData()->getSignature() == HKB_BLENDER_GENERATOR){
        return static_cast<const hkbBlenderGenerator *>(parentBG.constData())->isParametricBlend();
    }else{
        LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": isParametricBlend()!\nNo parent blender generator'!!!");
    }
    return false;
}

bool hkbBlenderGeneratorChild::hasChildren() const{
    if (generator.data()){
        return true;
    }
    return false;
}

QString hkbBlenderGeneratorChild::getName() const{
    if (parentBG.constData()){
        QString name;
        if (parentBG.constData()->getSignature() == HKB_BLENDER_GENERATOR){
            const hkbBlenderGenerator *par = static_cast<const hkbBlenderGenerator *>(parentBG.constData());
            name = par->getName()+"_CHILD"+QString::number(getThisIndex());
        }else if (parentBG.constData()->getSignature() == HKB_POSE_MATCHING_GENERATOR){
            const hkbPoseMatchingGenerator *par = static_cast<const hkbPoseMatchingGenerator *>(parentBG.constData());
            name = par->getName()+"_CHILD"+QString::number(getThisIndex());
        }
        return name;
    }else{
        LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": getName()!\nNo parent blender generator'!!!");
    }
    return "";
}

int hkbBlenderGeneratorChild::getThisIndex() const{
    if (parentBG.constData()){
        return static_cast<DataIconManager *>(parentBG.data())->getIndexOfObj((DataIconManager *)this);
    }else{
        CRITICAL_ERROR_MESSAGE("hkbBlenderGeneratorChild:::getThisIndex() !\nNo parent blender generator'!!!");
    }
    return -1;
}

void hkbBlenderGeneratorChild::updateReferences(long &ref){
    setReference(ref);
    ref++;
    setBindingReference(ref);
    if (boneWeights.data()){
        ref++;
        boneWeights.data()->setReference(ref);
    }
}

QVector<HkxObject *> hkbBlenderGeneratorChild::getChildrenOtherTypes() const{
    QVector<HkxObject *> list;
    if (boneWeights.data()){
        list.append(boneWeights.data());
    }
    return list;
}

bool hkbBlenderGeneratorChild::merge(HkxObject *recessiveObject){
    hkbBlenderGeneratorChild *recobj;
    if (!getIsMerged() && recessiveObject && recessiveObject->getSignature() == HKB_BLENDER_GENERATOR_CHILD){
        recobj = static_cast<hkbBlenderGeneratorChild *>(recessiveObject);
        injectWhileMerging(recobj);
        if (!boneWeights.data() && recobj->boneWeights.data()){
            recobj->boneWeights.data()->fixMergedIndices(static_cast<BehaviorFile *>(getParentFile()));
            getParentFile()->addObjectToFile(recobj->boneWeights.data(), -1);
        }
        return true;
    }else{
        return false;
    }
}

bool hkbBlenderGeneratorChild::operator==(const hkbBlenderGeneratorChild & other){
    if (
            weight != other.weight ||
            worldFromModelWeight != other.worldFromModelWeight ||
            //!parentBG.data() ||
            //!other.parentBG.data() ||
            static_cast<hkbGenerator *>(parentBG.data())->getName() != static_cast<hkbGenerator *>(other.parentBG.data())->getName()
        )
    {
        return false;
    }
    //boneweights???
    return true;
}

QList<DataIconManager *> hkbBlenderGeneratorChild::getChildren() const{
    QList<DataIconManager *> list;
    if (generator.data()){
        list.append(static_cast<DataIconManager*>(generator.data()));
    }
    return list;
}

int hkbBlenderGeneratorChild::getIndexOfObj(DataIconManager *obj) const{
    if (generator.data() == (HkxObject *)obj){
        return 0;
    }
    return -1;
}

bool hkbBlenderGeneratorChild::insertObjectAt(int , DataIconManager *obj){
    if (((HkxObject *)obj)->getType() == TYPE_GENERATOR){
        generator = HkxSharedPtr((HkxObject *)obj);
    }else{
        return false;
    }
    return true;
}

bool hkbBlenderGeneratorChild::removeObjectAt(int index){
    if (index == 0 || index == -1){
        generator = HkxSharedPtr();
    }else{
        return false;
    }
    return true;
}

bool hkbBlenderGeneratorChild::link(){
    if (!getParentFile()){
        return false;
    }
    if (!static_cast<HkDynamicObject *>(this)->linkVar()){
        LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": link()!\nFailed to properly link 'variableBindingSet' data field!");
    }
    HkxSharedPtr *ptr = static_cast<BehaviorFile *>(getParentFile())->findHkxObject(boneWeights.getShdPtrReference());
    if (ptr){
        if ((*ptr)->getSignature() != HKB_BONE_WEIGHT_ARRAY){
            LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": link()!\n'boneWeights' data field is linked to invalid child!");
            setDataValidity(false);
        }
        boneWeights = *ptr;
    }
    ptr = static_cast<BehaviorFile *>(getParentFile())->findGenerator(generator.getShdPtrReference());
    if (!ptr){
        LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": link()!\nFailed to properly link 'generator' data field!");
        setDataValidity(false);
    }else if ((*ptr)->getType() != TYPE_GENERATOR || (*ptr)->getSignature() == BS_BONE_SWITCH_GENERATOR_BONE_DATA || (*ptr)->getSignature() == HKB_STATE_MACHINE_STATE_INFO || (*ptr)->getSignature() == HKB_BLENDER_GENERATOR_CHILD){
        LogFile::writeToLog(getParentFile()->getFileName()+": "+getClassname()+": link()!\n'generator' data field is linked to invalid child!");
        setDataValidity(false);
        generator = *ptr;
    }else{
        generator = *ptr;
    }
    return true;
}

void hkbBlenderGeneratorChild::unlink(){
    HkDynamicObject::unlink();
    parentBG = HkxSharedPtr();
    generator = HkxSharedPtr();
    boneWeights = HkxSharedPtr();
}

QString hkbBlenderGeneratorChild::evaluateDataValidity(){
    QString errors;
    bool isvalid = true;
    QString temp = HkDynamicObject::evaluateDataValidity(); if (temp != ""){errors.append(temp+getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Invalid variable binding set!\n");}
    if (boneWeights.data() && boneWeights.data()->getSignature() != HKB_BONE_WEIGHT_ARRAY){
        isvalid = false;
        errors.append(getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Invalid boneWeights type! Signature: "+QString::number(boneWeights.data()->getSignature(), 16)+"\n");
    }
    if (!generator.data()){
        isvalid = false;
        errors.append(getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Null generator!\n");
    }else if (generator.data()->getType() != HkxObject::TYPE_GENERATOR){
        isvalid = false;
        errors.append(getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Invalid generator type! Signature: "+QString::number(generator.data()->getSignature(), 16)+"\n");
    }
    if (!parentBG.data()){
        isvalid = false;
        errors.append(getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Null parentBG!\n");
    }else if (parentBG.data()->getSignature() != HKB_BLENDER_GENERATOR && parentBG.data()->getSignature() != HKB_POSE_MATCHING_GENERATOR){
        isvalid = false;
        errors.append(getParentFile()->getFileName()+": "+getClassname()+": Ref: "+getReferenceString()+": "+getName()+": Invalid parentBG type! Signature: "+QString::number(parentBG.data()->getSignature(), 16)+"\n");
    }
    setDataValidity(isvalid);
    return errors;
}

hkbBlenderGeneratorChild::~hkbBlenderGeneratorChild(){
    refCount--;
}
