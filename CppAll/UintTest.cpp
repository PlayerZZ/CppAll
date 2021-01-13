#include "UintTest.h"
#include "ThreadWorker.h"
#include <QEventLoop>
#include <QTimer>
#include "Tasker.h"
#include <QThreadPool>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include <TXCOS.h>
#include "cpp_primer.h"
UnitTest::UnitTest(QObject *parent)
	: QObject(parent)
{
}

UnitTest::~UnitTest()
{
	getchar();
}
#ifdef TEST_ALL
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
	//not free can't delete
	t1.close();
	QFile t2("test1/test2/2.txt");
	t2.open(QFile::WriteOnly);
	t2.close();
	ch::removeDirForce("test1");
	QVERIFY(!dir.exists("test1"));
}

void UnitTest::test_OpencvVideoCapture()
{
	//һЩvideoCapture�ĺ��� �������ȴ����֪�����ĸ�����ͷ�ģ�������Ҫ���ײ��ffmpeg ֮��Ŀ��
	int i = 0;
	cv::VideoCapture cap(0);
	//�����Զ��佹 https://answers.opencv.org/question/96137/is-there-any-range-of-values-for-the-exposure-flag/
	std::vector<cv::Mat> images(6,cv::Mat());
	if (cap.isOpened())
	{
		//cv::Mat mat;
		for (size_t i = 0; i < images.size(); i++)
		{
			cap.read(images[i]);
		}
	}
	else {
		cv::Mat mat = cv::imread("wechat.jpg");
		images = std::vector<cv::Mat>(6, mat);
	}
	cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.75);
	//�ֶ��佹
	cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);
	//���ý���
	cap.set(cv::CAP_PROP_EXPOSURE, 8);
	//ͼƬ�ں� hdr���
	cv::Mat fusion = ch::fusionImage(images);
	QVERIFY(fusion.size == images[0].size);
}

void UnitTest::test_Qt_threadPool()
{
	//����qt���̳߳�
	Dispatcher dis;
	for (int i=0;i<10;i++)
	{
		Tasker *tasker = new Tasker(&dis);
		QObject::connect(tasker, &Tasker::signal_finished, &dis, &Dispatcher::slot_finished, Qt::QueuedConnection);
		QThreadPool::globalInstance()->start(tasker);
	}
	QEventLoop loop;
	QTimer::singleShot(2000, [&] {loop.exit(); });
	loop.exec();

}

void UnitTest::test_Qt_Concurrent()
{
	//����Qt�Ĳ�����
	auto main_thread_id = QThread::currentThreadId();
	qDebug() << "0 current thread id:" << QThread::currentThreadId();
	QtConcurrent::run([=]()
	{
		// ��Ҫִ�еĴ���
		qDebug() << "1 current thread id:" << QThread::currentThreadId();
		QVERIFY(main_thread_id != QThread::currentThreadId());
	});
	QFutureWatcher<void> *future_wathcher = new QFutureWatcher<void>;
	connect(future_wathcher, &QFutureWatcher<void>::finished, this, [&] {
		//ִ�����Ĳ���
		qDebug() << "2.2 current thread id:" << QThread::currentThreadId();
		QVERIFY(main_thread_id == QThread::currentThreadId());
	});
	QFuture<void> future = QtConcurrent::run([=]()
	{
		//ִ�еĲ���
		qDebug() << "2.1 current thread id:" << QThread::currentThreadId();
		QVERIFY(main_thread_id != QThread::currentThreadId());
	});
	future_wathcher->setFuture(future);
	QEventLoop loop;
	QTimer::singleShot(20, [&] {loop.exit(); });
	loop.exec();
}
#endif
void UnitTest::test_TxCos()
{
	TXCOS cos;
	QVERIFY(cos.sendFile("Resources/wechat.jpg"));
}
class D {
	constexpr static int a = 0;
	constexpr static int b = 10;
};
void testSize() {
	class A { virtual void t1() {}; };
	class B :public A {};
	auto t1 = sizeof(A);


	//A a;
	//auto t2 = sizeof(a);
	auto t3 = sizeof(B);
	B b;
	auto t4 = sizeof(b);
	int *p = new int(10);
	auto t5 = sizeof(p);
	class C {
		void f1() {};
		void f2(int i) {};
	};
	auto t6 = sizeof(C);
	auto t7 = sizeof(D);
	D d;
	auto t8 = sizeof(d);
}
void UnitTest::test_cpp_primer()
{
// 	chapter1();
// 	chapter2();
// 	chapter3();
//	chapter4();
// 	chapter5();
// 	chapter6();
// 	chapter7();
//	chapter8();
//	chapter9();
//	chapter10();
//	chapter11();
	chapter12();
	testSize();
	chapter12_9();
}

