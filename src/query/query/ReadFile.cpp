#include "ReadFile.h"

//用文件名读取单个html文件，返回MyString
MyString read_Html(char* filename)
{
	//返回的string 
	MyString html_info;

	//临时读取文件的string类
	/*MyString temp_info;*/
	string temp = filename;
	string file_path = "input\\" + temp;

	//cout << file_path;
	ifstream in(file_path, ios::in);
	if (!in)//如果打开失败
	{
		cout << "打开文件出错" << endl;
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

//读取所有html文件，返回一个字符串链表
MyStringLinkedList* readFile()
{
	MyStringLinkedList* list = new MyStringLinkedList;
	system("dir /B input  >> filelist.txt");

	//cout << file_path;
	ifstream in("filelist.txt", ios::in);
	if (!in)//如果打开失败
	{
		cout << "打开文件出错" << endl;
		return NULL;
	}

	std::string line;
	while (std::getline(in,line))
	{

		//得到名称
		string tempName = line;
		for (int i = 0; i < 5; i++)
		{
			tempName.pop_back();
		}

		list->add(read_Html(&line[0]), tempName);
		
	}

	return list;
}

