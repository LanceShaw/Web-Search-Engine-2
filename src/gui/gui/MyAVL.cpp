#include "MyAVL.h"

//测试文件
void MyAVLTree_Test1()
{
	//一些中文单词
	wstring warr[] = { L"梅西",L"爱情",L"加油",L"在意",L"卡卡",L"胜利",L"北京",L"西安" };
	int ilen = sizeof(warr) / sizeof(warr[0]);

	//用自己的MyString
	MyString *arr = new MyString[ilen];
	for (int i = 0; i < ilen; i++)
	{
		MyString temp(&warr[i][0]);
		arr[i] = temp;
	}

	//建立一棵树
	MyAVLTree<MyString>* tree = new MyAVLTree<MyString>();

	cout << "== 依次添加: ";

	for (int i = 0; i<ilen; i++)
	{
		wcout << arr[i];
		cout << " ";
		//不断插入元素
		tree->insert(arr[i]);
	}
	//测试remove函数
	tree->remove(arr[4]);


	//测试search函数
	const wchar_t* p1 = L"石油";
	MyString a1(p1);
	MyAVLTreeNode<MyString>* a11 = tree->search(a1);


	cout << "\n== 高度: " << tree->height() << endl;
	// 销毁二叉树
	tree->destroy();
}
