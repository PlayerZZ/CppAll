#include "UintTest.h"
#include "ThreadWorker.h"
#include <QEventLoop>
UnitTest::UnitTest(QObject *parent)
	: QObject(parent)
{
}

UnitTest::~UnitTest()
{
}

void UnitTest::test_Qt_thread()
{
	QThread *work_thread = new QThread;
	QEventLoop loop;
	ThreadWorker* main_thread_worker = new ThreadWorker(nullptr);
	ThreadWorker* work_thread_worker = new ThreadWorker(nullptr);
	work_thread_worker->moveToThread(work_thread);
	QObject::connect(main_thread_worker, &ThreadWorker::signal_start_work, work_thread_worker, &ThreadWorker::slots_start_work, Qt::QueuedConnection);
	QObject::connect(work_thread_worker, &ThreadWorker::signal_finished_work, main_thread_worker, &ThreadWorker::slot_finished_work, Qt::QueuedConnection);
	QObject::connect(work_thread, &QThread::finished, work_thread_worker, &ThreadWorker::deleteLater);
	work_thread->start();
	main_thread_worker->signal_start_work();
	QThread::sleep(2);
	loop.processEvents();
	//把阻塞的事件处理完
	QVERIFY(work_thread_worker->thread_id != main_thread_worker->thread_id);
}


