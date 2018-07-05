#include "MyString.h"


//Ĭ�ϵĹ��캯��
MyString::MyString()
{
	m_data = new wchar_t[1];
	*m_data = '\0';//��ʵ����Ϊ0
}

//ʹ��const wchar_t* ����ʼ��
MyString::MyString(const wchar_t* ptr)
{
	if (NULL == ptr)
	{
		m_data = new wchar_t[1];
		*m_data = '\0';
	}
	else
	{
		unsigned long len = wcslen(ptr);
		m_data = new wchar_t[len + 1];
		//        for( unsigned long i = 0 ; i < len ; i++)
		//        {
		//            m_data[i] = ptr[i];
		//        }
		wcscpy(m_data, ptr);
	}
}

//�������캯��
MyString::MyString(const MyString& rhs)
{
	unsigned long len = wcslen(rhs.m_data);
	m_data = new wchar_t[len + 1];
	//    for( unsigned long  i = 0 ; i < len ; i++)
	//    {
	//        m_data[i] = rhs.m_data[i];
	//    }
	wcscpy(m_data, rhs.m_data);
}

//���� == �����
bool MyString::operator ==(const MyString& rhs)
{
	int result = wcscmp(m_data, rhs.m_data);
	if (0 == result)
		return true;
	else
		return false;
}

//���� > �����
bool MyString::operator >(const MyString& rhs)
{
	int result = wcscmp(m_data, rhs.m_data);
	if (result > 0)
		return true;
	else
		return false;
}

//���� < �����
bool MyString::operator < (const MyString& rhs)
{
	int result = wcscmp(m_data, rhs.m_data);
	if (result < 0)
		return true;
	else
		return false;
}

//���� != �����
bool MyString::operator !=(const MyString& rhs)
{
	int result = wcscmp(m_data, rhs.m_data);
	if (0 == result)
		return false;
	else
		return true;
}

//���� ��ֵ = ������
MyString& MyString::operator =(const MyString& rhs)
{
	if (this != &rhs)
	{
		delete[] m_data;
		unsigned long  len = wcslen(rhs.m_data);
		m_data = new wchar_t[len + 1];
		for (unsigned long i = 0; i < len; i++)
		{
			m_data[i] = rhs.m_data[i];
		}
		m_data[len] = '\0';
	}
	return *this;
}

//���������+
MyString MyString::operator+(const MyString &rhs)
{
	MyString newMyString;
	if (!rhs.m_data)
		newMyString = *this;
	else if (!m_data)
		newMyString = rhs;
	else {
		newMyString.m_data = new wchar_t[wcslen(m_data) + wcslen(rhs.m_data) + 1];
		wcscpy(newMyString.m_data, m_data);
		wcscat(newMyString.m_data, rhs.m_data);
	}
	return newMyString;
}

//����+�����
MyString MyString::operator+(wchar_t right)
{
	MyString newMyString;
	unsigned long len = wcslen(m_data);
	newMyString.m_data = new wchar_t[len + 2];

	for (unsigned long i = 0; i < len; i++)
	{
		newMyString.m_data[i] = m_data[i];
	}
	newMyString.m_data[len] = right;
	newMyString.m_data[len + 1] = '\0';
	return newMyString;
}

//�����±������[]
wchar_t MyString::operator [](const unsigned int index)
{
	return m_data[index];
}

//��������
MyString::~MyString()
{
	delete[] m_data;
}

//�������������� <<
wostream& operator<<(wostream& output, const MyString &rhs)
{
	unsigned long len = wcslen(rhs.m_data);
	for (unsigned long i = 0; i < len; i++)
	{
		output << rhs.m_data[i];
	}
	return output;
}

//��������������� >>
wistream& operator >> (wistream& input, MyString &rhs)
{
	rhs.m_data = new wchar_t[2];
	rhs.m_data[0] = input.get();
	rhs.m_data[1] = '\0';
	return input;
}

//ȡ���Ӵ�
MyString MyString::subString(int pos, int length)
{
	MyString newMyString;
	unsigned long this_length = wcslen(this->m_data);
	if (pos < 0 || pos >= this_length || pos + length - 1 >= this_length)
	{
		return newMyString;
	}
	else
	{
		newMyString.m_data = new wchar_t[length + 1];
		for (int i = 0; i < length; i++)
		{
			newMyString.m_data[i] = this->m_data[pos + i];
		}
		newMyString.m_data[length] = '\0';
	}
	return newMyString;
}


//�����ַ���
void MyString::concat(MyString& right)
{
	unsigned long left_len = wcslen(this->m_data);
	unsigned long right_len = wcslen(right.m_data);
	unsigned long total_length = left_len + right_len;

	wchar_t* temp = new wchar_t[total_length + 1];

	for (unsigned long i = 0; i < left_len; i++)
	{
		temp[i] = this->m_data[i];
	}
	for (unsigned long i = left_len; i < total_length; i++)
	{
		temp[i] = right.m_data[i - left_len];
	}

	temp[total_length] = '\0';
	delete[] m_data;
	m_data = temp;
}


//�����Ӵ�λ��
long long MyString::indexOf(const MyString& pattern)//KMP�㷨ʵ��
{
	const long long target_length = wcslen(this->m_data);
	const long long pattern_length = wcslen(pattern.m_data);
	long long * overlay_value = new long long[pattern_length];
	overlay_value[0] = -1;
	long long index = 0;
	for (unsigned long i = 1; i < pattern_length; ++i)
	{
		index = overlay_value[i - 1];
		while (index >= 0 && pattern.m_data[index + 1] != pattern.m_data[i])
		{
			index = overlay_value[index];
		}
		if (pattern.m_data[index + 1] == pattern.m_data[i])
		{
			overlay_value[i] = index + 1;
		}
		else
		{
			overlay_value[i] = -1;
		}
	}
	//match algorithm start
	long long pattern_index = 0;
	long long target_index = 0;
	while (pattern_index < pattern_length && target_index < target_length)
	{
		if (this->m_data[target_index] == pattern.m_data[pattern_index])
		{
			++target_index;
			++pattern_index;
		}
		else if (pattern_index == 0)
		{
			++target_index;
		}
		else
		{
			pattern_index = overlay_value[pattern_index - 1] + 1;
		}
	}

	if (pattern_index == pattern_length)
	{
		delete[] overlay_value;
		return target_index - pattern_index;
	}
	else
	{
		delete[] overlay_value;
		return -1;
	}
}


//���Ժ���
void MyString_test()
{

	const wchar_t* p0 = L"���";
	//wcout<< wcslen(p0)<<endl;


	//subMyString ����
	const wchar_t* p1 = L"�������й�����";
	MyString a(p1);
	wcout << a.m_data;
	cout << wcslen(p1) << endl;

	const wchar_t* p2 = L"hello,world";
	MyString b(p2);
	cout << wcslen(p2) << endl;



	//concat ����
	a.concat(b);
	wcout << a;
	cout << endl;
	cout << wcslen(a.m_data) << endl;

	//indexOf ����
	//    const wchar_t* p2 = L"����";
	// MyString test(p2);
	//cout << a.indexOf(test) << endl;
}