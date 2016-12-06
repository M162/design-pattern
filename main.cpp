//
//  main.cpp
//  design patten-observer
//
//  Created by 程之远 on 2016/11/20.
//  Copyright © 2016年 程之远. All rights reserved.
//

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


class object{
public:
    virtual bool getChanged(){return false;};
    virtual void update(object*){};
};

class observer;

class observable: public object{
private:                    //protected?
    list<object*> list_obs;                       //object链表
    bool changed;                                  //保存observerble的状态
public:
    observable(): changed(false) {}
    
    void notify();                                 //通知
    void addobs(object*);                         //添加观察者
    void deleteobs(object*);                      //删除观察者
    void update(object* o);                         //更新object链表
    
    void setChanged(bool);                     //设置状态
    bool getChanged();                     //得到状态
};



class observer: public object{
public:
    observer(){}
    void update(object*);
    
};

////////////

void observable::addobs(object* o){
    list_obs.push_back(o);
}

void observable::deleteobs(object* o){                           //再看
    list<object*>::iterator iter;
    iter = find(list_obs.begin(), list_obs.end(), o);
    if (list_obs.end() != iter)
    {
            list_obs.erase(iter);
    }
}

void observable::notify(){
    list<object*>::iterator iter1;
    list<object*>::iterator iter2;
    for (iter1 = list_obs.begin(), iter2 = list_obs.end(); iter1 != iter2; ++iter1)
    {
        (*iter1)->update(this);
    }
}

void observable::setChanged(bool b){
    changed = b;
}

bool observable::getChanged(){
    return changed;
}

void observable::update(object* o){
    this->setChanged(o->getChanged());
    this->notify();
}


void observer::update(object* o){
    if(o == NULL)                        //自己写判断函数
        return;
    bool b;
    b = o->getChanged();
    if(b == true)
        cout << "true\n" << endl;
    else
        cout << "false\n" << endl;
    
}
//////////////////////////////////////////////////////////////


int main(int argc, const char * argv[]) {
    observer* o1 = new observer();
    observer* o2 = new observer();
    observable* o3 = new observable();
    observer* o4 = new observer();
    
    o3->addobs(o4);
    
    observable* o = new observable();
    o->addobs(o1);
    o->addobs(o2);
    o->addobs(o3);
    o->setChanged(true);
    o->notify();
    
    o->deleteobs(o1);
    o->setChanged(false);
    o->notify();
    
    system("pause");
    return 0;
}
