#ifndef PERSISTENCEWORKER_HPP_
#define PERSISTENCEWORKER_HPP_

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <qfile.h>
#include <qtextstream.h>
#include <QWaitCondition>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>

class PersistenceWorker : public QObject, public QRunnable
{
	Q_OBJECT

public:
	PersistenceWorker(QString persistencePath, QStringList* imageFileNameList, cv::EM* emModel, cv::vector<cv::vector<double>>* imagesHistograms, cv::vector<cv::vector<double>>* imagesZigZagHistograms);
	~PersistenceWorker();
	void run();


private:
	cv::vector<cv::vector<double>>* fImagesZigZagHistograms;
	cv::EM *fEMModel;
	cv::vector<cv::vector<double>>* fImagesHistograms;
	QStringList* fImageFileNameList;
	QString fPersistencePath;

signals:
	void initializeTotalProgressDialogSignal(QString, int);
	void increaseTotalProgressDialogSignal();
};
#endif //PERSISTENCEWORKER_HPP_