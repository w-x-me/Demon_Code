/********************************************************************************
** Form generated from reading UI file 'template_macth.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATE_MACTH_H
#define UI_TEMPLATE_MACTH_H

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

class Ui_Template_MacthClass
{
public:
    QWidget *centralWidget;
    QLabel *Image_Show_label;
    QPushButton *Template_Macth_btn;
    QPushButton *Template_Macth_btn_2;
    QLabel *Image_Show_label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Template_MacthClass)
    {
        if (Template_MacthClass->objectName().isEmpty())
            Template_MacthClass->setObjectName(QStringLiteral("Template_MacthClass"));
        Template_MacthClass->resize(915, 647);
        centralWidget = new QWidget(Template_MacthClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Image_Show_label = new QLabel(centralWidget);
        Image_Show_label->setObjectName(QStringLiteral("Image_Show_label"));
        Image_Show_label->setGeometry(QRect(0, 0, 741, 541));
        Template_Macth_btn = new QPushButton(centralWidget);
        Template_Macth_btn->setObjectName(QStringLiteral("Template_Macth_btn"));
        Template_Macth_btn->setGeometry(QRect(814, 22, 91, 31));
        Template_Macth_btn_2 = new QPushButton(centralWidget);
        Template_Macth_btn_2->setObjectName(QStringLiteral("Template_Macth_btn_2"));
        Template_Macth_btn_2->setGeometry(QRect(820, 130, 91, 31));
        Image_Show_label_2 = new QLabel(centralWidget);
        Image_Show_label_2->setObjectName(QStringLiteral("Image_Show_label_2"));
        Image_Show_label_2->setGeometry(QRect(830, 470, 61, 61));
        Template_MacthClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Template_MacthClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 915, 23));
        Template_MacthClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Template_MacthClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Template_MacthClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Template_MacthClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Template_MacthClass->setStatusBar(statusBar);

        retranslateUi(Template_MacthClass);
        QObject::connect(Template_Macth_btn, SIGNAL(clicked()), Template_MacthClass, SLOT(Template_Macth_Method()));
        QObject::connect(Template_Macth_btn_2, SIGNAL(clicked()), Template_MacthClass, SLOT(Template_Macth1_Method()));

        QMetaObject::connectSlotsByName(Template_MacthClass);
    } // setupUi

    void retranslateUi(QMainWindow *Template_MacthClass)
    {
        Template_MacthClass->setWindowTitle(QApplication::translate("Template_MacthClass", "Template_Macth", 0));
        Image_Show_label->setText(QApplication::translate("Template_MacthClass", "1", 0));
        Template_Macth_btn->setText(QApplication::translate("Template_MacthClass", "\345\214\271\351\205\215(\345\275\242\347\212\266)", 0));
        Template_Macth_btn_2->setText(QApplication::translate("Template_MacthClass", "\345\214\271\351\205\215(\347\233\270\345\205\263\346\200\247)", 0));
        Image_Show_label_2->setText(QApplication::translate("Template_MacthClass", "1", 0));
    } // retranslateUi

};

namespace Ui {
    class Template_MacthClass: public Ui_Template_MacthClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATE_MACTH_H
