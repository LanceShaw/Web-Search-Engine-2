#include "MyHashTable.h"


//Ĭ�Ϲ��캯��
MyHashTable::MyHashTable()
{
	max_len = 0;
	hashNodeList = new hashNode[63589];
}


//��ʼ��Hash��ʱ��ÿһ���ʷŵ���Ӧ��λ����
void MyHashTable::addHashValue(wstring newString)
{
	//����hash��Ԫ����󳤶�
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

//����ʱ���ж��Ƿ��ڴʿ���
int MyHashTable::findHashValue(wstring newString)
{
	int hashValue = GetHash(newString);
	hashNode* p = &hashNodeList[hashValue];

	while (p != NULL)
	{
		if (wcscmp(&newString[0], &p->data[0]) == 0)//���������ͬ
		{
			return hashValue;
		}
		p = p->next;//��һ���ڵ����
	}
	return -1;
}

//����һ���ַ�������Ӧ�õ�һ����ϣֵ
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