#include "InitiateAllWorker.hpp"

InitiateAllWorker::InitiateAllWorker(QThreadPool* pool, QThreadPool* assistantPool, QMutex* waitForStepFinishLock, QWaitCondition* waitForStepFinishWaitCondition, bool loadPersistenceData) :
	QObject(0),
	fThreadPool(pool),
	fAssistantPool(assistantPool),
	fWaitForStepFinishLock(waitForStepFinishLock),
	fWaitForStepFinishWaitCondition(waitForStepFinishWaitCondition),
	fLoadPersistenceData(loadPersistenceData){
}


InitiateAllWorker::~InitiateAllWorker()
{
}

void InitiateAllWorker::run(){
	if (!fLoadPersistenceData) {
		emit updateStatusTab5Signal("Loading Files...");
		emit loadFilesSignal();
		fWaitForStepFinishLock->lock();
		fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
		fWaitForStepFinishLock->unlock();

		emit updateStatusTab5Signal("Calculating Signals...");
		emit calculateSignalsSignal();

		fWaitForStepFinishLock->lock();
		fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
		fWaitForStepFinishLock->unlock();
		fThreadPool->waitForDone();



		emit updateStatusTab5Signal("Calculating Histograms...");
		emit calculateHistogramsSignal();
		fWaitForStepFinishLock->lock();
		fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
		fWaitForStepFinishLock->unlock();
		fThreadPool->waitForDone();

		//persistence thread. this thread will store the model and all histograms into files for future use
		emit updateStatusTab5Signal("Storing Model and Histograms...");
		emit storeModelAndHistogramsSignal();
		fWaitForStepFinishLock->lock();
		fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
		fWaitForStepFinishLock->unlock();
		fAssistantPool->waitForDone();
	}
	else {
		emit updateStatusTab5Signal("Loading Model and Histograms...");
		emit loadModelAndHistogramsSignal();
		fWaitForStepFinishLock->lock();
		fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
		fWaitForStepFinishLock->unlock();
		fAssistantPool->waitForDone();
	}

	emit updateStatusTab5Signal("Comparing...");
	emit loadImagesToCalculateSuccessRateForAllSignal();
	fWaitForStepFinishLock->lock();
	fWaitForStepFinishWaitCondition->wait(fWaitForStepFinishLock);
	fWaitForStepFinishLock->unlock();
	fAssistantPool->waitForDone();

	
	emit updateStatusTab5Signal("All done.");

}
