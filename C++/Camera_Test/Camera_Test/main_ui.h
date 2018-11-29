#ifndef MAIN_UI_H
#define MAIN_UI_H
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include<QDebug>
#include "ui_main_ui.h"
#include "QFileDialog"
#include"camera-detection.h"
class main_ui : public QMainWindow
{
	Q_OBJECT

public:
	main_ui(QWidget *parent = 0);
	~main_ui();
	CameraDetection camera_detection;
protected:
	QString file_path;
	QStringList fileNames;
protected slots:
	void Slot_1();//ÎÛµã¼ì²â
	void Slot_2();// R/G¼ì²â
	void Slot_3();// B/G¼ì²â
	void Slot_4();// ÊÓ³¡½Ç¼ì²â
	void Slot_5();// Ðý×ª½Ç¼Ó²â
	void Slot_6();// ÇãÐ±½Ç¼ì²â
	void Slot_7();// SFR¼ì²â
	void Slot_8();// »Ò¶ÈÖµ¼ì²â
	void Slot_9();// Êµµã¼ì²â
	void Open_File(); //´ò¿ªÎÄ¼þ
private:
	Ui::main_uiClass ui;
};

#endif // MAIN_UI_H
