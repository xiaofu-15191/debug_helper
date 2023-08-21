#pragma once
#pragma execution_character_set("utf-8")
#include "ui_debug_helper.h"
#include<QtWidgets/QWidget>
#include<QPushbutton>
#include<QIcon>
#include<QLineedit>
#include<QLabel>
#include<QBytearray>
#include<QDialog>
#include<QFont>
#include<QFileDialog>
#include<QString>
#include<QTextBrowser>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<fstream>
class Main_Window: public QWidget
{

public:
	int folder_path_size=0,run_status;//run_status=-1表示CE,=0表示成功编译,=1表示RE,=2表示成功运行
	QMenuBar *Menubar;
	QMenu *file_menu,*run_menu;
	QPushButton *start_next_button,*step_into_button,*step_out_button,*step_over_button,*stop_button,*compile_button,*compile_and_run_button;
	QDialog *folder_select_dialog,*program_select_dialog;
	QWidget *folder_select_window,*program_select_window;
	QLineEdit *folder_path_edit,*program_path_edit;
	QTextBrowser *path_viewer;
	QLabel *status_view;
	QAction *select_program_action,*select_folder_action,*compile_action,*compile_and_run_action;
	int str_find(char *,const char *);
	void str_putin(char *,int *,const char *);
	void menubar_init();
	void select_folder();
	void folder_path_input();
	void select_program();
	void program_path_input();
	void button_init();
	void run();
	void compile();
	void compile_and_run();
	void show_the_run_status();
	void path_view();
	void compile_error_view();
	Ui::debug_helperClass ui;
	Main_Window(QWidget* parent=nullptr);

private:
	
};

//class Program_Select_Window : public QWidget
//{
//	Q_OBJECT
//public:
//	char *path;
//	Program_Select_Window(QWidget *parent = nullptr);
//	~Program_Select_Window();
//private:
//	QLabel *text;
//	QLineEdit *program_path;
//	Ui::debug_helperClass ui;
//	void path_input();
//};