//
//  MyInterface.h
//  Chinese_Divider2
//
//  Created by ShaoYushan on 2016/11/12.
//  Copyright © 2016年 邵钰杉. All rights reserved.
//

#ifndef MyInterface_h
#define MyInterface_h

#include "MyStack.h"
#include "MyString.h"
#include "MyStringLinkedList.h"
#include "MyHashTable.h"
#include "MyAVL.h"

#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <fstream>
#include <locale>

using namespace std;

//判断字符串中是否含有关键字,均是非嵌套情况，0代表没有，1代表文章标题、2代表问题名称、3代表作者
int int_myString_conclude_keywords(MyString& current_string);

//判断字符串中是否含有关键字以及之后的处理,非嵌套情况
MyString MyString_conclude_keywords(MyString& current_string);

//每一个转义字符对应一个wchar_t字符
wchar_t escapeCharacter_to_wchar(MyString& testString);

//将输入string中的转义字符去掉
MyString delete_escapeCharacter(MyString& targetString);

//extractInfo()该接口执行解析网页操作，返回结果为一个字符串链表,每一个节点包含一个网页的一个信息
MyStringLinkedList* extractInfo(MyStringNode* current_node);

//initDictionary(...):该接口执行载入词库等初始化操作
MyHashTable* Hash_initDictionary();

//divideWords(...):该接口执行分词操作，返回结果保存为字符串链表
MyStringLinkedList* divideWords(MyHashTable* myHash, MyString& myString);



#endif /* MyInterface_h */
