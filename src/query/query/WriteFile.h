#ifndef WriteFile_h
#define WriteFile_h

#include <iostream>
#include <fstream>
#include "MyStringLinkedList.h"
#include "MyHtmLInfo.h"

using namespace std;

//��һ��ʵ��ʱдinfo����txt�ļ�
void write_info_or_txt(MyStringLinkedList* list_info, string filename);

//��һ��ʵ��д�ļ�
void test1_write_file();

#endif