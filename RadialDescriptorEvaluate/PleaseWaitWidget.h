#ifndef PLEASEWAITWIDGET_H
#define PLEASEWAITWIDGET_H

#include <QWidget>
#include "ui_PleaseWaitWidget.h"

class PleaseWaitWidget : public QWidget{ 
	Q_OBJECT

public:
	PleaseWaitWidget(QWidget *parent = 0);
	~PleaseWaitWidget();
	void setupUi();
	Ui::PleaseWaitWidget fUi;

private:
	
};

#endif // PLEASEWAITWIDGET_H
