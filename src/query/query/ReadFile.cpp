#include "ReadFile.h"

//���ļ�����ȡ����html�ļ�������MyString
MyString read_Html(char* filename)
{
	//���ص�string 
	MyString html_info;

	//��ʱ��ȡ�ļ���string��
	/*MyString temp_info;*/
	string temp = filename;
	string file_path = "input\\" + temp;

	//cout << file_path;
	ifstream in(file_path, ios::in);
	if (!in)//�����ʧ��
	{
		cout << "���ļ�����" << endl;
		return NULL;
	}

	wbuffer_convert<codecvt_utf8<wchar_t> > conv(in.rdbuf());
	wistream istr(&conv);

	/*while( istr >> temp_info)
	{
	html_info.concat(temp_info);
	}*/

	std::wstring line;
	while (std::getline(istr, line))
	{
		MyString temp_info(&line[0]);
		html_info.concat(temp_info);
	}

	in.close();
	return html_info;

}

//��ȡ����html�ļ�������һ���ַ�������
MyStringLinkedList* readFile()
{
	MyStringLinkedList* list = new MyStringLinkedList;
	system("dir /B input  >> filelist.txt");

	//cout << file_path;
	ifstream in("filelist.txt", ios::in);
	if (!in)//�����ʧ��
	{
		cout << "���ļ�����" << endl;
		return NULL;
	}

	std::string line;
	while (std::getline(in,line))
	{

		//�õ�����
		string tempName = line;
		for (int i = 0; i < 5; i++)
		{
			tempName.pop_back();
		}

		list->add(read_Html(&line[0]), tempName);
		
	}

	return list;
}

