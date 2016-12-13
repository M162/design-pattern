//
//  UndoableEdit.h
//  design pattern-undo redo
//
//  Created by 程之远 on 2016/12/12.
//  Copyright © 2016年 程之远. All rights reserved.
//

#ifndef UndoableEdit_h
#define UndoableEdit_h


#endif /* UndoableEdit_h */

#include <string>
#include <list>



using namespace std;


////////////////////////////////////////////////////
//接口UndoableEdit
////////////////////////////////////////////////////

class UndoableEdit{
public:
    UndoableEdit(){};
    virtual ~UndoableEdit(){}
    virtual void undo(){};
    virtual bool canUndo(){ return false; };
    virtual void redo(){};
    virtual bool canRedo(){ return false; };
    virtual void die(){};
    virtual void addEdit(UndoableEdit* anEdit){};
};

