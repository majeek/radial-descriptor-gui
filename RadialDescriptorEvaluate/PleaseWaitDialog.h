#ifndef PLEASEWAITDIALOG_H
#define PLEASEWAITDIALOG_H

#include <QDialog>
#include "ui_PleaseWaitDialog.h"

class PleaseWaitDialog : public QDialog{ 
	Q_OBJECT

public:
	PleaseWaitDialog();
	PleaseWaitDialog(QDialog *parent);
	~PleaseWaitDialog();
	void setupUi();
	Ui::PleaseWaitDialog fUi;

private:
	
};

#endif // PLEASEWAITDIALOG_H
