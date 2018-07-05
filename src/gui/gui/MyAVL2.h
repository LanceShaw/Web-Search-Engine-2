#ifndef MyAVL2_h
#define MyAVL2_h
//这是我写的第二个AVL树，之前的AVL树用递归实现的插入，效率太低
//于是我自己又写了另一种非递归实现的AVL树，非递归实现的话需要使用平衡因子
//下面是使用平衡因子需要的预定义
#define LH +1   // 左高 
#define EH 0    // 等高 
#define RH -1   // 右高 

#include <iomanip>
#include <iostream>
#include "MyString.h"
#include "MyDocuList.h"
using namespace std;

//节点
template <class T>
class MyAVLTree2Node{
    public:
        T key;                // 关键字(键值)
        int bf;         // 平衡因子
		int DF;      //单词出现在多少文章中
		int occur;   //单词出现的总次数
		int current_docID;//现阶段的文章ID
        MyAVLTree2Node *left;    // 左孩子
        MyAVLTree2Node *right;    // 右孩子
		MyDoculist<T>* html_docuList;  // 单词对应的文档链表

        MyAVLTreeNode(T value, MyAVLTree2Node *l, MyAVLTree2Node *r):
			key(value), height(0),DF(0),occur(0),left(l),right(r),html_docuList(nullptr),current_docID(-1) {}
};

//树的定义
template <class T>
class MyAVL2Tree2 {
private:
    MyAVLTree2Node<T> *mRoot;    // 根结点

public:
    MyAVL2Tree2();
    ~MyAVL2Tree2();

	// 销毁AVL树
    void destroy();
private:
	// 销毁AVL树
    void destroy(MyAVLTreeNode<T>* &tree);
};


//构造函数
template <class T>
MyAVL2Tree2<T>::MyAVL2Tree2():mRoot(NULL)
{
}

// 析构函数
template <class T>
MyAVL2Tree2<T>::~MyAVL2Tree2() 
{
    destroy(mRoot);
}

// 销毁AVL树
template <class T>
void MyAVL2Tree2<T>::destroy(MyAVLTree2Node<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T>
void MyAVL2Tree2<T>::destroy()
{
    destroy(mRoot);
}
#endif