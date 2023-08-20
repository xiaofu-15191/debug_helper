#pragma once

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
#include<Qstring>
#include<QTextBrowser>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
class Main_Window: public QWidget
{

public:
	Main_Window(QWidget* parent=nullptr);

private:
	int folder_path_size=0,can_debug=0;
	QMenuBar *Menubar;
	QMenu *program_select_menu;
	QPushButton *start_next_button,*step_into_button,*step_out_button,*step_over_button,*stop_button,*build_button;
	QDialog *folder_select_dialog,*program_select_dialog;
	QWidget *folder_select_window,*program_select_window;
	QLineEdit *folder_path_edit,*program_path_edit;
	QTextBrowser *path_viewer;
	QLabel *compile_view;
	QFont font;
	QAction* select_program_action;
	void menubar_init();
	void select_folder();
	void folder_path_input();
	void select_program();
	void program_path_input();
	void button_init();
	void build();
	void show_the_compile_success(int);
	void path_view();
	void compile_error_view();
	void code_read_out_find();
	Ui::debug_helperClass ui;
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