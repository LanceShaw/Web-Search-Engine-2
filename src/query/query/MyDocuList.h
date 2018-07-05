#ifndef MyDocuList_h
#define MyDocuList_h

class MyDoculistNode
{
public:
	int DocID;//���ָõ��ʵ��ĵ�
	int Times;//�õ��ʳ��ֵĴ���
	MyDoculistNode* next;//ָ����һ���ڵ�
	MyDoculistNode* before;//ָ��ǰһ���ڵ�
	MyDoculistNode():Times(0),DocID(0),next(nullptr),before(nullptr){}//Ĭ�Ϲ��캯��
};

template <class T>
class MyDoculist
{
public:

	T term;//����
	MyDoculistNode* head;//�ĵ������ͷ�ڵ�

	//Ĭ�Ϲ��캯��
	MyDoculist();
	MyDoculist(T key, int docID);

	void Add(int DocumentID);//�ڵ��ʶ�Ӧ���ĵ������У��¼�����ĵ��ļ�¼�����߸�ԭ��¼�е�Times++
	int Search(int DocumentID);//��������ĵ����Ƿ�����˸õ��ʣ����ظõ��ʳ��ֵĴ���
	void Edit(  MyDoculistNode* prev_node,MyDoculistNode* current_node);//�������µ����������һ���ڵ������ǰ��Ľڵ��Times��
	void Remove(int DocumentID);//ɾ��ĳ�ĵ�����������еļ�¼

};

//Ĭ�Ϲ��캯��
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

//�������µ����������һ���ڵ������ǰ��Ľڵ��Times��
template <class T>
void MyDoculist<T>::Edit(MyDoculistNode* prev_node, MyDoculistNode* current_node)
{
	//������Ҫ���������������Ƚϸ��ӣ���Ҫ�����´���
	while(prev_node->Times < current_node->Times)
	{
		//����prev_node��current_node����Ϣ
		int prev_times = prev_node->Times;
		int prev_ID = prev_node->DocID;
		int curr_times = current_node->Times;
		int curr_ID = current_node->DocID;

		prev_node->DocID = curr_ID;
		prev_node->Times = curr_times;
		current_node->Times = prev_times;
		current_node->DocID = prev_ID;

		prev_node = prev_node->before;//����
		current_node = current_node->before;
		if(prev_node == nullptr)//����Ѿ���ͷ��
		{
			break;
		}
	}

	return;
}

//�ڵ��ʶ�Ӧ���ĵ������У��¼�����ĵ��ļ�¼�����߸�ԭ��¼�е�Times++
template <class T>
void MyDoculist<T>::Add(int DocumentID)
{
	if( this->head == nullptr)//���ͷ�ڵ�Ϊ��
	{
		head = new MyDoculistNode;
		head->DocID = DocumentID;
		head->Times++;
	}
	else//���ͷ�ڵ㲻��
	{
		MyDoculistNode* prev_node = this->head;
		MyDoculistNode* current_node = this->head;
		while(  current_node != nullptr && DocumentID != current_node->DocID)
		{
			prev_node = current_node;
			current_node = current_node->next;
		}

		if(current_node != nullptr)//������ȵ����
		{
			current_node->Times++;//�������
			this->Edit(prev_node,current_node);
		}
		else//�յ����,˵����û������ڵ�
		{
			prev_node->next  = new MyDoculistNode;//�����½ڵ�
			prev_node->next->DocID = DocumentID;//��ֵID
			prev_node->next->Times++;//times++
			prev_node->next->before = prev_node;//ָ��ָ��λ�ñ仯
		}

	}
	
}

//��������ĵ����Ƿ�����˸õ��ʣ����ظõ��ʳ��ֵĴ���
template <class T>
int MyDoculist<T>::Search(int DocumentID)
{
	MyDoculistNode* current_node = this->head;
	while( current_node != nullptr && current_node->DocID != DocumentID)
	{
		current_node = current_node->next;		
	}

	//����ǿգ�֤���������������
	if( current_node == nullptr)
	{
		return 0;
	}
	else
	{
		return current_node->Times;
	}
}

//ɾ��ĳ�ĵ�����������еļ�¼
template <class T>
void MyDoculist<T>::Remove(int DocumentID)
{
	if( this->head == nullptr)//���ͷ�ڵ�Ϊ��
	{
		return;
	}
	else//���ͷ�ڵ㲻��
	{
		MyDoculistNode* prev_node = this->head;
		MyDoculistNode* current_node = this->head;
		while( current_node != nullptr && DocumentID != current_node->DocID )
		{
			prev_node = current_node;
			current_node = current_node->next;
		}

		if(current_node != nullptr )//�ҵ��˶�Ӧ�Ľڵ�
		{
			prev_node->next = current_node->next;
			current_node->next = nullptr;
		}
		else//û���ҵ���Ӧ�Ľڵ�
		{
			return;
		}

	}
}

#endif