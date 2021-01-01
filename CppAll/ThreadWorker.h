#pragma once

#include <QObject>
#include <QDebug>
#include <QThread>
class ThreadWorker : public QObject
{
	Q_OBJECT

public:
	ThreadWorker(QObject *parent=nullptr);
	~ThreadWorker();
	Qt::HANDLE thread_id;
signals:
	void signal_start_work();
	void signal_finished_work();
public slots:
	void slots_start_work();
	void slot_finished_work();
};
