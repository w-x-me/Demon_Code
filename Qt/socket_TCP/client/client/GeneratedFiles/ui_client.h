/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clientClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *clientClass)
    {
        if (clientClass->objectName().isEmpty())
            clientClass->setObjectName(QStringLiteral("clientClass"));
        clientClass->resize(600, 400);
        centralWidget = new QWidget(clientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 200, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 200, 75, 23));
        clientClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(clientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        clientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(clientClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        clientClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(clientClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        clientClass->setStatusBar(statusBar);

        retranslateUi(clientClass);
        QObject::connect(pushButton, SIGNAL(clicked()), clientClass, SLOT(connect_server()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), clientClass, SLOT(send_server()));

        QMetaObject::connectSlotsByName(clientClass);
    } // setupUi

    void retranslateUi(QMainWindow *clientClass)
    {
        clientClass->setWindowTitle(QApplication::translate("clientClass", "client", 0));
        pushButton->setText(QApplication::translate("clientClass", "\350\277\236\346\216\245", 0));
        pushButton_2->setText(QApplication::translate("clientClass", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class clientClass: public Ui_clientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
