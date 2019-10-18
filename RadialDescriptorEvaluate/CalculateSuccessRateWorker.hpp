#ifndef CALCULATESUCCESSRATEWORKER_HPP
#define CALCULATESUCCESSRATEWORKER_HPP


#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "SignalDescriptor.hpp"
#include "PointDescriptor.h"
#include "SharedWorkersFunctions.hpp"


class CalculateSuccessRateWorker : public QObject, public QRunnable{
	Q_OBJECT


public:
	CalculateSuccessRateWorker(QStringList imageFileNames, int method, int radius, int vectorsCount, 
								   double interpolationValue, int minDistance, 
								   cv::Mat image, cv::vector<cv::vector<double>>* imagesHistograms, 
								   cv::vector<cv::vector<double>>* imagesZigZagHistograms, 
								   int numberOfLevels, int levelRadiusPercentage, int maxSignals, cv::EM* model, double gaussBlur, 
								   int kernelSize, int minVariance, int workerId, QString imageToDetectName, int backgroundColor, QObject* parent = 0);
	~CalculateSuccessRateWorker(void);

private:
	QStringList fImageFileNames;
	int fMethod;
	cv::Mat fImage;
	double fInterpolationValue;
	int fMinDistance;
	int fVectorsCount;
	int fRadius;
	int fNumberOfLevels;
	int fLevelRadiusPercentage;
	int fMaxSignals;
	double fGaussBlur;
	int fKernelSize;
	int fMinVariance;
	cv::EM *fModel;
	cv::vector<cv::vector<double>>* fImagesHistograms;
	//cv::vector<cv::Mat> fImagesDistanceHistograms;
	cv::vector<cv::vector<double>>* fImagesZigZagHistograms;

	QString fImageToDetectName;
	int fWorkerId;
	int fBackgroundColor;
public slots:
	void run();


signals:
	void error(QString error);
	void updateProgressBar(int, int);

	void acquireProgressBarSlot(int);
	void releaseProgressBarSlot(int);
	void returnCalculateSuccessRateResult(cv::vector<double>,cv::vector<double>,int);

};
#endif //CALCULATESUCCESSRATEWORKER_HPP