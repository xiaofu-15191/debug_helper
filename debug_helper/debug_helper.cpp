#include "debug_helper.h"

char folder_path[10000],program_path[10000],output_to[100],compile_information_char[100000],code[1100][1100],profile_path[10000];
int nxt[1010];

Main_Window::Main_Window(QWidget* parent):QWidget(parent)
{
	this->setFont(QFont("Fira Code, 微软雅黑"));
	this->setWindowIcon(QIcon(":/debug_helper/icons/run-with-debugging-tb.png"));
	this->setFixedSize(840,550);
	menubar_init();
	select_folder();
	status_view=new QLabel(this);
	button_init();
}
int Main_Window::str_find(char * source,const char *going_to_find)
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
void Main_Window::str_putin(char *put_in,int *cnt,const char *source)
{
	int source_size=strlen(source);
	for(int i=0;i<source_size;i++)
		put_in[++(*cnt)]=source[i];
}
void Main_Window::menubar_init()
{
	Menubar=new QMenuBar(this);
	select_program_action=new QAction("打开文件");
	select_program_action->setShortcut(tr("Ctrl+O"));
	connect(select_program_action,&QAction::triggered,this,&Main_Window::select_program);
	select_folder_action=new QAction("打开文件夹");
	select_folder_action->setShortcut(tr("Ctrl+K,Ctrl+O"));
	connect(select_folder_action,&QAction::triggered,this,&Main_Window::select_folder);
	compile_action=new QAction("编译");
	compile_action->setShortcut(tr("F9"));
	connect(compile_action,&QAction::triggered,this,&Main_Window::compile);
	compile_and_run_action=new QAction("编译运行");
	compile_and_run_action->setShortcut(tr("F11"));
	connect(compile_and_run_action,&QAction::triggered,this,&Main_Window::compile_and_run);
	file_menu=new QMenu("文件",Menubar);
	file_menu->addAction(select_program_action);
	file_menu->addAction(select_folder_action);
	run_menu=new QMenu("运行",Menubar);
	run_menu->addAction(compile_action);
	run_menu->addAction(compile_and_run_action);
	Menubar->addMenu(file_menu);
	Menubar->addMenu(run_menu);
	Menubar->addSeparator();
	Menubar->show();
}
void Main_Window::path_view()
{
	path_viewer=new QTextBrowser(this);
	path_viewer->setFont(QFont("Fira Code"));
	path_viewer->setText(QString(program_path));
	path_viewer->resize(510,26);
	path_viewer->move(280,32);
	path_viewer->show();
}
void Main_Window::compile_error_view()
{
	QDialog* compile_error_dialog=new QDialog(this);
	QWidget* compile_error_window=new QWidget(compile_error_dialog);
	compile_error_dialog->resize(600,400);
	compile_error_window->resize(600,400);
	compile_error_dialog->setWindowTitle(QString("编译错误"));
	QTextBrowser* error_text_browser=new QTextBrowser(compile_error_window);
	error_text_browser->resize(600,400);
	error_text_browser->setFont(QFont("Fira Code"));
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
void Main_Window::folder_path_input()
{
	QByteArray tmp=folder_path_edit->displayText().toLatin1();
	folder_path_size=strlen(tmp.data());
	char temp[10000]="";
	for(int i=0; i<strlen(tmp.data()); i++)
	{
		folder_path[i]=tmp.data()[i];
		program_path[i]=folder_path[i];
		output_to[i]=folder_path[i];
		profile_path[i]=folder_path[i];
		temp[i]=folder_path[i];
	}
	if(folder_path[folder_path_size-1]!='/'&&folder_path[folder_path_size-1]!='\\')
	{
		folder_path[folder_path_size]='/';
		program_path[folder_path_size]='/';
		output_to[folder_path_size]='/';
		profile_path[folder_path_size]='/';
		temp[folder_path_size]='/';
		folder_path_size++;
	}
	int profile_path_size=folder_path_size-1;
	str_putin(profile_path,&profile_path_size,".debug_helper_profile");
	strcat(output_to,"debug_helper_compile.txt");
}
void Main_Window::select_folder()
{
	folder_select_dialog=new QDialog(this);
	folder_select_window=new QWidget(folder_select_dialog);
	folder_select_dialog->resize(600,50);
	folder_select_window->resize(600,50);
	folder_select_dialog->setWindowTitle(QString("输入工作目录："));
	folder_path_edit=new QLineEdit(folder_select_window);
	folder_path_edit->resize(550,25);
	folder_path_edit->move(25,10);
	folder_path_edit->setFont(QFont("Fira Code"));
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
	program_select_dialog->setWindowTitle(QString("输入Cpp文件名："));
	program_path_edit=new QLineEdit(program_select_window);
	program_path_edit->resize(500,25);
	program_path_edit->move(25,10);
	program_path_edit->setFont(QFont("Fira Code"));
	connect(program_path_edit,&QLineEdit::returnPressed,this,&Main_Window::program_path_input);
	connect(program_path_edit,&QLineEdit::returnPressed,program_select_dialog,&QDialog::close);
	connect(program_path_edit,&QLineEdit::returnPressed,this,&Main_Window::path_view);
	program_select_dialog->show();
}
void Main_Window::button_init()
{
	//start next button
	start_next_button=new QPushButton("开始/继续调试(F5)",this);
	start_next_button->setIcon(QIcon(":/debug_helper/icons/continue-tb.png"));
	start_next_button->resize(150,30);
	start_next_button->move(30,490);
	//step into button
	step_into_button=new QPushButton("单步进入(F8)",this);
	step_into_button->setIcon(QIcon(":/debug_helper/icons/stepinto-tb.png"));
	step_into_button->resize(125,30);
	step_into_button->move(210,490);
	//step out button
	step_out_button=new QPushButton("单步跳出(F6)",this);
	step_out_button->setIcon(QIcon(":/debug_helper/icons/stepout-tb.png"));
	step_out_button->resize(120,30);
	step_out_button->move(365,490);
	//step over button
	step_over_button=new QPushButton("逐过程(F7)",this);
	step_over_button->setIcon(QIcon(":/debug_helper/icons/stepover-tb.png"));
	step_over_button->resize(125,30);
	step_over_button->move(515,490);
	//stop button
	stop_button=new QPushButton("停止调试(Shift+F5)",this);
	stop_button->setIcon(QIcon(":/debug_helper/icons/stop-tb.png"));
	stop_button->resize(140,30);
	stop_button->move(670,490);
	//compile button
	compile_button=new QPushButton("编译(F9)",this);
	compile_button->setIcon(QIcon(":/debug_helper/icons/compile-tb.png"));
	compile_button->resize(115,30);
	compile_button->move(30,30);
	connect(compile_button,&QPushButton::clicked,this,&Main_Window::compile);
	//compile and run button
	compile_and_run_button=new QPushButton("编译运行(F11)",this);
	compile_and_run_button->setIcon(QIcon(":/debug_helper/icons/run-tb.png"));
	compile_and_run_button->resize(115,30);
	compile_and_run_button->move(155,30);
	connect(compile_and_run_button,&QPushButton::clicked,this,&Main_Window::compile_and_run);
}
void Main_Window::run()
{
	char tmp[10100]="";
	int cnt=-1;
	for(int i=0;i<strlen(program_path)-4;i++)
		tmp[++cnt]=program_path[i];
	str_putin(tmp,&cnt," && pause");
	int result=system(tmp);
	if(result!=0)
		run_status=1;
	else
		run_status=2;
	show_the_run_status();
}
void Main_Window::compile()
{
	run_status=0;
	char args[1000]="";
	/*fgets(args,sizeof(args),profile);
	if(strlen(args)<2)
	{
		str_putin(args,&args_size,"-g -std=c++14 -Wall");
		fprintf(profile,"-g -std=c++14 -Wall\n");
	}*/
	int args_size=-1;
	std::ifstream fin(profile_path);
	fin>>args;
	fin.close();
	std::ofstream fout(profile_path);
	if(strlen(args)<2)
	{
		char temp[10000]="";
		int temp_size=-1;
		#ifdef _WIN32
			str_putin(temp,&temp_size,"del ");
		#else
			str_putin(temp,&temp_size,"rm ");
		#endif
		str_putin(temp,&temp_size,profile_path);
		system(temp);
		str_putin(args,&args_size,"-g -std=c++14 -Wall");
		fout<<"-g -std=c++14 -Wall";
	}
	if(args[strlen(args)-1]=='\n')
		args[strlen(args)-1]=' ';
	char tmp[10000]="";
	int cnt=-1;
	str_putin(tmp,&cnt,"g++ \"");
	str_putin(tmp,&cnt,program_path);
	str_putin(tmp,&cnt,"\" -o \"");
	for(int i=0;i<strlen(program_path)-4;i++)
		tmp[++cnt]=program_path[i];
	str_putin(tmp,&cnt,"\" ");
	//compile args
	str_putin(tmp,&cnt,args);
	str_putin(tmp,&cnt," 2> ");
	str_putin(tmp,&cnt,output_to);
	int result=system(tmp);
	if(result!=0)
	{
		run_status=-1;
		show_the_run_status();
		compile_error_view();
	}
	else
		show_the_run_status();
}
void Main_Window::compile_and_run()
{
	compile();
	if(run_status==0)
		run();
}
void Main_Window::show_the_run_status()
{
	if(run_status==-1)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CE.png")));
		status_view->resize(90,18);
	}
	else if(run_status==0)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/CS.png")));
		status_view->resize(108,18);
	}
	else if(run_status==1)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/RE.png")));
		status_view->resize(90,18);
	}
	else if(run_status==2)
	{
		status_view->setPixmap(QPixmap(QString(":/debug_helper/icons/RS.png")));
		status_view->resize(84,18);
	}
	status_view->move(30,75);
	status_view->show();
}