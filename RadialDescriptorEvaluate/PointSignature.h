#ifndef _PointSignature_H_
#define _PointSignature_H_

#include <opencv2\core\core.hpp>
//#include "PointRing.h" 
#include "OctRing.h"


class PointSignature {
protected:

	int      _radius;
	cv::vector<double>  fSamplePoints;
	double _variance;
public:
	PointSignature();
	PointSignature(int radius);
	PointSignature(cv::Mat image, int radius); 

	~PointSignature(void);

	void  setRadius(int r);
	void  setVariance();

	int   getRadius();
	double getVariance();
	int getSamplePointsSize(); 

	double getSamplePoint(int i);
	void  setSamplePoints(cv::Point2i, cv::vector<cv::Point2i>&, cv::Mat); 
	
	cv::vector<double>&  getSamplePoints();
	double alignedDistance(PointSignature& other, const int sampleSize, const int samplingMethod);
	double distance(PointSignature& sig);
	
};

#endif 

