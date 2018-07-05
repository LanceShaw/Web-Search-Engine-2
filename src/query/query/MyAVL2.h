#ifndef MyAVL2_h
#define MyAVL2_h
//������д�ĵڶ���AVL����֮ǰ��AVL���õݹ�ʵ�ֵĲ��룬Ч��̫��
//�������Լ���д����һ�ַǵݹ�ʵ�ֵ�AVL�����ǵݹ�ʵ�ֵĻ���Ҫʹ��ƽ������
//������ʹ��ƽ��������Ҫ��Ԥ����
#define LH +1   // ��� 
#define EH 0    // �ȸ� 
#define RH -1   // �Ҹ� 

#include <iomanip>
#include <iostream>
#include "MyString.h"
#include "MyDocuList.h"
using namespace std;

//�ڵ�
template <class T>
class MyAVLTree2Node{
    public:
        T key;                // �ؼ���(��ֵ)
        int bf;         // ƽ������
		int DF;      //���ʳ����ڶ���������
		int occur;   //���ʳ��ֵ��ܴ���
		int current_docID;//�ֽ׶ε�����ID
        MyAVLTree2Node *left;    // ����
        MyAVLTree2Node *right;    // �Һ���
		MyDoculist<T>* html_docuList;  // ���ʶ�Ӧ���ĵ�����

        MyAVLTreeNode(T value, MyAVLTree2Node *l, MyAVLTree2Node *r):
			key(value), height(0),DF(0),occur(0),left(l),right(r),html_docuList(nullptr),current_docID(-1) {}
};

//���Ķ���
template <class T>
class MyAVL2Tree2 {
private:
    MyAVLTree2Node<T> *mRoot;    // �����

public:
    MyAVL2Tree2();
    ~MyAVL2Tree2();

	// ����AVL��
    void destroy();
private:
	// ����AVL��
    void destroy(MyAVLTreeNode<T>* &tree);
};


//���캯��
template <class T>
MyAVL2Tree2<T>::MyAVL2Tree2():mRoot(NULL)
{
}

// ��������
template <class T>
MyAVL2Tree2<T>::~MyAVL2Tree2() 
{
    destroy(mRoot);
}

// ����AVL��
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