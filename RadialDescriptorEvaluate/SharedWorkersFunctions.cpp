#include "SharedWorkersFunctions.hpp"


cv::Mat SharedWorkersFunctions::loadUnicodeImage(QString fileName){

	QFile file(fileName);
	std::vector<char> buffer;
	buffer.resize(file.size());
	if (!file.open(QIODevice::ReadOnly)) {
		return cv::Mat();
	}
	file.read(buffer.data(), file.size());
	file.close();
	cv::Mat image = cv::imdecode(buffer, CV_LOAD_IMAGE_UNCHANGED);

	return image;
	//cv::Mat img =  cv::imread(fileName.toStdString());
	//return img;
}

void SharedWorkersFunctions::createUnicodePath(QString path){
	//wchar_t fullPathArray[200];
	//int count = path.toWCharArray(fullPathArray);
	//fullPathArray[count] = '\0';
	//CreateDirectoryW(fullPathArray, nullptr);
	CreateDirectoryW((const wchar_t *)path.utf16(), nullptr);
}

void SharedWorkersFunctions::saveUnicodeImage(QString fileName, cv::Mat image, std::string type){

	//wchar_t fileNameFull[200];
	//int count = fileName.toWCharArray(fileNameFull);
	//fileNameFull[count] = '\0';
	std::vector<uchar> buff;
	cv::imencode("." + type, image, buff);
	//std::ofstream outfile(fileNameFull, std::ofstream::binary);
	std::ofstream outfile((const wchar_t *)fileName.utf16(), std::ofstream::binary);
	outfile.write(reinterpret_cast<const char*>(buff.data()), buff.size());
	outfile.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets shift value. </summary>
///
/// <remarks>	majeek, 3/15/2014. </remarks>
///
/// <param name="vectorsCount">	Number of vectors. </param>
/// <param name="radius">	   	The radius. </param>
///
/// <returns>	The shift value. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SharedWorkersFunctions::getShiftValue(int vectorsCount, int radius){
	// find signals
	int shift = 2;
	for (int i=0;i<vectorsCount;i++)
		shift = shift * 2;
	shift = shift+radius;

	return shift;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Prepare image, convert to grayscale, pad it and apply gaussian blur. </summary>
///
/// <remarks>	majeek, 3/15/2014. </remarks>
///
/// <param name="imageToPrepare">	The image to prepare. </param>
/// <param name="vectorsCount">  	Number of vectors. </param>
/// <param name="kernelSize">	 	Size of the kernel. </param>
/// <param name="gaussBlur">	 	The gauss blur. </param>
/// <param name="radius">		 	The radius. </param>
///
/// <returns>	A cv::Mat. The prepared image. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat SharedWorkersFunctions::prepareImage(cv::Mat imageToPrepare, int vectorsCount, int kernelSize, double gaussBlur, int radius, int backgroundColor){
	
	cv::Mat image;

	if (imageToPrepare.channels() != 1)
		//convert to grayscale
		cv::cvtColor(imageToPrepare, image, CV_RGB2GRAY);
	else
		image = imageToPrepare.clone();
	int shift = getShiftValue(vectorsCount, radius);
	//if background color sent from main is 0, means we use mean, otherwise, we use background color.
	//if (backgroundColor == 0){
	//	//calculate median background color
	//	QVector<qint16> bgColors;
	//	for (int row = 0; row < image.rows; row++){
	//		bgColors.push_back((qint16)image.at<uchar>(row, 0));
	//		bgColors.push_back((qint16)image.at<uchar>(row, image.cols - 1));
	//	}

	//	for (int col = 0; col < image.cols; col++){
	//		bgColors.push_back((qint16)image.at<uchar>(0, col));
	//		bgColors.push_back((qint16)image.at<uchar>(image.rows - 1, col));
	//	}
	//	qSort(bgColors);
	//	backgroundColor = bgColors.at(bgColors.size() / 2);
	//}
	//padd it with  lines everywhere //background white
	cv::Mat padded = cv::Mat::ones(image.rows + 2 * shift, image.cols + 2 * shift, image.type()) * backgroundColor;
	image.copyTo(padded(cv::Rect(shift, shift, image.cols, image.rows)));
	
	if (backgroundColor == 0){
		//need to copy line "shift" to line 0 to shift-1
		for (int col = 0; col < shift; col++)
			for (int row = 0; row < image.rows; row++)
				padded.at<uchar>(shift + row, col) = padded.at<uchar>(shift + row, shift);

		//need to copy line shift+image.cols-1 to line image.cols to image.cols+shift-1
		for (int col = 0; col < shift; col++)
			for (int row = 0; row < image.rows; row++)
				padded.at<uchar>(shift + row, shift + image.cols + col) = padded.at<uchar>(shift + row, shift + image.cols - 1);

		//then copy row "shift" to row 0 to shift-1
		for (int row = 0; row < shift; row++)
			for (int col = 0; col < padded.cols; col++)
				padded.at<uchar>(row, col) = padded.at <uchar>(shift, col);

		//copy row shift + image.rows-1 to image.rows to image.rows+shift-1
		for (int row = shift + image.rows; row < padded.rows; row++)
			for (int col = 0; col < padded.cols; col++)
				padded.at<uchar>(row, col) = padded.at <uchar>(shift + image.rows - 1, col);
	}
	if (gaussBlur!=0.0)
		cv::GaussianBlur(padded,padded,cv::Size(kernelSize,kernelSize),gaussBlur);

	return padded;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates a feature of a given pixel co-ordinates for an image. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="i">				 	Zero-based index of the. </param>
/// <param name="j">				 	The int to process. </param>
/// <param name="padded">			 	The padded. </param>
/// <param name="interpolationValue">	The interpolation value. </param>
/// <param name="radius">			 	The radius. </param>
/// <param name="vectorsCount">		 	Number of vectors. </param>
/// <param name="minVariance">		 	The minimum variance. </param>
///
/// <returns>	null if it doesn't pass the average variance threshold, else the new feature. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

SignalDescriptor* SharedWorkersFunctions::createFeature(int i, int j, cv::Mat padded, double interpolationValue, int radius, int vectorsCount, int minVariance){

	PointDescriptor pd = PointDescriptor(padded,cv::Point2i(j,i), interpolationValue);
	pd.createRingSignatureSet(radius, vectorsCount);
	pd.calculateDescriptorMatrix();
	//if the option is checked and point descriptor passes variance threshold, it is added.
	SignalDescriptor *sd  = nullptr;
	if (pd.getAverageVariance() >= minVariance){
		pd.findDominantSet();
		pd.calculateDominantSignal();
		sd = new SignalDescriptor(pd.getCenterPoint().y, pd.getCenterPoint().x, radius, pd.getAverageVariance(), pd.getDominantSignal());
		sd->setFarthestRing(pd.getFarthestRing());
	}
	return sd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sort features by variance. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="imageSignalsDescriptors">	[in,out] If non-null, the image signals descriptors. </param>
///
/// <returns>	returns the sorted features by variance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SharedWorkersFunctions::sortFeaturesByVariance(cv::vector<SignalDescriptor*>& imageSignalsDescriptors){
	
	for (int i = 0; i<imageSignalsDescriptors.size(); i++){
		int maxIndex = -1;
		double maxVariance = 0;
		for (int j = i; j<imageSignalsDescriptors.size(); j++){
			if (imageSignalsDescriptors[j]->getVariance()>maxVariance){
				maxIndex = j;
				maxVariance = imageSignalsDescriptors[j]->getVariance();
			}
		}
		SignalDescriptor* sd = imageSignalsDescriptors[i];
		imageSignalsDescriptors[i] = imageSignalsDescriptors[maxIndex];
		imageSignalsDescriptors[maxIndex] = sd;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets top k features. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="minDistance">			  	The minimum distance between two feature co-ordinates. </param>
/// <param name="sortedSignalDescriptors">	[in,out] [in,out] If non-null, the sorted signal
/// 										descriptors. </param>
/// <param name="maxSignals">			  	The number of required signals. </param>
///
/// <returns>	Top K features, where two features are of distance minDistance at least, if possible. Otherwise, just top K features. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SharedWorkersFunctions::getTopKFeatures(int minDistance, cv::vector<SignalDescriptor*> &sortedSignalDescriptors, int maxSignals, cv::vector<SignalDescriptor*> *topImageSignalsDescriptors){


	if (minDistance!=-1){
		//we split each descriptor with all its surroundings and put them into 1 group
		cv::vector<cv::vector<SignalDescriptor*>> signalGroups;

		while (sortedSignalDescriptors.size()>0){
			//initialize new goup
			cv::vector<SignalDescriptor*> oneSignalGroup;
			SignalDescriptor* frontElement = sortedSignalDescriptors[0];
			oneSignalGroup.push_back(frontElement);
			sortedSignalDescriptors.erase(sortedSignalDescriptors.begin());
			//find indexes of new signals around our signal descriptor
			cv::vector<int> indexesToGroup; //indexes added here

			int row = frontElement->getRow();
			int col = frontElement->getCol();
			for(int i=0;i<sortedSignalDescriptors.size();i++){
				int diffRow = std::abs(sortedSignalDescriptors[i]->getRow()-row);
				int diffCol = std::abs(sortedSignalDescriptors[i]->getCol()-col);
				if ((diffRow <= minDistance) && (diffCol <= minDistance)) //if in range
					indexesToGroup.push_back(i);
			}
			//add new signals to same group and remove from older one
			for (int i=0;i<indexesToGroup.size();i++)
				oneSignalGroup.push_back(sortedSignalDescriptors[indexesToGroup[i]]);
			//remove signals from sortedSignalDescriptors
			for (int i=indexesToGroup.size()-1;i>=0;i--)
				sortedSignalDescriptors.erase(sortedSignalDescriptors.begin()+indexesToGroup[i]);
			//add group to signalGroups
			signalGroups.push_back(oneSignalGroup);
		}
	
		//we take 1 element from each group hoping to reach number of points required. if not we do another wave
		
		int i=0;
		int numOfGroups = signalGroups.size();
		int elementsToAdd = maxSignals;
		bool success = false;
		while (elementsToAdd!=0){
			if (!signalGroups[i].empty()){
				success = true;
				topImageSignalsDescriptors->push_back(signalGroups[i][0]);
				signalGroups[i].erase(signalGroups[i].begin());
				elementsToAdd--;
			}
			i++;
			//if we scanned all possible groups and all are empty then we stop, otherwise we reset.
			if (i==numOfGroups){
				if (!success)
					elementsToAdd =0;
				else{
					i=0;
					success = false;
				}
			}
		}
		//free signalGroups
		for (cv::vector<SignalDescriptor*> sdVec : signalGroups)
			for (SignalDescriptor* sd : sdVec)
				delete sd;
	
	}else { //we just take first K elements.
		for (int i=0;i<maxSignals;i++){
			topImageSignalsDescriptors->push_back(sortedSignalDescriptors[i]);
			sortedSignalDescriptors[i] = nullptr;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw circles for each feature (coordinates) on image. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="image">					 	The image. </param>
/// <param name="shift">					 	The shift. </param>
/// <param name="gaussBlur">				 	The gauss blur. </param>
/// <param name="kernelSize">				 	Size of the kernel. </param>
/// <param name="topImageSignalsDescriptors">	[in,out] If non-null, the top image signals
/// 											descriptors. </param>
///
/// <returns>	The image with features drawn on it. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat SharedWorkersFunctions::drawFeaturesOnImage(cv::Mat image, int shift, double gaussBlur, int kernelSize, cv::vector<SignalDescriptor*> *topImageSignalsDescriptors){

	cv::Mat markedImage = cv::Mat::ones(image.rows + 2*shift, image.cols + 2*shift, image.type());
	for (int i=0;i<markedImage.rows;i++)
		for (int j=0;j<markedImage.cols;j++)
			markedImage.at<cv::Vec3b>(i,j) = cv::Vec3b(255,255,255);

			
	image.copyTo(markedImage(cv::Rect(shift, shift, image.cols, image.rows)));
	
	if (gaussBlur!=0.0)
		cv::GaussianBlur(markedImage,markedImage,cv::Size(kernelSize,kernelSize),gaussBlur);
	
	int i=0;
	for (SignalDescriptor* sd : *topImageSignalsDescriptors){
		//add right point box
		cv::vector<cv::Point2i>::iterator iter;
		cv::vector<cv::Point> rightFarthestRing = sd->getFarthestRing();
		for (iter = rightFarthestRing.begin(); iter != rightFarthestRing.end(); iter++){
			cv::Point curPoint = *iter;
			if (curPoint.x>0 && curPoint.y>0 && curPoint.x<markedImage.cols && curPoint.y<markedImage.rows)
				markedImage.at<cv::Vec3b>(curPoint) = cv::Vec3b(0,255,0);
		}
		//add center point for right point
		markedImage.at<cv::Vec3b>(sd->getRow(),sd->getCol()) = cv::Vec3b(0,255,0);
		i++;
	}

	return markedImage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Cluster features into the different clusters. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="topImageSignalsDescriptors">	[in,out] If non-null, the top image signals
/// 											descriptors. </param>
/// <param name="model">					 	[in,out] If non-null, the model. </param>
///
/// <returns>	A cv::vector&lt;double&gt; </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::vector<double> SharedWorkersFunctions::clusterFeatures(cv::vector<SignalDescriptor*> &topImageSignalsDescriptors, cv::EM* model){
	// cluster the signals
	int numberOfSignals = topImageSignalsDescriptors.size();
	//initialize data for historgram
	int clusters = model->get<int>("nclusters");
	cv::vector<double> imageHistogramValues(clusters);
	//fill data with values
	for (int i=0; i<numberOfSignals;i++){
		cv::Vec2d result = model->predict(topImageSignalsDescriptors[i]->getSignal());
		topImageSignalsDescriptors[i]->setCluster(result[1]);
		imageHistogramValues[result[1]]++;
	}
	return imageHistogramValues;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Converts histogram matrix to vector. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="distanceHistogram">	The distance histogram. </param>
///
/// <returns>	A cv::vector&lt;double&gt; </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::vector<double> SharedWorkersFunctions::histogramMatrixToVector(cv::Mat distanceHistogram){
	//convert distance histogram matrix to vector
	cv::vector<double> distanceHistogramVector;
	for (int i_i=0;i_i<distanceHistogram.rows;i_i++)
		for (int j_j=0;j_j<distanceHistogram.cols;j_j++)
			distanceHistogramVector.push_back(distanceHistogram.at<double>(i_i,j_j));
	return distanceHistogramVector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Compare histograms. </summary>
///
/// <remarks>	majeek, 3/14/2014. </remarks>
///
/// <param name="imagesHistograms">			   	[in,out] [in,out] If non-null, the images
/// 											histograms. </param>
/// <param name="imagesDistanceHistograms">	   	[in,out] The images distance histograms. </param>
/// <param name="imagesZigZagHistograms">	   	[in,out] The images zig zag histograms. </param>
/// <param name="method">					   	The method. </param>
/// <param name="imageHistogramValues">		   	[in,out] The image histogram values. </param>
/// <param name="imageDistanceHistogramVector">	[in,out] The image distance histogram vector. </param>
/// <param name="zigzagImageDistanceHistogram">	[in,out] The zigzag image distance histogram. </param>
/// <param name="comparisonVector">			   	[in,out] The comparison vector. </param>
/// <param name="distanceComparisonVector">	   	[in,out] The distance comparison vector. </param>
/// <param name="zigZagComparisonVector">	   	[in,out] The zig zag comparison vector. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SharedWorkersFunctions::compareHistograms(cv::vector<cv::vector<double>>* imagesHistograms, cv::vector<cv::vector<double>>* imagesZigZagHistograms, int method, cv::vector<double> &imageHistogramValues, cv::vector<double> &zigzagImageDistanceHistogram, cv::vector<double> &comparisonVector,cv::vector<double> &zigZagComparisonVector){
	for (int i=0;i<imagesHistograms->size();i++){
		
		cv::vector<double> histogram = imagesHistograms->at(i);
		//cv::Mat distanceHistogram = imagesDistanceHistograms[i];
		
		//generate zig zag histogram from distance histogram
		cv::vector<double> zigZagDistanceHistogram = imagesZigZagHistograms->at(i);
		

		//convert distance histogram matrix to vector
		//cv::vector<double> distanceHistogramVector = SharedWorkersFunctions::histogramMatrixToVector(distanceHistogram);
		

		double comparisonResult = -1;
		double comparisonResultZigZag = -1;
		//double distanceComparisonResult = -1;


		//normalize histograms
		histogram = SharedWorkersFunctions::normalizeDistanceVector(histogram); 
		//distanceHistogramVector = SharedWorkersFunctions::normalizeDistanceVector(distanceHistogramVector);
		zigZagDistanceHistogram = SharedWorkersFunctions::normalizeDistanceVector(zigZagDistanceHistogram);
		if (method==1){ //chi-squared
			//regular histogram 			
			comparisonResult = SharedWorkersFunctions::compareHistChiSquare(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = SharedWorkersFunctions::compareHistChiSquare(distanceHistogramVector, imageDistanceHistogramVector);
			// zig zag distance histogram			
			comparisonResultZigZag = SharedWorkersFunctions::compareHistChiSquare(zigzagImageDistanceHistogram, zigZagDistanceHistogram);
		}else if (method==0){ //cosine similarity
			//regular histogram 			
			comparisonResult = -1*SharedWorkersFunctions::compareHistCosineDistance(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = -1*SharedWorkersFunctions::compareHistCosineDistance(distanceHistogramVector, imageDistanceHistogramVector);
			// zig zag distance histogram			
			comparisonResultZigZag = -1*SharedWorkersFunctions::compareHistCosineDistance(zigzagImageDistanceHistogram, zigZagDistanceHistogram);
		}else if (method==2){ //eulidean distance
			//regular histogram 			
			comparisonResult = SharedWorkersFunctions::compareHistEuclideanDistance(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = SharedWorkersFunctions::compareHistEuclideanDistance(distanceHistogramVector, imageDistanceHistogramVector);
			// zig zag distance histogram			
			comparisonResultZigZag = SharedWorkersFunctions::compareHistEuclideanDistance(zigzagImageDistanceHistogram, zigZagDistanceHistogram);
		}else{ //we compare all
				//regular histogram 			
			comparisonResult = SharedWorkersFunctions::compareHistChiSquare(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = SharedWorkersFunctions::compareHistChiSquare(distanceHistogramVector, imageDistanceHistogramVector);
			// zig zag distance histogram			
			comparisonResultZigZag = SharedWorkersFunctions::compareHistChiSquare(zigzagImageDistanceHistogram, zigZagDistanceHistogram);

			comparisonVector.push_back(comparisonResult);
			//distanceComparisonVector.push_back(distanceComparisonResult);
			zigZagComparisonVector.push_back(comparisonResultZigZag);


			//regular histogram 			
			comparisonResult = -1*SharedWorkersFunctions::compareHistCosineDistance(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = -1*SharedWorkersFunctions::compareHistCosineDistance(distanceHistogramVector, imageDistanceHistogramVector);
			// zig zag distance histogram			
			comparisonResultZigZag = -1*SharedWorkersFunctions::compareHistCosineDistance(zigzagImageDistanceHistogram, zigZagDistanceHistogram);


			comparisonVector.push_back(comparisonResult);
			//distanceComparisonVector.push_back(distanceComparisonResult);
			zigZagComparisonVector.push_back(comparisonResultZigZag);


			//regular histogram 			
			comparisonResult = SharedWorkersFunctions::compareHistEuclideanDistance(imageHistogramValues, histogram);
			//distance histogram			
			//distanceComparisonResult = SharedWorkersFunctions::compareHistEuclideanDistance(distanceHistogramVector, imageDistanceHistogramVector);
			//zig zag distance histogram			
			comparisonResultZigZag = SharedWorkersFunctions::compareHistEuclideanDistance(zigzagImageDistanceHistogram, zigZagDistanceHistogram);

		}

		comparisonVector.push_back(comparisonResult);
		//distanceComparisonVector.push_back(distanceComparisonResult);
		zigZagComparisonVector.push_back(comparisonResultZigZag);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates zig zag distance histogram. </summary>
///
/// <remarks>	majeek, 4/23/2014. </remarks>
///
/// <param name="distanceHistogram">	The distance histogram. </param>
///
/// <returns>	The new zig zag distance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::vector<double> SharedWorkersFunctions::createZigZagDistance(cv::Mat distanceHistogram){

	cv::vector<double> zigZagResult;
	

	int row = 0;
	int col = 0;
	
	while (row!=0 || col!=distanceHistogram.cols-1){
		//first we go down
		while (col!=distanceHistogram.cols){
			zigZagResult.push_back(distanceHistogram.at<double>(row,col));
			row++;
			col++;
		}
		//now we go up
		row-=2;
		col--;
		if (row!=0 || col!=distanceHistogram.cols-1){
			while (row!=-1){
				zigZagResult.push_back(distanceHistogram.at<double>(row,col));
				row--;
				col--;
			}
			row++;
			col+=2;
		}
	}
	zigZagResult.push_back(distanceHistogram.at<double>(0,distanceHistogram.cols-1));
	return zigZagResult;
}
		



////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates zig zag distance vector of the distance histogram. </summary>
///
/// <remarks>	majeek, 2/3/2014. </remarks>
///
/// <param name="distanceHistogram">	The distance histogram. </param>
///
/// <returns>	The new zig zag distance vector. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

//cv::vector<double> SharedWorkersFunctions::createZigZagDistance(cv::Mat distanceHistogram){
//
//	cv::vector<double> zigZagResult;
//
//	zigZagResult.push_back(distanceHistogram.at<double>(0,0));
//	zigZagResult.push_back(distanceHistogram.at<double>(0,1));
//	int row = 1;
//	int col = 0;
//	bool goingDown = false;
//	if (distanceHistogram.rows % 2 == 0){
//		bool incremented = false;
//		while (row != distanceHistogram.rows){
//			zigZagResult.push_back(distanceHistogram.at<double>(row, col));
//			if (!incremented && (col == 0)){
//				incremented = true;
//				row++;
//				goingDown = false;
//			}else if (!incremented && (row == 0)){
//				incremented = true;
//				goingDown = true;
//				col++;
//			}else if (goingDown){
//				incremented = false;
//				col--;
//				row++;
//			}else if (!goingDown){
//				incremented = false;
//				col++;
//				row--;
//			}
//		}
//	}else{
//		bool incremented = false;
//		while (col != distanceHistogram.cols){
//			zigZagResult.push_back(distanceHistogram.at<double>(row, col));
//			if (!incremented && (col == 0)){
//				incremented = true;
//				row++;
//				goingDown = false;
//			}else if (!incremented && (row == 0)){
//				incremented = true;
//				goingDown = true;
//				col++;
//			}else if (goingDown){
//				incremented = false;
//				col--;
//				row++;
//			}else if (!goingDown){
//				incremented = false;
//				col++;
//				row--;
//			}
//		}
//	}
//
//	return zigZagResult;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calcaulate image distance hisogram. </summary>
///
/// <remarks>	majeek, 12/17/2013. </remarks>
///
/// <param name="numberOfClusters">			Number of clusters. </param>
/// <param name="imageSignals">				[in,out] If non-null, the image signals. </param>
/// <param name="levelRadiusPercentage">	The level radius percentage. </param>
/// <param name="image">					The image. Provide the padded image!! Not the original one!! </param>
/// <param name="numberOfLevels">			Number of levels. </param>
///
/// <returns>	A cv::Mat. The generated distance histogram. </returns>
///
/// ### <param name="rangeSize">	Size of the range. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat SharedWorkersFunctions::calcaulateImageDistanceHisogram(int numberOfClusters, cv::vector<SignalDescriptor*>* imageSignals, int levelRadiusPercentage, cv::Mat image, int numberOfLevels){

	//image matrix which contains the different histogram values, row for each cluster, col for each cluster (0...n)

	int levelRadius;
	if (image.rows > image.cols)
		levelRadius = std::floor(image.cols * (levelRadiusPercentage / 100.0) + 0.5);
	else
		levelRadius = std::floor(image.rows * (levelRadiusPercentage / 100.0) + 0.5);

	cv::Mat gaussianKernelFull = cv::getGaussianKernel(levelRadius*2+1,1,CV_64FC1); 
	cv::Mat gaussianKernel = cv::Mat(levelRadius,1,CV_64FC1); //1 column vector
	cv::vector<double> gaussKernelVec;
	for (int i=0;i<levelRadius;i++){
		gaussianKernel.at<double>(i,0) = gaussianKernelFull.at<double>(levelRadius+i);
		gaussKernelVec.push_back( gaussianKernelFull.at<double>(levelRadius+i));
	}

	//we'll do it for image 0 only then move it to a thread.
	cv::Mat distanceHistogram = cv::Mat::zeros(numberOfClusters, numberOfClusters, CV_64FC1);

	// split the signals to different groups - following their clusters
	cv::vector<cv::vector<SignalDescriptor*>> clusteredImageSignals;
	for (int i=0;i<numberOfClusters;i++)
		clusteredImageSignals.push_back(cv::vector<SignalDescriptor*>());
	for (int i=0;i<imageSignals->size();i++){
		int clusterIndex = imageSignals->at(i)->getCluster();
		clusteredImageSignals[clusterIndex].push_back(imageSignals->at(i));
	}

	// for each cluster
	for (int l=0;l<numberOfClusters;l++){
		// for each signal in cluster l 
		for (int i=0;i<clusteredImageSignals[l].size();i++){
			// the signal i in cluster l
			SignalDescriptor* currentSignal = clusteredImageSignals[l][i];
			// we scan each cluster and calculate the distance vector for that cluster
			for (int j=0;j<numberOfClusters;j++){
				// slot 0 distance 1 // slot 1 distance 2 // slot 2 distance 3
				cv::Mat distanceVector = cv::Mat::zeros(1, levelRadius, CV_64FC1); //1 row vector
				//we scan each point in cluster j and calculate the distance vector for (i,j)
				for (int k=0;k<clusteredImageSignals[j].size();k++){
					int distance = currentSignal->calculateDistance(*(clusteredImageSignals[j][k]));
					bool found = false;
					for (int i=numberOfLevels;i<=numberOfLevels*levelRadius && !found;i+=levelRadius){
						if (distance < i){
							distanceVector.at<double>(0,(i/double(numberOfLevels))-1)+=1;
							found = true;
						}
					}	
				}
				cv::Mat result = distanceVector*gaussianKernel;
				//qDebug() << i << j;
				distanceHistogram.at<double>(l,j) += result.at<double>(0,0);
			}
		}
	}


	return distanceHistogram;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Normalize distance vector. </summary>
///
/// <remarks>	majeek, 3/10/2014. </remarks>
///
/// <param name="zigZag">	The zig zag. </param>
///
/// <returns>	A cv::vector&lt;double&gt; </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::vector<double> SharedWorkersFunctions::normalizeDistanceVector(cv::vector<double> zigZag){
	double sum = 0;
	cv::vector<double> result;
	for (int i=0;i<zigZag.size();i++)
		sum += zigZag[i];
	
	for (int i=0;i<zigZag.size();i++)
		result.push_back(zigZag[i]/sum);
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Normalize distance histogram. </summary>
///
/// <remarks>	majeek, 3/10/2014. </remarks>
///
/// <param name="distanceHistogram">	The distance histogram. </param>
///
/// <returns>	A cv::Mat. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat SharedWorkersFunctions::normalizeDistanceHistogram(cv::Mat distanceHistogram){
	//normalize its sum = 1
	//count sum
	cv::Mat result = cv::Mat::zeros(distanceHistogram.size(),distanceHistogram.type());
	double sum = 0;
	for (int i=0;i<distanceHistogram.rows;i++)
		for (int j=0;j<distanceHistogram.cols;j++)
			sum += distanceHistogram.at<double>(i,j);
	//element wise divide by sum
	for (int i=0;i<distanceHistogram.rows;i++)
		for (int j=0;j<distanceHistogram.cols;j++)
			result.at<double>(i,j) =  distanceHistogram.at<double>(i,j)/sum;
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Convert this object into a string representation. </summary>
///
/// <remarks>	majeek, 3/11/2014. </remarks>
///
/// <param name="histogramVector">	The histogram vector. </param>
///
/// <returns>	A QString that represents this object. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SharedWorkersFunctions::toString(cv::vector<double> histogramVector){
	QString string("[");
	for (int i=0;i<histogramVector.size();i++){
		string += QString::number(histogramVector[i]);
		if (i==histogramVector.size()-1)
			string += "]";
		else
			string += ",";
	}
	return string;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Compare histograms using chi square rounded to 5th decimal </summary>
///
/// <remarks>	majeek, 2/6/2014. </remarks>
///
/// <param name="firstHistogram"> 	The first histogram. </param>
/// <param name="secondHistogram">	The second histogram. </param>
///
/// <returns>	A double. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

double SharedWorkersFunctions::compareHistChiSquare(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram){

	double distance =0;
	for (int i=0;i<firstHistogram.size();i++)
		distance +=cv::pow((firstHistogram[i]-secondHistogram[i]),2)/(firstHistogram[i]+secondHistogram[i]+DBL_EPSILON);
	
	//gotta multiply by 0.5 to conform with chi-square equasion.
	return std::floor(distance*10000+0.5)/10000;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Compare hist cosine distance. Following wikipedia's equasion. </summary>
///
/// <remarks>	majeek, 4/21/2014. </remarks>
///
/// <param name="firstHistogram"> 	The first histogram. </param>
/// <param name="secondHistogram">	The second histogram. </param>
///
/// <returns>	A double. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

double SharedWorkersFunctions::compareHistCosineDistance(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram){
	
	double numinator =0;
	double denominatorFirstHist = 0;
	double denominatorSecondHist = 0;
	for (int i=0;i<firstHistogram.size();i++){
		double firstElem = firstHistogram[i];
		double secondElem = secondHistogram[i];
		numinator += firstElem*secondElem;
		denominatorFirstHist += firstElem*firstElem;
		denominatorSecondHist += secondElem*secondElem;
	}
	return numinator/(cv::sqrt(denominatorFirstHist)*cv::sqrt(denominatorSecondHist));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Compare hist euclidean distance. Following wikipedia's equasion. </summary>
///
/// <remarks>	majeek, 4/21/2014. </remarks>
///
/// <param name="firstHistogram"> 	The first histogram. </param>
/// <param name="secondHistogram">	The second histogram. </param>
///
/// <returns>	A double. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

double SharedWorkersFunctions::compareHistEuclideanDistance(cv::vector<double> firstHistogram, cv::vector<double> secondHistogram){
	double distance =0;
	for (int i=0;i<firstHistogram.size();i++){
		double firstElem = firstHistogram[i];
		double secondElem = secondHistogram[i];
		distance +=cv::pow(firstElem-secondElem,2);
	}
	return cv::sqrt(distance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Stores best results. </summary>
///
/// <remarks>	Majeed Kassis, 8/15/2014. </remarks>
///
/// <param name="fullPath">										Full pathname of the full file. </param>
/// <param name="wordPart">										The word part. </param>
/// <param name="matches">										The matches. </param>
/// <param name="comparisonType">								Type of the comparison. </param>
/// <param name="fImagesToCalculateSuccessRateFileNameList">	[in,out] List of images to
/// 															calculate success rate file names. </param>
/// <param name="fCalculateSuccessRateImageIndex">				[in,out] Zero-based index of the
/// 															calculate success rate image. </param>
/// <param name="fImageFileNameList">							[in,out] List of image file
/// 															names. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SharedWorkersFunctions::storeBestResults(QString fullPath, QString wordPart,
	cv::vector<cv::vector<double>> matches, QString comparisonType, QStringList& fImagesToCalculateSuccessRateFileNameList,
	cv::vector<int>& fCalculateSuccessRateImageIndex, QStringList& fImageFileNameList){
	
	
	QString fileName =  fullPath + "/" +  "bestResults-" + comparisonType + "-" + wordPart + ".csv";
	QFile outFile(fileName);
	outFile.open(QFile::WriteOnly | QFile::Truncate | QIODevice::Text);
	QTextStream outStream(&outFile);
	outStream.setCodec("UTF-16");

	

	outStream << "Top1," << "Top2," << "Top3," << "Top4," << "Top5" << "\n";

	cv::vector<int> finalResults;
	for (int i = 0; i < 5; i++)
		finalResults.push_back(0);

	int k = 0;
	for (cv::vector<double> comparisonVector : matches){
		//QString valueToWrite = "for " + QString::number(k) + ":\t";
		cv::vector<bool> topMatch;
		for (int i = 0; i < 5; i++)
			topMatch.push_back(false);
		for (int i = 0; i < 5; i++){
			// find minimum
			// best one is the winner!!
			double min = DBL_MAX;
			int minIndex = -1;
			for (int m = 0; m < comparisonVector.size(); m++){
				if (comparisonVector[m] < min){
					minIndex = m;
					min = comparisonVector[m];
				}
			}

			comparisonVector[minIndex] = 1;
			QString im1 = fImagesToCalculateSuccessRateFileNameList[fCalculateSuccessRateImageIndex[k]];
			QString im2 = fImageFileNameList[minIndex];

			im1.remove(0, im1.lastIndexOf("-"));
			im2.remove(0, im2.lastIndexOf("-"));
			if (im1.compare(im2) == 0){
				for (int j = i; j < 5; j++)
					topMatch[j] = true;
			}
		}
		for (int i = 0; i < 5; i++)
		if (topMatch[i])
			finalResults[i]++;
		k++;
	}

	outStream << finalResults[0] << "," << finalResults[1] << "," <<
		finalResults[2] << "," << finalResults[3] << "," <<
		finalResults[4] << "\n";
	outStream.flush();
	outFile.close();
}