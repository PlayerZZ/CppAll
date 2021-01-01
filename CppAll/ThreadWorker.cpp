#include "ThreadWorker.h"
ThreadWorker::ThreadWorker(QObject *parent)
	: QObject(parent)
{
	thread_id = QThread::currentThreadId();
}

ThreadWorker::~ThreadWorker()
{
}

void ThreadWorker::slots_start_work()
{
	thread_id = QThread::currentThreadId();
	qDebug() << "worker in thread:" << thread_id << "start work";
	QThread::sleep(1);
	emit signal_finished_work();
}

void ThreadWorker::slot_finished_work()
{
	qDebug() << "worker in thread:" << QThread::currentThreadId() << " finished work";
}
