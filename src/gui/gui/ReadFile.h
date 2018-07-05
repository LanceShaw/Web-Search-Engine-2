#ifndef ReadFile_h
#define ReadFile_h

#include "MyString.h"
#include "MyStringLinkedList.h"
#include "MyPageList.h"
#include "MyAVL.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <io.h>

#include "qfile.h"
#include "qstring.h"
#include "qtextstream.h"
#include "qiodevice.h"
#include "qdir.h"
#include "qdebug.h"

using namespace std;

//用文件名读取单个html文件，返回MyString
MyString read_Html1(char* filename);
//读取所有html文件，返回一个字符串链表
MyStringLinkedList* readFile1();

//QString转为MyString
MyString QString_to_myString(QString s);
//MyString转换为QString
QString myString_to_QString(MyString s);

//把一行转换为MyPageList
MyPageList* searchPageList(MyAVLTree<MyString>* tree, MyStringLinkedList* word_list);

//用文件名读取单个html文件，返回MyString
MyString read_Html(QString filename);
//读取所有html文件，返回一个字符串链表
MyStringLinkedList* readFile();


#endif