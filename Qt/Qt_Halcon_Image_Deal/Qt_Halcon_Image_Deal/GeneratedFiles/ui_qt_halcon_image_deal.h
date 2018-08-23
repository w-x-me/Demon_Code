/********************************************************************************
** Form generated from reading UI file 'qt_halcon_image_deal.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_HALCON_IMAGE_DEAL_H
#define UI_QT_HALCON_IMAGE_DEAL_H

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

class Ui_Qt_Halcon_Image_DealClass
{
public:
    QWidget *centralWidget;
    QPushButton *Read_Image;
    QPushButton *Deal_Image;
    QLabel *Image_lb;
    QLabel *Image_lb_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_Halcon_Image_DealClass)
    {
        if (Qt_Halcon_Image_DealClass->objectName().isEmpty())
            Qt_Halcon_Image_DealClass->setObjectName(QStringLiteral("Qt_Halcon_Image_DealClass"));
        Qt_Halcon_Image_DealClass->resize(678, 577);
        centralWidget = new QWidget(Qt_Halcon_Image_DealClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Read_Image = new QPushButton(centralWidget);
        Read_Image->setObjectName(QStringLiteral("Read_Image"));
        Read_Image->setGeometry(QRect(130, 460, 75, 23));
        Deal_Image = new QPushButton(centralWidget);
        Deal_Image->setObjectName(QStringLiteral("Deal_Image"));
        Deal_Image->setGeometry(QRect(490, 470, 75, 23));
        Image_lb = new QLabel(centralWidget);
        Image_lb->setObjectName(QStringLiteral("Image_lb"));
        Image_lb->setGeometry(QRect(340, 90, 251, 261));
        Image_lb_2 = new QLabel(centralWidget);
        Image_lb_2->setObjectName(QStringLiteral("Image_lb_2"));
        Image_lb_2->setGeometry(QRect(70, 100, 251, 221));
        Qt_Halcon_Image_DealClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_Halcon_Image_DealClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 678, 23));
        Qt_Halcon_Image_DealClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_Halcon_Image_DealClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_Halcon_Image_DealClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qt_Halcon_Image_DealClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_Halcon_Image_DealClass->setStatusBar(statusBar);

        retranslateUi(Qt_Halcon_Image_DealClass);
        QObject::connect(Read_Image, SIGNAL(clicked()), Qt_Halcon_Image_DealClass, SLOT(My_read_image()));
        QObject::connect(Deal_Image, SIGNAL(clicked()), Qt_Halcon_Image_DealClass, SLOT(My_deal_image()));

        QMetaObject::connectSlotsByName(Qt_Halcon_Image_DealClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_Halcon_Image_DealClass)
    {
        Qt_Halcon_Image_DealClass->setWindowTitle(QApplication::translate("Qt_Halcon_Image_DealClass", "Qt_Halcon_Image_Deal", 0));
        Read_Image->setText(QApplication::translate("Qt_Halcon_Image_DealClass", "\350\257\273\345\217\226\345\233\276\347\211\207", 0));
        Deal_Image->setText(QApplication::translate("Qt_Halcon_Image_DealClass", "\345\244\204\347\220\206\345\233\276\345\203\217", 0));
        Image_lb->setText(QApplication::translate("Qt_Halcon_Image_DealClass", "\346\230\276\347\244\272\345\233\276\345\203\217", 0));
        Image_lb_2->setText(QApplication::translate("Qt_Halcon_Image_DealClass", "\346\230\276\347\244\272\345\233\276\345\203\217", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_Halcon_Image_DealClass: public Ui_Qt_Halcon_Image_DealClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_HALCON_IMAGE_DEAL_H
