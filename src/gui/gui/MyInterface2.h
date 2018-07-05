#ifndef MyInterface2_h
#define MyInterface2_h

//这个头文件写第二次实验的主要接口

#include "MyInterface.h"
#include "MyHtmLInfo.h"
#include "MyPageList.h"
#include "MyHashTable.h"
#include "MyHtmLInfo.h"

#include <windows.h>
using namespace std;

//initDictionary(...):该接口执行载入词库等初始化操作,并把结果保存为一棵AVL树
//但是最后比较了AVL树和Hash表的效率，选择了使用Hash表来存储词典
MyAVLTree<MyString>* AVL_initDictionary();

//最后生成的AVL树：每分出一个单词，就把它加到AVL树中树中
//这个接口实现分词后实时把词加入AVL树
void test2_divideAndInsertWords(MyHashTable* myHash, MyString& myString, MyAVLTree<MyString>* myAVL, int docID);


//直接读取500个网页的信息，得到他们的分词结果，并用分的词去持续优化AVL树中的节点
MyAVLTree<MyString>* AVL_HandleAllHtml(MyHashTable* myHash);

//用已经存起来的网页的信息去得到分词产生的AVL树
MyAVLTree<MyString>* AVL_GetInfoFromSavedHtml(MyHtmLInfo* myList, MyHashTable* myHash);

//把每次从query中读取的一行返回一个结果
void line_to_result(MyAVLTree<MyString>* tree, wstring& line, MyHashTable* myHash, wostream& output);

//这个函数实现读取query.txt文件并将结果输出到result.txt文件的功能
void query_to_result();

void query_to_result2();

//string转化为wstring
std::wstring  StringToWString(const std::string& s);



#endif