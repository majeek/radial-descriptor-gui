#include "CreateHistogramsWorker.hpp"


CreateHistogramsWorker::CreateHistogramsWorker(QString modelPath, cv::vector<cv::vector<SignalDescriptor*>*>* descriptorPointsForAllImages,
											   cv::vector<cv::Mat> images, int numberOfLevels,
											   int levelRadiusPercentage, int radius, int vectorsCount,
											   double gaussBlur, int kernelSize, int numberOfClusters, int backgroundColor):
	fModelPath(modelPath),
	fDescriptorPointsForAllImages(descriptorPointsForAllImages),
	fImages(images),
	fNumberOfLevels(numberOfLevels),
	fLevelRadiusPercentage(levelRadiusPercentage),
	fRadius(radius),
	fVectorsCount(vectorsCount),
	fGaussBlur(gaussBlur),
	fKernelSize(kernelSize),
	fNumberOfClusters(numberOfClusters),
	fBackgroundColor(backgroundColor){
}


CreateHistogramsWorker::~CreateHistogramsWorker(void){
}


void CreateHistogramsWorker::run(){
	
	emit showMessageWaitWindow();
	emit updateComparisonProgress("Training model");
	cv::EM* model = new cv::EM(fNumberOfClusters);

	//combine all signals for EM input
	cv::Mat allSignals;
	for (int i=0;i<fDescriptorPointsForAllImages->size();i++){
		for (int j=0;j<fDescriptorPointsForAllImages->at(i)->size();j++){
			allSignals.push_back(fDescriptorPointsForAllImages->at(i)->at(j)->getSignal());
		}
	}

	//train model
	cv::Mat labels(allSignals.rows,1,CV_32SC1);

	model->train(allSignals,cv::noArray(),labels,cv::noArray());
	
	int i=0;
	for (int img_i=0;img_i<fDescriptorPointsForAllImages->size();img_i++){
		for (int j=0;j<fDescriptorPointsForAllImages->at(img_i)->size();j++){
			fDescriptorPointsForAllImages->at(img_i)->at(j)->setCluster(labels.at<int>(i,0));
			i++;
		}
	}

	//values to return
	cv::vector<cv::vector<double>>* imagesHistograms = new cv::vector<cv::vector<double>>();
	//cv::vector<cv::Mat> imagesDistanceHistograms;
	cv::vector<cv::vector<double>>* imagesZigZagHistograms = new cv::vector<cv::vector<double>>();

	
	emit updateComparisonProgress("Creating histograms");
	//create histograms
	for (int i=0;i<fDescriptorPointsForAllImages->size();i++){
		int numberOfSignals = fDescriptorPointsForAllImages->at(i)->size();
		std::vector<SignalDescriptor*> *imageSignals = fDescriptorPointsForAllImages->at(i);
		//initialize data for historgram
		cv::vector<double> values;
		
		for (int i=0;i<fNumberOfClusters;i++)
			values.push_back(0);

		//fill data with values
		for (int i=0; i<numberOfSignals;i++){
			//cv::Vec2d result;
			//result = model->predict(imageSignals->at(i)->getSignal());
			//values->at(result[1])++;
			values.at(imageSignals->at(i)->getCluster())++; //TODO check change
		}
		imagesHistograms->push_back(values);
	}
	
	emit updateComparisonProgress("Creating distance and zigzag histograms");
	//create distance and zigzag histograms
	for (int img_i=0;img_i<fDescriptorPointsForAllImages->size();img_i++){
		cv::Mat padded = SharedWorkersFunctions::prepareImage(fImages[img_i], fVectorsCount, fKernelSize, fGaussBlur, fRadius, fBackgroundColor);
		cv::Mat distanceHistogram = SharedWorkersFunctions::calcaulateImageDistanceHisogram(fNumberOfClusters, fDescriptorPointsForAllImages->at(img_i), fLevelRadiusPercentage, padded, fNumberOfLevels);
		//normalize histogram and save it.
		//imagesDistanceHistograms.push_back(distanceHistogram);
		//create a zigzag of the histogram and save it.
		cv::vector<double> zigZag = SharedWorkersFunctions::createZigZagDistance(distanceHistogram);
		imagesZigZagHistograms->push_back(zigZag);
	}

	emit hideMessageWaitWindow();
	emit returnHistogramsSignal(imagesHistograms, imagesZigZagHistograms, model);
}
