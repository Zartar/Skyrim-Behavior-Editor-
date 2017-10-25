#include "bstweenermodifierui.h"

#include "src/hkxclasses/hkxobject.h"
#include "src/hkxclasses/behavior/modifiers/BSTweenerModifier.h"
#include "src/hkxclasses/behavior/hkbvariablebindingset.h"
#include "src/filetypes/behaviorfile.h"
#include "src/ui/genericdatawidgets.h"

#include <QGridLayout>
#include <QHeaderView>

#define BASE_NUMBER_OF_ROWS 8

#define NAME_ROW 0
#define ENABLE_ROW 1
#define TWEEN_POSITION_ROW 2
#define TWEEN_ROTATION_ROW 3
#define USE_TWEEN_DURATION_ROW 4
#define TWEEN_DURATION_ROW 5
#define TARGET_POSITION_ROW 6
#define TARGET_ROTATION_ROW 7

#define NAME_COLUMN 0
#define TYPE_COLUMN 1
#define BINDING_COLUMN 2
#define VALUE_COLUMN 3

#define BINDING_ITEM_LABEL QString("Use Property     ")

QStringList BSTweenerModifierUI::headerLabels = {
    "Name",
    "Type",
    "Bound Variable",
    "Value"
};

BSTweenerModifierUI::BSTweenerModifierUI()
    : bsData(NULL),
      topLyt(new QGridLayout),
      table(new TableWidget(QColor(Qt::white))),
      name(new LineEdit),
      enable(new CheckBox),
      tweenPosition(new CheckBox),
      tweenRotation(new CheckBox),
      useTweenDuration(new CheckBox),
      tweenDuration(new DoubleSpinBox),
      targetPosition(new QuadVariableWidget),
      targetRotation(new QuadVariableWidget)
{
    setTitle("BSTweenerModifier");
    table->setRowCount(BASE_NUMBER_OF_ROWS);
    table->setColumnCount(headerLabels.size());
    table->setHorizontalHeaderLabels(headerLabels);
    table->setItem(NAME_ROW, NAME_COLUMN, new TableWidgetItem("name"));
    table->setItem(NAME_ROW, TYPE_COLUMN, new TableWidgetItem("hkStringPtr", Qt::AlignCenter));
    table->setItem(NAME_ROW, BINDING_COLUMN, new TableWidgetItem("N/A", Qt::AlignCenter));
    table->setCellWidget(NAME_ROW, VALUE_COLUMN, name);
    table->setItem(ENABLE_ROW, NAME_COLUMN, new TableWidgetItem("enable"));
    table->setItem(ENABLE_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(ENABLE_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(ENABLE_ROW, VALUE_COLUMN, enable);
    table->setItem(TWEEN_POSITION_ROW, NAME_COLUMN, new TableWidgetItem("tweenPosition"));
    table->setItem(TWEEN_POSITION_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(TWEEN_POSITION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(TWEEN_POSITION_ROW, VALUE_COLUMN, tweenPosition);
    table->setItem(TWEEN_ROTATION_ROW, NAME_COLUMN, new TableWidgetItem("tweenRotation"));
    table->setItem(TWEEN_ROTATION_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(TWEEN_ROTATION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(TWEEN_ROTATION_ROW, VALUE_COLUMN, tweenRotation);
    table->setItem(USE_TWEEN_DURATION_ROW, NAME_COLUMN, new TableWidgetItem("useTweenDuration"));
    table->setItem(USE_TWEEN_DURATION_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(USE_TWEEN_DURATION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(USE_TWEEN_DURATION_ROW, VALUE_COLUMN, useTweenDuration);
    table->setItem(TWEEN_DURATION_ROW, NAME_COLUMN, new TableWidgetItem("tweenDuration"));
    table->setItem(TWEEN_DURATION_ROW, TYPE_COLUMN, new TableWidgetItem("hkReal", Qt::AlignCenter));
    table->setItem(TWEEN_DURATION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(TWEEN_DURATION_ROW, VALUE_COLUMN, tweenDuration);
    table->setItem(TARGET_POSITION_ROW, NAME_COLUMN, new TableWidgetItem("targetPosition"));
    table->setItem(TARGET_POSITION_ROW, TYPE_COLUMN, new TableWidgetItem("hkVector4", Qt::AlignCenter));
    table->setItem(TARGET_POSITION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(TARGET_POSITION_ROW, VALUE_COLUMN, targetPosition);
    table->setItem(TARGET_ROTATION_ROW, NAME_COLUMN, new TableWidgetItem("targetRotation"));
    table->setItem(TARGET_ROTATION_ROW, TYPE_COLUMN, new TableWidgetItem("hkQuaternion", Qt::AlignCenter));
    table->setItem(TARGET_ROTATION_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(TARGET_ROTATION_ROW, VALUE_COLUMN, targetRotation);
    topLyt->addWidget(table, 0, 0, 8, 3);
    setLayout(topLyt);
}

void BSTweenerModifierUI::connectSignals(){
    connect(name, SIGNAL(editingFinished()), this, SLOT(setName()), Qt::UniqueConnection);
    connect(enable, SIGNAL(released()), this, SLOT(setEnable()), Qt::UniqueConnection);
    connect(tweenPosition, SIGNAL(released()), this, SLOT(setTweenPosition()), Qt::UniqueConnection);
    connect(tweenRotation, SIGNAL(released()), this, SLOT(setTweenRotation()), Qt::UniqueConnection);
    connect(useTweenDuration, SIGNAL(released()), this, SLOT(setUseTweenDuration()), Qt::UniqueConnection);
    connect(tweenDuration, SIGNAL(editingFinished()), this, SLOT(setTweenDuration()), Qt::UniqueConnection);
    connect(targetPosition, SIGNAL(editingFinished()), this, SLOT(setTargetPosition()), Qt::UniqueConnection);
    connect(targetRotation, SIGNAL(editingFinished()), this, SLOT(setTargetRotation()), Qt::UniqueConnection);
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)), Qt::UniqueConnection);
}

void BSTweenerModifierUI::disconnectSignals(){
    disconnect(name, SIGNAL(editingFinished()), this, SLOT(setName()));
    disconnect(enable, SIGNAL(released()), this, SLOT(setEnable()));
    disconnect(tweenPosition, SIGNAL(released()), this, SLOT(setTweenPosition()));
    disconnect(tweenRotation, SIGNAL(released()), this, SLOT(setTweenRotation()));
    disconnect(useTweenDuration, SIGNAL(released()), this, SLOT(setUseTweenDuration()));
    disconnect(tweenDuration, SIGNAL(editingFinished()), this, SLOT(setTweenDuration()));
    disconnect(targetPosition, SIGNAL(editingFinished()), this, SLOT(setTargetPosition()));
    disconnect(targetRotation, SIGNAL(editingFinished()), this, SLOT(setTargetRotation()));
    disconnect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)));
}

void BSTweenerModifierUI::connectToTables(GenericTableWidget *variables, GenericTableWidget *properties){
    if (variables && properties){
        disconnect(variables, SIGNAL(elementSelected(int,QString)), 0, 0);
        disconnect(properties, SIGNAL(elementSelected(int,QString)), 0, 0);
        connect(variables, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(properties, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewVariables(int)), variables, SLOT(showTable(int)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewProperties(int)), properties, SLOT(showTable(int)), Qt::UniqueConnection);
    }else{
        (qFatal("BSTweenerModifierUI::connectToTables(): One or more arguments are NULL!!"));
    }
}

void BSTweenerModifierUI::loadData(HkxObject *data){
    disconnectSignals();
    if (data){
        if (data->getSignature() == BS_TWEENER_MODIFIER){
            hkbVariableBindingSet *varBind = NULL;
            bsData = static_cast<BSTweenerModifier *>(data);
            name->setText(bsData->name);
            enable->setChecked(bsData->enable);
            tweenPosition->setChecked(bsData->tweenPosition);
            tweenRotation->setChecked(bsData->tweenRotation);
            useTweenDuration->setChecked(bsData->useTweenDuration);
            tweenDuration->setValue(bsData->tweenDuration);
            targetPosition->setValue(bsData->targetPosition);
            targetRotation->setValue(bsData->targetRotation);
            varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
            if (varBind){
                loadBinding(ENABLE_ROW, BINDING_COLUMN, varBind, "enable");
                loadBinding(TWEEN_POSITION_ROW, BINDING_COLUMN, varBind, "tweenPosition");
                loadBinding(TWEEN_ROTATION_ROW, BINDING_COLUMN, varBind, "tweenRotation");
                loadBinding(USE_TWEEN_DURATION_ROW, BINDING_COLUMN, varBind, "useTweenDuration");
                loadBinding(TWEEN_DURATION_ROW, BINDING_COLUMN, varBind, "tweenDuration");
                loadBinding(TARGET_POSITION_ROW, BINDING_COLUMN, varBind, "targetPosition");
                loadBinding(TARGET_ROTATION_ROW, BINDING_COLUMN, varBind, "targetRotation");
            }else{
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(TWEEN_POSITION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(TWEEN_ROTATION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(USE_TWEEN_DURATION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(TWEEN_DURATION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(TARGET_POSITION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(TARGET_ROTATION_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
            }
        }else{
            (qFatal("BSTweenerModifierUI::loadData(): The data is an incorrect type!!"));
        }
    }else{
        (qFatal("BSTweenerModifierUI::loadData(): The data is NULL!!"));
    }
    connectSignals();
}

void BSTweenerModifierUI::setName(){
    if (bsData){
        if (bsData->name != name->text()){
            bsData->name = name->text();
            static_cast<DataIconManager*>((bsData))->updateIconNames();
            bsData->getParentFile()->toggleChanged(true);
            emit modifierNameChanged(name->text(), static_cast<BehaviorFile *>(bsData->getParentFile())->getIndexOfModifier(bsData));
        }
    }else{
        (qFatal("BSTweenerModifierUI::setName(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setEnable(){
    if (bsData){
        bsData->enable = enable->isChecked();
        bsData->getParentFile()->toggleChanged(true);
    }else{
        (qFatal("BSTweenerModifierUI::setEnable(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setTweenPosition(){
    if (bsData){
        bsData->tweenPosition = tweenPosition->isChecked();
        bsData->getParentFile()->toggleChanged(true);
    }else{
        (qFatal("BSTweenerModifierUI::settweenPosition(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setTweenRotation(){
    if (bsData){
        bsData->tweenRotation = tweenRotation->isChecked();
        bsData->getParentFile()->toggleChanged(true);
    }else{
        (qFatal("BSTweenerModifierUI::settweenRotation(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setUseTweenDuration(){
    if (bsData){
        bsData->useTweenDuration = useTweenDuration->isChecked();
        bsData->getParentFile()->toggleChanged(true);
    }else{
        (qFatal("BSTweenerModifierUI::setuseTweenDuration(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setTweenDuration(){
    if (bsData){
        if (bsData->tweenDuration != tweenDuration->value()){
            bsData->tweenDuration = tweenDuration->value();
            bsData->getParentFile()->toggleChanged(true);
        }
    }else{
        (qFatal("BSTweenerModifierUI::settweenDuration(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setTargetPosition(){
    if (bsData){
        if (bsData->targetPosition != targetPosition->value()){
            bsData->targetPosition = targetPosition->value();
            bsData->getParentFile()->toggleChanged(true);
        }
    }else{
        (qFatal("BSTweenerModifierUI::settargetPosition(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::setTargetRotation(){
    if (bsData){
        if (bsData->targetRotation != targetRotation->value()){
            bsData->targetRotation = targetRotation->value();
            bsData->getParentFile()->toggleChanged(true);
        }
    }else{
        (qFatal("BSTweenerModifierUI::settargetRotation(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::viewSelected(int row, int column){
    if (bsData){
        bool isProperty = false;
        if (column == BINDING_COLUMN){
            switch (row){
            case ENABLE_ROW:
                if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "enable");
                break;
            case TWEEN_POSITION_ROW:
                if (table->item(TWEEN_POSITION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "tweenPosition");
                break;
            case TWEEN_ROTATION_ROW:
                if (table->item(TWEEN_ROTATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "tweenRotation");
                break;
            case USE_TWEEN_DURATION_ROW:
                if (table->item(USE_TWEEN_DURATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "useTweenDuration");
                break;
            case TWEEN_DURATION_ROW:
                if (table->item(TWEEN_DURATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "tweenDuration");
                break;
            case TARGET_POSITION_ROW:
                if (table->item(TARGET_POSITION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "targetPosition");
                break;
            case TARGET_ROTATION_ROW:
                if (table->item(TARGET_ROTATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "targetRotation");
                break;
            default:
                return;
            }
        }
    }else{
        (qFatal("BSTweenerModifierUI::viewSelected(): The 'bsData' pointer is NULL!!"));
    }
}

void BSTweenerModifierUI::selectTableToView(bool viewisProperty, const QString & path){
    if (bsData){
        if (viewisProperty){
            if (bsData->variableBindingSet.data()){
                emit viewProperties(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewProperties(0);
            }
        }else{
            if (bsData->variableBindingSet.data()){
                emit viewVariables(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewVariables(0);
            }
        }
    }else{
        (qFatal("BSTweenerModifierUI::selectTableToView(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::variableRenamed(const QString & name, int index){
    if (bsData){
        index--;
        hkbVariableBindingSet *bind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
        if (bind){
            int bindIndex = bind->getVariableIndexOfBinding("enable");
            if (bindIndex == index){
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("tweenPosition");
            if (bindIndex == index){
                table->item(TWEEN_POSITION_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("tweenRotation");
            if (bindIndex == index){
                table->item(TWEEN_ROTATION_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("useTweenDuration");
            if (bindIndex == index){
                table->item(USE_TWEEN_DURATION_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("tweenDuration");
            if (bindIndex == index){
                table->item(TWEEN_DURATION_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("targetPosition");
            if (bindIndex == index){
                table->item(TARGET_POSITION_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("targetRotation");
            if (bindIndex == index){
                table->item(TARGET_ROTATION_ROW, BINDING_COLUMN)->setText(name);
            }
        }
    }else{
        (qFatal("BSTweenerModifierUI::variableRenamed(): The 'bsData' pointer is NULL!!"));
    }
}

bool BSTweenerModifierUI::setBinding(int index, int row, const QString &variableName, const QString &path, hkVariableType type, bool isProperty){
    hkbVariableBindingSet *varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
    if (bsData){
        if (index == 0){
            varBind->removeBinding(path);
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
        }else if ((!isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableTypeAt(index - 1) == type) ||
                  (isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyTypeAt(index - 1) == type)){
            if (!varBind){
                varBind = new hkbVariableBindingSet(bsData->getParentFile());
                bsData->variableBindingSet = HkxSharedPtr(varBind);
            }
            if (isProperty){
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY)){
                    (qFatal("BSTweenerModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }else{
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_VARIABLE)){
                    (qFatal("BSTweenerModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+variableName);
            bsData->getParentFile()->toggleChanged(true);
        }else{
            (qWarning("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to bind a variable of an invalid type for this data field!!!"));
        }
    }else{
        (qFatal("BSTweenerModifierUI::setBinding(): The data is NULL!!"));
    }
    return true;
}

void BSTweenerModifierUI::setBindingVariable(int index, const QString &name){
    if (bsData){
        bool isProperty = false;
        int row = table->currentRow();
        switch (row){
        case ENABLE_ROW:
            if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "enable", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case TWEEN_POSITION_ROW:
            if (table->item(TWEEN_POSITION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "tweenPosition", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case TWEEN_ROTATION_ROW:
            if (table->item(TWEEN_ROTATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "tweenRotation", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case USE_TWEEN_DURATION_ROW:
            if (table->item(USE_TWEEN_DURATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "useTweenDuration", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case TWEEN_DURATION_ROW:
            if (table->item(TWEEN_DURATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "tweenDuration", VARIABLE_TYPE_REAL, isProperty);
            break;
        case TARGET_POSITION_ROW:
            if (table->item(TARGET_POSITION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "targetPosition", VARIABLE_TYPE_VECTOR4, isProperty);
            break;
        case TARGET_ROTATION_ROW:
            if (table->item(TARGET_ROTATION_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "targetRotation", VARIABLE_TYPE_QUATERNION, isProperty);
            break;
        default:
            return;
        }
        bsData->getParentFile()->toggleChanged(true);
    }else{
        (qFatal("BSTweenerModifierUI::setBindingVariable(): The data is NULL!!"));
    }
}

void BSTweenerModifierUI::loadBinding(int row, int colunm, hkbVariableBindingSet *varBind, const QString &path){
    if (bsData){
        if (varBind){
            int index = varBind->getVariableIndexOfBinding(path);
            QString varName;
            if (index != -1){
                if (varBind->getBindingType(path) == hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY){
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyNameAt(index, true);
                    table->item(row, colunm)->setCheckState(Qt::Checked);
                }else{
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableNameAt(index);
                }
            }
            if (varName == ""){
                varName = "NONE";
            }
            table->item(row, colunm)->setText(BINDING_ITEM_LABEL+varName);
        }else{
            (qFatal("BSTweenerModifierUI::loadBinding(): The variable binding set is NULL!!"));
        }
    }else{
        (qFatal("BSTweenerModifierUI::loadBinding(): The data is NULL!!"));
    }
}