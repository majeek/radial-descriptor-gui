#ifndef LOADDATAWORKER_HPP_
#define LOADDATAWORKER_HPP_

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>
#include <QWaitCondition>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>

class LoadDataWorker : public QObject, public QRunnable
{
	Q_OBJECT
public:
	LoadDataWorker(QString persistencePath, QStringList* imageFileNameList, cv::EM * emModel, cv::vector<cv::vector<double>>* imagesHistograms, cv::vector<cv::vector<double>>* imagesZigZagHistograms);
	~LoadDataWorker();
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
#endif