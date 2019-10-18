#include "PleaseWaitDialog.h"

PleaseWaitDialog::PleaseWaitDialog() : QDialog(0){
	
}



PleaseWaitDialog::PleaseWaitDialog(QDialog *parent = 0) : QDialog(parent){
	
}

PleaseWaitDialog::~PleaseWaitDialog(){

}


void PleaseWaitDialog::setupUi(){
	fUi.setupUi(this);
}