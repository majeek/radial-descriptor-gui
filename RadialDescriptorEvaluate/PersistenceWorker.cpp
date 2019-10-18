#include "PersistenceWorker.hpp"



PersistenceWorker::PersistenceWorker(QString persistencePath, QStringList* imageFileNameList, cv::EM* emModel, cv::vector<cv::vector<double>>* imagesHistograms, cv::vector<cv::vector<double>>* imagesZigZagHistograms) :
	fPersistencePath(persistencePath),
	fImageFileNameList(imageFileNameList), 
	fEMModel(emModel), fImagesHistograms(imagesHistograms), 
	fImagesZigZagHistograms(imagesZigZagHistograms){
}


PersistenceWorker::~PersistenceWorker(){
}

void PersistenceWorker::run() {
	emit initializeTotalProgressDialogSignal("Storing Model & Histograms...", fImageFileNameList->size());
	cv::FileStorage fs((fPersistencePath + "/model").toStdString(), cv::FileStorage::WRITE);
	fEMModel->write(fs);
	fs.release();
	QFile namesFile(fPersistencePath + "/imagesList");
	namesFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream namesOut(&namesFile);
	for (int i = 0; i < fImageFileNameList->size(); i++) {
		namesOut << fImageFileNameList->at(i) << "\n";
		QFile file(fPersistencePath + "/" + fImageFileNameList->at(i) + "-occurrence");
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&file);
		
		for (double val : fImagesHistograms->at(i))
			out << val << "\t";
		out.flush();
		file.close();
		QFile file2(fPersistencePath + "/" + fImageFileNameList->at(i) + "-cooccurrence");
		file2.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out2(&file2);
		for (double val : fImagesZigZagHistograms->at(i))
			out2 << val << "\t";
		out2.flush();
		file2.close();
		emit increaseTotalProgressDialogSignal();
	}
	namesOut.flush();
	namesFile.close();
}