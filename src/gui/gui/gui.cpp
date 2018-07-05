#include "gui.h"

gui::gui(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::guiClass)
{
	//����������
	ui->setupUi(this);
	this->setFixedSize(600,700);
	this->setWindowTitle("HTML Search Engine");

	//�ı����ʼ��
	searchEdit = new QLineEdit(this);
	searchEdit->setGeometry(30, 30, 400, 30);

	//��ť��ʼ��
	searchButton = new QPushButton("Search",this);
	searchButton->setGeometry(450, 30, 70, 30);

	//��ʾ���ڳ�ʼ��
	showEdit = new QTextEdit(this);
	showEdit->setReadOnly(true);
	showEdit->setGeometry(30, 70, 490, 500);

	//��һƪ����һƪ��ť
	nextPageButton = new QPushButton("next",this);
	nextPageButton->setGeometry(470, 600, 50, 30);
	prevPageButton = new QPushButton("before", this);
	prevPageButton->setGeometry(30, 600, 50, 30);



	mythread = new My_Thread;

	QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	QObject::connect(nextPageButton, SIGNAL(clicked()), this, SLOT(moveToNext()));
	QObject::connect(prevPageButton, SIGNAL(clicked()), this, SLOT(moveToPrev()));
}


void gui::para_init()
{
	show();
	mythread->run();

}

gui::~gui()
{

}



//����ѡ�еĴʻ�
void gui::highLight()
{
	MyStringNode* p = word_list->head;
	while (p != nullptr)
	{
		QString stltemp = myString_to_QString(p->data);
		QTextDocument* document = showEdit->document();
		QTextCursor highlight_cursor(document);
		QTextCharFormat color_format(highlight_cursor.charFormat());
		color_format.setForeground(Qt::red);
		while (!highlight_cursor.isNull() && !highlight_cursor.atEnd())
		{
			highlight_cursor = document->find(stltemp, highlight_cursor, QTextDocument::FindCaseSensitively);
			if (!highlight_cursor.isNull())
			{
				highlight_cursor.mergeCharFormat(color_format);
			}
		}
		p = p->next;
	}
}

//��QTextEdit����ʾ��ҳ
void gui::showHtml()
{
	showEdit->clear();
	if (curr_docu != nullptr)
	{
		MyString htmlString = read_Html(&curr_docu->filename[0]);
		MyString htmlString1 = delete_escapeCharacter(htmlString);
		QString QTempString = myString_to_QString(htmlString1);
		showEdit->setHtml(QTempString);
		this->highLight();
	}
	else
	{
		showEdit->append("End of Html!");
	}
}

//��������ʾ��ҳ
void gui::search()
{
	showEdit->clear();
	QString line = searchEdit->text();

	//���������ִʲ�����list
	 word_list = divideWords(mythread->hash_Dictionary, QString_to_myString(line));

	//�Էִ����������������
	MyPageList* searchList = searchPageList(mythread->AVL_words, word_list);

	 curr_docu = searchList->head;

	showHtml();
	
}

//�Ƶ���һƪ����
void gui::moveToNext()
{
	if (curr_docu != nullptr)
	{
		if (curr_docu->next != nullptr)
		{
			curr_docu = curr_docu->next;
			showHtml();
		}
		else
		{
			showEdit->clear();
			showEdit->append("End of Html!");
		}
	}
	
}

//�Ƶ�ǰһƪ����
void gui::moveToPrev()
{
	if (curr_docu != nullptr)
	{
		if (curr_docu->before != nullptr)
		{
			curr_docu = curr_docu->before;
			showHtml();
		}
		else
		{
			showEdit->clear();
			showEdit->append("End of Html!");
		}
	}
}