#ifndef MyPageList_h
#define MyPageList_h

#include "MyString.h"

class MyPageListNode
{
public:
	int times;//���ʳ��ֵ��ܴ���
	int docID;//�ĵ����
	int type_of_word;//����ĵ��������ٲ�ͬ�Ĳ�ѯ����
	string filename;//���µ�����
	MyPageListNode* next;//ָ����һ����ָ��
	MyPageListNode* before;//ָ��ǰһ����ָ��
	MyPageListNode():times(0),docID(0),type_of_word(0),next(nullptr),before(nullptr)
	{
	}
};

class MyPageList
{
public:

	MyPageListNode* head;//ͷ�ڵ�

	//����һ���½ڵ�
	void Add(int docID,int docTimes);

	//�༭�µĽڵ�:�µĽڵ��������
	void Edit(MyPageListNode* prev_node , MyPageListNode* current_node);

	//Ĭ�Ϲ��캯��
	MyPageList():head(nullptr){}

};

string id_to_filename(int  docID);

#endif