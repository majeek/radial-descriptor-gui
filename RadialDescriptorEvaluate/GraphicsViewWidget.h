#ifndef GRAPHICSVIEWWIDGET_H
#define GRAPHICSVIEWWIDGET_H

#include <QWidget>
#include "ui_GraphicsViewWidget.h"

class GraphicsViewWidget : public QWidget{
	Q_OBJECT

public:
	GraphicsViewWidget(QWidget *parent = 0);
	~GraphicsViewWidget();
	void setupUi();
	Ui::GraphicsViewWidget fUi;
	
private:
	
};

#endif // GraphicsViewWidget_H
