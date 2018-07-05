#include "MyHtmLInfo.h"

MyHtmLInfo::MyHtmLInfo()
{
	length = 0;
	int_docID = 0;
	next = nullptr;
}

//添加新的节点
void MyHtmLInfo::addNewInfo(MyStringNode* p, MyHashTable* myHash)
{
	//找到要写文件的那个html
	MyHtmLInfo* current_info = this;
	if (this->length == 0)
	{

	}
	else
	{
		while (current_info->next != nullptr)
		{
			current_info = current_info->next;//找到最后一个不是空的节点
		}
		current_info->next = new MyHtmLInfo;//给改节点下一个新建空间
		current_info = current_info->next;//移到下一个节点
	}

	this->length++;


	MyStringLinkedList* info_list = extractInfo(p);//文章全部信息

	MyStringNode* pointer = info_list->head;
	while (pointer->next != NULL)
	{
		pointer = pointer->next;//一直读到字符串结尾
	}

	MyString content_string = pointer->data;//正文的字符串
	MyStringLinkedList* word_list = divideWords(myHash, content_string);//分词得到的全部信息

	current_info->fileName = p->filename;//文件名称
	current_info->title = info_list->head->data;//标题
	current_info->question = info_list->head->next->data;//问题
	current_info->author = info_list->head->next->next->data;//作者
	current_info->content = content_string;//正文的全部信息
	current_info->words_content = word_list;//正文的分词结果

	int length = current_info->fileName.length();
	for (int i = 0; i < length; i++)
	{
		current_info->int_docID = 10 * current_info->int_docID + current_info->fileName[i] - '0';
	}

}

//把文章的所有信息读到一个MyHtmLInfo的对象中
MyHtmLInfo* MyHtmL_GetInfo(MyHashTable* myHash)
{

	//设置全局中文输出
	setlocale(LC_ALL, "chs");

	//读取网页得到存储网页信息的字符串链表
	MyStringLinkedList* list_htmlInfo = readFile();


	//最后返回的MyHtmlInfo对象
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