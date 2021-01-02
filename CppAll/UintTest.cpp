#include "UintTest.h"
#include "ThreadWorker.h"
#include <QEventLoop>
#include <QTimer>
#include <ch_tools.h>
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
	//һЩopencv ��صĺ��� ��μ����?
	//��ȡͼƬ
	QImage image("Resources/wechat.jpg");
	cv::Mat mat = ch::QImage2cvMat(image);
	QImage image2 = ch::cvMat2QImage(mat);
	//��Ϊ���صĹ�ϵ ���ǶԱȵ�����ֵ
	QVERIFY(image == image2);
}

void UnitTest::test_StringConvert()
{
	std::string text = "����";
	QString qstr = _Q("����");
	std::string text_1 = _STR(qstr);
	QVERIFY(text == text_1);

}

void UnitTest::test_RemoveDir()
{
	//�ȴ���Ŀ¼
	QDir dir;
	dir.mkpath("test1/test2");
	//�����ļ�
	QFile t1("test1/1.txt");
	t1.open(QFile::WriteOnly);
	QFile t2("test1/test2/2.txt");
	t2.open(QFile::WriteOnly);
	ch::removeDirForce("test1");
	QVERIFY(!dir.exists("test1"));
}

