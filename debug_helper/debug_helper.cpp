#include "debug_helper.h"

char folder_path[10000],program_path[10000],output_to[100],compile_information_char[100000],code[1000][1000];

Main_Window::Main_Window(QWidget* parent):QWidget(parent)
{
	font.setFamily("JetBrains Mono");
	menubar_init();
	select_folder();
	compile_view=new QLabel(this);
	this->setWindowIcon(QIcon(":/debug_helper/icons/run-with-debugging-tb.png"));
	this->setFixedSize(820,550);
	button_init();
}
void Main_Window::menubar_init()
{
	Menubar=new QMenuBar(this);
	Menubar->setFont(font);
	select_program_action=new QAction("Select Program");
	select_program_action->setShortcut(tr("Ctrl+O"));
	program_select_menu=new QMenu("Files",Menubar);
	program_select_menu->setFont(font);
	program_select_menu->addAction(select_program_action);
	Menubar->addMenu(program_select_menu);
	Menubar->addSeparator();
	connect(select_program_action,&QAction::triggered,this,&Main_Window::select_program);
	Menubar->show();
}
void Main_Window::path_view()
{
	path_viewer=new QTextBrowser(this);
	path_viewer->setFont(font);
	path_viewer->setText(QString(program_path));
	path_viewer->resize(504,25);
	path_viewer->move(286,32);
	path_viewer->show();
}
void Main_Window::compile_error_view()
{
	QDialog* compile_error_dialog=new QDialog(this);
	QWidget* compile_error_window=new QWidget(compile_error_dialog);
	compile_error_dialog->resize(600,400);
	compile_error_window->resize(600,400);
	compile_error_dialog->setWindowTitle(QString("Compile Error"));
	QTextBrowser* error_text_browser=new QTextBrowser(compile_error_window);
	error_text_browser->setFont(font);
	error_text_browser->resize(600,400);
	FILE* in=fopen(output_to,"r");
	int sum=0;
	while(!feof(in))
	{
		char tmp='\0';
		if(fscanf(in,"%c",&tmp))
		{
			compile_information_char[sum++]=tmp;
			if(sum==100000) break;
		}
	}
	error_text_browser->setText(QString(compile_information_char));
	error_text_browser->show();
	compile_error_dialog->show();
}
void Main_Window::code_read_out_find()
{
	if(!can_debug) return;
	FILE* in=fopen(program_path,"r");
	int hang=0,lie=0;
	while(!feof(in))
	{
		char tmp='\0';
		if(fscanf(in,"%c",&tmp))
		{
			if(tmp=='\n')
			{
				hang++;
				lie=0;
				continue;
			}
			if(hang==1000) break;
			code[hang][lie++]=tmp;
		}
	}
}
void Main_Window::folder_path_input()
{
	QByteArray tmp=folder_path_edit->displayText().toLatin1();
	folder_path_size=strlen(tmp.data());
	for(int i=0; i<strlen(tmp.data()); i++)
	{
		folder_path[i]=tmp.data()[i];
		program_path[i]=folder_path[i];
		output_to[i]=folder_path[i];
	}
	if(folder_path[folder_path_size-1]!='/'&&folder_path[folder_path_size-1]!='\\')
	{
		folder_path[folder_path_size]='/';
		program_path[folder_path_size]='/';
		output_to[folder_path_size]='/';
		folder_path_size++;
	}
	strcat(output_to,"debug_helper_compile.txt");
}
void Main_Window::select_folder()
{
	folder_select_dialog=new QDialog(this);
	folder_select_window=new QWidget(folder_select_dialog);
	folder_select_dialog->resize(600,50);
	folder_select_window->resize(600,50);
	folder_select_dialog->setWindowTitle(QString("Input the folder path which you want to work in:"));
	folder_path_edit=new QLineEdit(folder_select_window);
	folder_path_edit->resize(550,25);
	folder_path_edit->move(25,10);
	folder_path_edit->setFont(font);
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&Main_Window::folder_path_input);
	connect(folder_path_edit,&QLineEdit::returnPressed,folder_select_dialog,&QDialog::close);
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&Main_Window::path_view);
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&Main_Window::select_program);
	folder_select_dialog->show();
}
void Main_Window::program_path_input()
{
	memset(program_path,0,sizeof(program_path));
	QByteArray tmp=program_path_edit->displayText().toLatin1();
	for(int i=0; i<folder_path_size; i++)
		program_path[i]=folder_path[i];
	for(int i=0; i<strlen(tmp.data()); i++)
		program_path[i+folder_path_size]=tmp.data()[i];
}
void Main_Window::select_program()
{
	program_select_dialog=new QDialog(this);
	program_select_window=new QWidget(program_select_dialog);
	program_select_dialog->resize(550,40);
	program_select_window->resize(550,40);
	program_select_dialog->setWindowTitle(QString("Input the name of source code(.cpp) which you want to debug:"));
	program_path_edit=new QLineEdit(program_select_window);
	program_path_edit->resize(500,25);
	program_path_edit->move(25,10);
	program_path_edit->setFont(font);
	connect(program_path_edit,&QLineEdit::returnPressed,this,&Main_Window::program_path_input);
	connect(program_path_edit,&QLineEdit::returnPressed,program_select_dialog,&QDialog::close);
	connect(program_path_edit,&QLineEdit::returnPressed,this,&Main_Window::path_view);
	program_select_dialog->show();
}
void Main_Window::button_init()
{
	//start next button
	start_next_button=new QPushButton("Start/Continue(F5)",this);
	start_next_button->setIcon(QIcon(":/debug_helper/icons/continue-tb.png"));
	start_next_button->resize(150,30);
	start_next_button->move(30,490);
	start_next_button->setFont(font);
	//step into button
	step_into_button=new QPushButton("Step Into(F8)",this);
	step_into_button->setIcon(QIcon(":/debug_helper/icons/stepinto-tb.png"));
	step_into_button->resize(125,30);
	step_into_button->move(210,490);
	step_into_button->setFont(font);
	//step out button
	step_out_button=new QPushButton("Step Out(F6)",this);
	step_out_button->setIcon(QIcon(":/debug_helper/icons/stepout-tb.png"));
	step_out_button->resize(120,30);
	step_out_button->move(365,490);
	step_out_button->setFont(font);
	//step over button
	step_over_button=new QPushButton("Step Over(F7)",this);
	step_over_button->setIcon(QIcon(":/debug_helper/icons/stepover-tb.png"));
	step_over_button->resize(125,30);
	step_over_button->move(515,490);
	step_over_button->setFont(font);
	//stop button
	stop_button=new QPushButton("Stop(Shift+F5)",this);
	stop_button->setIcon(QIcon(":/debug_helper/icons/stop-tb.png"));
	stop_button->resize(120,30);
	stop_button->move(670,490);
	stop_button->setFont(font);
	//build button
	build_button=new QPushButton("Build(F9)",this);
	build_button->setIcon(QIcon(":/debug_helper/icons/build-tb.png"));
	build_button->resize(115,30);
	build_button->move(30,30);
	build_button->setFont(font);
	build_button->setShortcut(tr("F9"));
	connect(build_button,&QPushButton::clicked,this,&Main_Window::build);
}
void Main_Window::build()
{
	char tmp[10000]="",args[1000]="-g -std=c++14 -Wall";//You can rewrite the args as g++ compile args.
	int cnt=-1;
	tmp[++cnt]='g';tmp[++cnt]='+';tmp[++cnt]='+';tmp[++cnt]=' ';
	//cpp path
	tmp[++cnt]='"';
	for(int i=0;i<strlen(program_path);i++)
		tmp[++cnt]=program_path[i];
	tmp[++cnt]='"';
	//program path
	tmp[++cnt]=' ';
	tmp[++cnt]='-';tmp[++cnt]='o';tmp[++cnt]=' ';
	tmp[++cnt]='"';
	for(int i=0;i<strlen(program_path)-4;i++)
		tmp[++cnt]=program_path[i];
	tmp[++cnt]='"';
	tmp[++cnt]=' ';
	//compile args
	for(int i=0;i<strlen(args);i++) tmp[++cnt]=args[i];
	tmp[++cnt]=' ';tmp[++cnt]='2';tmp[++cnt]='>';tmp[++cnt]=' ';
	int result=system(strcat(tmp,output_to));//wrong=1
	can_debug=(!result);
	show_the_compile_success(result);
}
void Main_Window::show_the_compile_success(int happen)
{
	if(happen==1)
	{
		compile_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CE.png")));
		compile_view->resize(90,18);
	}
	else
	{
		compile_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CS.png")));
		compile_view->resize(130,18);
	}
	compile_view->move(150,35);
	compile_view->show();
	memset(compile_information_char,0,sizeof(compile_information_char));
	if(happen==1)
		compile_error_view();
	else
		code_read_out_find();
}