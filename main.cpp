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

class observer;

///////////抽象基类
class observable{
private:                    //protected?
    list<observer*> list_obs;                       //observer链表
    bool changed;                                  //保存observerble的状态
public:
    observable(): changed(false) {}
    
    void notify();                                 //通知
    void addobs(observer*);                         //添加观察者
    void deleteobs(observer*);                      //删除观察者
    
    virtual void setChanged(bool);                     //设置状态
    virtual bool getChanged();                     //得到状态
};



class observer{
//private:
public:
    observer(){}
    virtual void update(observable*);
    
};


void observable::addobs(observer* o){
    list_obs.push_back(o);
}

void observable::deleteobs(observer* o){                           //再看
    list<observer*>::iterator iter;
    iter = find(list_obs.begin(), list_obs.end(), o);
    if (list_obs.end() != iter)
    {
            list_obs.erase(iter);
    }
}

void observable::notify(){
    list<observer*>::iterator iter1;
    list<observer*>::iterator iter2;
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


void observer::update(observable* o){
    if(o == NULL)                        //自己写判断函数
        return;
    
}
//////////////////////////////////////////////////////////////


int main(int argc, const char * argv[]) {
    cout << "helloworld" << endl;
    return 0;
}
