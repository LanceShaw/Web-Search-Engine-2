//
//  MyMyStack.h
//  Chinese_Divider2
//
//  Created by ShaoYushan on 2016/11/11.
//  Copyright © 2016年 邵钰杉. All rights reserved.
//

#ifndef MyStack_h
#define MyStack_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// 栈声明

template<typename T>
class MyStack
{
public:
    //默认构造函数
    MyStack();

    //析构函数
    ~MyStack();

    //入栈
    void push(const T& node);

    //栈顶元素
    T Top();

    //出栈
    void pop();

    //栈的大小
    int size()const;

    //判断栈知否非空
    bool Empty() const;

    //清理
    void clear();

private:

    //栈中结点
    struct MyStackNode
    {
        T data;
        MyStackNode* next;
        MyStackNode(const T& Newdata, MyStackNode* nextNode)
        :data(Newdata),next(nextNode)
        {}
    };

    //栈顶元素
    MyStackNode * top;
    // 防止默认拷贝和默认赋值
    MyStack(const MyStack& rhs);

    //重载 = 运算符
    MyStack& operator=(const MyStack& rhs);

    //栈的大小
    int MyStack_size;
};

template<typename T>
MyStack<T>::MyStack()
:top(nullptr),MyStack_size(0)
{

}

template<typename T>
MyStack<T>::~MyStack()
{
    clear();
}

template<typename T>
void MyStack<T>::push(const T& node)
{
    top = new MyStackNode(node,top);
    MyStack_size ++;
}

template<typename T>
T MyStack<T>::Top()
{
    if (Empty())
    {
        return NULL;
        //_DEBUG_ERROR("Error, MyStack is empty!");
    }
    return top->data;
}

template<typename T>
void MyStack<T>::pop()
{
    if (Empty())
    {
        return ;
        //_DEBUG_ERROR("Error, MyStack is empty!");
    }
    MyStackNode* topOfMyStack = top;
    top = top->next;
    delete topOfMyStack;
    topOfMyStack = nullptr;
    MyStack_size --;
    return;
}

template<typename T>
bool MyStack<T>::Empty() const
{
    return top == nullptr;
}

template<typename T>
void MyStack<T>::clear()
{
    while (top)
    {
        MyStackNode* topOfMyStack = top;
        top = top->next;
        delete topOfMyStack;

    }
    MyStack_size = 0;
}
template<typename T>
int MyStack<T>::size()const
{
    return MyStack_size;
}

void MyStack_test();

#endif /* MyStack_h */
