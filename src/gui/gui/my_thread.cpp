#include "my_thread.h"

My_Thread::My_Thread(QObject * parent) : QObject(parent) {
	
}

My_Thread::~My_Thread() {
	
}

void My_Thread::run()
{
	hash_Dictionary = Hash_initDictionary();
	AVL_words = AVL_HandleAllHtml(hash_Dictionary);
	emit threadFinish();
}