#include "LoadDataWorker.hpp"



LoadDataWorker::LoadDataWorker(QString persistencePath, QStringList* imageFileNameList, cv::EM* emModel, cv::vector<cv::vector<double>>* imagesHistograms, cv::vector<cv::vector<double>>* imagesZigZagHistograms):
	fPersistencePath(persistencePath),
	fImageFileNameList(imageFileNameList),
	fEMModel(emModel), fImagesHistograms(imagesHistograms),
	fImagesZigZagHistograms(imagesZigZagHistograms) {
}


LoadDataWorker::~LoadDataWorker()
{
}

void LoadDataWorker::run() {
	cv::FileStorage fs((fPersistencePath + "/model").toStdString(), cv::FileStorage::READ);
	fEMModel->read(fs["StatModel.EM"]);
	fs.release();
	QFile namesFile(fPersistencePath + "/imagesList");
	namesFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream namesIn(&namesFile);
	while (!namesIn.atEnd()) {
		QString imageName;
		namesIn >> imageName;
		if (!imageName.isEmpty())
			fImageFileNameList->push_back(imageName);
	}
	namesFile.close();
	emit initializeTotalProgressDialogSignal("Loading Model & Histograms...", fImageFileNameList->size());

	for (int i = 0; i < fImageFileNameList->size();i++){
		QFile file(fPersistencePath + "/" + fImageFileNameList->at(i) + "-occurrence");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in(&file);
		cv::vector<double> vals;
		while (!in.atEnd()) {
			double val;
			in >> val;
			vals.push_back(val);
		}
		fImagesHistograms->push_back(vals);
		file.close();
		QFile file2(fPersistencePath + "/" + fImageFileNameList->at(i) + "-cooccurrence");
		file2.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in2(&file2);
		cv::vector<double> vals2;
		while (!in2.atEnd()) {
			double val;
			in2 >> val;
			vals2.push_back(val);
		}
		fImagesZigZagHistograms->push_back(vals2);
		file.close();
		emit increaseTotalProgressDialogSignal();
	}
	
}