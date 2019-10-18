#ifndef CALCULATESIGNALSWORKER_H
#define CALCULATESIGNALSWORKER_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "SignalDescriptor.hpp"
#include "PointDescriptor.h"
#include "SharedWorkersFunctions.hpp"


class CalculateSignalsWorker : public QObject, public QRunnable
{
	Q_OBJECT

public:
	CalculateSignalsWorker(int kernelSize, int radius, int vectorsCount, double interpolationValue, int minDistance, int imageIndex, cv::Mat image, double gaussBlur, int maxSignals, int minVariance, int levelRadiusPercentage, int numberOfLevels, int backgroundColor);
	~CalculateSignalsWorker();
	void run();

signals:
	void sendDebugMessage(QString);
	void error(QString error);
	void updateProgressBar(int, int);
	void returnCalculateSignalsResults(cv::vector<SignalDescriptor*>*, int);
	void returnCalculateSignalsResults(cv::Mat, cv::vector<SignalDescriptor*>*, int);
	void acquireProgressBarSlot(int);
	void releaseProgressBarSlot(int);

private:
	int fLevelRadiusPercentage;
	int fNumberOfLevels;
	int fImageIndex;
	int fKernelSize;
	int fRadius;
	int fVectorsCount;
	int fMinVariance;
	double fInterpolationValue;
	int fMinDistance;
	cv::Mat fImage;
	double fGaussBlur;
	int fMaxSignals;
	int fBackgroundColor;
};

#endif // CALCULATESIGNALSWORKER_H
