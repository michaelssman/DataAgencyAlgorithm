//
//  BST.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/5.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "BST.hpp"

using namespace std;

void BSTTest()
{
    BST<int> m;
    Element<int> a,b,c,d,e,f,g,h,i,j,k,l;
    a.key = 5;
    b.key = 3;
    c.key = 11;
    d.key = 3;
    e.key = 15;
    f.key = 2;
    g.key = 8;
    h.key = 22;
    i.key = 20;
    j.key = 9;
//    k.key = 9;
//    l.key = 9;

    cout << endl;
    cout << m.Insert(a) << endl;//a=5
    cout << m.Insert(b) << endl;
    cout << m.Insert(c) << endl;
    cout << m.Insert(d) << endl;
    cout << m.Insert(e) << endl;
    cout << m.Insert(f) << endl;
    cout << m.Insert(g) << endl;
    cout << m.Insert(h) << endl;

    m.display();
    
    BSTNode<int> *p = m.Search(f);
    cout << "找到的是：" << p->data.key << endl;
    
    BSTNode<int> *p2 = m.IterSearch(f);
    cout << "找到的是：" << p2->data.key << endl;

    cout << "\n" << m.Insert(b);
}
