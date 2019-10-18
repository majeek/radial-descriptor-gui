#include "DebugWidget.hpp"

DebugWidget::DebugWidget(QWidget *parent)
	: QWidget(parent)
{
}

DebugWidget::~DebugWidget()
{

}

void DebugWidget::setupUi(){
	fUi.setupUi(this);
}

