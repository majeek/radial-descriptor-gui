#include "PointSignature.h"

PointSignature::PointSignature() : _variance(0){ }
PointSignature::PointSignature(int radius) : _radius(radius), _variance(0){}
PointSignature::PointSignature(cv::Mat image, int radius) : _radius(radius), _variance(0){}


void  PointSignature::setRadius(int r) { _radius = r; }


int   PointSignature::getRadius()          { return _radius; }
double PointSignature::getVariance()        { setVariance(); return _variance; }
int PointSignature::getSamplePointsSize(){ return fSamplePoints.size(); }

double PointSignature::getSamplePoint(int i)     { return fSamplePoints[i]; }


cv::vector<double>&  PointSignature::getSamplePoints()   { return fSamplePoints; }



////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Majeed Kassis, 10/31/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

PointSignature::~PointSignature(void){
}


/// <summary>	The variance as the integral of signature. </summary>
void PointSignature::setVariance() {
	_variance = 0 ;
	if (fSamplePoints.size() == 0 )
		return ;

	cv::vector<double>::iterator iter ; 
	for ( iter = fSamplePoints.begin() ; iter != fSamplePoints.end(); iter++ )
		_variance += abs(*iter) ;
	_variance /= fSamplePoints.size() ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Compute the distance between two aligned signatures. </summary>
///
/// <param name="sig">	[in,out] The signature. </param>
///
/// <returns>	The distance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

double PointSignature::distance(PointSignature& sig){
	int size = cv::min(fSamplePoints.size(), sig.getSamplePoints().size());
	double dist = 0 ;
	for ( int i = 0 ; i < size ; i++ ){
		double d = fSamplePoints[i] - sig.getSamplePoint(i) ;
		dist += d*d ;
	}
	return dist/size ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets the samples. </summary>
///
/// <param name="reference">	The reference center point. </param>
/// <param name="ring">			[in,out] The ring vector to be filed. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PointSignature::setSamplePoints(cv::Point2i reference, cv::vector<cv::Point2i>& ring, cv::Mat image){
	fSamplePoints.clear() ;
	// double refVal = _imageMat.at<unsigned char>(reference);
	// instead of refVal alone we average refVal with the values of the 8 neigbour pixels
	// less noisy that way
	double refVal = 0;
	for (int i=-1;i<2;i++)
		for (int j=-1;j<2;j++)
			refVal += image.at<unsigned char>(cv::Point2i(reference.x+i,reference.y+j));
	refVal = refVal / 9.0;

	cv::vector<cv::Point2i>::iterator iter ;
	for( iter = ring.begin(); iter != ring.end(); iter++){
		double ring_value = (double)image.at<unsigned char>(*iter);
		fSamplePoints.push_back(refVal - ring_value);
	}
}