#include "hkxfile.h"
#include "hkobject.h"
//#include "utility.h"
#include "hkxxmlreader.h"
#include "modifiers.h"
#include "generators.h"
#include "mainwindow.h"

void HkxFile::writeToLog(const QString & message, bool isError){
    if (ui){
        ui->writeToLog(message, isError);
    }
}

void HkxFile::setProgressData(const QString & message, int value){
    ui->setProgressData(message, value);
}

BehaviorFile::BehaviorFile(MainWindow *window, const QString & name): HkxFile(window, name){
    reader.setBehaviorFile(this);
    if (!parse()){
        writeToLog("MainWindow: parse() failed!");
        getUI()->drawGraph = false;
    }
    reader.clear();
}

template <typename T>
bool BehaviorFile::appendAndReadData(int index, T * obj){
    bool ok;
    QByteArray temp = reader.getNthAttributeValueAt(index, 0);
    if (temp.at(0) == '#'){
        temp.remove(0, 1);
    }
    if (obj->getType() == HkObject::TYPE_GENERATOR){
        generators.append(HkObjectExpSharedPtr(reinterpret_cast<hkbGenerator*>(obj), temp.toLong(&ok)));
    }else if (obj->getType() == HkObject::TYPE_MODIFIER){
        modifiers.append(HkObjectExpSharedPtr(reinterpret_cast<hkbModifier*>(obj), temp.toLong(&ok)));
    }else if (obj->getType() == HkObject::TYPE_OTHER){
        otherTypes.append(HkObjectExpSharedPtr(obj, temp.toLong(&ok)));
    }else{
        writeToLog("BehaviorFile: appendAndReadData() failed!\nInvalid type enum for this object!\nObject signature is: "+QString::number(obj->getSignature(), 16), true);
        return false;
    }
    if (!ok){
        writeToLog("BehaviorFile: appendAndReadData() failed!\nThe object reference string contained invalid characters and failed to convert to an integer!", true);
        return false;
    }
    //Skip the current line.
    index++;
    if (!obj->readData(reader, index)){
        return false;
    }
    return true;
}

bool BehaviorFile::parse(){
    if (!reader.parse()){
        return false;
    }
    int index = 2;
    bool ok = true;
    qulonglong signature;
    QByteArray value;
    setProgressData("Creating HKX objects...", 60);
    while (index < reader.getNumElements()){
        value = reader.getNthAttributeNameAt(index, 1);
        if (value == "class"){
            value = reader.getNthAttributeValueAt(index, 2);
            if (value != ""){
                signature = value.toULongLong(&ok, 16);
                if (!ok){
                    writeToLog("BehaviorFile: parse() failed!\nThe object signature string contained invalid characters and failed to convert to an integer!", true);
                    return false;
                }
                if (signature == HKB_STATE_MACHINE_STATE_INFO){
                    if (!appendAndReadData(index, new hkbStateMachineStateInfo(this))){
                        return false;
                    }
                }else if (signature == HKB_STATE_MACHINE){
                    if (!appendAndReadData(index, new hkbStateMachine(this))){
                        return false;
                    }
                }else if (signature == HKB_MODIFIER_GENERATOR){
                    if (!appendAndReadData(index, new hkbModifierGenerator(this))){
                        return false;
                    }
                }else if (signature == BS_I_STATE_TAGGING_GENERATOR){
                    if (!appendAndReadData(index, new BSiStateTaggingGenerator(this))){
                        return false;
                    }
                }else if (signature == BS_CYCLIC_BLEND_TRANSITION_GENERATOR){
                    if (!appendAndReadData(index, new BSCyclicBlendTransitionGenerator(this))){
                        return false;
                    }
                }else if (signature == BS_BONE_SWITCH_GENERATOR){
                    if (!appendAndReadData(index, new BSBoneSwitchGenerator(this))){
                        return false;
                    }
                }else if (signature == BS_BONE_SWITCH_GENERATOR_BONE_DATA){
                    if (!appendAndReadData(index, new BSBoneSwitchGeneratorBoneData(this))){
                        return false;
                    }
                }else if (signature == BS_SYNCHRONIZED_CLIP_GENERATOR){
                    if (!appendAndReadData(index, new BSSynchronizedClipGenerator(this))){
                        return false;
                    }
                }else if (signature == HKB_MANUAL_SELECTOR_GENERATOR){
                    if (!appendAndReadData(index, new hkbManualSelectorGenerator(this))){
                        return false;
                    }
                }else if (signature == HKB_BLENDER_GENERATOR_CHILD){
                    if (!appendAndReadData(index, new hkbBlenderGeneratorChild(this))){
                        return false;
                    }
                }else if (signature == HKB_BLENDER_GENERATOR){
                    if (!appendAndReadData(index, new hkbBlenderGenerator(this))){
                        return false;
                    }
                }else if (signature == BS_OFFSET_ANIMATION_GENERATOR){
                    if (!appendAndReadData(index, new BSOffsetAnimationGenerator(this))){
                        return false;
                    }
                }else if (signature == HKB_POSE_MATCHING_GENERATOR){
                    if (!appendAndReadData(index, new hkbPoseMatchingGenerator(this))){
                        return false;
                    }
                }else if (signature == HKB_CLIP_GENERATOR){
                    if (!appendAndReadData(index, new hkbClipGenerator(this))){
                        return false;
                    }
                }else if (signature == HKB_BEHAVIOR_REFERENCE_GENERATOR){
                    if (!appendAndReadData(index, new hkbBehaviorReferenceGenerator(this))){
                        return false;
                    }
                }/*else if (signature == HKB_STATE_MACHINE_TRANSITION_INFO_ARRAY){
                    if (!appendAndReadData(index, new hkbStateMachineTransitionInfoArray(this))){
                        return false;
                    }
                }else if (signature == HKB_STATE_MACHINE_EVENT_PROPERTY_ARRAY){
                    if (!appendAndReadData(index, new hkbStateMachineEventPropertyArray(this))){
                        return false;
                    }
                }*/else if (signature == HKB_BEHAVIOR_GRAPH){
                    if (!appendAndReadData(index, new hkbBehaviorGraph(this))){
                        return false;
                    }
                }else if (signature == HK_ROOT_LEVEL_CONTAINER){
                    if (!appendAndReadData(index, new hkRootLevelContainer(this))){
                        return false;
                    }
                    setRootObject(otherTypes.last());
                }else{
                    writeToLog("BehaviorFile: parse()!\nUnknown signature detected!\nUnknown object class name is: "+reader.getNthAttributeValueAt(index, 1)+"\nUnknown object signature is: "+QString::number(signature, 16));
                }
            }
        }
        index++;
    }
    closeFile();
    setProgressData("Linking HKX objects...", 80);
    if (!link()){
        writeToLog("BehaviorFile: parse() failed because link() failed!", true);
        return false;
    }
    return true;
}

