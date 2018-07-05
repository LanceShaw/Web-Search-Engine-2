#include "MyHtmLInfo.h"

MyHtmLInfo::MyHtmLInfo()
{
	length = 0;
	int_docID = 0;
	next = nullptr;
}

//����µĽڵ�
void MyHtmLInfo::addNewInfo(MyStringNode* p, MyHashTable* myHash)
{
	//�ҵ�Ҫд�ļ����Ǹ�html
	MyHtmLInfo* current_info = this;
	if (this->length == 0)
	{

	}
	else
	{
		while (current_info->next != nullptr)
		{
			current_info = current_info->next;//�ҵ����һ�����ǿյĽڵ�
		}
		current_info->next = new MyHtmLInfo;//���Ľڵ���һ���½��ռ�
		current_info = current_info->next;//�Ƶ���һ���ڵ�
	}

	this->length++;


	MyStringLinkedList* info_list = extractInfo(p);//����ȫ����Ϣ

	MyStringNode* pointer = info_list->head;
	while (pointer->next != NULL)
	{
		pointer = pointer->next;//һֱ�����ַ�����β
	}

	MyString content_string = pointer->data;//���ĵ��ַ���
	MyStringLinkedList* word_list = divideWords(myHash, content_string);//�ִʵõ���ȫ����Ϣ

	current_info->fileName = p->filename;//�ļ�����
	current_info->title = info_list->head->data;//����
	current_info->question = info_list->head->next->data;//����
	current_info->author = info_list->head->next->next->data;//����
	current_info->content = content_string;//���ĵ�ȫ����Ϣ
	current_info->words_content = word_list;//���ĵķִʽ��

	int length = current_info->fileName.length();
	for (int i = 0; i < length; i++)
	{
		current_info->int_docID = 10 * current_info->int_docID + current_info->fileName[i] - '0';
	}

}

//�����µ�������Ϣ����һ��MyHtmLInfo�Ķ�����
MyHtmLInfo* MyHtmL_GetInfo(MyHashTable* myHash)
{

	//����ȫ���������
	setlocale(LC_ALL, "chs");

	//��ȡ��ҳ�õ��洢��ҳ��Ϣ���ַ�������
	MyStringLinkedList* list_htmlInfo = readFile();


	//��󷵻ص�MyHtmlInfo����
	MyHtmLInfo* myInfo = new MyHtmLInfo;

	MyStringNode* p = list_htmlInfo->head;
	while (p != NULL)
	{
		myInfo->addNewInfo(p, myHash);
		cout << p->filename << "Finished!" << endl;
		p = p->next;
	}

	return myInfo;

}