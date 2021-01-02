#include "UintTest.h"
#include "ThreadWorker.h"
#include <QEventLoop>
#include <QTimer>
UnitTest::UnitTest(QObject *parent)
	: QObject(parent)
{
}

UnitTest::~UnitTest()
{
	getchar();
}

void UnitTest::test_Qt_thread()
{
	//QT 多线程正确用法
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
	//把阻塞的事件处理完
// 	QThread::msleep(1200);
// 	loop.processEvents();
	// 不知道为啥不能单独用这个 想来应该要阻塞才对啊
	// 知道了 因为这个是它的最大处理时间而不是等待时间，没有类似waitOneEvent的操作 要么exec 然后等着处理所有，要么就这个procssEvent不等待
	// loop.processEvents(QEventLoop::AllEvents,2000);
	
	//所有就有了另一种写法…… 有个延时函数保证了它的信号槽可以执行完
	connect(work_thread_worker, &ThreadWorker::signal_finished_work, [&] {QTimer::singleShot(10, [&] {loop.exit(); }); });
	loop.exec();
	QVERIFY(work_thread_worker->thread_id != main_thread_worker->thread_id);
}

void UnitTest::test_OpencvAbout()
{
	//一些opencv 相关的函数

}

