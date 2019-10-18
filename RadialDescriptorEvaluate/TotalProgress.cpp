#include "TotalProgress.h"

TotalProgress::TotalProgress(QDialog *parent)
	: QDialog(parent){
	
}

TotalProgress::~TotalProgress()
{

}

void TotalProgress::setupUi(){
	fUi.setupUi(this);
}
