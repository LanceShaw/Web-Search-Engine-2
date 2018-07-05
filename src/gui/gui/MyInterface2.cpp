#include "MyInterface2.h"

//initDictionary(...):�ýӿ�ִ������ʿ�ȳ�ʼ������,���ѽ������Ϊһ��AVL��
//�������Ƚ���AVL����Hash���Ч�ʣ�ѡ����ʹ��Hash�����洢�ʵ�
MyAVLTree<MyString>* AVL_initDictionary()
{
	MyAVLTree<MyString>* myAVLTree = new MyAVLTree<MyString>;

	std::locale chs("chs");
	std::wifstream ifs("Dictionary/�ʿ�_ansi.dic");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	std::wstring line;

	while (std::getline(ifs, line))
	{
		MyString tempString(&line[0]);
		myAVLTree->insert(tempString);
	}

	ifs.close();
	return myAVLTree;
}

//������ɵ�AVL����ÿ�ֳ�һ�����ʣ��Ͱ����ӵ�AVL��������
//����ӿ�ʵ�ִַʺ�ʵʱ�Ѵʼ���AVL��
void test2_divideAndInsertWords(MyHashTable* myHash, MyString& myString, MyAVLTree<MyString>* myAVL, int docID )
{
	//������ҳ�ļ��ַ�����
	unsigned long string_total_length = wcslen(myString.m_data);

	//������󳤶�
	//int word_max_length = myHash->max_len;
	int word_max_length = 6;
	//�ִ�
	for (unsigned long i = 0; i < string_total_length; i++)
	{
		for (int temp_len = word_max_length; temp_len >= 1; temp_len--)
		{
			MyString tempString = myString.subString(i, temp_len);
			if (myHash->findHashValue(tempString.m_data) >= 0)
			{
				//���Ҹõ�����AVL�����Ƿ����
				MyAVLTreeNode<MyString>* result = myAVL->iterativeSearch(tempString);

				if (result == nullptr)//������
				{
					myAVL->insert(tempString);
					result = myAVL->iterativeSearch(tempString);
					result->html_docuList = new MyDoculist<MyString>(tempString, docID);//��ʼ�������ĵ�
					result->occur++;//�����ܴ���++
					if (docID != result->current_docID)//���Ҫ��������±����֮ǰ��ͬ��˵����������
					{
						result->current_docID = docID;//�޸ı��
						result->DF++;//DF++
					}
				}
				else//����
				{
					result->html_docuList->Add(docID);
					result->occur++;//�����ܴ���++
					if (docID != result->current_docID)//���Ҫ��������±����֮ǰ��ͬ��˵����������
					{
						result->current_docID = docID;//�޸ı��
						result->DF++;//DF++
					}
				}

				i = i + temp_len - 1;
				break;
			}
		}
	}
}


//ֱ�Ӷ�ȡ500����ҳ����Ϣ���õ����ǵķִʽ�������÷ֵĴ�ȥ�����Ż�AVL���еĽڵ�
MyAVLTree<MyString>* AVL_HandleAllHtml(MyHashTable* myHash)
{
	//����ȫ���������
	setlocale(LC_ALL, "chs");

	//��ȡ��ҳ�õ��洢��ҳ��Ϣ���ַ�������
	MyStringLinkedList* list_htmlInfo = readFile();

	//���ص�AVL������ÿ����ҳ�ķִʽ���
	MyAVLTree<MyString>* myAVL = new MyAVLTree<MyString>;


	MyStringNode* p = list_htmlInfo->head;
	while (p != NULL)
	{
		MyStringLinkedList* info_list = extractInfo(p);//����ȫ����Ϣ

		MyStringNode* pointer = info_list->head;
		while (pointer->next != NULL)
		{
			pointer = pointer->next;//һֱ�����ַ�����β
		}
		MyString content_string = pointer->data;//���ĵ��ַ���

		string file_name = p->filename;//�ļ���
		int docID = 0;//���ļ���ת��Ϊ���
		int length = file_name.length();
		for (int i = 0; i < length; i++)
		{
			docID = 10 * docID + file_name[i] - '0';
		}

		test2_divideAndInsertWords(myHash, content_string, myAVL, docID);

		cout << "FILE: " << file_name << " Finished!" << endl;//�ڿ���̨�����Ϣ����ʾ����

		p = p->next;//�õ���һ����ҳ��Ϣ
	}

	return myAVL;
}

