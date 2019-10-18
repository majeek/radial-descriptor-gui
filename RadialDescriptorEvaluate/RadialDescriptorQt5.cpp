#include "RadialDescriptorQt5.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Majeed Kassis, 6/5/2013. </remarks>
///
/// <param name="parent">	[in,out] If non-nullptr, the parent. </param>
/// <param name="flags"> 	The flags. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

RadialDescriptorQt5::RadialDescriptorQt5(QWidget *parent) : QMainWindow(parent){
	fIsCalculateSuccessRate = false;
	
	//register meta types
	qRegisterMetaType<cv::Mat>("cv::Mat");
	qRegisterMetaType<QString>("QString");
	qRegisterMetaType<QVector<double>>("QVector<double>");
	qRegisterMetaType<cv::vector<double>>("cv::vector<double>");
	qRegisterMetaType<cv::vector<cv::Mat>>("cv::vector<cv::Mat>");
	qRegisterMetaType<cv::vector<cv::vector<double>*>>("cv::vector<cv::vector<double>*>");
	qRegisterMetaType<cv::vector<cv::vector<double>>>("cv::vector<cv::vector<double>>");

	fCalculateSuccessRateForAllWorkerWaitCondition = new QWaitCondition();
	fCalculateSuccessRateForAllWorkerWaitConditionMutex = new QMutex();

	//thread pool size must be the same as fProgressBarUsage size.
	fThreadPool = new QThreadPool();
	//updateNumberOfThreads();
	THREAD_POOL_SIZE = 30;
	fThreadPool->setMaxThreadCount(THREAD_POOL_SIZE);
	fAssistantPool = new QThreadPool();
	fAssistantPool->setMaxThreadCount(1);
	
	fInitiateAllPool = new QThreadPool();
	fInitiateAllPool->setMaxThreadCount(1);

	fWaitForStepFinishLock = new QMutex();
	fWaitForStepFinishWaitCondition = new QWaitCondition();

	for (int i=0;i<THREAD_POOL_SIZE;i++)
		fProgressBarUsage.push_back(-1);


	fImagesHistograms = new cv::vector<cv::vector<double>>();
	fImagesZigZagHistograms = new cv::vector<cv::vector<double>>();
	fDescriptorPointsForAllImages = new cv::vector<cv::vector<SignalDescriptor*>*>();

	fEMModel = nullptr;

	fMessageWaitWidget.setupUi();
	fMessageWaitWidget.hide();

	fTotalProgressDialog.setupUi();
	fTotalProgressDialog.hide();

	fUi.setupUi(this);
	fDebugWidget.setupUi();
	fProgressBarsWaitDialog.setupUi();
	addProgerssBarObjects(); 
	addProgressBarGroupBoxObjects();

	QObject::connect(this, SIGNAL(saveBestMatchesSignal()), this, SLOT(saveBestMatchesSlot()));
	QObject::connect(fUi.pushButtonChooseResultsStoragePathTab5, SIGNAL(clicked()), this, SLOT(chooseStoragePathSlot()));
	QObject::connect(fUi.pushButtonTrainPath, SIGNAL(clicked()), this, SLOT(chooseTrainPathSlot()));
	QObject::connect(fUi.pushButtonTestPath, SIGNAL(clicked()), this, SLOT(chooseTestPathSlot()));
	QObject::connect(fUi.pushButtonInitiateProcess, SIGNAL(clicked()), this, SLOT(initiateProcessSlot()));
	QObject::connect(fUi.pushButtonSummarizeResults, SIGNAL(clicked()), this, SLOT(summarizeResultsSlot()));
	QObject::connect(fUi.pushButtonPersistencePath, SIGNAL(clicked()), this, SLOT(choosePersistencePathSlot()));
	
}

