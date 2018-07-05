#ifndef ReadFile_h
#define ReadFile_h

#include "MyString.h"
#include "MyStringLinkedList.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <io.h>


using namespace std;

//用文件名读取单个html文件，返回MyString
MyString read_Html(char* filename);
//读取所有html文件，返回一个字符串链表
MyStringLinkedList* readFile();

#endif