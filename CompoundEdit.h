//
//  CompoundEdit.h
//  design pattern-undo redo
//
//  Created by 程之远 on 2016/12/12.
//  Copyright © 2016年 程之远. All rights reserved.
//

#ifndef CompoundEdit_h
#define CompoundEdit_h


#endif /* CompoundEdit_h */

#include <string>
#include <list>

using namespace std;

////////////////////////////////////////////////////////////////////////////
//CompoundEdit
////////////////////////////////////////////////////////////////////////////

class CompoundEdit : public AbstractUndoableEdit{
private:
    bool inProgress;
protected:
    list<UndoableEdit*> edits;
public:
    CompoundEdit(): inProgress(true){}
    virtual void undo(){};                    //先注释掉，回头再看
    virtual bool canUndo(){return NULL;};
    virtual void redo(){};
    virtual bool canRedo(){return NULL;};
    virtual void die(){};

    virtual void addEdit(UndoableEdit* anEdit);
};

void CompoundEdit::addEdit(UndoableEdit* anEdit){
    edits.push_back(anEdit);
}