void RadialDescriptorQt5::summarizeResultsSlot(){
	QString resultsPath = fUi.lineEditResultsStoragePathTab5->text();
	QStringList methods = QDir(resultsPath).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Dirs);
	for (QString method : methods){
		QString methodPath = resultsPath + "/" + method;
		//add image file names to image combo box and load the image files into matrices
		QStringList wordPartDirectories = QDir(methodPath).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Dirs);
		QStringListIterator iter(wordPartDirectories);

		QStringList wordPartsList;
		QVector<QVector<int>> wordPartSuccessOccurrence;
		QVector<QVector<int>> wordPartFailureOccurrence;
		QVector<QVector<int>> wordPartSuccessCoOccurrence;
		QVector<QVector<int>> wordPartFailureCoOccurrence;
		while (iter.hasNext()){ //next dir
			QString wordPart = iter.next();
			wordPartsList.push_back(wordPart);
			//qDebug() << "Detecting " << dirName;
			QStringList resultsListForWordPart = QDir(methodPath + "/" + wordPart).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
			QVector<int> detectionSuccessOccurrence;
			QVector<int> detectionFailureOccurrence;
			QVector<int> detectionSuccessCoOccurrence;
			QVector<int> detectionFailureCoOccurrence;
			for (int i = 0; i < 5; i++){
				detectionSuccessOccurrence.push_back(0);
				detectionFailureOccurrence.push_back(0);
				detectionSuccessCoOccurrence.push_back(0);
				detectionFailureCoOccurrence.push_back(0);
			}
			for (QString oneResult : resultsListForWordPart){
				//open file, read data into 3 vectors
				QFile csvFile(methodPath + "/" + wordPart + "/" + oneResult);
				csvFile.open(QIODevice::ReadOnly | QIODevice::Text);
				QTextStream in(&csvFile);
				in.setCodec("UTF-8");
				QVector<QString> wordPartsList;
				QVector<double> occurrenceHistogram;
				QVector<double> coOccurrenceHistogram;
				in.readLine(); //skip first line
				while (!in.atEnd()){
					QStringList splitLine = in.readLine().split(",");
					QStringList fileNameSegments = splitLine[0].split("-");
					wordPartsList.push_back(fileNameSegments[fileNameSegments.size() - 1].split(".")[0].trimmed()); //get word part
					occurrenceHistogram.push_back(splitLine[1].toDouble()); //get occurrence value
					coOccurrenceHistogram.push_back(splitLine[2].toDouble()); //get coccurrence value
				}
				//sort vectors for top 5 // no need for sort!! find 5 min values!!
				QVector<int> sortedOccurrenceHistogram;
				QVector<int> sortedCoOccurrenceHistogram;
				for (int i = 0; i < 5; i++){
					int minOccurrenceIndex = 0;
					int minCoOccurrenceIndex = 0;
					for (int j = 0; j < occurrenceHistogram.size(); j++){
						if (occurrenceHistogram[j] < occurrenceHistogram[minOccurrenceIndex])
							minOccurrenceIndex = j;
						if (coOccurrenceHistogram[j] < coOccurrenceHistogram[minCoOccurrenceIndex])
							minCoOccurrenceIndex = j;
					}
					occurrenceHistogram[minOccurrenceIndex] = DBL_MAX;
					coOccurrenceHistogram[minCoOccurrenceIndex] = DBL_MAX;
					sortedOccurrenceHistogram.push_back(minOccurrenceIndex);
					sortedCoOccurrenceHistogram.push_back(minCoOccurrenceIndex);
				}
				for (int i = 0; i < 5; i++){
					bool foundOccurrence = false;
					bool foundCoOccurrence = false;
					for (int j = 0; j <= i; j++){
						if (wordPartsList[sortedOccurrenceHistogram[j]] == wordPart)
							foundOccurrence = true;
						if (wordPartsList[sortedCoOccurrenceHistogram[j]] == wordPart)
							foundCoOccurrence = true;
							
					}
					if (foundOccurrence)
						detectionSuccessOccurrence[i]++;
					else detectionFailureOccurrence[i]++;
					if (foundCoOccurrence)
						detectionSuccessCoOccurrence[i]++;
					else detectionFailureCoOccurrence[i]++;
				}
				csvFile.close();
			}
			wordPartSuccessOccurrence.push_back(detectionSuccessOccurrence);
			wordPartFailureOccurrence.push_back(detectionFailureOccurrence);
			wordPartSuccessCoOccurrence.push_back(detectionSuccessCoOccurrence);
			wordPartFailureCoOccurrence.push_back(detectionFailureCoOccurrence);
		}
		QFile outFile(resultsPath + "/" + method + "Results.txt");
		if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&outFile);
		out.setCodec("UTF-8");

		for (int i = 0; i < 5; i++){
			out << "TOP-" << QString::number(i + 1) << "\n";
			for (QString wordParts : wordPartsList)
				out << wordParts << "\t";
			out << "\n";
			for (QVector<int> occurrence : wordPartSuccessOccurrence)
				out << occurrence[i] << "\t";
			out << "\n";
			for (QVector<int> occurrence : wordPartFailureOccurrence)
				out << occurrence[i] << "\t";
			out << "\n";
			double hitRate = 0;
			for (int j = 0; j < wordPartSuccessOccurrence.size(); j++)
				hitRate += (double)wordPartSuccessOccurrence[j][i] / (wordPartSuccessOccurrence[j][i] + wordPartFailureOccurrence[j][i]);
			hitRate /= wordPartSuccessOccurrence.size();
			out << "Occurrence hit rate = " << hitRate << "\n";
			for (QString wordParts : wordPartsList)
				out << wordParts << "\t";
			out << "\n";
			for (QVector<int> occurrence : wordPartSuccessCoOccurrence)
				out << occurrence[i] << "\t";
			out << "\n";
			for (QVector<int> occurrence : wordPartFailureCoOccurrence)
				out << occurrence[i] << "\t";
			out << "\n";
			hitRate = 0;
			for (int j = 0; j < wordPartSuccessCoOccurrence.size(); j++)
				hitRate += (double)wordPartSuccessCoOccurrence[j][i] / (wordPartSuccessCoOccurrence[j][i] + wordPartFailureCoOccurrence[j][i]);
			hitRate /= wordPartSuccessOccurrence.size();
			out << "Coccurrence hit rate = " << hitRate << "\n";
		}

		out.flush();
		outFile.close();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Majeed Kassis, 6/5/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

