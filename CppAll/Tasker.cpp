#include "Tasker.h"
#include <thread>
Tasker::Tasker(QObject *obj)
	:  m_obj(obj)
{
	//�����obj ����parent ��Ϊ���Ҫ���źŲ� ��Ҫ��movetothread ���е�
	//����������Զ�ɾ��
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
	//����һ �̳���QObject �����ź�
	
	auto thread_id = std::this_thread::get_id();
	qDebug() << "task thread id:" << QThread::currentThreadId();
	//���ǵ��ƶ�������߳��������������̵߳����ź�
	moveToThread(QThread::currentThread());
	emit signal_finished(QString("emit singnal"));
	//������ ʹ��Ԫ����ֱ�ӵ��ö���
	//QMetaObject::invokeMethod(this->parent, "setText", Q_ARG(QString, "this is AA!"));
	//���ֻ�̳���QRunable �Ǿ���û��parent�� ���Ե��Լ������������
	//����Ƿ���ֵ ��ҪQ_RETURN_ARG
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
