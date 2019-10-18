#ifndef CALCULATESUCCESSRATEFORALLWORKER_HPP
#define CALCULATESUCCESSRATEFORALLWORKER_HPP

#include <QObject>
#include <QRunnable>
#include <QStringList>
#include <QMutex>
#include <QDir>
#include <QDebug>
#include <QThreadPool>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "CalculateSuccessRateWorker.hpp"
#include "RadialDescriptorQt5.hpp"

class CalculateSuccessRateForAllWorker : public QObject, public QRunnable{
	Q_OBJECT

public:
	CalculateSuccessRateForAllWorker(QString path, QThreadPool* threadPool, int method, int radius, int vectorsCount, 
								   double interpolationValue, int minDistance, 
								   cv::vector<cv::vector<double>>* imagesHistograms, 
								   cv::vector<cv::vector<double>>* imagesZigZagHistograms, 
								   int numberOfLevels, int levelRadiusPercentage, int maxSignals, cv::EM* model, double gaussBlur, 
								   int kernelSize, int minVariance, QWaitCondition* calculateSuccessRateForAllWorkerWaitCondition, 
								   QMutex* calculateSuccessRateForAllWorkerWaitConditionMutex, int backgroundColor, QObject* parent = 0);
	~CalculateSuccessRateForAllWorker();

signals:
	void initializeProgressBarWaitDialogSignal(QString, int);
	void connectCalculateSuccessRateWorkerSignalsAndRunItSignal(CalculateSuccessRateWorker*);
	void updateSuccessRateVariablesSignal(cv::vector<cv::Mat>  imagesToCalculateSuccessRateVector,
													 int numberOfImagesToSuccessRate,
													 QStringList imagesToCalculateSuccessRateFileNameList);
public slots:
	void run(void);

private:
	QString fPath;
	QThreadPool* fThreadPool;
	int fMethod;
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
	QWaitCondition* fCalculateSuccessRateForAllWorkerWaitCondition;
	QMutex *fCalculateSuccessRateForAllWorkerWaitConditionMutex;
	cv::vector<cv::vector<double>>* fImagesHistograms;
	//cv::vector<cv::Mat> fImagesDistanceHistograms;
	cv::vector<cv::vector<double>>* fImagesZigZagHistograms;
	int fBackgroundColor;

	void calculateSuccessRateForOneDirectory(cv::vector<cv::Mat>& imagesMats, QStringList imagesNames, QString dirName);
	
};

#endif // CALCULATESUCCESSRATEFORALLWORKER_HPP