RadialDescriptorQt5::~RadialDescriptorQt5(){
	
	delete fCalculateSuccessRateForAllWorkerWaitCondition;
	delete fCalculateSuccessRateForAllWorkerWaitConditionMutex;

	delete fThreadPool;
	delete fAssistantPool;

	delete fInitiateAllPool;
	delete fWaitForStepFinishLock;
	delete fWaitForStepFinishWaitCondition;

	if (fEMModel != nullptr)
		delete fEMModel;
	
	/*for (cv::vector<double>* histogram : fImagesHistograms){
		delete histogram;
		histogram = nullptr;
	}*/
/*
	for (cv::vector<SignalDescriptor*>* v1 : *fDescriptorPointsForAllImages){
		for (SignalDescriptor* sd : *v1)
			delete sd;
		delete v1;
	}
	delete fDescriptorPointsForAllImages;*/
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the wait window. </summary>
///
/// <remarks>	majeek, 12/4/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::showProgressBarsWaitWindow(){
	fProgressBarsWaitDialog.show();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Hides the wait window. </summary>
///
/// <remarks>	majeek, 12/4/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::hideProgressBarsWaitWindow(){
	fProgressBarsWaitDialog.hide();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Acquires the progress bar slot for threadNumber. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
///
/// <param name="threadNumber">	The thread number. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::acquireProgressBarSlot(int threadNumber){
	fAcquireOrReleaseProgressBarSlot.lock();
	int i=0;
	while (fProgressBarUsage[i]!=-1)
		i++;
	fProgressBarUsage[i]=threadNumber;
	//update name of group box that contains the progress bar
	fProgressBarGroupBoxVector[i]->setTitle("Image " + QString::number(threadNumber));
	fAcquireOrReleaseProgressBarSlot.unlock();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Releases the progress bar slot of threadNumber. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
///
/// <param name="threadNumber">	The thread number. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::releaseProgressBarSlot(int threadNumber){
	fAcquireOrReleaseProgressBarSlot.lock();
	int i=0;
	while (fProgressBarUsage[i]!=threadNumber)
		i++;
	fProgressBarUsage[i]=-1;

	//reset progress bar value back to 0
	fProgressBarProgressBarVector[i]->reset();
	fProgressBarGroupBoxVector[i]->setTitle("Done");
	
	//increment global progress bar
	int progressInc = fProgressBarsWaitDialog.fUi.labelCompleteImages->text().toInt()+1;
	fProgressBarsWaitDialog.fUi.labelCompleteImages->setText(QString::number(progressInc));
	double newValue = progressInc/fProgressBarsWaitDialog.fUi.labelTotalImages->text().toDouble()*100.0;
	fProgressBarsWaitDialog.fUi.progressBarTotalProgress->setValue(newValue);
	//if all done, hide.
	if (fProgressBarsWaitDialog.fUi.progressBarTotalProgress->value()==100){
		fProgressBarsWaitDialog.hide();
		if (fIsCalculateSuccessRate)
			emit saveBestMatchesSignal();
	}
	fAcquireOrReleaseProgressBarSlot.unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the descriptors vector and images vector with the calculated signal results. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
///
/// <param name="image">	   	The image. </param>
/// <param name="imageSignals">	[in,out] If non-null, the image signals. </param>
/// <param name="imageIndex">  	Zero-based index of the image. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::updateCalculateSignalResults(cv::Mat image, cv::vector<SignalDescriptor*>* imageSignals, int imageIndex){
	ffDescriptorPointsForAllImagesAndfImagesLock.lock();
	fModifiedImages[imageIndex] = image;
	fDescriptorPointsForAllImages->at(imageIndex) = imageSignals;
	ffDescriptorPointsForAllImagesAndfImagesLock.unlock();
}

void RadialDescriptorQt5::updateCalculateSignalResults(cv::vector<SignalDescriptor*>* imageSignals, int imageIndex){
	ffDescriptorPointsForAllImagesAndfImagesLock.lock();
	fDescriptorPointsForAllImages->at(imageIndex) = imageSignals;
	ffDescriptorPointsForAllImagesAndfImagesLock.unlock();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Clears the images histograms vector. </summary>
///
/// <remarks>	majeek, 11/23/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the progress described by message for the progress window. </summary>
///
/// <remarks>	majeek, 12/4/2013. </remarks>
///
/// <param name="message">	The message. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::updateProgressBar(int progressBarIndex, int percentage){
	int index = -1;
	int i = 0;
	while (index == -1){
		if (fProgressBarUsage[i] == progressBarIndex)
			index = i;
		i++;
	}
	fProgressBarProgressBarVector[index]->setValue(percentage);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Stores best result for the success rate of a given result. </summary>
///
/// <remarks>	majeek, 2/11/2014. </remarks>
///
/// <param name="comparisonResults"> 	The comparison results. </param>
/// <param name="imageToDetectIndex">	Zero-based index of the image to detect. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::storeBestResult(cv::vector<double> comparisonResults, cv::vector<double> zigZagDistanceHistogramComparisonResult, int imageToDetectIndex){

	fCalculateSuccessRateResultStorageLock.lock();
	fCalculateSuccessRateMatches.push_back(comparisonResults);
	//fCalculateSuccessRateDistanceMatches.push_back(distanceHistogramComparisonResult);
	fCalculateSuccessRateZigZagDistanceMatches.push_back(zigZagDistanceHistogramComparisonResult);
	fCalculateSuccessRateImageIndex.push_back(imageToDetectIndex);
	fNumberOfImagesToSuccessRate--;
	fCalculateSuccessRateResultStorageLock.unlock();

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Initializes the progress bar wait dialog slot. 
/// 			For success rating for all </summary>
///
/// <remarks>	majeek, 2/10/2014. </remarks>
///
/// <param name="title">	The title. </param>
/// <param name="size"> 	The size. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::initializeProgressBarWaitDialogSlot(QString title, int size){
	fIsCalculateSuccessRate = true;
	//reset progress bar ui
	fProgressBarsWaitDialog.fUi.progressBarTotalProgress->reset();
	fProgressBarsWaitDialog.fUi.labelCompleteImages->setText("0");
	fProgressBarsWaitDialog.fUi.labelTotalImages->setText(QString::number(size));
	fProgressBarsWaitDialog.setWindowTitle(title);
	fProgressBarsWaitDialog.show();

	fNumberOfImagesToSuccessRate = size;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Connects CalculateSuccessRateWorker signals, then runs it. </summary>
///
/// <remarks>	majeek, 2/11/2014. </remarks>
///
/// <param name="worker">	[in,out] If non-null, the worker. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::connectCalculateSuccessRateWorkerSignalsAndRunIt(CalculateSuccessRateWorker* worker){
	
	QObject::connect(worker, SIGNAL(returnCalculateSuccessRateResult(cv::vector<double>, cv::vector<double>, int)), this, SLOT(storeBestResult(cv::vector<double>, cv::vector<double>, int)));
	QObject::connect(worker,SIGNAL(acquireProgressBarSlot(int)),this,SLOT(acquireProgressBarSlot(int)));	
	QObject::connect(worker,SIGNAL(releaseProgressBarSlot(int)),this,SLOT(releaseProgressBarSlot(int)));
	QObject::connect(worker,SIGNAL(updateProgressBar(int,int)),this,SLOT(updateProgressBar(int,int)));
	worker->setAutoDelete(true);
	fThreadPool->start(worker);	
}


