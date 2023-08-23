#include "debug_helper.h"
#include<QtWidgets/QApplication>
int main(int argc,char* argv[])
{
	QApplication a(argc,argv);
	debug_helper w;
	w.show();
	a.exec();
	return 0;
}