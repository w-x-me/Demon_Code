/********************************************************************************
** Form generated from reading UI file 'timer_example.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMER_EXAMPLE_H
#define UI_TIMER_EXAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Timer_ExampleClass
{
public:
    QWidget *centralWidget;
    QLabel *Image_Show_label;
    QPushButton *Start_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Timer_ExampleClass)
    {
        if (Timer_ExampleClass->objectName().isEmpty())
            Timer_ExampleClass->setObjectName(QStringLiteral("Timer_ExampleClass"));
        Timer_ExampleClass->resize(722, 569);
        centralWidget = new QWidget(Timer_ExampleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Image_Show_label = new QLabel(centralWidget);
        Image_Show_label->setObjectName(QStringLiteral("Image_Show_label"));
        Image_Show_label->setGeometry(QRect(0, 0, 611, 501));
        Start_btn = new QPushButton(centralWidget);
        Start_btn->setObjectName(QStringLiteral("Start_btn"));
        Start_btn->setGeometry(QRect(640, 40, 75, 23));
        Timer_ExampleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Timer_ExampleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 722, 23));
        Timer_ExampleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Timer_ExampleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Timer_ExampleClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Timer_ExampleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Timer_ExampleClass->setStatusBar(statusBar);

        retranslateUi(Timer_ExampleClass);
        QObject::connect(Start_btn, SIGNAL(clicked()), Timer_ExampleClass, SLOT(Start()));

        QMetaObject::connectSlotsByName(Timer_ExampleClass);
    } // setupUi

    void retranslateUi(QMainWindow *Timer_ExampleClass)
    {
        Timer_ExampleClass->setWindowTitle(QApplication::translate("Timer_ExampleClass", "Timer_Example", 0));
        Image_Show_label->setText(QApplication::translate("Timer_ExampleClass", "TextLabel", 0));
        Start_btn->setText(QApplication::translate("Timer_ExampleClass", "\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Timer_ExampleClass: public Ui_Timer_ExampleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMER_EXAMPLE_H
