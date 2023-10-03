/********************************************************************************
** Form generated from reading UI file 'debug_helper.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUG_HELPER_H
#define UI_DEBUG_HELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_debug_helperClass
{
public:
    QMenuBar *menuBar;
    //QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *debug_helperClass)
    {
        if (debug_helperClass->objectName().isEmpty())
            debug_helperClass->setObjectName("debug_helperClass");
        debug_helperClass->resize(600, 400);
        menuBar = new QMenuBar(debug_helperClass);
        menuBar->setObjectName("menuBar");
        debug_helperClass->setMenuBar(menuBar);
        /*mainToolBar = new QToolBar(debug_helperClass);
        mainToolBar->setObjectName("mainToolBar");
        debug_helperClass->addToolBar(mainToolBar);*/
        centralWidget = new QWidget(debug_helperClass);
        centralWidget->setObjectName("centralWidget");
        debug_helperClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(debug_helperClass);
        statusBar->setObjectName("statusBar");
        debug_helperClass->setStatusBar(statusBar);

        retranslateUi(debug_helperClass);

        QMetaObject::connectSlotsByName(debug_helperClass);
    } // setupUi

    void retranslateUi(QMainWindow *debug_helperClass)
    {
        debug_helperClass->setWindowTitle(QCoreApplication::translate("debug_helperClass", "debug_helper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class debug_helperClass: public Ui_debug_helperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUG_HELPER_H
