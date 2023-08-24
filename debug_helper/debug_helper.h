#pragma once
#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_debug_helper.h"
#include<QtWidgets/QWidget>
#include<QtWidgets/QMainWindow>
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
class debug_helper: public QMainWindow
{
public:
	int folder_path_size=0,run_status;//run_status=-1表示CE,=0表示成功编译,=1表示RE,=2表示成功运行
	QPushButton *start_next_button,*step_into_button,*step_out_button,*step_over_button,*stop_button,*compile_button,*compile_and_run_button,*compare_button;
	QDialog *folder_select_dialog,*program_select_dialog;
	QWidget *folder_select_window,*program_select_window;
	QLineEdit *folder_path_edit,*program_path_edit,*compare_edit_1,*compare_edit_2;
	QTextBrowser *path_viewer;
	QLabel *status_view;
	QAction *select_program_action,*select_folder_action,*compile_action,*compile_and_run_action,*compare_action;
	debug_helper(QWidget* parent=nullptr);
	int str_find(char *,const char *);
	void str_putin(char *,int *,const char *);
	void menubar_init();
	void select_folder();
	void folder_path_input();
	void select_program();
	void program_path_input();
	void main_init();
	void run();
	void compile();
	void compile_and_run();
	void show_the_run_status();
	void path_view();
	void compile_error_view();
	void compare();
	Ui::debug_helperClass ui;

private:

};
#endif MAINWINDOW_H
