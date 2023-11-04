#pragma once
#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_debug_helper.h"
#include<QtWidgets/QWidget>
#include<QtWidgets/QMainWindow>
#include<QSettings>
#include<QPushButton>
#include<QCloseEvent>
#include<QIcon>
#include<QLineEdit>
#include<QLabel>
#include<QByteArray>
#include<QDialog>
#include<QFont>
#include<QFileDialog>
#include<QTextEdit>
#include<QString>
#include<QTextBrowser>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QProcess>
#include<QGridLayout>
#include<QFileDialog>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<fstream>
class debug_helper: public QMainWindow
{
public:
	int folder_path_size=0,run_status=-3,debugging=0;//run_status=-1表示CE,=0表示成功编译,=1表示RE,=2表示成功运行
	QPushButton *start_next_button,*step_into_button,*step_out_button,*step_over_button,*stop_button,*compile_button,*run_button,*compile_and_run_button,*compare_button,*breakpoint_window_button;
	QDialog *folder_select_dialog,*program_select_dialog,*breakpoint_dialog;
	QWidget *folder_select_window,*program_select_window,*breakpoint_window;
	QLineEdit *folder_path_edit,*program_path_edit,*compare_edit_1,*compare_edit_2;
	QTextEdit *breakpoint_input;
	QTextBrowser *debug_viewer;
	QLabel *tip_1,*tip_2;
	QAction *open_file_action,*compile_action,*run_action,*compile_and_run_action,*compare_action,*start_next_action,*step_into_action,*step_out_action,*step_over_action,*stop_action;
	QProcess *gdb;
	QGridLayout *layout;
	debug_helper(QWidget* parent=nullptr);
	int str_find(char *,const char *);
	void str_putin(char *,int *,const char *);
	void menubar_init();
	void main_init();
	/*void select_folder();
	void folder_path_input();
	void select_program();
	void program_path_input();*/
	void open_file();
	void path_view();
	void run();
	void compile();
	void compile_and_run();
	//void show_the_run_status();
	void compile_error_view();
	void compare();
	void start_next_button_do();
	void step_into_button_do();
	void step_out_button_do();
	void step_over_button_do();
	void stop_button_do();
	void breakpoint_select();
	void breakpoint_putin_array();
	//void set_color();
	Ui::debug_helperClass ui;

private:

};
#endif MAINWINDOW_H
