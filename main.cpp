//
//  main.cpp
//  design pattern-undo redo
//
//  Created by 程之远 on 2016/12/6.
//  Copyright © 2016年 程之远. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>

#include "UndoableEdit.h"
#include "AbstractUndoableEdit.h"
#include "UndoableEditListenerAndEvent.h"
#include "CompoundEdit.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////
//UndoManager
////////////////////////////////////////////////////////////////////////////

class UndoManager : public CompoundEdit, public UndoableEditListener{
private:
    int indexOfNextAdd;
//    int limit;           //限制不要了
public:
    UndoManager(): indexOfNextAdd(0){}
    void undo();
    bool canUndo();
    void redo();
    bool canRedo();
    void die(){};
    void addEdit(UndoableEdit* anEdit);
    void UndoableEditHappened(UndoableEditEvent* uee);
protected:
    void trimEdits(int from);
};

void UndoManager::undo(){
    if(canUndo() == false) return;
    list<UndoableEdit*>::iterator ite = edits.begin();
    for(int i = 1; i != indexOfNextAdd; i++){              //ite移到indexOfNextAdd
        ite++;
    }
    (*ite)->undo();
    indexOfNextAdd--;
}

bool UndoManager::canUndo(){
    if(indexOfNextAdd == 0)
        return false;
    else
        return true;
}

void UndoManager::redo(){
    if(canRedo() == false) return;
    list<UndoableEdit*>::iterator ite = edits.begin();
    for(int i = 0; i != indexOfNextAdd; i++){              //ite移到indexOfNextAdd的后面一个
        ite++;
    }
    (*ite)->redo();
    indexOfNextAdd++;
}

bool UndoManager::canRedo(){
    if(indexOfNextAdd == edits.size())
        return false;
    else
        return true;
}

void UndoManager::addEdit(UndoableEdit* anEdit){
    trimEdits(indexOfNextAdd);
    edits.push_back(anEdit);
}

void UndoManager::UndoableEditHappened(UndoableEditEvent* uee){
    addEdit(uee->getEdit());
    indexOfNextAdd++;
}

void UndoManager::trimEdits(int from){
    list<UndoableEdit*>::iterator ite = edits.begin();
    for(int i = 0; i != from; i++){              //ite移到indexOfNextAdd的后面一个
        ite++;
    }
    while(ite != edits.end()){
        ite = edits.erase(ite);
    }
}

////////////////////////////////////////////////////////////////////////////
//UndoableEditSupport
////////////////////////////////////////////////////////////////////////////

class UndoableEditSupport{
protected:
    int updateLevel;
    CompoundEdit* compoundEdit = new CompoundEdit();
    list<UndoableEditListener*> listeners;
    
//    void _postEdit(UndoableEdit e);                //意义何在？
    CompoundEdit* createCompoundEdit();
public:
    UndoableEditSupport(){};
    void addUndoableEditListener(UndoableEditListener* i);
    void removeUndoableEditListener(UndoableEditListener* i);
    UndoableEditListener getUndoableEditListeners();
    void postEdit(UndoableEdit* e);
    int getUpdateLevel();
    void beginUpdate();
    void endUpdate();
    string toString();
};

void UndoableEditSupport::postEdit(UndoableEdit* e){
    UndoableEditEvent* uee = new UndoableEditEvent(e);
    list<UndoableEditListener*>::iterator ite = listeners.begin();
    for(; ite != listeners.end(); ite++){
        (*ite)->UndoableEditHappened(uee);
    }
}

void UndoableEditSupport::addUndoableEditListener(UndoableEditListener* i){
    listeners.push_back(i);
}


////////////////////////////////////////////////////////////////////////////
//MyEdit
////////////////////////////////////////////////////////////////////////////

class MyEdit{
protected:
    UndoableEditSupport* ues = new UndoableEditSupport();
    list<string> s;
public:
    MyEdit(){}
    void setStrList(list<string> ss);
    list<string> getStrList();
    UndoableEditSupport* getUES();
    void addUndoableEditListener(UndoableEditListener* uel);
    void outstr();
};

void MyEdit::setStrList(list<string> ss){
    s = ss;
}

list<string> MyEdit::getStrList(){
    return s;
}

UndoableEditSupport* MyEdit::getUES(){
    return ues;
}

void MyEdit::addUndoableEditListener(UndoableEditListener* uel){
    ues->addUndoableEditListener(uel);
}

void MyEdit::outstr(){
    list<string>::iterator ite = s.begin();
    for(; ite != s.end(); ite++){
        cout << *ite << " ";
    }
}

////////////////////////////////////////////////////////////////////////////
//myUndoableEdit
////////////////////////////////////////////////////////////////////////////


class myUndoableEdit: public AbstractUndoableEdit{
private:
    MyEdit* myEdit;
    list<string> str;                       //记录操作后的最新状况
public:
    myUndoableEdit(MyEdit* me);
    void undo();
    void redo();

};

myUndoableEdit::myUndoableEdit(MyEdit* me){
    myEdit = me;
    str = me->getStrList();
}

void myUndoableEdit::undo(){
    AbstractUndoableEdit::undo();
    list<string> s = str;
    list<string>::iterator ite = s.end();                //删除最后一个字符串
    ite--;
    s.erase(ite);
    myEdit->setStrList(s);
}

void myUndoableEdit::redo(){
    AbstractUndoableEdit::redo();
    myEdit->setStrList(str);
}


////////////////////////////////////////////////////////////////////////////


int main(int argc, const char * argv[]) {
    cout << "*********************************************\n"
         << "********    1.input(end with '$')   *********\n"
         << "********    2.undo                  *********\n"
         << "********    3.redo                  *********\n"
         << "********    4.quit                  *********\n"
         << "*********************************************\n"
         <<endl;
    MyEdit* myEdit = new MyEdit();
    UndoManager* manager = new UndoManager();
    myEdit->addUndoableEditListener(manager);
    list<string> s;              //文本，undo、redo的主要对象，存到myEdit里
    string str;                  //暂存文本中的字符串
    int func = 0;                 //功能号
    
    while(func != 4){
        cout << "请输入功能号：";
        cin >> func;
        switch (func) {
            case 1:{
                cout << "请输入文本：" <<endl;
                myEdit->outstr();
                while(true){
                    cin >> str;
                    if(str[str.length()-1] == '$'){
                        if(str.length() > 1){                 //如果字符串以‘$’结尾，则去掉‘$’，加到字符串数组中
                            str.erase(str.length()-1);
                            s.push_back(str);
                            myEdit->setStrList(s);
                            myUndoableEdit* mue = new myUndoableEdit(myEdit);
                            myEdit->getUES()->postEdit(mue);
                        }
                        break;       //输入‘$’表示文本输入结束
                    }
                    s.push_back(str);
                    myEdit->setStrList(s);
                    myUndoableEdit* mue = new myUndoableEdit(myEdit);
                    myEdit->getUES()->postEdit(mue);
                }
            }break;
            case 2:{
                manager->undo();
                s = myEdit->getStrList();
                myEdit->outstr();
                cout << endl;
            }break;
            case 3:{
                manager->redo();
                s = myEdit->getStrList();
                myEdit->outstr();
                cout << endl;
            }break;
            case 4:
                break;
            default:
                break;
        }
    }
    
    return 0;
}
