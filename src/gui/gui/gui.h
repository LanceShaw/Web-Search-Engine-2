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
	//һЩ��Ա����
	void para_init();
	void showHtml();
	void highLight();
	//һЩ���ӻ���Ա����
	QPushButton* searchButton;
	QLineEdit* searchEdit;
	QTextEdit* showEdit;
	QPushButton* nextPageButton;
	QPushButton* prevPageButton;

	My_Thread* mythread;

	//һЩ��Ա����
	MyHashTable* hash_Dictionary ;
	MyAVLTree<MyString>* AVL_words;

	//��ǰ���ı�
	MyPageListNode* curr_docu;
	//��Ҫ�����Ĵʻ�
	MyStringLinkedList* word_list;

public slots:
	void search();
	//�Ƶ���һƪ����
	void moveToNext();
	//�Ƶ�ǰһƪ����
	void moveToPrev();
private:
	Ui::guiClass *ui;
};




#endif // GUI_H
