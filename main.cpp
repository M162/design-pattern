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
#include <string>

using namespace std;


class object{
public:
    virtual bool getChanged(){return false;};
    virtual void update(object*){};
};

class observer;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

class observable: public object{
private:                    //protected?
    list<object*> list_obs;                       //object链表
    bool changed;                                  //保存observerble的状态
    string name;
public:
    observable(string s): changed(false), name(s){}
    
    string getName(){return name;}
    
    void notify();                                 //通知
    void addobs(object*);                         //添加观察者
    void deleteobs(object*);                      //删除观察者
    void update(object* o);                         //更新object链表
    
    void setChanged(bool);                     //设置状态
    bool getChanged();                     //得到状态
};

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

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

class observer: public object{
private:
    string name;
public:
    string getName(){return name;}
    
    observer(string s): name(s){}
    void update(object*);
    
};

void observer::update(object* o){
    if(o == NULL)
        return;
    bool b;
    b = o->getChanged();
    if(b == true)
        cout << name << ": true\n";
    else
        cout << name << ": false\n";
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

observable* getObservable(list<observable*> observableList, string name){
    list<observable*>::iterator ite = observableList.begin();
    for(; ite != observableList.end(); ite++){
        if(!(((*ite)->getName()).compare(name)))
            return *ite;
    }
    return NULL;
}

observer* getObserver(list<observer*> observerList, string name){
    list<observer*>::iterator ite = observerList.begin();
    for(; ite != observerList.end(); ite++){
        if(!(((*ite)->getName()).compare(name)))
            return *ite;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    cout << "*********************************************\n"
         << "********    1.establish observable  *********\n"
         << "********    2.establish observer    *********\n"
         << "********    3.add                   *********\n"
         << "********    4.notify_true           *********\n"
         << "********    5.notify_false          *********\n"
         << "********    6.quit                  *********\n"
         << "*********************************************\n"
         <<endl;
    
    list<observer*> observerList;
    list<observable*> observableList;
    
    observable* oa;
    observer* o;
    observable* o2;
    
    int func = 0;
    string name;
    
    while(func != 6){
        cout << "请输入功能号：";
        cin >> func;
        switch (func) {
            case 1:{
                cout << "请输入名称：";
                cin >> name;
                observable* o = new observable(name);
                observableList.push_back(o);
            }break;
            case 2:{
                cout << "请输入名称：";
                cin >> name;
                observer* o = new observer(name);
                observerList.push_back(o);
            }break;
            case 3:{
                cout << "请输入被观察者的名称：";
                cin >> name;
                oa = getObservable(observableList, name);
                if(oa == NULL){
                    cout << "未找到名为"  << name << "的被观察者" <<endl;
                    break;
                } 
                cout << "请输入观察者的名称：";
                cin >> name;
                o = getObserver(observerList, name);
                if(o == NULL){
                    o2 = getObservable(observableList, name);
                    if(o2 == NULL){
                    cout << "未找到名为"  << name << "的观察者" <<endl;
                    break;
                    }
                    else
                        oa->addobs(o2);
                }
                else
                    oa->addobs(o);
            }break;
            case 4:{
                cout << "请输入被观察者名称：";
                cin >> name;
                oa = getObservable(observableList, name);
                if(oa == NULL){
                    cout << "未找到名为"  << name << "的被观察者" <<endl;
                    break;
                }
                else{
                    oa->setChanged(true);
                    oa->notify();
                }
            }break;
            case 5:{
                cout << "请输入被观察者名称：";
                cin >> name;
                oa = getObservable(observableList, name);
                if(oa == NULL){
                    cout << "未找到名为"  << name << "的被观察者" <<endl;
                    break;
                }
                else{
                    oa->setChanged(false);
                    oa->notify();
                }
            }break;
            case 6:
                break;
            default:
                break;
        }
    }
    return 0;
}
