#ifndef RADIALDESCRIPTORQT5_H
#define RADIALDESCRIPTORQT5_H


#include <QDebug>
#include <QThread>
#include <QMetaObject>
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QVector>
#include <QWaitCondition>
#include <QMutex>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "PointDescriptor.h"
#include "SignalDescriptor.hpp"
#include "PleaseWaitDialog.h"
#include "PleaseWaitWidget.h"
#include "HelpWidget.hpp"
#include "TableWidget.h"
#include "TotalProgress.h"
#include "ui_RadialDescriptorQt5.h"
#include "DebugWidget.hpp"

#include <QMutex>
#include <QThreadPool>
#include "CalculateSignalsWorker.hpp"
#include "CalculateSuccessRateWorker.hpp"
#include "CalculateSuccessRateForAllWorker.hpp"
#include "CreateHistogramsWorker.hpp"
#include "InitiateAllWorker.hpp"
#include "PersistenceWorker.hpp"
#include "LoadDataWorker.hpp"


class RadialDescriptorQt5 : public QMainWindow
{
	Q_OBJECT


public:
	RadialDescriptorQt5(QWidget *parent = 0);
	~RadialDescriptorQt5();

private:
	int THREAD_POOL_SIZE;
	QVector<QGroupBox*> fProgressBarGroupBoxVector;
	QVector<QProgressBar*> fProgressBarProgressBarVector;
	bool fIsCalculateSuccessRate;
	//all point parameters
	cv::vector<PointDescriptor*> fDescriptorPoints;
	cv::Mat fToSendMat;

	TableWidget fTableWidget;
	Ui::RadialDescriptorGUIClass fUi;


	PleaseWaitDialog fProgressBarsWaitDialog;
	PleaseWaitWidget fMessageWaitWidget;
	
	

	//3rd tab methods and variables
	QStringList fImageFileNameList;
	QString fImageFilePath;
	cv::vector<cv::vector<SignalDescriptor*>*>* fDescriptorPointsForAllImages;
	cv::vector<cv::Mat> fImages;
	cv::vector<cv::Mat> fModifiedImages;
	cv::vector<cv::vector<double>>* fImagesHistograms;
	//cv::vector<cv::Mat> fImagesDistanceHistograms;
	cv::vector<cv::vector<double>>* fImagesZigZagHistograms;
	cv::EM *fEMModel;
	
	cv::Mat fImageToDetectDistanceHistogram;
	QThreadPool *fThreadPool;
	QThreadPool *fAssistantPool;
	QThreadPool *fInitiateAllPool;

	QMutex fTotalProgressDialogLock;
	TotalProgress fTotalProgressDialog;

	cv::vector<int> fProgressBarUsage;
	
	QMutex fAcquireOrReleaseProgressBarSlot;
	QMutex ffDescriptorPointsForAllImagesAndfImagesLock;
	QMutex fCalculateSuccessRateResultStorageLock;
	
	QMutex *fWaitForStepFinishLock;
	QWaitCondition* fWaitForStepFinishWaitCondition;

	//compare histograms data
	QVector<double> fImageToDetectHistogram;
	cv::Mat fImageToDetectWithDescriptors;
	
	
	cv::vector<cv::Mat> fImagesToDetectVector;
	QString fImagesToDetectPath;
	QStringList fImagesToDetectFileNameList;
	
	//Tab4 calculate success rate
	cv::vector<cv::Mat> fImagesToCalculateSuccessRateVector;
	QString fImagesToCalculateSuccessRatePath;;
	QStringList fImagesToCalculateSuccessRateFileNameList;

	cv::vector<cv::vector<double>> fCalculateSuccessRateMatches;
	//cv::vector<cv::vector<double>> fCalculateSuccessRateDistanceMatches;
	cv::vector<cv::vector<double>>  fCalculateSuccessRateZigZagDistanceMatches;


	cv::vector<int> fCalculateSuccessRateImageIndex;
	int fNumberOfImagesToSuccessRate;


	QWaitCondition* fCalculateSuccessRateForAllWorkerWaitCondition;
	QMutex* fCalculateSuccessRateForAllWorkerWaitConditionMutex;

	
	DebugWidget fDebugWidget;
	QMutex fDebugWidgetMutex;

	void addProgressBarGroupBoxObjects();
	void addProgerssBarObjects();
signals:
	void saveBestMatchesSignal();

private slots:
	void saveBestMatchesSlot();
	//Workers shared slots
	void showProgressBarsWaitWindow();
	void hideProgressBarsWaitWindow();

	void updateProgressBar(int, int);
	void acquireProgressBarSlot(int);
	void releaseProgressBarSlot(int);

	void storeBestResult(cv::vector<double> comparisonResults, cv::vector<double> zigZagDistanceHistogramComparisonResult, int imageToDetectIndex);
	void chooseStoragePathSlot();
	void calculateSignalsSlot();
	void calculateHistogramsSlot();
	void loadImagesToCalculateSuccessRateForAllSlot();


	//CalcaulteSignalsWorkerSlots
	void updateCalculateSignalResults(cv::Mat image, cv::vector<SignalDescriptor*>* imageSignals, int imageIndex);
	void updateCalculateSignalResults(cv::vector<SignalDescriptor*>* imageSignals, int imageIndex);

	//CreateHistogramsWorkerSlots
	void storeHistogramsSlot(cv::vector<cv::vector<double>>*, cv::vector<cv::vector<double>>*, cv::EM*);

	//5th tab slots
	void chooseTrainPathSlot();
	void chooseTestPathSlot();
	void initiateProcessSlot();
	void updateStatusTab5Slot(QString);
	void summarizeResultsSlot();

	void initializeProgressBarWaitDialogSlot(QString title, int size);
	void connectCalculateSuccessRateWorkerSignalsAndRunIt(CalculateSuccessRateWorker* worker);
	void loadFilesSlot();


	void updateMessageWaitWindowSlot(QString message);
	void showMessageWaitWindowSlot();
	void hideMessageWaitWindowSlot();
	void updateSuccessRateVariablesSlot(cv::vector<cv::Mat>  imagesToCalculateSuccessRateVector, int numberOfImagesToSuccessRate, QStringList imagesToCalculateSuccessRateFileNameList);

	void storeModelAndHistogramsSlot();
	void loadModelAndHistogramsSlot();
	void initializeTotalProgressDialogSlot(QString title, int total);
	void increaseTotalProgressDialogSlot();
	void choosePersistencePathSlot();
	//debug window
	void sendDebugMessageSlot(QString message);
};

#endif // RadialDescriptorQt5_H