void RadialDescriptorQt5::choosePersistencePathSlot() {
	QString storagePath = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));
	if (!storagePath.isEmpty()) {
		fUi.lineEditPersistencePath->setText(storagePath);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose results storage path. </summary>
///
/// <remarks>	majeek, 3/11/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::chooseStoragePathSlot(){
	QString storagePath = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));
	if (!storagePath.isEmpty()){
		fUi.lineEditResultsStoragePathTab5->setText(storagePath);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	SLOT: Stores the histograms. Emitted from CreateHistogramsWorker. </summary>
///
/// <remarks>	majeek, 3/15/2014. </remarks>
///
/// <param name="histograms">			   	[in,out] If non-null, the histograms. </param>
/// <param name="distanceHistograms">	   	The distance histograms. </param>
/// <param name="zigzagDistanceHistograms">	The zigzag distance histograms. </param>
/// <param name="model">				   	[in,out] If non-null, the model. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::storeHistogramsSlot(cv::vector<cv::vector<double>>* histograms, cv::vector<cv::vector<double>>* zigzagDistanceHistograms, cv::EM* model){

	fImagesHistograms = histograms;
	//fImagesDistanceHistograms = distanceHistograms;
	fImagesZigZagHistograms = zigzagDistanceHistograms;
	//lets clear all signals to free some memory, since they are not needed anymore
	for (cv::vector<SignalDescriptor*>* v1 : *fDescriptorPointsForAllImages) {
		for (SignalDescriptor* sd : *v1)
			delete sd;
		delete v1;
	}
	delete fDescriptorPointsForAllImages;

	if (fEMModel != nullptr)
		
		delete fEMModel;
	fEMModel = model;

	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}




////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose train path slot. </summary>
///
/// <remarks>	Majeed Kassis, 8/14/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::chooseTrainPathSlot(){
	QString path = QFileDialog::getExistingDirectory(this, tr("Choose training path"));
	if (!path.isEmpty())
		fUi.lineEditTrainPath->setText(path);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Choose test path slot. </summary>
///
/// <remarks>	Majeed Kassis, 8/14/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::chooseTestPathSlot(){
	QString path = QFileDialog::getExistingDirectory(this, tr("Choose testing path"));

	if (!path.isEmpty())
		fUi.lineEditTestPath->setText(path);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Loads train set, generates signals, calculates histograms,
/// 			and compares with test set. </summary>
///
/// <remarks>	Majeed Kassis, 8/14/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
//NEEDED
void RadialDescriptorQt5::initiateProcessSlot(){
	bool loadPersistenceData = fUi.checkBoxLoadFromPersistence->isChecked();
	//get all file names under path
	InitiateAllWorker* worker = new InitiateAllWorker(fThreadPool, fAssistantPool, fWaitForStepFinishLock, fWaitForStepFinishWaitCondition, loadPersistenceData);
	
	QObject::connect(worker, SIGNAL(loadFilesSignal()), this, SLOT(loadFilesSlot()));
	QObject::connect(worker, SIGNAL(updateStatusTab5Signal(QString)), this, SLOT(updateStatusTab5Slot
		(QString)));
	QObject::connect(worker, SIGNAL(calculateSignalsSignal()), this, SLOT(calculateSignalsSlot()));
	QObject::connect(worker, SIGNAL(calculateHistogramsSignal()), this, SLOT(calculateHistogramsSlot()));
	QObject::connect(worker, SIGNAL(loadImagesToCalculateSuccessRateForAllSignal()), this, SLOT(loadImagesToCalculateSuccessRateForAllSlot()));
	QObject::connect(worker, SIGNAL(storeModelAndHistogramsSignal()), this, SLOT(storeModelAndHistogramsSlot()));
	QObject::connect(worker, SIGNAL(loadModelAndHistogramsSignal()), this, SLOT(loadModelAndHistogramsSlot()));

	worker->setAutoDelete(true);

	fInitiateAllPool->start(worker);
}


void RadialDescriptorQt5::loadModelAndHistogramsSlot() {
	QString persistencePath = fUi.lineEditPersistencePath->text();
	if (fEMModel != nullptr)
		delete fEMModel;
	fEMModel = new cv::EM();
	LoadDataWorker* worker = 
		new LoadDataWorker(persistencePath, &fImageFileNameList, fEMModel, fImagesHistograms, fImagesZigZagHistograms);
	QObject::connect(worker, SIGNAL(initializeTotalProgressDialogSignal(QString, int)), this, SLOT(initializeTotalProgressDialogSlot(QString, int)));
	QObject::connect(worker, SIGNAL(increaseTotalProgressDialogSignal()), this, SLOT(increaseTotalProgressDialogSlot()));
	worker->setAutoDelete(true);
	fAssistantPool->start(worker);
	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}