//���Ѿ�����������ҳ����Ϣȥ�õ��ִʲ�����AVL��
MyAVLTree<MyString>* AVL_GetInfoFromSavedHtml(MyHtmLInfo* myList, MyHashTable* myHash)
{
	//���ص�AVL������ÿ����ҳ�ķִʽ���
	MyAVLTree<MyString>* myAVL = new MyAVLTree<MyString>;

	while (myList != nullptr)
	{
		MyStringNode* p = myList->words_content->head;
		while (p != nullptr)
		{
			myAVL->insert(p->data);
			p = p->next;
		}
		myList = myList->next;
	}

	return myAVL;
}



//��ÿ�δ�query�ж�ȡ��һ�з���һ�����
void line_to_result(MyAVLTree<MyString>* tree, wstring& line, MyHashTable* myHash, wostream& output)
{
	wstring result;

	MyString tempString(&line[0]);
	MyStringLinkedList* word_list = divideWords(myHash, tempString);

	MyPageList* result_list = new MyPageList;

	MyStringNode* head = word_list->head;
	while (head != nullptr)
	{
		MyAVLTreeNode<MyString>* tempAVLNode = tree->iterativeSearch(head->data);
		if (tempAVLNode != nullptr)//�ҵ����Ǹ���
		{
			MyDoculist<MyString>* h_list = tempAVLNode->html_docuList;
			if (h_list != nullptr)
			{
				MyDoculistNode* d_head = h_list->head;
				while (d_head != nullptr)
				{
					result_list->Add(d_head->DocID, d_head->Times);
					d_head = d_head->next;
				}
			}
		}
		head = head->next;
	}

	MyPageListNode* p_head = result_list->head;
	bool need_space = false;
	while (p_head != nullptr)
	{
		if (need_space == true)
		{
			output << " ";
		}


		output << "("  << StringToWString(p_head->filename) <<","<< p_head->docID << "," << p_head->times << ")";

		if (need_space == false)
		{
			need_space = true;
		}

		p_head = p_head->next;
	}

	return ;

}

//�������ʵ�ֶ�ȡquery.txt�ļ�������������result.txt�ļ��Ĺ���
void query_to_result()
{
	//��ȡ�ֵ�õ���hash��
	MyHashTable* myHash = Hash_initDictionary();

	//500����ҳ���ɵĲ�ѯAVL��
	MyAVLTree<MyString>* tree = AVL_HandleAllHtml(myHash);

	//��ȡ�ļ�ʱ������������
	std::locale chs("chs");
	std::wifstream ifs("query.txt");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	if (!ifs)
	{
		cout << "error !";
		 return ;
	}
	
	//����ļ�ʱ�����������
	string filepath = "result.txt";
	std::ofstream fout(filepath);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fout.rdbuf());
	std::wostream ostr(&conv);
	if (!fout)
	{
		cout << "error !";
		 return;
	}

	//����ÿһ��ʱ�õ���line
	std::wstring line;
	while (std::getline(ifs, line))
	{
		line_to_result(tree,line,myHash,ostr);
		ostr << endl;
	}

	ifs.close();
	fout.close();
	remove("filelist.txt");
	return ;

}


//�������ʵ�ֶ�ȡquery.txt�ļ�������������result.txt�ļ��Ĺ���
void query_to_result2()
{
	//��ȡ�ֵ�õ���hash��
	MyHashTable* myHash = Hash_initDictionary();

	//�õ��洢����html��Ϣ��һ��list
	MyHtmLInfo* HtmLInfo_list = MyHtmL_GetInfo(myHash);

	//500����ҳ���ɵĲ�ѯAVL��
	MyAVLTree<MyString>* tree = AVL_GetInfoFromSavedHtml(HtmLInfo_list,myHash);

	//��ȡ�ļ�ʱ������������
	std::locale chs("chs");
	std::wifstream ifs("query.txt");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	if (!ifs)
	{
		cout << "error !";
		return;
	}

	//����ļ�ʱ�����������
	string filepath = "result2.txt";
	std::ofstream fout(filepath);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fout.rdbuf());
	std::wostream ostr(&conv);
	if (!fout)
	{
		cout << "error !";
		return;
	}

	//����ÿһ��ʱ�õ���line
	std::wstring line;
	while (std::getline(ifs, line))
	{
		line_to_result(tree, line, myHash, ostr);
		ostr << endl;
	}

	ifs.close();
	fout.close();
	return;

}

std::wstring  StringToWString(const std::string& s)
{
	std::wstring wszStr;

	int nLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, NULL);
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength);
	wszStr = lpwszStr;
	delete[] lpwszStr;

	return wszStr;
}


