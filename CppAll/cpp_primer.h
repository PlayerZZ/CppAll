#pragma once
//一些c++ primer的代码
#include <string>
#include <iostream>
#include "other1.h"
using namespace std;
inline void chapter1() {
	
	//1.1 complie
	// compile cmd
	//cc xx.cc
	//support c++11
	//-std=c++0x
	//1.2 io namesapce
	std::cout << "hello world";
	std::cout << "the sum of " << 1 << " and " << 2 << "is" \
		<< 1 + 2 << std::endl;
	//1.3 comment
	/**
	 * block comment
	 */
	// line comment
	//1.4 loop and if
	int i = 100;
	while (i--)
	{
		std::cout << "remain "<<i<<std::endl;
	}
	for (auto a=0;a<100;a++)
	{
		std::cout << "count " << a << std::endl;
		if (a%2==0)
		{
			std::cout << a <<"is even" << std::endl;
		}
		else {
			std::cout << a << "is odd" << std::endl;
		}
	}
	//1.5 sample class
	struct sale_item {
		std::string isbn;
	};
	//output redirect
	//addItems <infile >outfile
	//<infile input by the file
	//>outfile out to the file
	sale_item booka = { "1234" };
	sale_item bookb = { "abcd" };
	std::cout <<"booka " << (booka.isbn == bookb.isbn ? "equals" : "not equals") << " bookb" <<std::endl;
}
inline void chapter2(){
	//2.1 base type
	bool flag_1;
	char c1; wchar_t c2; char16_t c3; char32_t c4;
	short i1; int i2; long i3; long long i4;
	float f1; double f2; long double f3;
	//bite byte word
	unsigned int;
	signed int;
	//超过范围的表示数是未定义的行为
	//无符号转为有符号 超过范围也是未定义的行为
	//冷知识 int的位数取决于操作系统 所谓最低16位 最高32位（2个字节，4个字节）
	//字面值常量 整形的字面值常量是 有符号数
	// \n \t 这种转义序列 也可以用ascii码表示 \123 \x3a 这样的形式
	auto l1 = L'a';
	auto l2 = u8"hhh";
	auto l3 = 46ULL;
	auto l4 = 1E-3F;//科学计算法?
	auto l5 = 15.5L;
	//2.2 变量
	//列表初始化
	auto v1 = { 0 };
	int v2 = { 3 };
	//float v3{ 1.1 };//会有警告因为精度缺失
	double v3{ 1.3 };
	//定义在函数内部的变量 不会被初始化为0
	int o;
	std::cout << "o value:" << o << std::endl;
	//申明和定义分离
	extern int i;//说明我要用其他地方的i
	//这里的i不用extern也可以直接用是因为直接就在文件里面 如果是在dll 动态库里面就不行了
	cout << "extern i:" << i;
	//2.3 复合类型 指const & * 这些
	//引用
	int int1 = 123;
	int &int2 = int1;
	//指针
	int *int3 = &int2;//引用的地址就是它引用对象的地址
	assert(*int3 == int1);//解引用

}