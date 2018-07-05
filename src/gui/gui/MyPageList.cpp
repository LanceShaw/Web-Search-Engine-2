#include "MyPageList.h"


//�༭�µĽڵ�:�µĽڵ��������
void MyPageList::Edit(MyPageListNode* prev_node, MyPageListNode* current_node)
{
	//������Ҫ���������������Ƚϸ��ӣ���Ҫ�����´���

	//�ȶԸ��ݳ��ֲ�ѯ���ʵ��������ҳ��Ϣ����ʹ���ֶ���ؼ��ʵ���ҳ��Ϣ��ǰ
	while (prev_node->type_of_word < current_node->type_of_word)
	{
		//����prev_node��current_node����Ϣ
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

		prev_node = prev_node->before;//����
		current_node = current_node->before;
		if (prev_node == nullptr)//����Ѿ���ͷ��
		{
			break;
		}
	}

	//�ٸ�����ҳ�г��ֵĹؼ����ܸ�������ҳ����
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
			//����prev_node��current_node����Ϣ
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

			prev_node = prev_node->before;//����
			current_node = current_node->before;
			if (prev_node == nullptr)//����Ѿ���ͷ��
			{
				break;
			}
		}
	}
}

//����һ���½ڵ�
void MyPageList::Add(int docID, int docTimes)
{
	if (head == nullptr)//���ͷ�ڵ��ǿգ�����һ���µ�ͷ�ڵ�
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

		if (current_node != nullptr)//������ȵ����
		{
			current_node->times = current_node->times + docTimes;//�ܴ������
			current_node->type_of_word++;//���ֵĴ�������������������ҳ��Ϣ���Ե���Ϊ���ഫ��ȥ�ģ����Բ��ý����ж�
			this->Edit(prev_node, current_node);
		}
		else//�յ����,˵����û������ڵ�
		{
			prev_node->next = new MyPageListNode;//�����½ڵ�
			prev_node->next->docID = docID;//��ֵID
			prev_node->next->times = prev_node->next->times + docTimes;//times����
			prev_node->next->type_of_word++;
			prev_node->next->filename = id_to_filename(docID);
			prev_node->next->before = prev_node;//ָ��ָ��λ�ñ仯
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