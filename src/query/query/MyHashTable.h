#ifndef MyHashTable_h
#define MyHashTable_h

#include<iostream>
#include<string>

using namespace std;

//给定一个字符串，对应得到一个哈希值
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
	//默认构造函数
	MyHashTable();

	//最长字符串长度
	int max_len;

	//hash表的数组
	hashNode* hashNodeList ;

	//初始化Hash表时，计算Hash值
	void addHashValue(wstring newString);

	//查找时，判断是否在词库里
	int findHashValue(wstring newString);

private:

};



#endif