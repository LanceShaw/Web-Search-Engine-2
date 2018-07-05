//
//  MyStringLinkedList.h
//  Chinese_Divider2
//
//  Created by ShaoYushan on 2016/11/11.
//  Copyright © 2016年 邵钰杉. All rights reserved.
//

#ifndef MyStringLinkedList_h
#define MyStringLinkedList_h

#include "MyString.h"
#include "iostream"
using namespace std;

struct MyStringNode
{
    MyString data;//数据域
    MyStringNode* next;//指向下一个的指针
	string filename;//记录文件名称
    MyStringNode(const MyString& input):
    data(input),next(NULL),filename("")
    {
    }
    MyStringNode():
	data(NULL),next(NULL),filename("")
    {
    }
};


class MyStringLinkedList
{
private:

public:

    //链表头
    MyStringNode* head;	

    //链表长度
    int list_size;

    //默认构造函数
    MyStringLinkedList();

    //添加元素
    void add(const MyString& newString);

	//添加元素,记录文件名称
	void add(const MyString& newString,string input_filename);

    //删除元素
    void remove(const MyString& targetString);

    //查找某元素位置
    MyStringNode* search(const MyString& targetString);

};

void MyStringLinkedList_Test();




#endif /* MyStringLinkedList_h */
