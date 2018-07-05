#include "MyInterface.h"


//�ж��ַ������Ƿ��йؼ���,���Ƿ�Ƕ�������0����û�У�1�������±��⡢2�����������ơ�3��������
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

//�ж��ַ������Ƿ��йؼ����Լ�֮��Ĵ���,��Ƕ�����
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

//ÿһ��ת���ַ���Ӧһ��wchar_t�ַ�
wchar_t escapeCharacter_to_wchar(MyString& testString)
{
	if (wcscmp(&testString.m_data[0], L"&quot;") == 0)
	{
		return L'"';
	}
	if (wcscmp(&testString.m_data[0], L"&ldquo;") == 0)
	{
		return L'��';
	}
	if (wcscmp(&testString.m_data[0], L"&rdquo;") == 0)
	{
		return L'��';
	}
	if (wcscmp(&testString.m_data[0], L"&mdash;") == 0)
	{
		return L'��';
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
		return L'��';
	}
	if (wcscmp(&testString.m_data[0], L"&deg;") == 0)
	{
		return L'��';
	}
	return NULL;
}

//������string�е�ת���ַ�ȥ��
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
				if (right_pos >= left_pos + 8)//�����8���ַ�
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

//extractInfo()�ýӿ�ִ�н�����ҳ���������ؽ��Ϊһ���ַ�������,ÿһ���ڵ����һ����ҳ��һ����Ϣ
MyStringLinkedList* extractInfo(MyStringNode* current_node)
{

	MyStringLinkedList* list_info = new MyStringLinkedList;//���ص��ַ�������
	MyStack<MyString> my_stack;//�õ���ջ
	wchar_t *wchar_string = current_node->data.m_data;//�������ĵ�wchar_t
	MyString MyString_html = current_node->data;//���µ�string����
	unsigned long total_length = wcslen(wchar_string);//�������ĵĳ���

	MyString MyString_content;//�洢���ĵ��ַ���

							  //һЩflag
	int flag_end = 0;//��������ж��Ƿ�Ҫ��ȡ��Ϣ�����ַ���������,����������ȡ���µı��⡢���⡢���ߡ�����,����ֻ�����޷�����������Ƕ�ױ�ǩ�����
	int flag_content = 0;//�����Ƿ�������
	int flag_bracket = 0;//�����쳣�����ţ���ʼΪ0��������������1��������������0
	int num_content = 0; //����content������
	int flag_hasReadAuthor = 0;//�Ƿ�������ߣ��������ߺ��ȡ��һ�����ģ������һ�����ĺ���0

							   //����
	unsigned long left_pos = 0;//������
	unsigned long right_pos = 0;//������

								//��ʼ��ҳ����
	for (unsigned long i = 0; i < total_length; i++)
	{
		//��'<'�����
		if (wchar_string[i] == '<')
		{
			if (flag_bracket == 0)
			{
				left_pos = i;//�޸�����ֵ
				flag_bracket = 1;//�޸�����flag
				if (flag_content == 1 && flag_hasReadAuthor == 1)//�����������ڶ����ģ���������Ϣ���ֺ������
				{
					MyString tempString = MyString_html.subString(right_pos + 1, left_pos - right_pos - 1);
					MyString_content.concat(tempString);
				}
			}
		}

		//�ǡ�/�������
		else if (wchar_string[i] == '/')
		{
			if (wchar_string[i - 1] == '<' || wchar_string[i + 1] == '>')//��Ч��'<'
			{
				flag_end = 1;//�޸Ľ���flag
			}
		}

		//�ǡ�>�������
		else if (wchar_string[i] == '>')
		{
			if (flag_bracket == 1)//����������
			{
				flag_bracket = 0;//�޸�flagֵ

				if (flag_end == 0)//ǰ��ǩ���
				{
					right_pos = i;//��¼������
					MyString tempString = MyString_html.subString(left_pos, right_pos - left_pos + 1);
					if (int_myString_conclude_keywords(tempString) > 0)//��������ؼ���
					{
						my_stack.push(tempString);//ѹջ
					}
					else if (tempString.indexOf(MyString(L"class=\"content\"")) >= 0)
					{
						flag_content = 1;//��ʾ��������
						num_content++;//����num_content
					}
				}

				else if (flag_end == 1)//���ǩ���
				{
					flag_end = 0;
					if (int_myString_conclude_keywords(my_stack.Top()) > 0)
					{

						MyString left_string = MyString_conclude_keywords(my_stack.Top());
						MyString right_string = MyString_html.subString(right_pos + 1, left_pos - right_pos - 1);
						if (int_myString_conclude_keywords(my_stack.Top()) == 3)//�������ߣ�
						{
							flag_hasReadAuthor = 1;//��flag��1

												   //�ж����߽�β�Ƿ���','
							int tempLen = wcslen(right_string.m_data);
							if (right_string.m_data[tempLen - 1] == L',' || right_string.m_data[tempLen - 1] == L'��')//�����β�����Ļ���Ӣ�ĵĶ���
							{
								right_string.m_data[tempLen - 1] = '\0';
							}

						}
						left_string.concat(right_string);
						list_info->add(left_string);
					}
					my_stack.pop();
					if (flag_content == 1)//���ڶ�����
					{
						right_pos = i;//�޸�������ֵ
						MyString tempString = MyString_html.subString(left_pos, i - left_pos + 1);
						if (tempString.indexOf(MyString(L"/div")) >= 0)
						{
							flag_content = 0;//������������
							flag_hasReadAuthor = 0;//�޸�flagֵΪ0
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

//initDictionary(...):�ýӿ�ִ������ʿ�ȳ�ʼ������
MyHashTable* Hash_initDictionary()
{
	MyHashTable* myHashTable = new MyHashTable;

	std::locale chs("chs");
	std::wifstream ifs("Dictionary/�ʿ�_ansi.dic");
	ifs.imbue(chs);
	std::wcout.imbue(chs);
	std::wstring line;
	while (std::getline(ifs, line))
	{
		myHashTable->addHashValue(line);

	}
	return myHashTable;

}

//divideWords(...):�ýӿ�ִ�зִʲ��������ؽ������Ϊ�ַ�������
MyStringLinkedList* divideWords(MyHashTable* myHash, MyString& myString)
{
	//���ص��ַ�������
	MyStringLinkedList* words_list = new MyStringLinkedList;

	//������ҳ�ļ��ַ�����
	unsigned long string_total_length = wcslen(myString.m_data);

	//������󳤶�
	//int word_max_length = myHash->max_len;
	int word_max_length = 4;
	//�ִ�
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
