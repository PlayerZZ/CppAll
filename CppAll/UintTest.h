#pragma once

#include <QObject>
#include <QTest>
#include "ch_tools.h"
class UnitTest : public QObject
{
	Q_OBJECT

public:
	UnitTest(QObject *parent=nullptr);
	~UnitTest();
private slots:
#ifdef TEST_ALL
void test_Qt_thread();
void test_OpencvAbout();
void test_StringConvert();
void test_RemoveDir();
void test_OpencvVideoCapture();
void test_Qt_threadPool();
void test_Qt_Concurrent();
#endif // TEST_ALL ���Լ�������Ĳ��� ������ȥ��������
void test_TxCos();
};
