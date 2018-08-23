/********************************************************************************
** Form generated from reading UI file 'sever_tcp.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEVER_TCP_H
#define UI_SEVER_TCP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sever_tcpClass
{
public:
    QWidget *centralWidget;
    QPushButton *Server_Start_Bt;
    QPushButton *Send_info_Bt;
    QTextEdit *textEdit;
    QPlainTextEdit *plainTextEdit;
    QFrame *line;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sever_tcpClass)
    {
        if (sever_tcpClass->objectName().isEmpty())
            sever_tcpClass->setObjectName(QStringLiteral("sever_tcpClass"));
        sever_tcpClass->resize(600, 400);
        centralWidget = new QWidget(sever_tcpClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Server_Start_Bt = new QPushButton(centralWidget);
        Server_Start_Bt->setObjectName(QStringLiteral("Server_Start_Bt"));
        Server_Start_Bt->setGeometry(QRect(130, 290, 75, 23));
        Send_info_Bt = new QPushButton(centralWidget);
        Send_info_Bt->setObjectName(QStringLiteral("Send_info_Bt"));
        Send_info_Bt->setGeometry(QRect(340, 290, 75, 23));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(70, 220, 431, 61));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(70, 10, 431, 191));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 200, 591, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        sever_tcpClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(sever_tcpClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        sever_tcpClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sever_tcpClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sever_tcpClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(sever_tcpClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        sever_tcpClass->setStatusBar(statusBar);

        retranslateUi(sever_tcpClass);
        QObject::connect(Server_Start_Bt, SIGNAL(clicked()), sever_tcpClass, SLOT(My_Server_Start()));
        QObject::connect(Send_info_Bt, SIGNAL(clicked()), sever_tcpClass, SLOT(My_Send_Info()));

        QMetaObject::connectSlotsByName(sever_tcpClass);
    } // setupUi

    void retranslateUi(QMainWindow *sever_tcpClass)
    {
        sever_tcpClass->setWindowTitle(QApplication::translate("sever_tcpClass", "sever_tcp", 0));
        Server_Start_Bt->setText(QApplication::translate("sever_tcpClass", "\345\274\200\345\220\257", 0));
        Send_info_Bt->setText(QApplication::translate("sever_tcpClass", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class sever_tcpClass: public Ui_sever_tcpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEVER_TCP_H
