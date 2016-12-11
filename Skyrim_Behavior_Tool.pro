#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T01:56:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Skyrim_Behavior_Tool
TEMPLATE = app

# remove possible other optimization flags
#QMAKE_CXXFLAGS_DEBUG -= -O
#QMAKE_CXXFLAGS_DEBUG -= -O1
#QMAKE_CXXFLAGS_DEBUG -= -O2

# add the desired -O3 if not present
#QMAKE_CXXFLAGS_DEBUG *= -O3

SOURCES += \
    src/main.cpp \
    src/filetypes/hkxfile.cpp \
    src/ui/mainwindow.cpp \
    src/xml/hkxxmlreader.cpp \
    src/hkxclasses/behavior/hkbbehaviorgraphstringdata.cpp \
    src/hkxclasses/hkxobject.cpp \
    src/hkxclasses/behavior/hkbvariablevalueset.cpp \
    src/hkxclasses/behavior/hkbbehaviorgraphdata.cpp \
    src/hkxclasses/behavior/generators/hkbbehaviorgraph.cpp \
    src/hkxclasses/behavior/generators/hkbgenerator.cpp \
    src/hkxclasses/hkrootlevelcontainer.cpp \
    src/hkxclasses/behavior/generators/hkbbehaviorreferencegenerator.cpp \
    src/hkxclasses/behavior/generators/hkbstatemachine.cpp \
    src/hkxclasses/behavior/generators/hkbstatemachinestateinfo.cpp \
    src/hkxclasses/behavior/generators/hkbclipgenerator.cpp \
    src/hkxclasses/behavior/generators/bscyclicblendtransitiongenerator.cpp \
    src/hkxclasses/behavior/generators/hkbblendergenerator.cpp \
    src/hkxclasses/behavior/generators/hkbblendergeneratorchild.cpp \
    src/hkxclasses/behavior/generators/hkbmanualselectorgenerator.cpp \
    src/hkxclasses/behavior/generators/hkbmodifiergenerator.cpp \
    src/hkxclasses/behavior/generators/bsboneswitchgenerator.cpp \
    src/hkxclasses/behavior/generators/bsboneswitchgeneratorbonedata.cpp \
    src/hkxclasses/behavior/generators/bsistatetagginggenerator.cpp \
    src/hkxclasses/behavior/generators/bssynchronizedclipgenerator.cpp \
    src/hkxclasses/behavior/generators/hkbposematchinggenerator.cpp \
    src/hkxclasses/behavior/generators/bsoffsetanimationgenerator.cpp \
    src/hkxclasses/behavior/hkbstringeventpayload.cpp \
    src/hkxclasses/behavior/hkbboneweightarray.cpp \
    src/hkxclasses/behavior/hkbstatemachineeventpropertyarray.cpp \
    src/hkxclasses/behavior/hkbstatemachinetransitioninfoarray.cpp \
    src/hkxclasses/behavior/modifiers/hkbmodifier.cpp \
    src/ui/hkxclassesui/hkdataui.cpp \
    src/ui/hkxclassesui/behaviorui/generators/bsistatetagginggeneratorui.cpp \
    src/ui/hkxclassesui/behaviorui/generators/modifiergeneratorui.cpp \
    src/ui/hkxclassesui/behaviorui/generators/manualselectorgeneratorui.cpp \
    src/ui/hkxclassesui/behaviorui/behaviorvariablesui.cpp \
    src/ui/hkxclassesui/behaviorui/eventsui.cpp \
    src/ui/hkxclassesui/behaviorui/generators/statemachineui.cpp \
    src/ui/hkxclassesui/behaviorui/generators/stateui.cpp \
    src/hkxclasses/behavior/hkbvariablebindingset.cpp \
    src/ui/hkxclassesui/behaviorui/transitionsui.cpp \
    src/ui/hkxclassesui/behaviorui/blendingtransitioneffectui.cpp \
    src/hkxclasses/behavior/hkbexpressioncondition.cpp \
    src/ui/genericdatawidgets.cpp \
    src/xml/hkxxmlwriter.cpp \
    src/hkxclasses/behavior/hkbcliptriggerarray.cpp \
    src/hkxclasses/behavior/hkbblendingtransitioneffect.cpp \
    src/hkxclasses/behavior/modifiers/hkbmodifierlist.cpp \
    src/hkxclasses/behavior/modifiers/hkbtwistmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbeventdrivenmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsisactivemodifier.cpp \
    src/hkxclasses/behavior/modifiers/bslimbikmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsspeedsamplermodifier.cpp \
    src/hkxclasses/behavior/modifiers/bslookatmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbfootikcontrolsmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbevaluateexpressionmodifier.cpp \
    src/hkxclasses/behavior/hkbexpressiondataarray.cpp \
    src/hkxclasses/behavior/modifiers/bsmodifyoncemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbrotatecharactermodifier.cpp \
    src/hkxclasses/behavior/modifiers/bseventondeactivatemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbdampingmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bseventonfalsetotruemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbkeyframebonesmodifier.cpp \
    src/hkxclasses/behavior/hkbboneindexarray.cpp \
    src/hkxclasses/behavior/modifiers/bsragdollcontactlistenermodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbpoweredragdollcontrolsmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbtimermodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbrigidbodyragdollcontrolsmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbgetupmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsdirectatmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbcomputedirectionmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbevaluatehandlemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbgethandleonbonemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbsensehandlemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbdelayedmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbdetectclosetogroundmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsdecomposevectormodifier.cpp \
    src/hkxclasses/behavior/generators/bgsgamebryosequencegenerator.cpp \
    src/hkxclasses/behavior/modifiers/bscomputeaddboneanimmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsdisttriggermodifier.cpp \
    src/hkxclasses/behavior/modifiers/bseventeveryneventsmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsgettimestepmodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsinterpvaluemodifier.cpp \
    src/hkxclasses/behavior/modifiers/bspassbytargettriggermodifier.cpp \
    src/hkxclasses/behavior/modifiers/bstimermodifier.cpp \
    src/hkxclasses/behavior/modifiers/bstweenermodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbattachmentmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbattributemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbcombinetransformsmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbcomputerotationfromaxisanglemodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbcomputerotationtotargetmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbeventsfromrangemodifier.cpp \
    src/hkxclasses/behavior/hkbeventrangedataarray.cpp \
    src/hkxclasses/behavior/modifiers/hkbextractragdollposemodifier.cpp \
    src/hkxclasses/behavior/hkbgeneratortransitioneffect.cpp \
    src/hkxclasses/behavior/modifiers/hkbgetworldfrommodelmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkblookatmodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbmirrormodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbmovecharactermodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbtransformvectormodifier.cpp \
    src/hkxclasses/behavior/modifiers/hkbproxymodifier.cpp \
    src/hkxclasses/behavior/modifiers/bsistatemanagermodifier.cpp \
    src/filetypes/behaviorfile.cpp \
    src/filetypes/projectfile.cpp \
    src/filetypes/characterfile.cpp \
    src/filetypes/skeletonfile.cpp \
    src/hkxclasses/behavior/hkbprojectdata.cpp \
    src/hkxclasses/behavior/hkbprojectstringdata.cpp \
    src/ui/customtreegraphicsview.cpp \
    src/ui/behaviorgraphui/behaviorgraphview.cpp \
    src/ui/behaviorgraphui/customtreegraphicsviewicon.cpp \
    src/hkxclasses/behavior/hkbmirroredskeletoninfo.cpp \
    src/hkxclasses/behavior/hkbcharacterstringdata.cpp \
    src/hkxclasses/behavior/hkbcharacterdata.cpp \
    src/hkxclasses/behavior/hkbfootikdriverinfo.cpp \
    src/hkxclasses/behavior/hkbhandikdriverinfo.cpp \
    src/hkxclasses/behavior/hkbstringcondition.cpp

