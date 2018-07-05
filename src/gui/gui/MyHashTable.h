#ifndef MyHashTable_h
#define MyHashTable_h

#include<iostream>
#include<string>

using namespace std;

//����һ���ַ�������Ӧ�õ�һ����ϣֵ
int GetHash(wstring string);

struct hashNode
{
	hashNode* next;
	wstring data;
	hashNode():next(NULL),data(L""){}
	hashNode(wstring this_string):next(NULL),data(this_string){}
};

class MyHashTable
{

public:
	//Ĭ�Ϲ��캯��
	MyHashTable();

	//��ַ�������
	int max_len;

	//hash�������
	hashNode* hashNodeList ;

	//��ʼ��Hash��ʱ������Hashֵ
	void addHashValue(wstring newString);

	//����ʱ���ж��Ƿ��ڴʿ���
	int findHashValue(wstring newString);

private:

};



#endif