void RadialDescriptorQt5::storeModelAndHistogramsSlot() {
	QString persistencePath = fUi.lineEditPersistencePath->text();
	PersistenceWorker* worker = 
		new PersistenceWorker(persistencePath, &fImageFileNameList, fEMModel, fImagesHistograms, fImagesZigZagHistograms);
	QObject::connect(worker, SIGNAL(initializeTotalProgressDialogSignal(QString, int)), this, SLOT(initializeTotalProgressDialogSlot(QString, int)));
	QObject::connect(worker, SIGNAL(increaseTotalProgressDialogSignal()), this, SLOT(increaseTotalProgressDialogSlot()));
	worker->setAutoDelete(true);

	fAssistantPool->start(worker);
	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}

void RadialDescriptorQt5::initializeTotalProgressDialogSlot(QString title, int total) {

	fTotalProgressDialog.fUi.progressBarTotalProgress->reset();
	fTotalProgressDialog.fUi.labelCompleteImages->setText("0");
	fTotalProgressDialog.fUi.labelTotalImages->setText(QString::number(total));
	fTotalProgressDialog.setWindowTitle(title);
	fTotalProgressDialog.show();
}

void RadialDescriptorQt5::increaseTotalProgressDialogSlot() {

	fTotalProgressDialogLock.lock();
	int current = fTotalProgressDialog.fUi.labelCompleteImages->text().toInt() + 1;
	double total = fTotalProgressDialog.fUi.labelTotalImages->text().toDouble();
	fTotalProgressDialog.fUi.progressBarTotalProgress->setValue(current / total * 100);
	fTotalProgressDialog.fUi.labelCompleteImages->setText(QString::number(current));
	if ((current / total * 100) == 100)
		fTotalProgressDialog.hide();
	fTotalProgressDialogLock.unlock();
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the status tab 5 progress by value. </summary>
///
/// <remarks>	Majeed Kassis, 8/14/2014. </remarks>
///
/// <param name="value">	The value. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::updateStatusTab5Slot(QString value){
	fUi.labelInitiateAllProgress->setText(value);
}


void RadialDescriptorQt5::sendDebugMessageSlot(QString message){
	fDebugWidgetMutex.lock();
	if (!fDebugWidget.isVisible())
		fDebugWidget.show();
	fDebugWidget.fUi.textEditDebug->append(message);
	fDebugWidgetMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Loads the images found in a directory. </summary>
///
/// <remarks>	Majeek, 11/21/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

//FIRST STEP
void RadialDescriptorQt5::loadFilesSlot(){
	//get path 
	if (fUi.lineEditTrainPath->text().isEmpty())
		fImageFilePath = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));//, QFileDialog::DontResolveSymlinks);
	else
		fImageFilePath = fUi.lineEditTrainPath->text();

	if (!fImageFilePath.isEmpty()){
		//clear data if found
		fImages.clear();
		fModifiedImages.clear();
		//get all file names under path
		fImageFileNameList = QDir(fImageFilePath).entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);// | QDir::AllDirs);//, QDir::DirsFirst);//(QDir::Filter::Files,QDir::SortFlag::NoSort)



		//add image file names to image combo box and load the image files into matrices
		QStringListIterator iter(fImageFileNameList);
		while (iter.hasNext()){
			QString imageFileName = iter.next();
			cv::Mat img = SharedWorkersFunctions::loadUnicodeImage(fImageFilePath + "/" + imageFileName);
			if (img.channels() != 1)
				cv::cvtColor(img, img, CV_RGB2GRAY);
			cv::Mat result;
			//increase size by 4 times.
			cv::resize(img, result, cv::Size(), 4, 4, CV_INTER_CUBIC);
			fImages.push_back(result);
			fModifiedImages.push_back(result);
		}
	}
	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculates the signals for all points with high variance in all 
/// 			images in folder. </summary>
///
/// <remarks>	majeek, 11/22/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

