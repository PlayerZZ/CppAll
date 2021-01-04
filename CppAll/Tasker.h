#pragma once

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QDebug>
//������ ʹ��QObject ��Ϊ���źŲ�
//�����ǿ�����parent ����
class Tasker : public QObject,public QRunnable
{
	Q_OBJECT

public:
	Tasker(QObject *obj);
	~Tasker();
	void run();
signals:
	void signal_finished(QString);
private:
	QObject* m_obj;
};

class Dispatcher : public QObject
{
	Q_OBJECT

public:
	Dispatcher(QObject* parent = nullptr);
	~Dispatcher();
public slots:
	void slot_finished(QString qstr);
};