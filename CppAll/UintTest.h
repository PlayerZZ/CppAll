#pragma once

#include <QObject>
#include <QTest>
class UnitTest : public QObject
{
	Q_OBJECT

public:
	UnitTest(QObject *parent=nullptr);
	~UnitTest();
private slots:
void test_Qt_thread();
};
