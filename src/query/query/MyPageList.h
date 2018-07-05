#ifndef MyPageList_h
#define MyPageList_h

#include "MyString.h"

class MyPageListNode
{
public:
	int times;//单词出现的总次数
	int docID;//文档编号
	int type_of_word;//这个文档包含多少不同的查询单词
	string filename;//文章的名称
	MyPageListNode* next;//指向下一个的指针
	MyPageListNode* before;//指向前一个的指针
	MyPageListNode():times(0),docID(0),type_of_word(0),next(nullptr),before(nullptr)
	{
	}
};

class MyPageList
{
public:

	MyPageListNode* head;//头节点

	//插入一个新节点
	void Add(int docID,int docTimes);

	//编辑新的节点:新的节点后来排序
	void Edit(MyPageListNode* prev_node , MyPageListNode* current_node);

	//默认构造函数
	MyPageList():head(nullptr){}

};

string id_to_filename(int  docID);

#endif