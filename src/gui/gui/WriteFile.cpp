#include "WriteFile.h"


//��һ��ʵ��ʱдinfo����txt�ļ�
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

//��һ��ʵ��д�ļ�
void test1_write_file()
{
	//����ȫ���������
	setlocale(LC_ALL, "chs");

	//��ȡ��ҳ�õ��洢��ҳ��Ϣ���ַ�������
	MyStringLinkedList* list_htmlInfo = readFile();

	//��ȡ�ֵ�õ���hash��
	MyHashTable* myHash = Hash_initDictionary();

	//����д�ļ��Ĳ���
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
		MyStringLinkedList* word_list = divideWords(myHash, content_string);//�ִʵõ���ȫ����Ϣ

		string file_name = p->filename;//�ļ���
		string file_name_info = file_name + ".info";
		string file_name_txt = file_name + ".txt";
		write_info_or_txt(info_list, file_name_info);//д��info�ļ�
		write_info_or_txt(word_list, file_name_txt);//д��txt�ļ�

		cout << "FILE: " << file_name << " Finished!" << endl;//�ڿ���̨�����Ϣ����ʾ����

		p = p->next;//�õ���һ����ҳ��Ϣ
	}

}