#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	gui w;
	w.para_init();
	return a.exec();

}