HEADERS  += \
    src/filetypes/hkxfile.h \
    src/ui/mainwindow.h \
    src/xml/hkxxmlreader.h \
    src/hkxclasses/behavior/hkbbehaviorgraphstringdata.h \
    src/hkxclasses/hkxobject.h \
    src/hkxclasses/behavior/hkbvariablevalueset.h \
    src/hkxclasses/behavior/hkbbehaviorgraphdata.h \
    src/hkxclasses/behavior/generators/hkbbehaviorgraph.h \
    src/hkxclasses/behavior/generators/hkbgenerator.h \
    src/hkxclasses/hkrootlevelcontainer.h \
    src/hkxclasses/behavior/generators/hkbbehaviorreferencegenerator.h \
    src/hkxclasses/behavior/generators/hkbstatemachine.h \
    src/hkxclasses/behavior/generators/hkbstatemachinestateinfo.h \
    src/hkxclasses/behavior/generators/hkbclipgenerator.h \
    src/hkxclasses/behavior/generators/bscyclicblendtransitiongenerator.h \
    src/hkxclasses/behavior/generators/hkbblendergenerator.h \
    src/hkxclasses/behavior/generators/hkbblendergeneratorchild.h \
    src/hkxclasses/behavior/generators/hkbmanualselectorgenerator.h \
    src/hkxclasses/behavior/generators/hkbmodifiergenerator.h \
    src/hkxclasses/behavior/generators/bsboneswitchgenerator.h \
    src/hkxclasses/behavior/generators/bsboneswitchgeneratorbonedata.h \
    src/hkxclasses/behavior/generators/bsistatetagginggenerator.h \
    src/hkxclasses/behavior/generators/bssynchronizedclipgenerator.h \
    src/hkxclasses/behavior/generators/hkbposematchinggenerator.h \
    src/hkxclasses/behavior/generators/bsoffsetanimationgenerator.h \
    src/hkxclasses/behavior/hkbstringeventpayload.h \
    src/hkxclasses/behavior/hkbboneweightarray.h \
    src/hkxclasses/behavior/hkbstatemachineeventpropertyarray.h \
    src/hkxclasses/behavior/hkbstatemachinetransitioninfoarray.h \
    src/ui/genericdatawidgets.h \
    src/hkxclasses/behavior/modifiers/hkbmodifier.h \
    src/ui/hkxclassesui/hkdataui.h \
    src/ui/hkxclassesui/behaviorui/generators/bsistatetagginggeneratorui.h \
    src/ui/hkxclassesui/behaviorui/generators/modifiergeneratorui.h \
    src/ui/hkxclassesui/behaviorui/generators/manualselectorgeneratorui.h \
    src/ui/hkxclassesui/behaviorui/behaviorvariablesui.h \
    src/utility.h \
    src/ui/hkxclassesui/behaviorui/eventsui.h \
    src/ui/hkxclassesui/behaviorui/generators/statemachineui.h \
    src/ui/hkxclassesui/behaviorui/generators/stateui.h \
    src/hkxclasses/behavior/hkbvariablebindingset.h \
    src/ui/hkxclassesui/behaviorui/transitionsui.h \
    src/ui/hkxclassesui/behaviorui/blendingtransitioneffectui.h \
    src/hkxclasses/behavior/hkbexpressioncondition.h \
    src/xml/hkxxmlwriter.h \
    src/hkxclasses/behavior/hkbcliptriggerarray.h \
    src/hkxclasses/behavior/hkbblendingtransitioneffect.h \
    src/hkxclasses/behavior/modifiers/hkbmodifierlist.h \
    src/hkxclasses/behavior/modifiers/hkbtwistmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbeventdrivenmodifier.h \
    src/hkxclasses/behavior/modifiers/bsisactivemodifier.h \
    src/hkxclasses/behavior/modifiers/bslimbikmodifier.h \
    src/hkxclasses/behavior/modifiers/bsspeedsamplermodifier.h \
    src/hkxclasses/behavior/modifiers/bslookatmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbfootikcontrolsmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbevaluateexpressionmodifier.h \
    src/hkxclasses/behavior/hkbexpressiondataarray.h \
    src/hkxclasses/behavior/modifiers/bsmodifyoncemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbrotatecharactermodifier.h \
    src/hkxclasses/behavior/modifiers/bseventondeactivatemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbdampingmodifier.h \
    src/hkxclasses/behavior/modifiers/bseventonfalsetotruemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbkeyframebonesmodifier.h \
    src/hkxclasses/behavior/hkbboneindexarray.h \
    src/hkxclasses/behavior/modifiers/bsragdollcontactlistenermodifier.h \
    src/hkxclasses/behavior/modifiers/hkbpoweredragdollcontrolsmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbtimermodifier.h \
    src/hkxclasses/behavior/modifiers/hkbrigidbodyragdollcontrolsmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbgetupmodifier.h \
    src/hkxclasses/behavior/modifiers/bsdirectatmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbcomputedirectionmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbevaluatehandlemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbgethandleonbonemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbsensehandlemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbdelayedmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbdetectclosetogroundmodifier.h \
    src/hkxclasses/behavior/modifiers/bsdecomposevectormodifier.h \
    src/hkxclasses/behavior/generators/bgsgamebryosequencegenerator.h \
    src/hkxclasses/behavior/modifiers/bscomputeaddboneanimmodifier.h \
    src/hkxclasses/behavior/modifiers/bsdisttriggermodifier.h \
    src/hkxclasses/behavior/modifiers/bseventeveryneventsmodifier.h \
    src/hkxclasses/behavior/modifiers/bsgettimestepmodifier.h \
    src/hkxclasses/behavior/modifiers/bsinterpvaluemodifier.h \
    src/hkxclasses/behavior/modifiers/bspassbytargettriggermodifier.h \
    src/hkxclasses/behavior/modifiers/bstimermodifier.h \
    src/hkxclasses/behavior/modifiers/bstweenermodifier.h \
    src/hkxclasses/behavior/modifiers/hkbattachmentmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbattributemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbcombinetransformsmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbcomputerotationfromaxisanglemodifier.h \
    src/hkxclasses/behavior/modifiers/hkbcomputerotationtotargetmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbeventsfromrangemodifier.h \
    src/hkxclasses/behavior/hkbeventrangedataarray.h \
    src/hkxclasses/behavior/modifiers/hkbextractragdollposemodifier.h \
    src/hkxclasses/behavior/hkbgeneratortransitioneffect.h \
    src/hkxclasses/behavior/modifiers/hkbgetworldfrommodelmodifier.h \
    src/hkxclasses/behavior/modifiers/hkblookatmodifier.h \
    src/hkxclasses/behavior/modifiers/hkbmirrormodifier.h \
    src/hkxclasses/behavior/modifiers/hkbmovecharactermodifier.h \
    src/hkxclasses/behavior/modifiers/hkbtransformvectormodifier.h \
    src/hkxclasses/behavior/modifiers/hkbproxymodifier.h \
    src/hkxclasses/behavior/modifiers/bsistatemanagermodifier.h \
    src/filetypes/behaviorfile.h \
    src/filetypes/projectfile.h \
    src/filetypes/characterfile.h \
    src/filetypes/skeletonfile.h \
    src/hkxclasses/behavior/hkbprojectdata.h \
    src/hkxclasses/behavior/hkbprojectstringdata.h \
    src/ui/customtreegraphicsview.h \
    src/ui/behaviorgraphui/behaviorgraphview.h \
    src/ui/behaviorgraphui/customtreegraphicsviewicon.h \
    src/hkxclasses/behavior/hkbmirroredskeletoninfo.h \
    src/hkxclasses/behavior/hkbcharacterstringdata.h \
    src/hkxclasses/behavior/hkbcharacterdata.h \
    src/hkxclasses/behavior/hkbfootikdriverinfo.h \
    src/hkxclasses/behavior/hkbhandikdriverinfo.h \
    src/hkxclasses/behavior/hkbstringcondition.h
