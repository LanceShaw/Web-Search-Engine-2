#include "ReadFile.h"


//用文件名读取单个html文件，返回MyString
MyString read_Html1(char* filename)
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
MyStringLinkedList* readFile1()
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


//QString转为MyString
MyString QString_to_myString(QString s)
{
	wstring tempW = s.toStdWString();
	const wchar_t* p = &tempW[0];
	MyString a(p);
	return a;
}

//MyString转换为QString
QString myString_to_QString(MyString s)
{
	wstring tempW;
	int length = wcslen(s.m_data);
	for (int i = 0; i < length; i++)
	{
		tempW = tempW + s.m_data[i];
	}
	QString str0(QString::fromStdWString(tempW));
	return str0;
}

//把一行转换为MyPageList
MyPageList* searchPageList(MyAVLTree<MyString>* tree, MyStringLinkedList* word_list)
{
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

	return result_list;
}


//用文件名读取单个html文件，返回MyString
MyString read_Html(QString filename)
{
	//返回的string 
	MyString html_info;

	//临时读取文件的string类
	/*MyString temp_info;*/
	QString temp = filename;
	QString file_path = "input\\" + temp;
	// file_path = temp;
	 qDebug() << QDir::currentPath();

	//cout << file_path;
	QFile *file = new QFile(file_path);
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "ERROR";
		return NULL;
	}

	QString all_content = file->readAll();
	html_info = QString_to_myString(all_content);

	file->close();

	return html_info;

}


//读取所有html文件，返回一个字符串链表
MyStringLinkedList* readFile()
{
	MyStringLinkedList* list = new MyStringLinkedList;

	system("dir /B input  >> filelist.txt");

	//cout << file_path;
	QFile *file = new QFile("./filelist.txt");
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		cout << "ERROR";
		return nullptr;
	}

	QString line;
	while (!file->atEnd())
	{

		//得到名称
		line = file->readLine();
		line = line.left(line.length() - 1);

		string tempName = line.toStdString();;
		for (int i = 0; i < 5; i++)//行尾会有一个\n，需要多删除一个
		{
			tempName.pop_back();
		}

		list->add(read_Html(line), tempName);

	}

	file->close();
	remove("filelist.txt");
	return list;

}