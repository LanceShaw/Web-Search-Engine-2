#include "MyInterface.h"


//判断字符串中是否含有关键字,均是非嵌套情况，0代表没有，1代表文章标题、2代表问题名称、3代表作者
int int_myString_conclude_keywords(MyString& current_string)
{
	MyString tempString1(L"<title>");
	if (current_string.indexOf(tempString1) >= 0)
	{
		return 1;
	}

	MyString tempString2(L"question-title");
	if (current_string.indexOf(tempString2) >= 0)
	{
		return 2;
	}

	MyString tempString3(L"author");
	if (current_string.indexOf(tempString3) >= 0)
	{
		return 3;
	}

	return 0;
}

//判断字符串中是否含有关键字以及之后的处理,非嵌套情况
MyString MyString_conclude_keywords(MyString& current_string)
{
	MyString tempString1(L"<title>");
	if (current_string.indexOf(tempString1) >= 0)
	{
		MyString tempString(L"");
		return tempString;
	}

	MyString tempString2(L"question-title");
	if (current_string.indexOf(tempString2) >= 0)
	{
		MyString tempString(L"");
		return tempString;
	}

	MyString tempString3(L"author");
	if (current_string.indexOf(tempString3) >= 0)
	{
		MyString tempString(L"");
		return tempString;
	}

	return NULL;
}

//每一个转义字符对应一个wchar_t字符
wchar_t escapeCharacter_to_wchar(MyString& testString)
{
	if (wcscmp(&testString.m_data[0], L"&quot;") == 0)
	{
		return L'"';
	}
	if (wcscmp(&testString.m_data[0], L"&ldquo;") == 0)
	{
		return L'“';
	}
	if (wcscmp(&testString.m_data[0], L"&rdquo;") == 0)
	{
		return L'”';
	}
	if (wcscmp(&testString.m_data[0], L"&mdash;") == 0)
	{
		return L'—';
	}
	if (wcscmp(&testString.m_data[0], L"&amp;") == 0)
	{
		return L'&';
	}
	if (wcscmp(&testString.m_data[0], L"&lt;") == 0)
	{
		return L'<';
	}
	if (wcscmp(&testString.m_data[0], L"&gt;") == 0)
	{
		return L'>';
	}
	if (wcscmp(&testString.m_data[0], L"&nbsp;") == 0)
	{
		return L' ';
	}
	if (wcscmp(&testString.m_data[0], L"&hellip;") == 0)
	{
		return L'…';
	}
	if (wcscmp(&testString.m_data[0], L"&deg;") == 0)
	{
		return L'°';
	}
	return NULL;
}

//将输入string中的转义字符去掉
MyString delete_escapeCharacter(MyString& targetString)
{
	MyString resultString;
	unsigned long total_length = wcslen(targetString.m_data);
	for (unsigned long i = 0; i < total_length; i++)
	{
		if (targetString.m_data[i] != L'&')
		{
			resultString = resultString + targetString.m_data[i];
		}
		else
		{
			unsigned long left_pos = i;
			unsigned long right_pos = left_pos;
			while (targetString.m_data[right_pos] != L';')
			{
				right_pos++;
				if (right_pos >= left_pos + 8)//最多有8个字符
				{
					break;
				}
			}
			MyString testString = targetString.subString(left_pos, right_pos - left_pos + 1);
			wchar_t add_wchar = escapeCharacter_to_wchar(testString);
			if (add_wchar != NULL)
			{
				resultString = resultString + add_wchar;
				i = i + right_pos - left_pos;
			}
		}
	}
	return resultString;
}

