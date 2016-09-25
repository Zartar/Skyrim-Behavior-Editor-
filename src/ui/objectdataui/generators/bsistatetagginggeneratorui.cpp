#include "bsistatetagginggeneratorui.h"
#include "src/hkxclasses/hkxobject.h"
#include "src/hkxclasses/generators/bsistatetagginggenerator.h"
#include "src/ui/genericdatawidgets.h"
#include "src/filetypes/hkxfile.h"
#include "src/ui/behaviorgraphui/behaviorgraphui.h"
#include "src/ui/behaviorgraphui/behaviorgraphicons.h"
#include "src/hkxclasses/hkbvariablebindingset.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QHeaderView>
#include <QSpinBox>

/*
 * BSiStateTaggingGeneratorUI
 */

QStringList BSiStateTaggingGeneratorUI::headerLabels1 = {
    "Name",
    "Type",
    "Value"
};

BSiStateTaggingGeneratorUI::BSiStateTaggingGeneratorUI()
    : behaviorView(NULL),
      bsData(NULL),
      lyt(new QVBoxLayout),
      table(new QTableWidget),
      name(new QLineEdit),
      pDefaultGenerator(new QComboBox),
      iStateToSetAs(new QSpinBox),
      iStateToSetAsBind(new QComboBox),
      iPriority(new QSpinBox),
      iPriorityBind(new QComboBox)
{
    setTitle("BSiStateTaggingGenerator");
    table->setRowCount(4);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(headerLabels1);
    table->setCellWidget(0, 0, name);
    table->setItem(0, 1, new QTableWidgetItem("String"));
    table->setItem(0, 2, new QTableWidgetItem("N/A"));
    table->setItem(0, 3, new QTableWidgetItem("N/A"));
    table->setItem(1, 0, new QTableWidgetItem("pDefaultGenerator"));
    table->setItem(1, 1, new QTableWidgetItem("hkbGenerator"));
    table->setCellWidget(1, 2, pDefaultGenerator);
    table->setItem(2, 0, new QTableWidgetItem("iStateToSetAs"));
    table->setItem(2, 1, new QTableWidgetItem("Int"));
    table->setCellWidget(2, 2, iStateToSetAsBind);
    table->setCellWidget(2, 3, iStateToSetAs);
    table->setItem(3, 0, new QTableWidgetItem("iPriority"));
    table->setItem(3, 1, new QTableWidgetItem("Int"));
    table->setCellWidget(3, 2, iPriorityBind);
    table->setCellWidget(3, 3, iPriority);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    lyt->addWidget(table);
    setLayout(lyt);
    //connect(name, SIGNAL(editingFinished()), this, SLOT(setName()));
    //connect(pDefaultGenerator, SIGNAL(activated(int)), this, SLOT(setDefaultGenerator(int)));
    //connect(iStateToSetAs, SIGNAL(editingFinished()), this, SLOT(setIStateToSetAs()));
    //connect(iPriority, SIGNAL(editingFinished()), this, SLOT(setIPriority()));
    //connect(iStateToSetAsBind, SIGNAL(activated(int)), this, SLOT(setIStateToSetAsBind(int)));
    //connect(iPriorityBind, SIGNAL(activated(int)), this, SLOT(setIPriorityBind(int)));
}

void BSiStateTaggingGeneratorUI::addVariableToLists(const QString & name){
    //dis//connect(iStateToSetAsBind, 0, this, 0);
    //dis//connect(iPriorityBind, 0, this, 0);
    iStateToSetAsBind->insertItem(iStateToSetAsBind->count(), name);
    iPriorityBind->insertItem(iPriorityBind->count(), name);
    //connect(iStateToSetAsBind, SIGNAL(activated(int)), this, SLOT(setIStateToSetAsBind(int)));
    //connect(iPriorityBind, SIGNAL(activated(int)), this, SLOT(setIPriorityBind(int)));
}

void BSiStateTaggingGeneratorUI::removeVariableFromLists(int index){
    index++;
    if (iStateToSetAsBind->currentIndex() == index){
        iStateToSetAsBind->setCurrentIndex(0);
    }
    iStateToSetAsBind->removeItem(index);
    if (iPriorityBind->currentIndex() == index){
        iPriorityBind->setCurrentIndex(0);
    }
    iPriorityBind->removeItem(index);
}

void BSiStateTaggingGeneratorUI::renameVariableInLists(const QString & newName, int index){
    index++;
    iStateToSetAsBind->setItemText(index, newName);
    iPriorityBind->setItemText(index, newName);
}

void BSiStateTaggingGeneratorUI::addGeneratorToLists(const QString & name){
    //dis//connect(pDefaultGenerator, 0, this, 0);
    pDefaultGenerator->insertItem(pDefaultGenerator->count(), name);
    //connect(pDefaultGenerator, SIGNAL(activated(int)), this, SLOT(setDefaultGenerator(int)));
}

void BSiStateTaggingGeneratorUI::removeGeneratorFromLists(int index){
    //dis//connect(pDefaultGenerator, 0, this, 0);
    pDefaultGenerator->removeItem(index);
    //connect(pDefaultGenerator, SIGNAL(activated(int)), this, SLOT(setDefaultGenerator(int)));
}

