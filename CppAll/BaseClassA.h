#pragma once
//��Ϊ��������ڵ���

//��ʼ������ ɶҲ���ɿ����м���Ĭ�Ϻ���
class DefaultClass
{
public:
	int num = 10;
};

//�����캯��Ū����private ������ķ���Ȩ��Ĭ�Ͼ���private��
class WiredClass
{
private:
	char c;
	WiredClass();
	~WiredClass();
};
struct MyStruct
{
	int num;
};

class BaseClassA
{
public:
	BaseClassA();
	~BaseClassA();
	void dosth() {
		//Ĭ�Ϲ��캯��
		DefaultClass a,b,c;
		//Ĭ�Ͽ������캯��
		DefaultClass d = a;
		//Ĭ�Ͽ�����ֵ����
		c = a;
		//Ĭ���б��� class�� struct����Ϊ�ۺ��ࣿ
		//DefaultClass f = { 10 };
		MyStruct t = { 10 };
		DefaultClass *h = new DefaultClass;
		//Ĭ����������
		delete h;
		
	};
};

