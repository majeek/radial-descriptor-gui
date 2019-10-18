#include "CalculateSuccessRateWorker.hpp"

CalculateSuccessRateWorker::CalculateSuccessRateWorker(QStringList fileNamesList, int method, int radius, int vectorsCount, 
								   double interpolationValue, int minDistance, 
								   cv::Mat image, cv::vector<cv::vector<double>>* imagesHistograms, 
								   cv::vector<cv::vector<double>>* imagesZigZagHistograms,
								   int numberOfLevels, int levelRadiusPercentage, int maxSignals, cv::EM* model, double gaussBlur, 
								   int kernelSize, int minVariance, int workerId, QString imageToDetectName,
								   int backgroundColor, QObject* parent) :
	QObject(parent),
	fImageFileNames(fileNamesList),
	fMethod(method),
	fRadius(radius), 
	fVectorsCount(vectorsCount), 
	fInterpolationValue(interpolationValue), 
	fMinDistance(minDistance), 
	fImage(image), 
	fImagesHistograms(imagesHistograms), 
	//fImagesDistanceHistograms(imagesDistanceHistograms),
	fImagesZigZagHistograms(imagesZigZagHistograms),
	fNumberOfLevels(numberOfLevels),
	fLevelRadiusPercentage(levelRadiusPercentage),
	fMaxSignals(maxSignals),
	fModel(model), 
	fGaussBlur(gaussBlur),
	fKernelSize(kernelSize),
	fMinVariance(minVariance),
	fImageToDetectName(imageToDetectName),
	fWorkerId(workerId),
	fBackgroundColor(backgroundColor){

}




CalculateSuccessRateWorker::~CalculateSuccessRateWorker(void){
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Receives an image attempts to detect it, and stores the result in a file </summary>
///
/// <remarks>	majeek, 12/23/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CalculateSuccessRateWorker::run(void){
	
		emit acquireProgressBarSlot(fWorkerId);
		//qDebug() <<  fGaussBlur << fMethod << fRadius <<	fVectorsCount << fInterpolationValue << fMinDistance <<	fRangeSize << fStepSize <<	fMaxSignals << fModel << fMinVariance << fKernelSize;
		int shift;
		cv::Mat padded;
		cv::vector<SignalDescriptor*> imageSignalsDescriptors;

		// find signals
		shift = SharedWorkersFunctions::getShiftValue(fVectorsCount, fRadius);

		//pad it with lines everywhere
		padded = SharedWorkersFunctions::prepareImage(fImage, fVectorsCount, fKernelSize, fGaussBlur, fRadius, fBackgroundColor);
		
		
		//scan image pixels and create descriptors
		int currentPercent = 0;
		for (int i = shift; i < padded.rows - shift; i++){
			for (int j = shift; j < padded.cols - shift; j++){
				SignalDescriptor *sd = SharedWorkersFunctions::createFeature(i, j, padded, fInterpolationValue, fRadius, fVectorsCount, fMinVariance);
				if (sd != nullptr)
					imageSignalsDescriptors.push_back(sd);
			}
			//update progress bar
			int percentage = 100 * (static_cast<double>(i - shift) / (static_cast<double>(padded.rows - 2 * shift)));
			if (currentPercent + 5 >= percentage){
				emit updateProgressBar(fWorkerId, percentage);
				currentPercent = percentage;
			}
		}
		if (imageSignalsDescriptors.size() == 0){
			int currentPercent = 0;
			for (int i = shift; i < padded.rows - shift; i++){
				for (int j = shift; j < padded.cols - shift; j++){
					SignalDescriptor *sd = SharedWorkersFunctions::createFeature(i, j, padded, fInterpolationValue, fRadius, fVectorsCount, 0);
					if (sd != nullptr)
						imageSignalsDescriptors.push_back(sd);
				}
				//update progress bar
				int percentage = 100 * (static_cast<double>(i - shift) / (static_cast<double>(padded.rows - 2 * shift)));
				if (currentPercent + 5 >= percentage){
					emit updateProgressBar(fWorkerId, percentage);
					currentPercent = percentage;
				}
			}
		}

		//sort descriptors by variance
		SharedWorkersFunctions::sortFeaturesByVariance(imageSignalsDescriptors);

		// if distance -1, we just take top K signals
		// otherwise we split the descriptors into groups - each group consists of a point and all 
		// its surrounding points of fMinDistnace -
		// and take highest variance from each group
		cv::vector<SignalDescriptor*> topImageSignalsDescriptors;
		SharedWorkersFunctions::getTopKFeatures(fMinDistance, imageSignalsDescriptors, fMaxSignals, &topImageSignalsDescriptors);

		//initialize data for historgram
		cv::vector<double> imageHistogramValues = SharedWorkersFunctions::clusterFeatures(topImageSignalsDescriptors, fModel);

		//create distance and zigzag distance histograms for the image
		cv::Mat imageDistanceHistogram = SharedWorkersFunctions::calcaulateImageDistanceHisogram(fModel->get<int>("nclusters"), &topImageSignalsDescriptors, fLevelRadiusPercentage, padded, fNumberOfLevels);
		//cv::vector<double> imageDistanceHistogramVector = SharedWorkersFunctions::histogramMatrixToVector(imageDistanceHistogram);
		cv::vector<double> zigzagImageDistanceHistogram = SharedWorkersFunctions::createZigZagDistance(imageDistanceHistogram);

		//normalize histograms
		imageHistogramValues = SharedWorkersFunctions::normalizeDistanceVector(imageHistogramValues);
		//imageDistanceHistogramVector = SharedWorkersFunctions::normalizeDistanceVector(imageDistanceHistogramVector);
		zigzagImageDistanceHistogram = SharedWorkersFunctions::normalizeDistanceVector(zigzagImageDistanceHistogram);

		// compare regular histogram and distance histogram with all histograms 

		cv::vector<double> comparisonVector;
		//cv::vector<double> distanceComparisonVector;
		cv::vector<double> zigZagComparisonVector;

		SharedWorkersFunctions::compareHistograms(fImagesHistograms, fImagesZigZagHistograms, fMethod,
			imageHistogramValues, zigzagImageDistanceHistogram, comparisonVector, zigZagComparisonVector);

		//clean up
		for (SignalDescriptor* sd : imageSignalsDescriptors)
			if (sd != nullptr)
				delete sd;
		for (SignalDescriptor* sd : topImageSignalsDescriptors)
			delete sd;
	
		emit updateProgressBar(fWorkerId, 100);
		emit returnCalculateSuccessRateResult(comparisonVector, zigZagComparisonVector, fWorkerId);
		emit releaseProgressBarSlot(fWorkerId);
}
