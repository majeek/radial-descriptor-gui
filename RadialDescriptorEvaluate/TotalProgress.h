#ifndef TOTALPROGRESS_H
#define TOTALPROGRESS_H

#include <QDialog>
#include "ui_TotalProgress.h"

class TotalProgress : public QDialog
{
	Q_OBJECT

public:
	TotalProgress(QDialog *parent = 0);
	~TotalProgress();
	void setupUi();
	Ui::TotalProgress fUi;

private:
	
};

#endif // TOTALPROGRESS_H
