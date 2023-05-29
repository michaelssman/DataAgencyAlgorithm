//
//  dsf.cpp
//  HHDataAgencyAlgorithmCPP
//
//  Created by Michael on 2023/4/28.
//

#include "dsf.hpp"
#include <string>
#include <iostream>
#include <fstream>//读文件
#include <cassert>
using namespace std;

//堆栈里的数据都是Object。
class Object
{
public:
    /**
     - 只有一个纯虚析构函数，用它来做接口使用。用的时候通过继承就可以使用堆栈了。
     - 纯虚析构函数必须写一个纯虚定义
     */
    virtual ~Object() = 0;
};

inline Object::~Object() {}

class Stack
{
    class Link
    {
    public:
        Object* data;
        Link* next;
        Link(Object* dat, Link* nxt) : data(dat), next (nxt){}
        ~Link() {}
    }* head;
public:
    Stack() : head(0) { }
    ~Stack()
    {
        while (head)
            delete pop();
    }
    void push(Object* dat)
    {
        head = new Link(dat, head);
    }
    Object* pop()
    {
        if(head == 0) return 0;
        Object* result = head->data;
        Link* oldHead = head;
        head = head->next;
        delete oldHead;
        return result;
    }
    Object* peek ()
    {
        //如果是空的就返回0，不是空的就返回堆栈中的数据
        return head ? head->data : 0;
    }
};


/**
 测试：
 
 需要做一个StringObject继承Object还要继承String
 
 继承Object，则都可以放到堆栈里。
 
 需要给它写一个析构函数，析构函数里看到被调用了被析构delete了。
 
 构造函数：传一个字符串，调用基类的构造函数。
 */
class StringObj : public Object, public string
{
public:
    ~StringObj ()
    {
        cout << "deleting string: " << *this << endl;
    }
    StringObj(string s) : string(s) {}
};

void testhhh()
{
    ifstream in("Test.cpp");//输入文件流
    
    Stack textlines;
    
    string line;
    //读到的每一个行都放到堆栈里
    while (getline(in, line)) {
        textlines.push(new StringObj(line));
    }
    
    StringObj *s;
    //    //输出每一行，结果是倒序的
    //    while ((s = (StringObj *)textlines.pop()) != 0) {
    //        cout << *s << endl;
    //        delete s;
    //    }
    
    //读取10行，把这10行进行delete。堆栈里剩下的数据会在函数结束的时候，堆栈析构，析构函数里会析构。
    for(int i = 0; i < 10; i++) {
        if((s = (StringObj*)textlines.pop()) == 0) break;
        cout << *s << endl;
        delete s;
    }
}
