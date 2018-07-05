#pragma once
#include <QObject>
#include "qthread.h"
#include "MyInterface2.h"

class My_Thread : public QObject {
	Q_OBJECT

public:
	My_Thread(QObject * parent = Q_NULLPTR);
	~My_Thread();

	MyHashTable* hash_Dictionary;
	MyAVLTree<MyString>* AVL_words;
	void run();
signals:
	void threadFinish();

private:
	
};
