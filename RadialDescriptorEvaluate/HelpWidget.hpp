#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include "ui_HelpWidget.h"

class HelpWidget : public QWidget{ 
	Q_OBJECT

public:
	HelpWidget(QWidget *parent = 0);
	~HelpWidget();
	void setupUi();
	Ui::HelpWidget fUi;

private:
	
};

#endif // HELPWIDGET_H
