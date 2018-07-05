#include "MyPageList.h"


//编辑新的节点:新的节点后来排序
void MyPageList::Edit(MyPageListNode* prev_node, MyPageListNode* current_node)
{
	//处理需要调整次序的情况，比较复杂，需要做如下处理

	//先对根据出现查询单词的种类对网页信息排序，使出现多个关键词的网页信息靠前
	while (prev_node->type_of_word < current_node->type_of_word)
	{
		//交换prev_node与current_node的信息
		int prev_times = prev_node->times;
		int prev_ID = prev_node->docID;
		int prev_type_word = prev_node->type_of_word;
		string prev_name = prev_node->filename;
		int curr_times = current_node->times;
		int curr_ID = current_node->docID;
		int curr_type_word = current_node->type_of_word;
		string curr_name = current_node->filename;

		prev_node->docID = curr_ID;
		prev_node->times = curr_times;
		prev_node->type_of_word = curr_type_word;
		prev_node->filename = curr_name;
		current_node->times = prev_times;
		current_node->docID = prev_ID;
		current_node->type_of_word = prev_type_word;
		current_node->filename = prev_name;

		prev_node = prev_node->before;//回溯
		current_node = current_node->before;
		if (prev_node == nullptr)//如果已经到头了
		{
			break;
		}
	}

	//再根据网页中出现的关键词总个数对网页排序
	if (prev_node == nullptr)
	{
		return;
	}
	else
	{
		while (prev_node->times < current_node->times)
		{
			if (prev_node->type_of_word > current_node->type_of_word)
			{
				break;
			}
			//交换prev_node与current_node的信息
			int prev_times = prev_node->times;
			int prev_ID = prev_node->docID;
			int prev_type_word = prev_node->type_of_word;
			string prev_name = prev_node->filename;
			int curr_times = current_node->times;
			int curr_ID = current_node->docID;
			int curr_type_word = current_node->type_of_word;
			string curr_name = current_node->filename;

			prev_node->docID = curr_ID;
			prev_node->times = curr_times;
			prev_node->type_of_word = curr_type_word;
			prev_node->filename = curr_name;
			current_node->times = prev_times;
			current_node->docID = prev_ID;
			current_node->type_of_word = prev_type_word;
			current_node->filename = prev_name;

			prev_node = prev_node->before;//回溯
			current_node = current_node->before;
			if (prev_node == nullptr)//如果已经到头了
			{
				break;
			}
		}
	}
}

//插入一个新节点
void MyPageList::Add(int docID, int docTimes)
{
	if (head == nullptr)//如果头节点是空，创建一个新的头节点
	{
		head = new MyPageListNode;
		head->docID = docID;
		head->times = head->times + docTimes;
		head->filename = id_to_filename(docID);
		head->type_of_word++;
	}
	else
	{
		MyPageListNode* prev_node = this->head;
		MyPageListNode* current_node = this->head;
		while (current_node != nullptr && docID != current_node->docID)
		{
			prev_node = current_node;
			current_node = current_node->next;
		}

		if (current_node != nullptr)//出现相等的情况
		{
			current_node->times = current_node->times + docTimes;//总次数相加
			current_node->type_of_word++;//出现的词语种类数量，由于网页信息是以单词为种类传进去的，所以不用进行判断
			this->Edit(prev_node, current_node);
		}
		else//空的情况,说明还没有这个节点
		{
			prev_node->next = new MyPageListNode;//创建新节点
			prev_node->next->docID = docID;//赋值ID
			prev_node->next->times = prev_node->next->times + docTimes;//times更新
			prev_node->next->type_of_word++;
			prev_node->next->filename = id_to_filename(docID);
			prev_node->next->before = prev_node;//指针指向位置变化
		}
	}

	return;
}

string id_to_filename(int docID)
{
	string result;
	int length = docID / 10;
	if (length == 0)
	{
		result = result + '0';
		result = result + '0';
		result = result + '0';
		char tempChar = '0' + docID - 0;
		result = result + tempChar;
		result = result + ".html";
	}
	else if (length >= 1 && length <= 9)
	{
		result = result + '0';
		result = result + '0';
		char tempChar = '0' + docID/10 - 0;
		result = result + tempChar;
		 tempChar = '0' + docID - (docID / 10) * 10 ;
		result = result + tempChar;

		result = result + ".html";
	}
	else if (length >= 10 && length <= 99)
	{
		result = result + '0';
		char tempChar = '0' + docID / 100 - 0;
		result = result + tempChar;
		 tempChar = '0' + (docID/10)%10 - 0;
		result = result + tempChar;
		 tempChar = '0' + docID % 10 - 0;
		result = result + tempChar;
		result = result + ".html";

	}
	else
	{
	}
	return result;
}