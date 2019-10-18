#include "CalculateSignalsWorker.hpp"

CalculateSignalsWorker::CalculateSignalsWorker(int kernelSize, int radius, int vectorsCount, double interpolationValue, int minDistance, int imageIndex, cv::Mat image, double gaussBlur, int maxSignals, int minVariance, int levelRadiusPercentage, int numberOfLevels, int backgroundColor) :
	QObject(0),
	fKernelSize(kernelSize),
	fRadius(radius),fVectorsCount(vectorsCount),  
	fInterpolationValue(interpolationValue), fMinDistance(minDistance), fImageIndex(imageIndex),
	fImage(image), fGaussBlur(gaussBlur),  
	fMaxSignals(maxSignals), fMinVariance(minVariance), fLevelRadiusPercentage(levelRadiusPercentage), fNumberOfLevels(numberOfLevels), fBackgroundColor(backgroundColor)
{}


CalculateSignalsWorker::~CalculateSignalsWorker(){

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Process an image, scan for descriptors, filter by variance
/// 			of K elements. </summary>
///
/// <remarks>	majeek, 12/4/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CalculateSignalsWorker::run(){
	cv::vector<SignalDescriptor*> *topImageSignalsDescriptors = new cv::vector<SignalDescriptor*>();
	topImageSignalsDescriptors->reserve(fMaxSignals);

	emit acquireProgressBarSlot(fImageIndex);

	//convert image to grayscale and apply gaussian blur
	cv::Mat padded = SharedWorkersFunctions::prepareImage(fImage, fVectorsCount, fKernelSize, fGaussBlur, fRadius, fBackgroundColor);

	int shift = SharedWorkersFunctions::getShiftValue(fVectorsCount, fRadius);

	cv::vector<SignalDescriptor*> imageSignalsDescriptors;

	//scan image pixels and create descriptors
	int currentPercentage = 0;
	for (int i = shift; i < padded.rows - shift; i++){
		for (int j = shift; j < padded.cols - shift; j++){
			SignalDescriptor *sd = SharedWorkersFunctions::createFeature(i, j, padded, fInterpolationValue, fRadius, fVectorsCount, fMinVariance);
			if (sd != nullptr)
				imageSignalsDescriptors.push_back(sd);
		}
		//update progress bar
		int percentage = 100 * (static_cast<double>(i - shift) / (static_cast<double>(padded.rows - 2 * shift)));
		if (currentPercentage + 1 < percentage){
			emit updateProgressBar(fImageIndex, percentage);
			currentPercentage = percentage;
		}
	}

	//sort descriptors by variance
	SharedWorkersFunctions::sortFeaturesByVariance(imageSignalsDescriptors);
	
	// if distance -1, we just take top K signals
	// otherwise we split the descriptors into groups - each group consists of a point and all 
	// its surrounding points of fMinDistnace -
	// and take highest variance from each group
	if (imageSignalsDescriptors.size() < fMaxSignals)
		emit sendDebugMessage("imageIndex=" + QString::number(fImageIndex) + "\tsignals=" + QString::number(imageSignalsDescriptors.size()));

	SharedWorkersFunctions::getTopKFeatures(fMinDistance, imageSignalsDescriptors, fMaxSignals, topImageSignalsDescriptors);

	emit updateProgressBar(fImageIndex, 100);
	//remove unused signals
	for (SignalDescriptor* sd : imageSignalsDescriptors)
		if (sd != nullptr){
			delete sd;
			sd = nullptr;
		}

	emit returnCalculateSignalsResults(topImageSignalsDescriptors, fImageIndex);
	emit releaseProgressBarSlot(fImageIndex);
}