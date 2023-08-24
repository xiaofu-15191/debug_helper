﻿#include "debug_helper.h"

char folder_path[10000],program_path[10000],error_output_to[100],compile_information_char[100000],code[1100][1100],profile_path[10000],args[10000],temp_str[10000],compare_1[10000],compare_2[10000],compare_path[10000],compare_information_char[100000];
int nxt[1010];
debug_helper::debug_helper(QWidget* parent):QMainWindow(parent)
{
	const QSize MAIN_SIZE_MAX=QSize(16777215,16777215),MAIN_SIZE_MIN=QSize(750,450);
	this->setMaximumSize(MAIN_SIZE_MAX);
	this->setMinimumSize(MAIN_SIZE_MIN);
	this->setWindowFlag(Qt::WindowMaximizeButtonHint,true);
	path_viewer=new QTextBrowser(this);
	path_viewer->hide();
	folder_select_dialog=new QDialog(this);
	folder_select_window=new QWidget(folder_select_dialog);
	folder_path_edit=new QLineEdit(folder_select_window);
	program_select_dialog=new QDialog(this);
	program_select_window=new QWidget(program_select_dialog);
	program_path_edit=new QLineEdit(program_select_window);
	this->setFont(QFont("Fira Code, 微软雅黑"));
	this->setWindowIcon(QIcon(":/debug_helper/icons/run-with-debugging-tb.png"));
	this->setWindowTitle(QString("Debug Helper"));
	this->resize(750,450);
	menubar_init();
	select_folder();
	status_view=new QLabel(this);
	status_view->move(375,75);
	main_init();
}
int debug_helper::str_find(char * source,const char *going_to_find)
{
	for(int i=0;i<strlen(source);i++)
	{
		bool ans=1;
		for(int j=0,k=i;j<strlen(going_to_find);j++,k++)
		{
			if(k==strlen(source)-1&&j<strlen(going_to_find)-1||going_to_find[j]!=source[k])
			{
				ans=0;
				break;
			}
		}
		if(ans==1) return i;
	}
	return 0x3f3f3f3f;
}
void debug_helper::str_putin(char *put_in,int *cnt,const char *source)
{
	int source_size=strlen(source);
	for(int i=0;i<source_size;i++)
		put_in[++(*cnt)]=source[i];
}
void debug_helper::menubar_init()
{
	select_program_action=new QAction("打开文件",nullptr);
	select_program_action->setShortcut(tr("Ctrl+O"));
	connect(select_program_action,&QAction::triggered,this,&debug_helper::select_program);
	select_folder_action=new QAction("打开文件夹",nullptr);
	select_folder_action->setShortcut(tr("Ctrl+K,Ctrl+O"));
	connect(select_folder_action,&QAction::triggered,this,&debug_helper::select_folder);
	compile_action=new QAction("编译",nullptr);
	compile_action->setShortcut(tr("F9"));
	connect(compile_action,&QAction::triggered,this,&debug_helper::compile);
	compile_and_run_action=new QAction("编译运行",nullptr);
	compile_and_run_action->setShortcut(tr("F11"));
	connect(compile_and_run_action,&QAction::triggered,this,&debug_helper::compile_and_run);
	compare_action=new QAction("对拍",nullptr);
	compare_action->setShortcut(tr("Alt+F11"));
	connect(compare_action,&QAction::triggered,this,&debug_helper::compare);
	QMenu *file_menu=this->menuBar()->addMenu(tr("文件"));
	file_menu->addAction(select_program_action);
	file_menu->addAction(select_folder_action);
	QMenu *run_menu=this->menuBar()->addMenu(tr("运行"));
	run_menu->addAction(compile_action);
	run_menu->addAction(compile_and_run_action);
	run_menu->addAction(compare_action);
	this->menuBar()->addSeparator();
	this->menuBar()->show();
}
void debug_helper::path_view()
{
	path_viewer->setFont(QFont("Fira Code"));
	path_viewer->setText(QString(program_path));
	path_viewer->resize(450,26);
	path_viewer->move(280,32);
	path_viewer->show();
}
void debug_helper::compile_error_view()
{
	QDialog* compile_error_dialog=new QDialog(this);
	QWidget* compile_error_window=new QWidget(compile_error_dialog);
	compile_error_dialog->setAttribute(Qt::WA_DeleteOnClose);
	compile_error_window->setAttribute(Qt::WA_DeleteOnClose);
	compile_error_dialog->resize(600,400);
	compile_error_window->resize(600,400);
	compile_error_dialog->setWindowTitle(QString("编译错误"));
	QTextBrowser* error_text_browser=new QTextBrowser(compile_error_window);
	error_text_browser->setAttribute(Qt::WA_DeleteOnClose);
	error_text_browser->resize(600,400);
	error_text_browser->setFont(QFont("Fira Code"));
	memset(compile_information_char,0,sizeof(compile_information_char));
	FILE* in=fopen(error_output_to,"r");
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
void debug_helper::compare()
{
	compile_and_run();
	QByteArray tmp1=compare_edit_1->displayText().toLatin1();
	QByteArray tmp2=compare_edit_2->displayText().toLatin1();
	memset(compare_1,0,sizeof(compare_1));
	memset(compare_2,0,sizeof(compare_2));
	int compare_1_size=-1,compare_2_size=-1;
	strcat(compare_1,tmp1.data());
	strcat(compare_2,tmp2.data());
	memset(temp_str,0,sizeof(temp_str));
	int temp_str_size=-1;
	#if _WIN32
		strcat(temp_str,"chcp 437 && fc \"");
	#else
		strcat(temp_str,"diff \"");
	#endif
	strcat(temp_str,compare_1);
	strcat(temp_str,"\" \"");
	strcat(temp_str,compare_2);
	strcat(temp_str,"\" > \"");
	strcat(temp_str,compare_path);
	strcat(temp_str,"\"");
	system(temp_str);
	QDialog *compare_dialog=new QDialog(this);
	QWidget *compare_window=new QWidget(compare_dialog);
	compare_dialog->setAttribute(Qt::WA_DeleteOnClose);
	compare_window->setAttribute(Qt::WA_DeleteOnClose);
	compare_dialog->resize(600,400);
	compare_window->resize(600,400);
	compare_dialog->setWindowTitle(QString("对拍结果"));
	QTextBrowser *compare_text_browser=new QTextBrowser(compare_window);
	compare_text_browser->setAttribute(Qt::WA_DeleteOnClose);
	compare_text_browser->resize(600,400);
	compare_text_browser->setFont(QFont("Fira Code,微软雅黑"));
	memset(compare_information_char,0,sizeof(compare_information_char));
	FILE *in=fopen(compare_path,"r");
	int sum=0;
	while(!feof(in))
	{
		char tmp='\0';
		if(fscanf(in,"%c",&tmp))
		{
			compare_information_char[sum++]=tmp;
			if(sum==100000) break;
		}
	}
	compare_text_browser->setText(QString(compare_information_char));
	compare_text_browser->show();
	compare_dialog->show();
}
void debug_helper::folder_path_input()
{
	QByteArray tmp=folder_path_edit->displayText().toLatin1();
	folder_path_size=strlen(tmp.data());
	for(int i=0; i<strlen(tmp.data()); i++)
	{
		folder_path[i]=tmp.data()[i];
		program_path[i]=folder_path[i];
		error_output_to[i]=folder_path[i];
		profile_path[i]=folder_path[i];
		compare_path[i]=folder_path[i];
		#if _WIN32
			if(folder_path[i]=='/')
			{
				folder_path[i]='\\';
				program_path[i]='\\';
				error_output_to[i]='\\';
				profile_path[i]='\\';
				compare_path[i]='\\';
			}
		#endif
	}
	if(folder_path[folder_path_size-1]!='/'&&folder_path[folder_path_size-1]!='\\')
	{
		char temp='/';
		#if _WIN32
			temp='\\';
		#endif
		folder_path[folder_path_size]=temp;
		program_path[folder_path_size]=temp;
		error_output_to[folder_path_size]=temp;
		profile_path[folder_path_size]=temp;
		compare_path[folder_path_size]=temp;
		folder_path_size++;
	}
	int profile_path_size=folder_path_size-1;
	strcat(profile_path,".debug_helper_profile");
	strcat(compare_path,".debug_helper_compare");
	strcat(error_output_to,".debug_helper_compile");
	int args_size=-1;
	std::ifstream fin(profile_path);
	fin>>args;
	fin.close();
}
void debug_helper::select_folder()
{
	folder_select_dialog->resize(600,50);
	folder_select_window->resize(600,50);
	folder_select_dialog->setWindowTitle(QString("输入工作目录："));
	folder_path_edit->resize(550,25);
	folder_path_edit->move(25,10);
	folder_path_edit->setFont(QFont("Fira Code"));
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&debug_helper::folder_path_input);
	connect(folder_path_edit,&QLineEdit::returnPressed,folder_select_dialog,&QDialog::close);
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&debug_helper::path_view);
	connect(folder_path_edit,&QLineEdit::returnPressed,this,&debug_helper::select_program);
	folder_select_dialog->show();
}
void debug_helper::program_path_input()
{
	memset(program_path,0,sizeof(program_path));
	QByteArray tmp=program_path_edit->displayText().toLatin1();
	for(int i=0; i<folder_path_size; i++)
		program_path[i]=folder_path[i];
	for(int i=0; i<strlen(tmp.data()); i++)
		program_path[i+folder_path_size]=tmp.data()[i];
	for(int i=0;i<strlen(program_path)-4;i++)
		compare_1[i]=program_path[i];
	int compare_1_size=strlen(compare_1)-1;
	strcat(compare_1,".out");
	for(int i=0;i<strlen(program_path)-4;i++)
		compare_2[i]=program_path[i];
	int compare_2_size=strlen(compare_2)-1;
	strcat(compare_2,".ans");
	compare_edit_1->setText(QString(compare_1));
	compare_edit_2->setText(QString(compare_2));
}
void debug_helper::select_program()
{
	program_select_dialog->resize(550,40);
	program_select_window->resize(550,40);
	program_select_dialog->setWindowTitle(QString("输入Cpp文件名："));
	program_path_edit->resize(500,25);
	program_path_edit->move(25,10);
	program_path_edit->setFont(QFont("Fira Code"));
	connect(program_path_edit,&QLineEdit::returnPressed,this,&debug_helper::program_path_input);
	connect(program_path_edit,&QLineEdit::returnPressed,program_select_dialog,&QDialog::close);
	connect(program_path_edit,&QLineEdit::returnPressed,this,&debug_helper::path_view);
	program_select_dialog->show();
}
void debug_helper::main_init()
{
	//start next button
	start_next_button=new QPushButton("开始/继续调试(F5)",this);
	start_next_button->setIcon(QIcon(":/debug_helper/icons/continue-tb.png"));
	start_next_button->resize(150,30);
	start_next_button->move(15,395);
	//step into button
	step_into_button=new QPushButton("单步进入(F8)",this);
	step_into_button->setIcon(QIcon(":/debug_helper/icons/stepinto-tb.png"));
	step_into_button->resize(125,30);
	step_into_button->move(180,395);
	//step out button
	step_out_button=new QPushButton("单步跳出(F6)",this);
	step_out_button->setIcon(QIcon(":/debug_helper/icons/stepout-tb.png"));
	step_out_button->resize(120,30);
	step_out_button->move(320,395);
	//step over button
	step_over_button=new QPushButton("逐过程(F7)",this);
	step_over_button->setIcon(QIcon(":/debug_helper/icons/stepover-tb.png"));
	step_over_button->resize(125,30);
	step_over_button->move(455,395);
	//stop button
	stop_button=new QPushButton("停止调试(Shift+F5)",this);
	stop_button->setIcon(QIcon(":/debug_helper/icons/stop-tb.png"));
	stop_button->resize(140,30);
	stop_button->move(595,395);
	//compile button
	compile_button=new QPushButton("编译(F9)",this);
	compile_button->setIcon(QIcon(":/debug_helper/icons/compile-tb.png"));
	compile_button->resize(115,30);
	compile_button->move(15,30);
	connect(compile_button,&QPushButton::clicked,this,&debug_helper::compile);
	//compile and run button
	compile_and_run_button=new QPushButton("编译运行(F11)",this);
	compile_and_run_button->setIcon(QIcon(":/debug_helper/icons/run-tb.png"));
	compile_and_run_button->resize(115,30);
	compile_and_run_button->move(145,30);
	connect(compile_and_run_button,&QPushButton::clicked,this,&debug_helper::compile_and_run);
	//compares
	compare_button=new QPushButton("对拍(Alt+F11)",this);
	compare_button->setIcon(QIcon(":/debug_helper/icons/diff-tb.png"));
	compare_button->resize(140,30);
	compare_button->move(305,70);
	compare_edit_1=new QLineEdit(this);
	compare_edit_1->setFont(QFont("Fira Code"));
	compare_edit_1->resize(285,28);
	compare_edit_1->move(15,71);
	compare_edit_2=new QLineEdit(this);
	compare_edit_2->setFont(QFont("Fira Code"));
	compare_edit_2->resize(285,28);
	compare_edit_2->move(450,71);
	connect(compare_button,&QPushButton::clicked,this,&debug_helper::compare);
}
void debug_helper::run()
{
	memset(temp_str,0,sizeof(temp_str));
	int cnt=-1;
	for(int i=0;i<strlen(program_path)-4;i++)
		temp_str[++cnt]=program_path[i];
	strcat(temp_str," && pause");
	int result=system(temp_str);
	if(result!=0)
		run_status=1;
	else
		run_status=2;
	show_the_run_status();
}
void debug_helper::compile()
{
	run_status=0;
	/*fgets(args,sizeof(args),profile);
	if(strlen(args)<2)
	{
		str_putin(args,&args_size,"-g -std=c++14 -Wall");
		fprintf(profile,"-g -std=c++14 -Wall\n");
	}*/
	if(args[strlen(args)-1]=='\n')
		args[strlen(args)-1]=' ';
	memset(temp_str,0,sizeof(temp_str));
	int cnt=-1;
	str_putin(temp_str,&cnt,"g++ \"");
	str_putin(temp_str,&cnt,program_path);
	str_putin(temp_str,&cnt,"\" -o \"");
	for(int i=0;i<strlen(program_path)-4;i++)
		temp_str[++cnt]=program_path[i];
	str_putin(temp_str,&cnt,"\" ");
	//compile args
	str_putin(temp_str,&cnt,args);
	str_putin(temp_str,&cnt," 2> ");
	str_putin(temp_str,&cnt,error_output_to);
	int result=system(temp_str);
	if(result!=0)
	{
		run_status=-1;
		show_the_run_status();
		compile_error_view();
	}
	else
		show_the_run_status();
}
void debug_helper::compile_and_run()
{
	compile();
	if(run_status==0)
		run();
}
void debug_helper::show_the_run_status()
{
	status_view->move(653,35);
	path_viewer->resize(360,26);
	if(run_status==-1)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CE.png")));
		status_view->resize(90,18);
	}
	else if(run_status==0)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CS.png")));
		status_view->resize(90,18);
	}
	else if(run_status==1)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/RE.png")));
		status_view->resize(90,18);
	}
	else if(run_status==2)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/RS.png")));
		status_view->resize(90,18);
	}
	status_view->show();
}