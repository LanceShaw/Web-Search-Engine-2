#include "MyInterface2.h"

//initDictionary(...):该接口执行载入词库等初始化操作,并把结果保存为一棵AVL树
//但是最后比较了AVL树和Hash表的效率，选择了使用Hash表来存储词典
MyAVLTree<MyString>* AVL_initDictionary()
{
	MyAVLTree<MyString>* myAVLTree = new MyAVLTree<MyString>;

	std::locale chs("chs");
	std::wifstream ifs("Dictionary/词库_ansi.dic");
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

//最后生成的AVL树：每分出一个单词，就把它加到AVL树中树中
//这个接口实现分词后实时把词加入AVL树
void test2_divideAndInsertWords(MyHashTable* myHash, MyString& myString, MyAVLTree<MyString>* myAVL, int docID )
{
	//整个网页文件字符长度
	unsigned long string_total_length = wcslen(myString.m_data);

	//词语最大长度
	//int word_max_length = myHash->max_len;
	int word_max_length = 6;
	//分词
	for (unsigned long i = 0; i < string_total_length; i++)
	{
		for (int temp_len = word_max_length; temp_len >= 1; temp_len--)
		{
			MyString tempString = myString.subString(i, temp_len);
			if (myHash->findHashValue(tempString.m_data) >= 0)
			{
				//查找该单词在AVL树中是否存在
				MyAVLTreeNode<MyString>* result = myAVL->iterativeSearch(tempString);

				if (result == nullptr)//不存在
				{
					myAVL->insert(tempString);
					result = myAVL->iterativeSearch(tempString);
					result->html_docuList = new MyDoculist<MyString>(tempString, docID);//初始化倒排文档
					result->occur++;//出现总次数++
					if (docID != result->current_docID)//如果要存入的文章编号与之前不同，说明有新文章
					{
						result->current_docID = docID;//修改编号
						result->DF++;//DF++
					}
				}
				else//存在
				{
					result->html_docuList->Add(docID);
					result->occur++;//出现总次数++
					if (docID != result->current_docID)//如果要存入的文章编号与之前不同，说明有新文章
					{
						result->current_docID = docID;//修改编号
						result->DF++;//DF++
					}
				}

				i = i + temp_len - 1;
				break;
			}
		}
	}
}


//直接读取500个网页的信息，得到他们的分词结果，并用分的词去持续优化AVL树中的节点
MyAVLTree<MyString>* AVL_HandleAllHtml(MyHashTable* myHash)
{
	//设置全局中文输出
	setlocale(LC_ALL, "chs");

	//读取网页得到存储网页信息的字符串链表
	MyStringLinkedList* list_htmlInfo = readFile();

	//返回的AVL树，用每个网页的分词建树
	MyAVLTree<MyString>* myAVL = new MyAVLTree<MyString>;


	MyStringNode* p = list_htmlInfo->head;
	while (p != NULL)
	{
		MyStringLinkedList* info_list = extractInfo(p);//文章全部信息

		MyStringNode* pointer = info_list->head;
		while (pointer->next != NULL)
		{
			pointer = pointer->next;//一直读到字符串结尾
		}
		MyString content_string = pointer->data;//正文的字符串

		string file_name = p->filename;//文件名
		int docID = 0;//把文件名转换为编号
		int length = file_name.length();
		for (int i = 0; i < length; i++)
		{
			docID = 10 * docID + file_name[i] - '0';
		}

		test2_divideAndInsertWords(myHash, content_string, myAVL, docID);

		cout << "FILE: " << file_name << " Finished!" << endl;//在控制台输出信息，显示进度

		p = p->next;//得到下一个网页信息
	}

	return myAVL;
}

//用已经存起来的网页的信息去得到分词产生的AVL树
MyAVLTree<MyString>* AVL_GetInfoFromSavedHtml(MyHtmLInfo* myList, MyHashTable* myHash)
{
	//返回的AVL树，用每个网页的分词建树
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



//把每次从query中读取的一行返回一个结果
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
		if (tempAVLNode != nullptr)//找到了那个词
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

//这个函数实现读取query.txt文件并将结果输出到result.txt文件的功能
void query_to_result()
{
	//读取字典得到的hash表
	MyHashTable* myHash = Hash_initDictionary();

	//500个网页生成的查询AVL树
	MyAVLTree<MyString>* tree = AVL_HandleAllHtml(myHash);

	//读取文件时读入流的设置
	std::locale chs("chs");
	std::wifstream ifs("query.txt");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	if (!ifs)
	{
		cout << "error !";
		 return ;
	}
	
	//输出文件时输出流的设置
	string filepath = "result.txt";
	std::ofstream fout(filepath);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fout.rdbuf());
	std::wostream ostr(&conv);
	if (!fout)
	{
		cout << "error !";
		 return;
	}

	//读入每一行时用到的line
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


//这个函数实现读取query.txt文件并将结果输出到result.txt文件的功能
void query_to_result2()
{
	//读取字典得到的hash表
	MyHashTable* myHash = Hash_initDictionary();

	//得到存储所有html信息的一个list
	MyHtmLInfo* HtmLInfo_list = MyHtmL_GetInfo(myHash);

	//500个网页生成的查询AVL树
	MyAVLTree<MyString>* tree = AVL_GetInfoFromSavedHtml(HtmLInfo_list,myHash);

	//读取文件时读入流的设置
	std::locale chs("chs");
	std::wifstream ifs("query.txt");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	if (!ifs)
	{
		cout << "error !";
		return;
	}

	//输出文件时输出流的设置
	string filepath = "result2.txt";
	std::ofstream fout(filepath);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fout.rdbuf());
	std::wostream ostr(&conv);
	if (!fout)
	{
		cout << "error !";
		return;
	}

	//读入每一行时用到的line
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


