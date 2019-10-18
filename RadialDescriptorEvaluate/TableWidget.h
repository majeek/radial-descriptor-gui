#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include "ui_TableWidget.h"

class TableWidget : public QWidget{
	Q_OBJECT

public:
	TableWidget(QWidget *parent = 0);
	~TableWidget();
	void setupUi();
	Ui::TableWidget fUi;
	
private:
	
};

#endif // TABLEWIDGET_H
