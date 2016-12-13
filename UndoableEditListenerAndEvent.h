//
//  UndoableEditListener.h
//  design pattern-undo redo
//
//  Created by 程之远 on 2016/12/12.
//  Copyright © 2016年 程之远. All rights reserved.
//

#ifndef UndoableEditListener_h
#define UndoableEditListener_h


#endif /* UndoableEditListener_h */


////////////////////////////////////////////////////////////////////////////
//UndoableEditEvent
////////////////////////////////////////////////////////////////////////////

class UndoableEditEvent{
private:
    UndoableEdit* myEdit;
public:
    UndoableEditEvent(UndoableEdit* ue): myEdit(ue){}
    UndoableEdit* getEdit();
};

UndoableEdit* UndoableEditEvent::getEdit(){
    return myEdit;
}

////////////////////////////////////////////////////////////////////////////
//UndoableEditListener ：UndoManager的接口
////////////////////////////////////////////////////////////////////////////

class UndoableEditListener{
public:
    UndoableEditListener(){}
    virtual void undo(){};
    virtual bool canUndo(){return NULL;};
    virtual void redo(){};
    virtual bool canRedo(){return NULL;};
    virtual void die(){};
    virtual void addEdit(UndoableEdit* anEdit){};
    virtual void UndoableEditHappened(UndoableEditEvent* e){};
    virtual void addUndoableEditListener(UndoableEditListener uel){};
protected:
    virtual void trimEdits(int from, int to){};
    
};

