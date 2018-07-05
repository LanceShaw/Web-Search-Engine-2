#include "gui.h"

gui::gui(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::guiClass)
{
	//主窗口设置
	ui->setupUi(this);
	this->setFixedSize(600,700);
	this->setWindowTitle("HTML Search Engine");

	//文本框初始化
	searchEdit = new QLineEdit(this);
	searchEdit->setGeometry(30, 30, 400, 30);

	//按钮初始化
	searchButton = new QPushButton("Search",this);
	searchButton->setGeometry(450, 30, 70, 30);

	//显示窗口初始化
	showEdit = new QTextEdit(this);
	showEdit->setReadOnly(true);
	showEdit->setGeometry(30, 70, 490, 500);

	//下一篇与上一篇按钮
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



//高亮选中的词汇
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

//在QTextEdit中显示网页
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

//搜索并显示网页
void gui::search()
{
	showEdit->clear();
	QString line = searchEdit->text();

	//对搜索栏分词产生的list
	 word_list = divideWords(mythread->hash_Dictionary, QString_to_myString(line));

	//对分词搜索后产生的链表
	MyPageList* searchList = searchPageList(mythread->AVL_words, word_list);

	 curr_docu = searchList->head;

	showHtml();
	
}

//移到下一篇文章
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

//移到前一篇文章
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