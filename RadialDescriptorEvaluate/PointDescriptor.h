#ifndef _PointDescriptor_H_
#define _PointDescriptor_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/ml/ml.hpp>
#include <QLabel>
#include "PointRing.h"
#include "PointSignature.h"
#include "TableWidget.h"





class PointDescriptor{
private:
	cv::Mat fImageMat;
	cv::Point2i fPoint;
	double fStartingWeight;
	cv::vector<PointSignature> fSignatures;
	//_dominantSet is the subset of _descriptor matrix
	// _descriptorMat includes all vectors retrieved from the _signatures vector
	cv::Mat	fDominantSet; //each row is a PointSignature 
	cv::Mat	fComparedDominantSet;
	
	cv::Mat	fDescriptorMat;
	cv::Mat fDominantSignal;
	cv::vector<cv::Point2i> fFarthestRing;
	cv::Mat fMellinFourierMat;
	int	fMinRadius;
	int	fMaxRadius;

	double calculateEuclideanDistance(cv::Mat, cv::Mat);
	double calculateMahalanobisDistance(cv::Mat, cv::Mat);
	double calculateChiSquaredDistance(cv::Mat, cv::Mat);
	cv::Mat normalizeVectors(cv::Mat);
	cv::Mat cutMatrix(cv::Mat, int);



public: 
	const static int EUCLIDEAN = 1;
	const static int MAHALANOBIS = 2;
	const static int CHI_SQUARED  = 4;
	PointDescriptor() {}
	//PointDescriptor(cv::Mat mat, cv::Point2i p): fImageMat(mat), fPoint(p),fStartingWeight(-1){}
	PointDescriptor(cv::Mat mat, cv::Point2i p, double interpolationValue);
	~PointDescriptor(void);

	void setMat(cv::Mat mat);
	void setPoint(cv::Point2i p);
	int getMinRadius();
	int getMaxRadius();

	cv::Mat runEM(int nclusters);
	void createRingSignatureSet(int, int); 
	cv::vector<cv::Point2i> getFarthestRing();
	void calculateDescriptorMatrix();//(int sampleSize, int method);
	void findDominantSet();//(int size);
	void calculateDominantSignal();
	void calculateDominantSignal(double);
	cv::Mat getDominantSignal();
	double getAverageVariance();
	cv::Mat getDominantSet();
	cv::Point2i getCenterPoint();
	double calculateDistance(PointDescriptor&, bool = false, int = 0);
	cv::Mat getComparedDominantSet();
	cv::Mat getDescriptorMatrix();

	void setComparedDominantSet(cv::Mat dominantSet);
	
	void setInterpolationValue(int);
	

};

#endif 