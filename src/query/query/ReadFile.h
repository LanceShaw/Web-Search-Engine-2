#ifndef ReadFile_h
#define ReadFile_h

#include "MyString.h"
#include "MyStringLinkedList.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <io.h>


using namespace std;

//���ļ�����ȡ����html�ļ�������MyString
MyString read_Html(char* filename);
//��ȡ����html�ļ�������һ���ַ�������
MyStringLinkedList* readFile();

#endif