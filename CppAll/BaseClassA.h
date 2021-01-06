#pragma once
//作为基类而存在的类

//初始化的类 啥也不干看看有几个默认函数
class DefaultClass
{
public:
	int num = 10;
};

//将构造函数弄到了private 而且类的访问权限默认就是private的
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
		//默认构造函数
		DefaultClass a,b,c;
		//默认拷贝构造函数
		DefaultClass d = a;
		//默认拷贝赋值函数
		c = a;
		//默认列表构造 class无 struct有因为聚合类？
		//DefaultClass f = { 10 };
		MyStruct t = { 10 };
		DefaultClass *h = new DefaultClass;
		//默认析构函数
		delete h;
		
	};
};