//SECOND STEP
void RadialDescriptorQt5::calculateSignalsSlot(){
	//reset progress bar ui
	fProgressBarsWaitDialog.fUi.progressBarTotalProgress->reset();
	fProgressBarsWaitDialog.fUi.labelCompleteImages->setText("0");
	fProgressBarsWaitDialog.fUi.labelTotalImages->setText(QString::number(fImages.size()));
	

	fProgressBarsWaitDialog.setWindowTitle("Calculating Signals");
	fProgressBarsWaitDialog.show();

//	clearAllPointsDescriptorVector();
//	clearImagesHistogramsVector();

	//parameters decide for the point scan (signal properties)
	int radius = fUi.lineEditSamplingRadiusTab3->text().toInt();
	int vectorsCount = fUi.lineEditNumberOfLevelsTab3->text().toInt();

	double interpolationValue = fUi.comboBoxLevel0WeightTab3->currentText().toDouble();

	double gaussBlur = fUi.lineEditImageBlurTab3->text().toDouble();
	int kernelSize = fUi.lineEditKernelSizeTab3->text().toInt();

	int levelRadiusPercentage = fUi.lineEditDistanceHistogramLevelStepTab3->text().toInt();
	int numberOfLevels = fUi.lineEditDistanceHistogramNumberOfLevelsTab3->text().toInt();

	int minDistance;
	if (fUi.checkBoxMinDistanceTab3->isChecked())
		minDistance = fUi.lineEditMinimumDistanceBetweenTwoPointsTab3->text().toInt();
	else minDistance = -1;

	int minVariance = fUi.lineEditMinimumVarianceTab3->text().toInt();

	int backgroundColor = 0;
	if (fUi.checkBoxBackgroundColorTab3->isChecked())
		backgroundColor = fUi.spinBoxBackgroundColorTab3->value();

	//number of points limit
	int maxSignals;
	if (fUi.checkBoxNumberOfPointsTab3->isChecked())
		maxSignals = fUi.lineEditNumberOfPointsTab3->text().toInt();
	else
		maxSignals = 0;

	for (int i = 0; i<fImages.size(); i++){
		fDescriptorPointsForAllImages->push_back(nullptr);
		//fImagesDistanceHistograms.push_back(cv::Mat());
		fImagesZigZagHistograms->push_back(cv::vector<double>());
	}

	for (int i = 0; i<fImages.size(); i++){
		//create worker, thread and run, connect signals
		CalculateSignalsWorker* worker = new CalculateSignalsWorker(kernelSize, radius, vectorsCount,
			interpolationValue, minDistance, i, fImages[i], gaussBlur, maxSignals, minVariance, levelRadiusPercentage, numberOfLevels, backgroundColor);

		//my signals
		QObject::connect(worker, SIGNAL(sendDebugMessage(QString)), this, SLOT(sendDebugMessageSlot(QString)));
		QObject::connect(worker, SIGNAL(acquireProgressBarSlot(int)), this, SLOT(acquireProgressBarSlot(int)));
		QObject::connect(worker, SIGNAL(releaseProgressBarSlot(int)), this, SLOT(releaseProgressBarSlot(int)));
		QObject::connect(worker, SIGNAL(updateProgressBar(int, int)), this, SLOT(updateProgressBar(int, int)));

		QObject::connect(worker,
			SIGNAL(returnCalculateSignalsResults(cv::vector<SignalDescriptor*>*, int)), this,
			SLOT(updateCalculateSignalResults(cv::vector<SignalDescriptor*>*, int)));


		worker->setAutoDelete(true);
		fThreadPool->start(worker);
	}

	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculates the histogram for each image in our list. </summary>
///
/// <remarks>	majeek, 11/23/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
//STEP THREE
void RadialDescriptorQt5::calculateHistogramsSlot(){
	//using results path to store the model for later use
	QString modelPath = fUi.lineEditResultsStoragePathTab5->text();

	//worker parameters
	int numberOfClusters = fUi.lineEditNumberOfClusters->text().toInt();


	int numberOfLevels = fUi.lineEditDistanceHistogramNumberOfLevelsTab3->text().toInt();
	int levelRadiusPercentage = fUi.lineEditDistanceHistogramLevelStepTab3->text().toInt();

	int radius = fUi.lineEditSamplingRadiusTab3->text().toInt();
	int vectorsCount = fUi.lineEditNumberOfLevelsTab3->text().toInt();
	double gaussBlur = fUi.lineEditImageBlurTab3->text().toDouble();
	int kernelSize = fUi.lineEditKernelSizeTab3->text().toInt();
	int backgroundColor = 0;
	if (fUi.checkBoxBackgroundColorTab3->isChecked())
		backgroundColor = fUi.spinBoxBackgroundColorTab3->value();


	//create worker and run it.
	CreateHistogramsWorker* worker = new CreateHistogramsWorker(modelPath, fDescriptorPointsForAllImages, fImages, numberOfLevels, levelRadiusPercentage, radius, vectorsCount, gaussBlur, kernelSize, numberOfClusters, backgroundColor);

	//my signals
	QObject::connect(worker, SIGNAL(returnHistogramsSignal(cv::vector<cv::vector<double>>*, cv::vector<cv::vector<double>>*, cv::EM*)), this, SLOT(storeHistogramsSlot(cv::vector<cv::vector<double>>*, cv::vector<cv::vector<double>>*, cv::EM*)));
	QObject::connect(worker, SIGNAL(updateComparisonProgress(QString)), this, SLOT(updateMessageWaitWindowSlot(QString)));
	QObject::connect(worker, SIGNAL(showMessageWaitWindow()), this, SLOT(showMessageWaitWindowSlot()));
	QObject::connect(worker, SIGNAL(hideMessageWaitWindow()), this, SLOT(hideMessageWaitWindowSlot()));
	worker->setAutoDelete(true);
	//send runnable to thread pool
	fThreadPool->start(worker);

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Loads images to calculate success rate for all. </summary>
///
/// <remarks>	majeek, 2/11/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
//STEP FOUR
void RadialDescriptorQt5::loadImagesToCalculateSuccessRateForAllSlot(){
	//get path 
	QString path;
	if (fUi.lineEditTestPath->text().isEmpty())
		path = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));
	else
		path = fUi.lineEditTestPath->text();


	if (!path.isEmpty()){
		//parameters decide for the point scan (signal properties)
		int radius = fUi.lineEditSamplingRadiusTab3->text().toInt();
		int vectorsCount = fUi.lineEditNumberOfLevelsTab3->text().toInt();

		double interpolationValue = fUi.comboBoxLevel0WeightTab3->currentText().toDouble();

		//min distance.
		int minDistance;
		if (fUi.checkBoxMinDistanceTab3->isChecked())
			minDistance = fUi.lineEditMinimumDistanceBetweenTwoPointsTab3->text().toInt();
		else minDistance = -1;

		//number of points limit
		int maxSignals;
		if (fUi.checkBoxNumberOfPointsTab3->isChecked())
			maxSignals = fUi.lineEditNumberOfPointsTab3->text().toInt();
		else
			maxSignals = 0;

		int method;
		if (fUi.comboBoxHistogramComparisonMethodTab4->currentIndex() == 0)
			method = CV_COMP_CORREL;
		else if (fUi.comboBoxHistogramComparisonMethodTab4->currentIndex() == 1)
			method = CV_COMP_CHISQR;
		else
			method = CV_COMP_BHATTACHARYYA;


		int numberOfLevels = fUi.lineEditDistanceHistogramNumberOfLevelsTab3->text().toInt();
		int levelRadiusPercentage = fUi.lineEditDistanceHistogramLevelStepTab3->text().toInt();

		double gaussBlur = fUi.lineEditImageBlurTab3->text().toDouble();
		int kernelSize = fUi.lineEditKernelSizeTab3->text().toInt();
		int minVariance = fUi.lineEditMinimumVarianceTab3->text().toInt();

		int backgroundColor = 0;
		if (fUi.checkBoxBackgroundColorTab3->isChecked())
			backgroundColor = fUi.spinBoxBackgroundColorTab3->value();

		//get all file names under path
		CalculateSuccessRateForAllWorker* worker = new CalculateSuccessRateForAllWorker(path, fThreadPool, method, radius, vectorsCount, interpolationValue, minDistance, fImagesHistograms,
			fImagesZigZagHistograms, numberOfLevels, levelRadiusPercentage, maxSignals, fEMModel, gaussBlur, kernelSize, minVariance, fCalculateSuccessRateForAllWorkerWaitCondition, fCalculateSuccessRateForAllWorkerWaitConditionMutex, backgroundColor);

		QObject::connect(worker, SIGNAL(initializeProgressBarWaitDialogSignal(QString, int)), this, SLOT(initializeProgressBarWaitDialogSlot(QString, int)));
		QObject::connect(worker, SIGNAL(connectCalculateSuccessRateWorkerSignalsAndRunItSignal(CalculateSuccessRateWorker*)), this, SLOT(connectCalculateSuccessRateWorkerSignalsAndRunIt(CalculateSuccessRateWorker*)));
		QObject::connect(worker, SIGNAL(updateSuccessRateVariablesSignal(cv::vector<cv::Mat>, int, QStringList)), this, SLOT(updateSuccessRateVariablesSlot(cv::vector<cv::Mat>, int, QStringList)));


		worker->setAutoDelete(true);

		fAssistantPool->start(worker);
	}

	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wakeAll();
	fWaitForStepFinishLock->unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the message wait window described by message. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
///
/// <param name="message">	The message. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::updateMessageWaitWindowSlot(QString message){
	fMessageWaitWidget.fUi.labelStatus->setText(message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Shows the message wait window. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::showMessageWaitWindowSlot(){
	fMessageWaitWidget.show();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Hides the message wait window. </summary>
///
/// <remarks>	majeek, 12/5/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::hideMessageWaitWindowSlot(){
	fMessageWaitWidget.hide();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the success rate variables needed in order to initiate a new 
/// 			success rate calculation round. </summary>
///
/// <remarks>	majeek, 2/12/2014. </remarks>
///
/// <param name="imagesToCalculateSuccessRateVector">	   	The images to calculate success rate
/// 														vector. </param>
/// <param name="numberOfImagesToSuccessRate">			   	Number of images to success rates. </param>
/// <param name="imagesToCalculateSuccessRateFileNameList">	List of images to calculate success
/// 														rate file names. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::updateSuccessRateVariablesSlot(cv::vector<cv::Mat>  imagesToCalculateSuccessRateVector, int numberOfImagesToSuccessRate, QStringList imagesToCalculateSuccessRateFileNameList){
	fImagesToCalculateSuccessRateVector.clear();
	fCalculateSuccessRateMatches.clear();
	//fCalculateSuccessRateDistanceMatches.clear();
	fCalculateSuccessRateZigZagDistanceMatches.clear();
	fCalculateSuccessRateImageIndex.clear();
	fImagesToCalculateSuccessRateFileNameList.clear();

	fImagesToCalculateSuccessRateVector = imagesToCalculateSuccessRateVector;
	fNumberOfImagesToSuccessRate = numberOfImagesToSuccessRate;
	fImagesToCalculateSuccessRateFileNameList = imagesToCalculateSuccessRateFileNameList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	View best matches. We store them into a file for now </summary>
///
/// <remarks>	majeek, 2/6/2014. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RadialDescriptorQt5::saveBestMatchesSlot(){

	
	fThreadPool->waitForDone();
	while (fNumberOfImagesToSuccessRate != 0);
	

	if (fUi.comboBoxHistogramComparisonMethodTab4->currentIndex() == 3){ //all 3 comparison methods

		//storing results into files
		QString wordPart = fImagesToCalculateSuccessRateFileNameList[0];
		wordPart.remove(0, wordPart.lastIndexOf("-"));
		if (wordPart.contains(".png"))
			wordPart.remove(".png");
		else if (wordPart.contains(".tif"))
			wordPart.remove(".tif");


		QVector<QString> metricFullPath;

		QString wordType = wordPart.remove(0, 1);

		QString chiSquared = fUi.lineEditResultsStoragePathTab5->text() + "/resultsChiSquared";
		SharedWorkersFunctions::createUnicodePath(chiSquared);
		QString chiSquaredToWordPart = chiSquared + "/" + wordType;
		SharedWorkersFunctions::createUnicodePath(chiSquaredToWordPart);
		metricFullPath.push_back(chiSquaredToWordPart);


		QString cosine = fUi.lineEditResultsStoragePathTab5->text() + "/resultsCosine";
		SharedWorkersFunctions::createUnicodePath(cosine);
		QString cosineWordPart = cosine + "/" + wordType;
		SharedWorkersFunctions::createUnicodePath(cosineWordPart);
		metricFullPath.push_back(cosineWordPart);


		QString euclidean = fUi.lineEditResultsStoragePathTab5->text() + "/resultsEuclidean";
		SharedWorkersFunctions::createUnicodePath(euclidean);
		QString euclideanWordPart = euclidean + "/" + wordType;
		SharedWorkersFunctions::createUnicodePath(euclideanWordPart);
		metricFullPath.push_back(euclideanWordPart);



		for (int i_i = 0; i_i < fCalculateSuccessRateMatches.size(); i_i++){
			QVector<QFile*> outFile;
			QVector<QTextStream*> outFileStream;
			//opening files
			for (int i = 0; i < 3; i++){
				//since results are not returned in their oder
				//we also store the order of the indexes returned in fCalculateSuccessRateImageIndex
				QString fileName = metricFullPath[i] + "/" + fImagesToCalculateSuccessRateFileNameList[fCalculateSuccessRateImageIndex[i_i]] + ".csv";
				QFile* file = new QFile(fileName);
				file->open(QFile::WriteOnly | QFile::Truncate);
				QTextStream* out = new QTextStream(file);
				out->setCodec("UTF-8");
				outFile.push_back(file);
				outFileStream.push_back(out);
				*out << "image," << "histogram," << "zigZagDistanceHistogram" << "\n";
			}

			for (int i = 0; i < fImageFileNameList.size(); i++){
				*outFileStream[0] << fImageFileNameList[i] << "," << fCalculateSuccessRateMatches[i_i][3 * i]
					<< ","/* << fCalculateSuccessRateDistanceMatches[i_i][3 * i] << "," */<< fCalculateSuccessRateZigZagDistanceMatches[i_i][3 * i] << "\n";
				*outFileStream[1] << fImageFileNameList[i] << "," << fCalculateSuccessRateMatches[i_i][3 * i + 1]
					<< ","/* << fCalculateSuccessRateDistanceMatches[i_i][3 * i + 1] << "," */<< fCalculateSuccessRateZigZagDistanceMatches[i_i][3 * i + 1] << "\n";
				*outFileStream[2] << fImageFileNameList[i] << "," << fCalculateSuccessRateMatches[i_i][3 * i + 2]
					<< ","/* << fCalculateSuccessRateDistanceMatches[i_i][3 * i + 2] << "," */<< fCalculateSuccessRateZigZagDistanceMatches[i_i][3 * i + 2] << "\n";
			}
			for (int i = 0; i < 3; i++){
				outFileStream[i]->flush();
				outFile[i]->close();
				delete outFileStream[i];
				outFileStream[i] = nullptr;
				delete outFile[i];
				outFile[i] = nullptr;
			}
		}
	}
	else{ //1 method only

		//storing results into files
		QString wordPart = fImagesToCalculateSuccessRateFileNameList[0];
		wordPart.remove(0, wordPart.lastIndexOf("-"));
		if (wordPart.contains(".png"))
			wordPart.remove(".png");
		else if (wordPart.contains(".tif"))
			wordPart.remove(".tif");


		QString dirName = fUi.lineEditResultsStoragePathTab5->text() + "/" + wordPart.remove(0, 1);
		SharedWorkersFunctions::createUnicodePath(dirName);



		for (int i_i = 0; i_i < fCalculateSuccessRateMatches.size(); i_i++){
			QString fileName = dirName + "/" + fImagesToCalculateSuccessRateFileNameList[i_i] + ".csv";
			QFile outFile(fileName);
			outFile.open(QFile::WriteOnly | QFile::Truncate | QIODevice::Text);
			QTextStream outStream(&outFile);
			outStream.setCodec("UTF-8");
			outStream << "image," << "histogram," << "zigZagDistanceHistogram" << "\n";
			for (int i = 0; i < fCalculateSuccessRateMatches[i_i].size(); i++)
				outStream << fImageFileNameList[i] << "," << fCalculateSuccessRateMatches[i_i][i]
				<< "," /*<< fCalculateSuccessRateDistanceMatches[i_i][i] << "," */<< fCalculateSuccessRateZigZagDistanceMatches[i_i][i] << "\n";

			outFile.close();
		}
		//occurrence histogram
		SharedWorkersFunctions::storeBestResults(dirName, wordPart, fCalculateSuccessRateMatches, "occurrence", fImagesToCalculateSuccessRateFileNameList, fCalculateSuccessRateImageIndex, fImageFileNameList);
		//co-occurrence histogram (zigzag)
		SharedWorkersFunctions::storeBestResults(dirName, wordPart, fCalculateSuccessRateZigZagDistanceMatches, "co-occurrence-zig-zag", fImagesToCalculateSuccessRateFileNameList, fCalculateSuccessRateImageIndex, fImageFileNameList);
	}


	fCalculateSuccessRateForAllWorkerWaitConditionMutex->lock();
	fCalculateSuccessRateForAllWorkerWaitCondition->wakeAll();
	fCalculateSuccessRateForAllWorkerWaitConditionMutex->unlock();

}

void RadialDescriptorQt5::addProgerssBarObjects(){
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_0);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_1);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_2);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_3);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_4);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_5);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_6);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_7);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_8);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_9);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_10);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_11);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_12);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_13);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_14);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_15);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_16);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_17);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_18);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_19);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_20);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_21);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_22);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_23);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_24);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_25);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_26);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_27);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_28);
	fProgressBarProgressBarVector.push_back(fProgressBarsWaitDialog.fUi.progressBar_29);

}
void RadialDescriptorQt5::addProgressBarGroupBoxObjects(){
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_0);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_1);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_2);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_3);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_4);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_5);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_6);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_7);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_8);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_9);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_10);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_11);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_12);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_13);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_14);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_15);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_16);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_17);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_18);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_19);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_20);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_21);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_22);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_23);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_24);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_25);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_26);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_27);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_28);
	fProgressBarGroupBoxVector.push_back(fProgressBarsWaitDialog.fUi.groupBox_29);

}