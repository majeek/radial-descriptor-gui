#ifndef SHAREDWORKERSFUNCTIONS_HPP
#define SHAREDWORKERSFUNCTIONS_HPP



#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
#include <sstream>
#include <fstream>
#include "SignalDescriptor.hpp"
#include "PointDescriptor.h"
#include <qstring.h>
#include <wchar.h>
#include <QFile>
#include <QTextCodec>
#define NOMINMAX
#include <windows.h>

namespace SharedWorkersFunctions{

	//worker functions
	int getShiftValue(int vectorsCount, int radius);
	cv::Mat prepareImage(cv::Mat imageToPrepare, int vectorsCount, int kernelSize, double gaussBlur, int radius, int backgroundColor = 0);
	SignalDescriptor* createFeature(int i, int j, cv::Mat padded, double interpolationValue, int radius, int vectorsCount, int minVariance);
	void sortFeaturesByVariance(cv::vector<SignalDescriptor*> &imageSignalsDescriptors);
	void getTopKFeatures(int minDistance, cv::vector<SignalDescriptor*> &sortedSignalDescriptors, int maxSignals, cv::vector<SignalDescriptor*>* topImageSignalsDescriptors);
	cv::Mat drawFeaturesOnImage(cv::Mat image, int shift, double gaussBlur, int kernelSize, cv::vector<SignalDescriptor*> *topImageSignalsDescriptors);
	cv::vector<double> clusterFeatures(cv::vector<SignalDescriptor*> &topImageSignalsDescriptors, cv::EM* model);
	cv::vector<double> histogramMatrixToVector(cv::Mat distanceHistogram);
	void compareHistograms(cv::vector<cv::vector<double>>* imagesHistograms, 
		cv::vector<cv::vector<double>>* imagesZigZagHistograms, int method, cv::vector<double> &imageHistogramValues, 
		cv::vector<double> &zigzagImageDistanceHistogram, 
		cv::vector<double> &comparisonVector,cv::vector<double> &zigZagComparisonVector);

	//histogram related functions
	cv::vector<double> createZigZagDistance(cv::Mat distanceHistogram);
	cv::Mat calcaulateImageDistanceHisogram(int numberOfClusters, cv::vector<SignalDescriptor*>* imageSignals, int levelRadiusPercentage, cv::Mat image, int numberOfLevels);
	
	QString toString(cv::vector<double> histogramVector);
	double compareHistChiSquare(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram);
	double compareHistCosineDistance(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram);
	double compareHistEuclideanDistance(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram);
	
	cv::vector<double> normalizeDistanceVector(cv::vector<double> zigZag);
	cv::Mat normalizeDistanceHistogram(cv::Mat distanceHistogram);
	void storeBestResults(QString fullPath, QString wordPart,
		cv::vector<cv::vector<double>> matches, QString comparisonType, QStringList& fImagesToCalculateSuccessRateFileNameList,
		cv::vector<int>& fCalculateSuccessRateImageIndex, QStringList& fImageFileNameList);

	
	cv::Mat loadUnicodeImage(QString fileName);
	void createUnicodePath(QString path);
	void saveUnicodeImage(QString fileName, cv::Mat image, std::string type);
	
};


#endif SHAREDWORKERSFUNCTIONS_HPP