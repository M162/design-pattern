//
//  AbstractUndoableEdit.h
//  design pattern-undo redo
//
//  Created by 程之远 on 2016/12/12.
//  Copyright © 2016年 程之远. All rights reserved.
//

#ifndef AbstractUndoableEdit_h
#define AbstractUndoableEdit_h


#endif /* AbstractUndoableEdit_h */

#include <string>
#include <list>

//#include "UndoableEdit.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
//抽象基类AbstractUndoableEdit
////////////////////////////////////////////////////////////////////////////

class AbstractUndoableEdit : public UndoableEdit{
private:
    string undoName;
    string redoName;
    bool hasBeenDone;
    bool alive;
public:
    AbstractUndoableEdit(): hasBeenDone(true), alive(true){}
    virtual void undo();
    virtual bool canUndo();
    virtual void redo();
    virtual bool canRedo();
    virtual void die();
    virtual void addEdit(UndoableEdit* anEdit){};
};

void AbstractUndoableEdit::undo(){
    hasBeenDone = false;
}

bool AbstractUndoableEdit::canUndo(){
    if(hasBeenDone == true)
        return true;
    else
        return false;
}

void AbstractUndoableEdit::redo(){
    hasBeenDone = true;
}

bool AbstractUndoableEdit::canRedo(){
    if(hasBeenDone == true)
        return false;
    else
        return true;
}
void AbstractUndoableEdit::die(){
    alive = false;
}

