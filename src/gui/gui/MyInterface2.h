#ifndef MyInterface2_h
#define MyInterface2_h

//���ͷ�ļ�д�ڶ���ʵ�����Ҫ�ӿ�

#include "MyInterface.h"
#include "MyHtmLInfo.h"
#include "MyPageList.h"
#include "MyHashTable.h"
#include "MyHtmLInfo.h"

#include <windows.h>
using namespace std;

//initDictionary(...):�ýӿ�ִ������ʿ�ȳ�ʼ������,���ѽ������Ϊһ��AVL��
//�������Ƚ���AVL����Hash���Ч�ʣ�ѡ����ʹ��Hash�����洢�ʵ�
MyAVLTree<MyString>* AVL_initDictionary();

//������ɵ�AVL����ÿ�ֳ�һ�����ʣ��Ͱ����ӵ�AVL��������
//����ӿ�ʵ�ִַʺ�ʵʱ�Ѵʼ���AVL��
void test2_divideAndInsertWords(MyHashTable* myHash, MyString& myString, MyAVLTree<MyString>* myAVL, int docID);


//ֱ�Ӷ�ȡ500����ҳ����Ϣ���õ����ǵķִʽ�������÷ֵĴ�ȥ�����Ż�AVL���еĽڵ�
MyAVLTree<MyString>* AVL_HandleAllHtml(MyHashTable* myHash);

//���Ѿ�����������ҳ����Ϣȥ�õ��ִʲ�����AVL��
MyAVLTree<MyString>* AVL_GetInfoFromSavedHtml(MyHtmLInfo* myList, MyHashTable* myHash);

//��ÿ�δ�query�ж�ȡ��һ�з���һ�����
void line_to_result(MyAVLTree<MyString>* tree, wstring& line, MyHashTable* myHash, wostream& output);

//�������ʵ�ֶ�ȡquery.txt�ļ�������������result.txt�ļ��Ĺ���
void query_to_result();

void query_to_result2();

//stringת��Ϊwstring
std::wstring  StringToWString(const std::string& s);



#endif