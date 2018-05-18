#include "behaviorgraphui.h"
#include "src/hkxclasses/hkxobject.h"
#include "src/hkxclasses/behavior/generators/hkbbehaviorgraph.h"
#include "src/hkxclasses/behavior/generators/hkbstatemachine.h"
#include "src/filetypes/behaviorfile.h"
#include "src/ui/genericdatawidgets.h"
#include "src/ui/behaviorgraphview.h"
#include "src/ui/treegraphicsitem.h"

#include <QGridLayout>
#include <QHeaderView>

#define BASE_NUMBER_OF_ROWS 3

#define NAME_ROW 0
#define VARIABLE_MODE_ROW 1
#define ROOT_GENERATOR_ROW 2

#define NAME_COLUMN 0
#define TYPE_COLUMN 1
#define VALUE_COLUMN 2

QStringList BehaviorGraphUI::headerLabels = {
    "Name",
    "Type",
    "Value"
};

BehaviorGraphUI::BehaviorGraphUI()
    : behaviorView(nullptr),
      bsData(nullptr),
      topLyt(new QGridLayout),
      table(new TableWidget(QColor(Qt::white))),
      name(new LineEdit),
      variableMode(new ComboBox)
{
    setTitle("hkbBehaviorGraph");
    table->setRowCount(BASE_NUMBER_OF_ROWS);
    table->setColumnCount(headerLabels.size());
    table->setHorizontalHeaderLabels(headerLabels);
    table->setItem(NAME_ROW, NAME_COLUMN, new TableWidgetItem("name"));
    table->setItem(NAME_ROW, TYPE_COLUMN, new TableWidgetItem("hkStringPtr", Qt::AlignCenter));
    table->setCellWidget(NAME_ROW, VALUE_COLUMN, name);
    table->setItem(VARIABLE_MODE_ROW, NAME_COLUMN, new TableWidgetItem("variableMode"));
    table->setItem(VARIABLE_MODE_ROW, TYPE_COLUMN, new TableWidgetItem("VariableMode", Qt::AlignCenter));
    table->setCellWidget(VARIABLE_MODE_ROW, VALUE_COLUMN, variableMode);
    table->setItem(ROOT_GENERATOR_ROW, NAME_COLUMN, new TableWidgetItem("rootGenerator"));
    table->setItem(ROOT_GENERATOR_ROW, TYPE_COLUMN, new TableWidgetItem("hkReal", Qt::AlignCenter));
    table->setItem(ROOT_GENERATOR_ROW, VALUE_COLUMN, new TableWidgetItem("NONE", Qt::AlignCenter, QColor(219, 219, 219), QBrush(Qt::black), "Click to view the list of generators"));
    topLyt->addWidget(table, 0, 0, 8, 3);
    setLayout(topLyt);
    connect(name, SIGNAL(editingFinished()), this, SLOT(setName()), Qt::UniqueConnection);
    connect(variableMode, SIGNAL(currentIndexChanged(int)), this, SLOT(setVariableMode(int)), Qt::UniqueConnection);
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelectedChild(int,int)), Qt::UniqueConnection);
}

void BehaviorGraphUI::loadData(HkxObject *data){
    blockSignals(true);
    if (data){
        if (data->getSignature() == HKB_BEHAVIOR_GRAPH){
            bsData = static_cast<hkbBehaviorGraph *>(data);
            name->setText(bsData->name);
            if (variableMode->count() == 0){
                variableMode->insertItems(0, bsData->VariableMode);
            }
            variableMode->setCurrentIndex(bsData->VariableMode.indexOf(bsData->variableMode));
            if (bsData->rootGenerator.data()){
                table->item(ROOT_GENERATOR_ROW, VALUE_COLUMN)->setText(static_cast<hkbGenerator *>(bsData->rootGenerator.data())->getName());
            }else{
                table->item(ROOT_GENERATOR_ROW, VALUE_COLUMN)->setText("NONE");
            }
        }else{
            CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::loadData(): The data is an incorrect type!!");
        }
    }else{
        CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::loadData(): The data is nullptr!!");
    }
    blockSignals(false);
}

