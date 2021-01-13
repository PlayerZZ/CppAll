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
	//一些opencv 相关的函数 如何检测呢?
	//读取图片
	QImage image("Resources/wechat.jpg");
	cv::Mat mat = ch::QImage2cvMat(image);
	QImage image2 = ch::cvMat2QImage(mat);
	//因为重载的关系 就是对比的像素值
	QVERIFY(image == image2);
}

void UnitTest::test_StringConvert()
{
	std::string text = "哈哈";
	QString qstr = _Q("哈哈");
	std::string text_1 = _STR(qstr);
	QVERIFY(text == text_1);

}

void UnitTest::test_RemoveDir()
{
	//先创建目录
	QDir dir;
	dir.mkpath("test1/test2");
	//创建文件
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
	//一些videoCapture的函数 但是这个却不能知道是哪个摄像头的，可能需要更底层的ffmpeg 之类的库吧
	int i = 0;
	cv::VideoCapture cap(0);
	//设置自动变焦 https://answers.opencv.org/question/96137/is-there-any-range-of-values-for-the-exposure-flag/
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
	//手动变焦
	cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);
	//设置焦距
	cap.set(cv::CAP_PROP_EXPOSURE, 8);
	//图片融合 hdr相关
	cv::Mat fusion = ch::fusionImage(images);
	QVERIFY(fusion.size == images[0].size);
}

void UnitTest::test_Qt_threadPool()
{
	//测试qt的线程池
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
	//测试Qt的并发性
	auto main_thread_id = QThread::currentThreadId();
	qDebug() << "0 current thread id:" << QThread::currentThreadId();
	QtConcurrent::run([=]()
	{
		// 需要执行的代码
		qDebug() << "1 current thread id:" << QThread::currentThreadId();
		QVERIFY(main_thread_id != QThread::currentThreadId());
	});
	QFutureWatcher<void> *future_wathcher = new QFutureWatcher<void>;
	connect(future_wathcher, &QFutureWatcher<void>::finished, this, [&] {
		//执行完后的操作
		qDebug() << "2.2 current thread id:" << QThread::currentThreadId();
		QVERIFY(main_thread_id == QThread::currentThreadId());
	});
	QFuture<void> future = QtConcurrent::run([=]()
	{
		//执行的操作
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

