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

//���ļ�����ȡ����html�ļ�������MyString
MyString read_Html1(char* filename);
//��ȡ����html�ļ�������һ���ַ�������
MyStringLinkedList* readFile1();

//QStringתΪMyString
MyString QString_to_myString(QString s);
//MyStringת��ΪQString
QString myString_to_QString(MyString s);

//��һ��ת��ΪMyPageList
MyPageList* searchPageList(MyAVLTree<MyString>* tree, MyStringLinkedList* word_list);

//���ļ�����ȡ����html�ļ�������MyString
MyString read_Html(QString filename);
//��ȡ����html�ļ�������һ���ַ�������
MyStringLinkedList* readFile();


#endif