void BehaviorGraphUI::setName(){
    if (bsData){
        if (bsData->name != name->text()){
            bsData->name = name->text();//Make sure name is valid...
            static_cast<DataIconManager*>((bsData))->updateIconNames();
            bsData->getParentFile()->setIsChanged(true);
        }
    }else{
        CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::setName(): The data is nullptr!!");
    }
}

void BehaviorGraphUI::setVariableMode(int index){
    if (bsData){
        bsData->variableMode = bsData->VariableMode.at(index);
        bsData->getParentFile()->setIsChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::setVariableMode(): The data is nullptr!!");
    }
}

void BehaviorGraphUI::viewSelectedChild(int row, int column){
    if (bsData){
        if (row == ROOT_GENERATOR_ROW && column == VALUE_COLUMN){
            if (bsData->getParentFile()){
                emit viewGenerators(static_cast<BehaviorFile *>(bsData->getParentFile())->getIndexOfGenerator(bsData->rootGenerator) + 1, hkbStateMachine::getClassname(), QStringList());
            }else{
                CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::viewSelectedChild(): The parent file is nullptr!!");
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE("StateMachineUI::viewSelectedChild(): The data is nullptr!!");
    }
}

void BehaviorGraphUI::setRootGenerator(int index, const QString &name){
    DataIconManager *ptr = nullptr;
    if (bsData){
        int indexOfGenerator = bsData->getIndexOfObj(static_cast<DataIconManager*>(bsData->rootGenerator.data()));
        if (behaviorView){
            ptr = static_cast<BehaviorFile *>(bsData->getParentFile())->getGeneratorDataAt(index - 1);
            if (ptr){
                if (name != ptr->getName()){
                    CRITICAL_ERROR_MESSAGE("::setDefaultGenerator():The name of the selected object does not match it's name in the object selection table!!!");
                    return;
                }else if (ptr->getSignature() != HKB_STATE_MACHINE){
                    WARNING_MESSAGE("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\nThe selected object is not a hkbStateMachine!!!");
                    return;
                }else if (ptr == bsData || !behaviorView->reconnectIcon(behaviorView->getSelectedItem(), static_cast<DataIconManager*>(bsData->rootGenerator.data()), 0, ptr, false)){
                    WARNING_MESSAGE("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\nYou are attempting to create a circular branch or dead end!!!");
                    return;
                }
            }else{
                if (behaviorView->getSelectedItem()){
                    behaviorView->removeItemFromGraph(behaviorView->getSelectedItem()->getChildWithData(static_cast<DataIconManager*>(bsData->rootGenerator.data())), indexOfGenerator);
                }else{
                    CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::setGenerator(): The selected icon is nullptr!!");
                    return;
                }
            }
            behaviorView->removeGeneratorData();
            table->item(ROOT_GENERATOR_ROW, VALUE_COLUMN)->setText(name);
            bsData->getParentFile()->setIsChanged(true);
        }else{
            CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::setGenerator(): The 'behaviorView' pointer is nullptr!!");
        }
    }else{
        CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::setGenerator(): The 'bsData' pointer is nullptr!!");
    }
}

void BehaviorGraphUI::setBehaviorView(BehaviorGraphView *view){
    behaviorView = view;
}

void BehaviorGraphUI::connectToTables(GenericTableWidget *generators){
    if (generators){
        disconnect(generators, SIGNAL(elementSelected(int,QString)), 0, 0);
        connect(generators, SIGNAL(elementSelected(int,QString)), this, SLOT(setRootGenerator(int,QString)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewGenerators(int,QString,QStringList)), generators, SLOT(showTable(int,QString,QStringList)), Qt::UniqueConnection);
    }else{
        CRITICAL_ERROR_MESSAGE("BehaviorGraphUI::connectToTables(): The argument is nullptr!!");
    }
}
