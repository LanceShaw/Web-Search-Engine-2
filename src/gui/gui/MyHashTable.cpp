#include "MyHashTable.h"


//默认构造函数
MyHashTable::MyHashTable()
{
	max_len = 0;
	hashNodeList = new hashNode[63589];
}


//初始化Hash表时，每一个词放到对应的位置里
void MyHashTable::addHashValue(wstring newString)
{
	//更新hash表元素最大长度
	if (newString.length() > max_len)
	{
		max_len = newString.length();
	}

	int hashValue = GetHash(newString);
	hashNode* p = &hashNodeList[hashValue];
	if (p->data == L"")
	{
		p->data = newString;
	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		hashNode *temp = new hashNode(newString);
		p->next = temp;
	}

}

//查找时，判断是否在词库里
int MyHashTable::findHashValue(wstring newString)
{
	int hashValue = GetHash(newString);
	hashNode* p = &hashNodeList[hashValue];

	while (p != NULL)
	{
		if (wcscmp(&newString[0], &p->data[0]) == 0)//如果二者相同
		{
			return hashValue;
		}
		p = p->next;//下一个节点查找
	}
	return -1;
}

//给定一个字符串，对应得到一个哈希值
int GetHash(wstring string)
{
	unsigned int A = 378551;
	unsigned int B = 63689;
	unsigned int hash = 0;
	int len = string.length();
	for (int i = 0; i < len; i++)
	{
		hash = hash * A + (int)string[i];
		A *= B;
	}
	return hash % 63589;
}