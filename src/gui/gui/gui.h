#ifndef gui_h
#define gui_h

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "MyInterface2.h"
#include "qlabel.h"
#include "qimage.h"
#include "qlineedit.h"
#include "qtextedit.h"
#include "qpushbutton.h"
#include "qstring.h"
#include "qpaintdevice.h"
#include "qmovie.h"
#include "my_thread.h"

class gui : public QMainWindow
{
	Q_OBJECT

public:
	gui(QWidget *parent = 0);
	~gui();
	//一些成员函数
	void para_init();
	void showHtml();
	void highLight();
	//一些可视化成员变量
	QPushButton* searchButton;
	QLineEdit* searchEdit;
	QTextEdit* showEdit;
	QPushButton* nextPageButton;
	QPushButton* prevPageButton;

	My_Thread* mythread;

	//一些成员变量
	MyHashTable* hash_Dictionary ;
	MyAVLTree<MyString>* AVL_words;

	//当前的文本
	MyPageListNode* curr_docu;
	//需要高亮的词汇
	MyStringLinkedList* word_list;

public slots:
	void search();
	//移到下一篇文章
	void moveToNext();
	//移到前一篇文章
	void moveToPrev();
private:
	Ui::guiClass *ui;
};




#endif // GUI_H