void BSiStateTaggingGeneratorUI::renameGeneratorInLists(const QString & name, int index){
    index++;
    pDefaultGenerator->setItemText(index, name);
}

void BSiStateTaggingGeneratorUI::setName(){
    if (bsData){
        bsData->name = name->text();
        bsData->updateIconNames();
        emit generatorNameChanged(name->text(), bsData->getParentFile()->getIndexOfGenerator(bsData) + 1);
    }
}

void BSiStateTaggingGeneratorUI::setIStateToSetAs(){
    if (bsData){
        bsData->iStateToSetAs = iStateToSetAs->value();
    }
}

void BSiStateTaggingGeneratorUI::setIPriority(){
    if (bsData){
        bsData->iPriority = iPriority->value();
    }
}

void BSiStateTaggingGeneratorUI::setIStateToSetAsBind(int index){
    if (bsData){
        //dis//connect(iStateToSetAsBind, 0, this, 0);
        hkbVariableBindingSet *varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
        if (behaviorView->behavior->getVariableTypeAt(index - 1) == VARIABLE_TYPE_INT32){
            if (!varBind){
                varBind = new hkbVariableBindingSet(behaviorView->behavior);
                bsData->variableBindingSet = HkxObjectExpSharedPtr(varBind);
                behaviorView->behavior->addObjectToFile(varBind);
            }
            varBind->addBinding("iStateToSetAs", index - 1);
        }else{
            QMessageBox msg;
            msg.setText("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to bind a variable of an invalid type for this data field!!!");
            msg.exec();
            if (varBind){
                //dis//connect(iStateToSetAsBind, 0, this, 0);
                int ind = varBind->getVariableIndexOfBinding("iStateToSetAs");
                if (ind > -1 && ind < iStateToSetAsBind->count()){
                    iStateToSetAsBind->setCurrentIndex(ind + 1);
                }
            }
        }
        //connect(iStateToSetAsBind, SIGNAL(activated(int)), this, SLOT(setIStateToSetAsBind(int)));
    }
}

void BSiStateTaggingGeneratorUI::setIPriorityBind(int index){
    if (bsData){
        //dis//connect(iPriorityBind, 0, this, 0);
        hkbVariableBindingSet *varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
        if (behaviorView->behavior->getVariableTypeAt(index - 1) == VARIABLE_TYPE_INT32){
            if (!varBind){
                varBind = new hkbVariableBindingSet(behaviorView->behavior);
                bsData->variableBindingSet = HkxObjectExpSharedPtr(varBind);
                behaviorView->behavior->addObjectToFile(varBind);
            }
            varBind->addBinding("iPriority", index - 1);
        }else{
            QMessageBox msg;
            msg.setText("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to bind a variable of an invalid type for this data field!!!");
            msg.exec();
            if (varBind){
                //dis//connect(iPriorityBind, 0, this, 0);
                int ind = varBind->getVariableIndexOfBinding("iPriority");
                if (ind > -1 && ind < iPriorityBind->count()){
                    iPriorityBind->setCurrentIndex(ind + 1);
                }
            }
        }
        //connect(iPriorityBind, SIGNAL(activated(int)), this, SLOT(setIPriorityBind(int)));
    }
}

void BSiStateTaggingGeneratorUI::setDefaultGenerator(int index){
    if (behaviorView && index > -1 && index < pDefaultGenerator->count()){
        HkxObject *ptr = bsData->getParentFile()->getGeneratorDataAt(index - 1);
        if (!ptr || ptr == bsData || !behaviorView->reconnectBranch(bsData->pDefaultGenerator.data(), ptr, behaviorView->getSelectedItem())){
            QMessageBox msg;
            msg.setText("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to create a circular branch or dead end!!!");
            msg.exec();
            int i = bsData->getParentFile()->getIndexOfGenerator(bsData->pDefaultGenerator);
            i++;
            //dis//connect(pDefaultGenerator, 0, this, 0);
            pDefaultGenerator->setCurrentIndex(i);
            //connect(pDefaultGenerator, SIGNAL(activated(int)), this, SLOT(setGenerator(int)));
            return;
        }
        if (index > 0){
            bsData->pDefaultGenerator = HkxObjectExpSharedPtr(ptr);
            behaviorView->removeGeneratorData();
        }
    }
}

void BSiStateTaggingGeneratorUI::loadComboBoxes(){
    QStringList genList = behaviorView->behavior->getGeneratorNames();
    genList.prepend("None");
    pDefaultGenerator->insertItems(0, genList);
}

void BSiStateTaggingGeneratorUI::loadData(HkxObject *data){
    if (data && data->getSignature() == BS_I_STATE_TAGGING_GENERATOR){
        bsData = static_cast<BSiStateTaggingGenerator *>(data);
        name->setText(bsData->name);
        //dis//connect(pDefaultGenerator, 0, this, 0);
        /*if (pDefaultGenerator->count() == 0){
            QStringList genList = bsData->getParentFile()->getGeneratorNames();
            genList.prepend("None");
            pDefaultGenerator->insertItems(0, genList);
        }*/
        int index = bsData->getParentFile()->getIndexOfGenerator(bsData->pDefaultGenerator) + 1;
        pDefaultGenerator->setCurrentIndex(index);
        //connect(pDefaultGenerator, SIGNAL(activated(int)), this, SLOT(setGenerator(int)));
    }
}
