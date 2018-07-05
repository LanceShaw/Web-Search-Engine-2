#include "MyAVL.h"

//�����ļ�
void MyAVLTree_Test1()
{
	//һЩ���ĵ���
	wstring warr[] = { L"÷��",L"����",L"����",L"����",L"����",L"ʤ��",L"����",L"����" };
	int ilen = sizeof(warr) / sizeof(warr[0]);

	//���Լ���MyString
	MyString *arr = new MyString[ilen];
	for (int i = 0; i < ilen; i++)
	{
		MyString temp(&warr[i][0]);
		arr[i] = temp;
	}

	//����һ����
	MyAVLTree<MyString>* tree = new MyAVLTree<MyString>();

	cout << "== �������: ";

	for (int i = 0; i<ilen; i++)
	{
		wcout << arr[i];
		cout << " ";
		//���ϲ���Ԫ��
		tree->insert(arr[i]);
	}
	//����remove����
	tree->remove(arr[4]);


	//����search����
	const wchar_t* p1 = L"ʯ��";
	MyString a1(p1);
	MyAVLTreeNode<MyString>* a11 = tree->search(a1);


	cout << "\n== �߶�: " << tree->height() << endl;
	// ���ٶ�����
	tree->destroy();
}
