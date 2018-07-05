#ifndef MyHtmLInfo_h
#define MyHtmLInfo_h


//����������洢��ҳ����Ϣ
//�������ʵ�ʲ�û��ʹ������࣬��Ϊ�����������ҳ��Ϣ�洢����ʵ����̫����

#include "MyInterface.h"
#include "MyString.h"
#include "MyStringLinkedList.h"
#include "ReadFile.h"

class MyHtmLInfo
{
public:
	int length;//���µ�������
	int int_docID;//���µ�ID
	string fileName;//��������

	MyString title;//���±���
	MyString question;//��������
	MyString author;//��������
	MyString content;//��������
	MyStringLinkedList* words_content;//���ķִʵĽ��

	MyHtmLInfo* next;//ָ����һ���ڵ�
	
	//Ĭ�Ϲ��캯��
	MyHtmLInfo();
	//�����µĽڵ�,��һ���Ѿ����ɵĹ�ϣ��
	void addNewInfo(MyStringNode* p,MyHashTable* myHash);

};

//�����µ�������Ϣ����һ��MyHtmLInfo�Ķ�����
MyHtmLInfo* MyHtmL_GetInfo(MyHashTable* myHash);

#endif