bool BehaviorFile::link(){
    if (!getRootObject().constData()){
        writeToLog("BehaviorFile: link() failed!\nThe root object of this behavior file is NULL!", true);
        return false;
    }else if (getRootObject()->getSignature() != HK_ROOT_LEVEL_CONTAINER){
        writeToLog("BehaviorFile: link() failed!\nThe root object of this behavior file is NOT a hkRootLevelContainer!\nThe root object signature is: "+QString::number(getRootObject()->getSignature(), 16), true);
        return false;
    }
    if (!static_cast<hkRootLevelContainer * >(getRootObject().data())->link()){
        writeToLog("BehaviorFile: link() failed!\nThe root object of this behavior file failed to link to it's children!", true);
        return false;
    }
    for (int i = generators.size() - 1; i >= 0; i--){
        if (!static_cast<hkbGenerator * >(generators.at(i).data())->link()){
            writeToLog("BehaviorFile: link() failed!\nA generator failed to link to it's children!\nObject signature: "+QString::number(generators.at(i)->getSignature(), 16)+"\nObject reference: "+QString::number(generators.at(i).getReference()), true);
            return false;
        }
    }
    return true;
}

HkObjectExpSharedPtr * BehaviorFile::findGenerator(long ref){
    if (ref < 0){
        return NULL;
    }
    for (int i = 0; i < generators.size(); i++){
        if (ref == generators.at(i).getReference()){
            return &generators[i];
        }
    }
    return NULL;
}

HkObjectExpSharedPtr * BehaviorFile::findModifier(long ref){
    if (ref < 0){
        return NULL;
    }
    for (int i = 0; i < modifiers.size(); i++){
        if (ref == modifiers.at(i).getReference()){
            return &modifiers[i];
        }
    }
    return NULL;
}

HkObjectExpSharedPtr * BehaviorFile::findHkObject(long ref){
    if (ref < 0){
        return NULL;
    }
    for (int i = 0; i < otherTypes.size(); i++){
        if (ref == otherTypes.at(i).getReference()){
            return &otherTypes[i];
        }
    }
    return NULL;
}




























