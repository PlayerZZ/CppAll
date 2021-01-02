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
	//QT ���߳���ȷ�÷�
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
	//���������¼�������
// 	QThread::msleep(1200);
// 	loop.processEvents();
	// ��֪��Ϊɶ���ܵ�������� ����Ӧ��Ҫ�����Ŷ԰�
	// ֪���� ��Ϊ��������������ʱ������ǵȴ�ʱ�䣬û������waitOneEvent�Ĳ��� Ҫôexec Ȼ����Ŵ������У�Ҫô�����procssEvent���ȴ�
	// loop.processEvents(QEventLoop::AllEvents,2000);
	
	//���о�������һ��д������ �и���ʱ������֤�������źŲۿ���ִ����
	connect(work_thread_worker, &ThreadWorker::signal_finished_work, [&] {QTimer::singleShot(10, [&] {loop.exit(); }); });
	loop.exec();
	QVERIFY(work_thread_worker->thread_id != main_thread_worker->thread_id);
}

void UnitTest::test_OpencvAbout()
{
	//һЩopencv ��صĺ���

}

