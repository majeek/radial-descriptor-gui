#ifndef DEBUGWIDGET_HPP
#define DEBUGWIDGET_HPP

#include <QWidget>
#include "ui_DebugWidget.h"

class DebugWidget : public QWidget
{
	Q_OBJECT

public:
	DebugWidget(QWidget *parent = 0);
	~DebugWidget();
	void setupUi();
	Ui::DebugWidget fUi;

private:
	
};

#endif // DEBUGWIDGET_HPP