//extractInfo()该接口执行解析网页操作，返回结果为一个字符串链表,每一个节点包含一个网页的一个信息
MyStringLinkedList* extractInfo(MyStringNode* current_node)
{

	MyStringLinkedList* list_info = new MyStringLinkedList;//返回的字符串链表
	MyStack<MyString> my_stack;//用到的栈
	wchar_t *wchar_string = current_node->data.m_data;//文章正文的wchar_t
	MyString MyString_html = current_node->data;//文章的string数据
	unsigned long total_length = wcslen(wchar_string);//文章正文的长度

	MyString MyString_content;//存储正文的字符串

							  //一些flag
	int flag_end = 0;//这个用来判断是否要提取信息进入字符串链表中,用它可以提取文章的标题、问题、作者、正文,但是只有它无法处理正文中嵌套标签的情况
	int flag_content = 0;//处理是否是正文
	int flag_bracket = 0;//处理异常的括号，初始为0，遇到左括号置1，遇到右括号置0
	int num_content = 0; //正文content的数量
	int flag_hasReadAuthor = 0;//是否读到作者，读到作者后读取第一个正文，读完第一个正文后置0

							   //坐标
	unsigned long left_pos = 0;//左坐标
	unsigned long right_pos = 0;//右坐标

								//开始网页解析
	for (unsigned long i = 0; i < total_length; i++)
	{
		//是'<'的情况
		if (wchar_string[i] == '<')
		{
			if (flag_bracket == 0)
			{
				left_pos = i;//修改坐标值
				flag_bracket = 1;//修改括号flag
				if (flag_content == 1 && flag_hasReadAuthor == 1)//两个条件，在读正文，是作者信息出现后的正文
				{
					MyString tempString = MyString_html.subString(right_pos + 1, left_pos - right_pos - 1);
					MyString_content.concat(tempString);
				}
			}
		}

		//是‘/’的情况
		else if (wchar_string[i] == '/')
		{
			if (wchar_string[i - 1] == '<' || wchar_string[i + 1] == '>')//有效的'<'
			{
				flag_end = 1;//修改结束flag
			}
		}

		//是‘>’的情况
		else if (wchar_string[i] == '>')
		{
			if (flag_bracket == 1)//处理表情符号
			{
				flag_bracket = 0;//修改flag值

				if (flag_end == 0)//前标签情况
				{
					right_pos = i;//记录右坐标
					MyString tempString = MyString_html.subString(left_pos, right_pos - left_pos + 1);
					if (int_myString_conclude_keywords(tempString) > 0)//如果包含关键字
					{
						my_stack.push(tempString);//压栈
					}
					else if (tempString.indexOf(MyString(L"class=\"content\"")) >= 0)
					{
						flag_content = 1;//表示进入正文
						num_content++;//增加num_content
					}
				}

				else if (flag_end == 1)//后标签情况
				{
					flag_end = 0;
					if (int_myString_conclude_keywords(my_stack.Top()) > 0)
					{

						MyString left_string = MyString_conclude_keywords(my_stack.Top());
						MyString right_string = MyString_html.subString(right_pos + 1, left_pos - right_pos - 1);
						if (int_myString_conclude_keywords(my_stack.Top()) == 3)//读到作者，
						{
							flag_hasReadAuthor = 1;//将flag置1

												   //判断作者结尾是否是','
							int tempLen = wcslen(right_string.m_data);
							if (right_string.m_data[tempLen - 1] == L',' || right_string.m_data[tempLen - 1] == L'，')//如果结尾是中文或者英文的逗号
							{
								right_string.m_data[tempLen - 1] = '\0';
							}

						}
						left_string.concat(right_string);
						list_info->add(left_string);
					}
					my_stack.pop();
					if (flag_content == 1)//正在读正文
					{
						right_pos = i;//修改右坐标值
						MyString tempString = MyString_html.subString(left_pos, i - left_pos + 1);
						if (tempString.indexOf(MyString(L"/div")) >= 0)
						{
							flag_content = 0;//结束正文输入
							flag_hasReadAuthor = 0;//修改flag值为0
						}
					}
				}
				else
				{
				}
			}
		}

	}
	MyString MyString_final_content(L"");
	MyString_final_content.concat(MyString_content);
	MyString final_last_content = delete_escapeCharacter(MyString_final_content);
	list_info->add(final_last_content);
	return list_info;
}

//initDictionary(...):该接口执行载入词库等初始化操作
MyHashTable* Hash_initDictionary()
{
	MyHashTable* myHashTable = new MyHashTable;

	std::locale chs("chs");
	std::wifstream ifs("Dictionary/词库_ansi.dic");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	std::wstring line;
	while (std::getline(ifs, line))
	{
		myHashTable->addHashValue(line);

	}
	return myHashTable;

}

//divideWords(...):该接口执行分词操作，返回结果保存为字符串链表
MyStringLinkedList* divideWords(MyHashTable* myHash, MyString& myString)
{
	//返回的字符串链表
	MyStringLinkedList* words_list = new MyStringLinkedList;

	//整个网页文件字符长度
	unsigned long string_total_length = wcslen(myString.m_data);

	//词语最大长度
	//int word_max_length = myHash->max_len;
	int word_max_length = 4;
	//分词
	for (unsigned long i = 0; i < string_total_length; i++)
	{
		for (int temp_len = word_max_length; temp_len >= 1; temp_len--)
		{
			MyString tempString = myString.subString(i, temp_len);
			if (myHash->findHashValue(tempString.m_data) >= 0)
			{
				words_list->add(tempString);
				i = i + temp_len - 1;
				break;
			}
		}
	}

	return words_list;
}
