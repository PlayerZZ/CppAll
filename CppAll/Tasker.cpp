#include "Tasker.h"
#include <thread>
Tasker::Tasker(QObject *obj)
	:  m_obj(obj)
{
	//这里的obj 不是parent 因为如果要用信号槽 就要用movetothread 才行的
	//任务结束后自动删除
	setAutoDelete(true);
}

Tasker::~Tasker()
{
}

void Tasker::run()
{
	QThread::msleep(100);
	//do some task
	//tell obj finished
	//方法一 继承了QObject 发送信号
	
	auto thread_id = std::this_thread::get_id();
	qDebug() << "task thread id:" << QThread::currentThreadId();
	//但是得移动到这个线程里面才能在这个线程调用信号
	moveToThread(QThread::currentThread());
	emit signal_finished(QString("emit singnal"));
	//方法二 使用元对象直接调用对象
	//QMetaObject::invokeMethod(this->parent, "setText", Q_ARG(QString, "this is AA!"));
	//如果只继承了QRunable 那就是没有parent的 所以得自己保存这个对象
	//如果是返回值 需要Q_RETURN_ARG
	QMetaObject::invokeMethod(m_obj, "slot_finished", Qt::QueuedConnection, Q_ARG(QString, "use by qmetaobject"));
}

Dispatcher::Dispatcher(QObject* parent /*= nullptr*/)
	: QObject(parent)
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::slot_finished(QString qstr)
{
	qDebug() << "finshed,arg:"<<qstr<<"Thread id:" << QThread::currentThreadId();
}
