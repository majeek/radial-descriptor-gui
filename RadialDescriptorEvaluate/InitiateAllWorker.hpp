#ifndef INITIATEALLWORKER_HPP_
#define INITIATEALLWORKER_HPP_

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <QThreadPool>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class InitiateAllWorker : public QObject, public QRunnable
{
	Q_OBJECT

public:
	InitiateAllWorker(QThreadPool* pool, QThreadPool* assistantPool, QMutex* waitForStepFinishLock, QWaitCondition* waitForStepFinishWaitCondition, bool loadPersistenceData);
	~InitiateAllWorker();
	void run();

private:
	bool fLoadPersistenceData;
	QThreadPool* fThreadPool;
	QThreadPool* fAssistantPool;
	QWaitCondition* fWaitForStepFinishWaitCondition;
	QMutex* fWaitForStepFinishLock;

signals:
	void error(QString error);
	void updateStatusTab5Signal(QString value);

	void loadFilesSignal();
	void calculateSignalsSignal();
	void calculateHistogramsSignal();
	void loadImagesToCalculateSuccessRateForAllSignal();
	void storeModelAndHistogramsSignal();
	void loadModelAndHistogramsSignal();




};
#endif //INITIATEALLWORKER_HPP_