#include "debug_helper.h"
#include<QtWidgets/QApplication>
#include<string>
int main(int argc,char* argv[])
{
	QApplication a(argc,argv);
	Main_Window w;
	w.show();
	a.exec();
	return 0;
}