//
//  MyString.h
//  Chinese_Divider2
//
//  Created by ShaoYushan on 2016/11/11.
//  Copyright © 2016年 邵钰杉. All rights reserved.
//

#ifndef MyString_h
#define MyString_h

# include <iostream>
# include <memory>
# include <cString>
# include <wchar.h>
# include <locale>
using namespace std;

class MyString
{
private:

public:
    //data数据
    wchar_t *m_data;

    //默认的构造函数
    MyString();

    //使用const wchar_t* 来初始化
    MyString(const wchar_t* ptr);

    //拷贝构造函数
    MyString(const MyString& rhs);

    //析构函数
    ~MyString();

    //查找子串位置(用KMP算法实现)
    long long indexOf(const MyString& pattern);

    //截取字符串
    MyString subString(int pos, int length);

    //连接字符串,把right接到this->m_data后面
    void concat( MyString& right);

    //重载赋值运算符
    MyString& operator=(const MyString& rhs);

    //重载+运算符
    MyString operator+(const MyString& rhs);

	//重载+运算符
	MyString operator+(wchar_t right);

    //重载下标
    wchar_t operator[](const unsigned int index);

    //重载判等 == 运算符
    bool operator==(const MyString& rhs);

	 //重载判等 > 运算符
    bool operator > (const MyString& rhs);

	 //重载判等 < 运算符
    bool operator < (const MyString& rhs);

    //重载 ！= 运算符
    bool operator !=(const MyString& rhs);

    //重载输出运算符<<
    friend wostream& operator<<(wostream& output, const MyString &rhs);

	//重载输出运算符>>
	friend wistream& operator>>(wistream& input, MyString &rhs);

};


#endif /* MyString_h */
