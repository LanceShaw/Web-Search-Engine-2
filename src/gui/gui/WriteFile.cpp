#include "WriteFile.h"


//第一次实验时写info或者txt文件
void write_info_or_txt(MyStringLinkedList* list_info, string filename)
{
	string filepath = "output/" + filename;
	std::ofstream fout(filepath);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fout.rdbuf());
	std::wostream ostr(&conv);

	if (!fout)
	{
		cout << "error !";
	}
	else
	{
		MyStringNode* p = list_info->head;
		while (p != NULL)
		{
			ostr << p->data;
			ostr << std::endl;
			p = p->next;
		}
		;
	}
	fout.close();
}

//第一次实验写文件
void test1_write_file()
{
	//设置全局中文输出
	setlocale(LC_ALL, "chs");

	//读取网页得到存储网页信息的字符串链表
	MyStringLinkedList* list_htmlInfo = readFile();

	//读取字典得到的hash表
	MyHashTable* myHash = Hash_initDictionary();

	//进行写文件的操作
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
		MyStringLinkedList* word_list = divideWords(myHash, content_string);//分词得到的全部信息

		string file_name = p->filename;//文件名
		string file_name_info = file_name + ".info";
		string file_name_txt = file_name + ".txt";
		write_info_or_txt(info_list, file_name_info);//写入info文件
		write_info_or_txt(word_list, file_name_txt);//写入txt文件

		cout << "FILE: " << file_name << " Finished!" << endl;//在控制台输出信息，显示进度

		p = p->next;//得到下一个网页信息
	}

}