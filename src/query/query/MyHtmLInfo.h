#ifndef MyHtmLInfo_h
#define MyHtmLInfo_h


//这个类用来存储网页的信息
//但是最后实际并没有使用这个类，因为如果把所有网页信息存储起来实在是太慢了

#include "MyInterface.h"
#include "MyString.h"
#include "MyStringLinkedList.h"
#include "ReadFile.h"

class MyHtmLInfo
{
public:
	int length;//文章的总数量
	int int_docID;//文章的ID
	string fileName;//文章名称

	MyString title;//文章标题
	MyString question;//文章问题
	MyString author;//文章作者
	MyString content;//正文内容
	MyStringLinkedList* words_content;//正文分词的结果

	MyHtmLInfo* next;//指向下一个节点
	
	//默认构造函数
	MyHtmLInfo();
	//加入新的节点,用一个已经生成的哈希表
	void addNewInfo(MyStringNode* p,MyHashTable* myHash);

};

//把文章的所有信息读到一个MyHtmLInfo的对象中
MyHtmLInfo* MyHtmL_GetInfo(MyHashTable* myHash);

#endif