#ifndef MyDocuList_h
#define MyDocuList_h

class MyDoculistNode
{
public:
	int DocID;//出现该单词的文档
	int Times;//该单词出现的次数
	MyDoculistNode* next;//指向下一个节点
	MyDoculistNode* before;//指向前一个节点
	MyDoculistNode():Times(0),DocID(0),next(nullptr),before(nullptr){}//默认构造函数
};

template <class T>
class MyDoculist
{
public:

	T term;//单词
	MyDoculistNode* head;//文档链表的头节点

	//默认构造函数
	MyDoculist();
	MyDoculist(T key, int docID);

	void Add(int DocumentID);//在单词对应的文档链表中，新加这个文档的记录，或者给原记录中的Times++
	int Search(int DocumentID);//搜索这个文档中是否出现了该单词，返回该单词出现的次数
	void Edit(  MyDoculistNode* prev_node,MyDoculistNode* current_node);//处理如下的情况：更新一个节点后它比前面的节点的Times大
	void Remove(int DocumentID);//删除某文档在这个单词中的记录

};

//默认构造函数
template <class T>
MyDoculist<T>::MyDoculist():head(nullptr)
{
	
}

template <class T>
MyDoculist<T>::MyDoculist(T key,int docID):term(key)
{
	head = new MyDoculistNode;
	head->DocID = docID;
	head->Times++;
}

//处理如下的情况：更新一个节点后它比前面的节点的Times大
template <class T>
void MyDoculist<T>::Edit(MyDoculistNode* prev_node, MyDoculistNode* current_node)
{
	//处理需要调整次序的情况，比较复杂，需要做如下处理
	while(prev_node->Times < current_node->Times)
	{
		//交换prev_node与current_node的信息
		int prev_times = prev_node->Times;
		int prev_ID = prev_node->DocID;
		int curr_times = current_node->Times;
		int curr_ID = current_node->DocID;

		prev_node->DocID = curr_ID;
		prev_node->Times = curr_times;
		current_node->Times = prev_times;
		current_node->DocID = prev_ID;

		prev_node = prev_node->before;//回溯
		current_node = current_node->before;
		if(prev_node == nullptr)//如果已经到头了
		{
			break;
		}
	}

	return;
}

//在单词对应的文档链表中，新加这个文档的记录，或者给原记录中的Times++
template <class T>
void MyDoculist<T>::Add(int DocumentID)
{
	if( this->head == nullptr)//如果头节点为空
	{
		head = new MyDoculistNode;
		head->DocID = DocumentID;
		head->Times++;
	}
	else//如果头节点不空
	{
		MyDoculistNode* prev_node = this->head;
		MyDoculistNode* current_node = this->head;
		while(  current_node != nullptr && DocumentID != current_node->DocID)
		{
			prev_node = current_node;
			current_node = current_node->next;
		}

		if(current_node != nullptr)//出现相等的情况
		{
			current_node->Times++;//次数相加
			this->Edit(prev_node,current_node);
		}
		else//空的情况,说明还没有这个节点
		{
			prev_node->next  = new MyDoculistNode;//创建新节点
			prev_node->next->DocID = DocumentID;//赋值ID
			prev_node->next->Times++;//times++
			prev_node->next->before = prev_node;//指针指向位置变化
		}

	}
	
}

//搜索这个文档中是否出现了该单词，返回该单词出现的次数
template <class T>
int MyDoculist<T>::Search(int DocumentID)
{
	MyDoculistNode* current_node = this->head;
	while( current_node != nullptr && current_node->DocID != DocumentID)
	{
		current_node = current_node->next;		
	}

	//如果是空，证明不存在这个单词
	if( current_node == nullptr)
	{
		return 0;
	}
	else
	{
		return current_node->Times;
	}
}

//删除某文档在这个单词中的记录
template <class T>
void MyDoculist<T>::Remove(int DocumentID)
{
	if( this->head == nullptr)//如果头节点为空
	{
		return;
	}
	else//如果头节点不空
	{
		MyDoculistNode* prev_node = this->head;
		MyDoculistNode* current_node = this->head;
		while( current_node != nullptr && DocumentID != current_node->DocID )
		{
			prev_node = current_node;
			current_node = current_node->next;
		}

		if(current_node != nullptr )//找到了对应的节点
		{
			prev_node->next = current_node->next;
			current_node->next = nullptr;
		}
		else//没有找到对应的节点
		{
			return;
		}

	}
}

#endif