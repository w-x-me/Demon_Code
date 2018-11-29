#include "main_ui.h"

main_ui::main_ui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.image_show->setScaledContents(true);
}

QString Result_Show(QString file_name, double result)
{
	QString result_str;
	result_str.append(file_name.mid(file_name.length() - 38, file_name.length() - 5));
	result_str.append(":");
	file_name = QString::number(result, 'f', 3);
	result_str.append(file_name);
	result_str.append("\n");
	return result_str;
}
//污点检测
void main_ui::Slot_1()
{
	qDebug() << "污点检测" << endl;
	ui.result_show->append("----------------------------污点(Bemilsh)检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.Blemish(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// R/G检测
void main_ui::Slot_2()
{
	qDebug() << "R/G检测" << endl;
	ui.result_show->append("----------------------------R/G检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.RG(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// B/G检测
void main_ui::Slot_3()
{
	qDebug() << "B/G检测" << endl;
	ui.result_show->append("----------------------------B/G检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.BG(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// 实点检测
void main_ui::Slot_4()
{
	qDebug() << "实点检测" << endl;
	ui.result_show->append("----------------------------实点检测:----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.DeadPixel(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// 灰度值检测
void main_ui::Slot_5()
{
	ui.result_show->append("----------------------------灰度值检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.RI(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// 旋转角检测
void main_ui::Slot_6()
{
	ui.result_show->append("----------------------------摄像头旋转角检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.Rotation(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
	
}

// 视场检测
void main_ui::Slot_7()
{
	ui.result_show->append("----------------------------视场角检测----------------------------");
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.FOV(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// 水平角检测
void main_ui::Slot_8()
{
	
	if (ui.param_1->text() == "1")
	{
		camera_detection.camera_number = 1;
		ui.result_show->append("----------------------------后置摄像头水平角检测----------------------------");
	}
	else
	{
		camera_detection.camera_number = 0;
		ui.result_show->append("----------------------------前置摄像头水平角检测----------------------------");
	}
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.Tilt(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
}

// SFR检测
void main_ui::Slot_9()
{
	if (ui.param_1->text() == "1")
	{
		camera_detection.camera_number = 1;
		ui.result_show->append("----------------------------后置摄像头SFR检测----------------------------");
	}
	else
	{
		camera_detection.camera_number = 0;
		ui.result_show->append("----------------------------前置摄像头SFR检测----------------------------");
	}
	QString result_str;
	for (auto tmp : fileNames)
	{
		double result;
		camera_detection.img_file = tmp.toStdString();
		camera_detection.SFR(result);
		result_str.append(Result_Show(tmp, result));
	}
	ui.result_show->append(result_str);
	
}

//打开文件
void main_ui::Open_File()
{
	qDebug() << "打开文件" << endl;
	QFileDialog *fileDialog = new QFileDialog(this);
	//定义文件对话框标题
	fileDialog->setWindowTitle(tr("打开图片"));
	//设置默认文件路径
	fileDialog->setDirectory(".\\");
	//设置文件过滤器
	fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
	//设置可以选择多个文件,默认为只能选择一个文件,可以选择多个文件：QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	
	//打印所有选择的文件的路径
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
		QPixmap img = QPixmap(fileNames[0]).scaled(ui.image_show->width(), ui.image_show->height());
		ui.image_show->setPixmap(img);
	}

	
}
main_ui::~main_ui()
{

}
