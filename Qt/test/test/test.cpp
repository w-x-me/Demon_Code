#include "test.h"

test::test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void test::label_show()
{
	ui.label->setText("hello word");
}
test::~test()
{

}
