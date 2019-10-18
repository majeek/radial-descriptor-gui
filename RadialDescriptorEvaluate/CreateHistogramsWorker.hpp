#ifndef CREATEHISTOGRAMSWORKER_HPP
#define CREATEHISTOGRAMSWORKER_HPP
#include <QObject>
#include <QRunnable>
#include <QThread>
#include "SharedWorkersFunctions.hpp"



class CreateHistogramsWorker : public QObject, public QRunnable{
	Q_OBJECT

public:
	CreateHistogramsWorker(void);
	CreateHistogramsWorker::CreateHistogramsWorker(QString modelPath, cv::vector<cv::vector<SignalDescriptor*>*>* descriptorPointsForAllImages,
											   cv::vector<cv::Mat> images, int numberOfLevels,
											   int levelRadiusPercentage, int radius, int vectorsCount,
											   double gaussBlur, int kernelSize, int numberOfClusters, int backgroundColor);
	~CreateHistogramsWorker(void);


public slots:
	void run();


signals:
	void error(QString error);
	void updateComparisonProgress(QString);
	void returnHistogramsSignal(cv::vector<cv::vector<double>>*, cv::vector<cv::vector<double>>*, cv::EM*);
	void showMessageWaitWindow();
	void hideMessageWaitWindow();

private:
	QString fModelPath;
	cv::vector<cv::vector<SignalDescriptor*>*>* fDescriptorPointsForAllImages;
	cv::vector<cv::Mat> fImages;
	int fNumberOfLevels;
	int fLevelRadiusPercentage;

	int fRadius;
	int fVectorsCount;
	double fGaussBlur;
	int fKernelSize;

	int fNumberOfClusters;
	int fBackgroundColor;

};

#endif
