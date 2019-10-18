#include "RadialDescriptorQt5.hpp"
#include <QtWidgets/QApplication>
//#include <vld.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(QPixmap(":/rd.png")));
	RadialDescriptorQt5 w;
	w.show();
	return a.exec();
}
