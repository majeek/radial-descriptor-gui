#include "CalculateSuccessRateForAllWorker.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor.  </summary>
///
/// <remarks>	Majeed Kassis, 9/22/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CalculateSuccessRateForAllWorker::~CalculateSuccessRateForAllWorker(){

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Majeed Kassis, 9/22/2014. </remarks>
///
/// <param name="path">												 	Full pathname of the
/// 																	file. </param>
/// <param name="threadPool">										 	[in,out] If non-null, the
/// 																	thread pool. </param>
/// <param name="method">											 	The method. </param>
/// <param name="radius">											 	The radius. </param>
/// <param name="vectorsCount">										 	Number of vectors. </param>
/// <param name="interpolationValue">								 	The interpolation value. </param>
/// <param name="minDistance">										 	The minimum distance. </param>
/// <param name="imagesHistograms">									 	[in,out] If non-null, the
/// 																	images histograms. </param>
/// <param name="imagesDistanceHistograms">							 	The images distance
/// 																	histograms. </param>
/// <param name="imagesZigZagHistograms">							 	The images zig zag
/// 																	histograms. </param>
/// <param name="numberOfLevels">									 	Number of levels. </param>
/// <param name="levelRadiusPercentage">							 	The level radius
/// 																	percentage. </param>
/// <param name="maxSignals">										 	The maximum signals. </param>
/// <param name="model">											 	[in,out] If non-null, the
/// 																	model. </param>
/// <param name="gaussBlur">										 	The gauss blur. </param>
/// <param name="kernelSize">										 	Size of the kernel. </param>
/// <param name="minVariance">										 	The minimum variance. </param>
/// <param name="calculateSuccessRateForAllWorkerWaitCondition">	 	[in,out] If non-null, the
/// 																	calculate success rate
/// 																	for all worker wait
/// 																	condition. </param>
/// <param name="calculateSuccessRateForAllWorkerWaitConditionMutex">	[in,out] If non-null, the
/// 																	calculate success rate
/// 																	for all worker wait
/// 																	condition mutex. </param>
/// <param name="parent">											 	[in,out] If non-null, the
/// 																	parent. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

CalculateSuccessRateForAllWorker::CalculateSuccessRateForAllWorker(QString path, QThreadPool* threadPool, 
																   int method, int radius, int vectorsCount, 
																   double interpolationValue, int minDistance, 
																   cv::vector<cv::vector<double>>* imagesHistograms, 
																   cv::vector<cv::vector<double>>* imagesZigZagHistograms, 
																   int numberOfLevels, 
																   int levelRadiusPercentage, int maxSignals, cv::EM* model, double gaussBlur, 
																   int kernelSize, int minVariance, QWaitCondition* calculateSuccessRateForAllWorkerWaitCondition, 
																   QMutex* calculateSuccessRateForAllWorkerWaitConditionMutex, int backgroundColor, QObject* parent): 
fPath(path), fThreadPool(threadPool), QObject(parent),
	fMethod(method),
	fRadius(radius), 
	fVectorsCount(vectorsCount), 
	fInterpolationValue(interpolationValue), 
	fMinDistance(minDistance), 
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
	fCalculateSuccessRateForAllWorkerWaitCondition(calculateSuccessRateForAllWorkerWaitCondition),
	fCalculateSuccessRateForAllWorkerWaitConditionMutex(calculateSuccessRateForAllWorkerWaitConditionMutex),
	fBackgroundColor(backgroundColor){
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Runs this object. </summary>
///
/// <remarks>	Majeed Kassis, 9/22/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CalculateSuccessRateForAllWorker::run(void){

	//add image file names to image combo box and load the image files into matrices
	QStringList wordPartDirectories = QDir(fPath).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::Dirs);
	QStringListIterator iter(wordPartDirectories);

	while (iter.hasNext()){ //next dir
		QString dirName = iter.next();
		//qDebug() << "Detecting " << dirName;
		QStringList imagesList = QDir(fPath + "/"+ dirName).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::Files);
		cv::vector<cv::Mat> imagesMats;
		for (QString imageName : imagesList){
			cv::Mat image = SharedWorkersFunctions::loadUnicodeImage(fPath + "/" + dirName + "/" + imageName);
			cv::resize(image, image, cv::Size(), 4, 4, CV_INTER_CUBIC);
			imagesMats.push_back(image);
		}
		emit updateSuccessRateVariablesSignal(imagesMats,imagesMats.size(),imagesList);
		calculateSuccessRateForOneDirectory(imagesMats, imagesList, dirName);
		fCalculateSuccessRateForAllWorkerWaitConditionMutex->lock();
		fCalculateSuccessRateForAllWorkerWaitCondition->wait(fCalculateSuccessRateForAllWorkerWaitConditionMutex);
		fCalculateSuccessRateForAllWorkerWaitConditionMutex->unlock();
		fThreadPool->waitForDone();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculates the success rate for one directory. </summary>
///
/// <remarks>	Majeed Kassis, 9/22/2014. </remarks>
///
/// <param name="imagesMats"> 	[in,out] The images mats. </param>
/// <param name="imagesNames">	List of names of the images. </param>
/// <param name="dirName">	  	Pathname of the directory. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CalculateSuccessRateForAllWorker::calculateSuccessRateForOneDirectory(cv::vector<cv::Mat>& imagesMats, QStringList imagesNames, QString dirName){

	emit initializeProgressBarWaitDialogSignal("Success Rate: Detecting Images for "+ dirName, imagesMats.size());
	for (int i=0;i<imagesMats.size();i++){
		//create worker, thread and run, connect signals
		CalculateSuccessRateWorker* worker = new CalculateSuccessRateWorker(imagesNames, fMethod, fRadius, fVectorsCount, fInterpolationValue, 
			fMinDistance, imagesMats[i], fImagesHistograms, fImagesZigZagHistograms, fNumberOfLevels, fLevelRadiusPercentage, fMaxSignals, fModel, fGaussBlur, fKernelSize, fMinVariance, i, imagesNames[i], fBackgroundColor);
		//emit signal to run worker
		emit connectCalculateSuccessRateWorkerSignalsAndRunItSignal(worker);
	}
}