#include "MyStringLinkedList.h"

//默认构造函数
MyStringLinkedList::MyStringLinkedList()
{
	head = new MyStringNode;
	list_size = 0;

}


//添加元素
void MyStringLinkedList::add(const MyString& newString)
{
	if (list_size == 0)
	{
		//unsigned long len = wcslen(newString.m_data);
		// head->data = new wchar_t[len+1];
		//head->data = newString;
		// wcscpy(head->data, newString.m_data);
		head = new MyStringNode(newString);
		list_size++;
		return;
	}
	else
	{
		MyStringNode* current_node = head;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		MyStringNode* next_node = new MyStringNode(newString);
		current_node->next = next_node;
		list_size++;
	}

}

//添加元素，记录文件名称
void MyStringLinkedList::add(const MyString& newString, string input_filename)
{
	if (list_size == 0)
	{
		//unsigned long len = wcslen(newString.m_data);
		// head->data = new wchar_t[len+1];
		//head->data = newString;
		// wcscpy(head->data, newString.m_data);
		head = new MyStringNode(newString);
		head->filename = input_filename;
		list_size++;
		return;
	}
	else
	{
		MyStringNode* current_node = head;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		MyStringNode* next_node = new MyStringNode(newString);
		next_node->filename = input_filename;
		current_node->next = next_node;
		list_size++;
	}

}

//删除元素
void MyStringLinkedList::remove(const MyString& target_String)
{
	if (list_size <= 0)
	{
		return;
	}
	else if (list_size == 1)
	{
		if (head->data == target_String)
		{
			head->data = NULL;
			list_size--;
		}
	}
	else
	{
		if (head->data == target_String)
		{
			MyStringNode* temp = head;
			head = head->next;
			delete temp;
			list_size--;
		}
		else
		{
			MyStringNode* previous_node = head;
			MyStringNode* current_node = head->next;
			while (current_node != NULL)
			{
				if (current_node->data == target_String)
				{
					previous_node->next = current_node->next;
					current_node->next = NULL;
					delete current_node;
					list_size--;
					break;
				}
				previous_node = previous_node->next;
				current_node = current_node->next;
			}
		}
	}
}

MyStringNode* MyStringLinkedList::search(const MyString& targetString)
{
	if (list_size <= 0)
	{
		return NULL;
	}
	else
	{
		MyStringNode* tempNode = head;
		while (tempNode != NULL)
		{
			if (tempNode->data == targetString)
			{
				return tempNode;
			}
			tempNode = tempNode->next;
		}
		return tempNode;
	}
}


void MyStringLinkedList_Test()
{
	MyStringLinkedList* list = new MyStringLinkedList;

	const wchar_t* a1 = L"我爱你中国";
	MyString s1(a1);
	list->add(s1);

	const wchar_t* a2 = L"你爱我吗";
	MyString s2(a2);
	list->add(s2);

	const wchar_t* a3 = L"I love you";
	MyString s3(a3);
	list->add(s3);

	//list->remove(s2);

	//MyStringNode* test = list->search(MyString(L"I love you"));

}