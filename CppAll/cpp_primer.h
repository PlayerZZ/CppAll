#pragma once
//一些c++ primer的代码
#include <string>
#include <iostream>
#include "other1.h"
#include <fstream>
using namespace std;
inline void chapter1() {
	
	//1.1 complie
	// compile cmd
	//cc xx.cc
	//support c++11
	//-std=c++0x
	//1.2 io namesapce
	{
		std::cout << "hello world";
		std::cout << "the sum of " << 1 << " and " << 2 << "is" \
			<< 1 + 2 << std::endl;
	}
	//1.3 comment
	/**
	 * block comment
	 */
	// line comment
	//1.4 loop and if
	{
		int i = 100;
		while (i--)
		{
			std::cout << "remain " << i << std::endl;
		}
		for (auto a = 0; a < 100; a++)
		{
			std::cout << "count " << a << std::endl;
			if (a % 2 == 0)
			{
				std::cout << a << "is even" << std::endl;
			}
			else {
				std::cout << a << "is odd" << std::endl;
			}
		}
	}
	//1.5 sample class
	{
		struct sale_item {
			std::string isbn;
		};
		//output redirect
		//addItems <infile >outfile
		//<infile input by the file
		//>outfile out to the file
		sale_item booka = { "1234" };
		sale_item bookb = { "abcd" };
		std::cout << "booka " << (booka.isbn == bookb.isbn ? "equals" : "not equals") << " bookb" << std::endl;
	}
}

struct Sale_data
{
	string bookNo;
	//unsigned units_sold = 0;//类内初始值
	//unsigned units_sold(0);//错误方式 可以用{}
	unsigned units_sold{ 0 };//类内初始值,这里只是范围变化并没有精度丢失 所以也不报错
	double revenue = 0.0;
	friend ostream &operator<<(ostream &output, const Sale_data& sale_data)
	{
		output << sale_data.bookNo <<" "<<sale_data.units_sold<<" "<<sale_data.revenue;
		return output;
	}
	friend istream &operator >> (istream& input, Sale_data& sale_data)
	{
		input >> sale_data.bookNo >> sale_data.units_sold >> sale_data.revenue;
		return input;
	}
};
inline void chapter2(){
	//2.1 base type
	{
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
	}
	//2.2 变量
	{
		//列表初始化
		auto v1 = { 0 };
		int v2 = { 3 };
		//float v3{ 1.1 };//会有警告因为精度缺失
		double v3{ 1.3 };
		//定义在函数内部的变量 不会被初始化为0
		//会报警告
// 		int o;
// 		std::cout << "o value:" << o << std::endl;
		//申明和定义分离
		extern int i;//说明我要用其他地方的i
		//这里的i不用extern也可以直接用是因为直接就在文件里面 如果是在dll 动态库里面就不行了
		cout << "extern i:" << i;
	}
	//2.3 复合类型 指const & * 这些
	{
		//引用
		int int1 = 123;
		int &int2 = int1;
		//指针
		int *int3 = &int2;//引用的地址就是它引用对象的地址
		assert(*int3 == int1);//解引用
		//void * 空指针可以指向任意对象
		int *p = nullptr;//这样不容易误解
		int *p1, int6;//前面是一个指针 后面是变量
		int **pp1;//指向指针的指针
	}
	//2.4 const 限定符
	{
		const int a = 10;
		//当多个文件中同时存在const 变量的时候，其实是各自不相同的
		//如果使用了extern 的话就可以检查是否重定义了
		//const 的引用
		int a1 = 20;
		const int &a2 = a1;
		const int &b = a;
		//指针和const
		//int *const c1 = &a;// 错误 这里加const 只是说这个对象不可修改为其他值
		//底层const 所以底层其实“更顶层”？//所以是const 修饰其左边的东西
		int * const const_diceng = &a1;
		//顶层const
		int const* c1 = &a;//这个指针的指向是可以修改的
		int const* const c2 = &a;//绑定死了 也不可修改
		const int *const c3 = &a;//等价于第一种写法 而且这种写法最规范 隔得最开
		//顶层const 可以写在里面
		//constexpr 定义的表达式其实也是常量，在编译器可以完成的计算操作
		//但是呢 vs2015是不支持的哈哈
		//const constexpr 因为编译器就定下来了 所以可以说是字面值类型 literal type 而不是说它有什么类型
		nullptr;
	}
	//2.5数据处理
	{
		//类型别名 type alias
		typedef double wages;
		typedef wages base,*p;
		{
			//等效于
			typedef double wages, base, *p;
		}
		{
			//等价于
			using wages = double;
		}
		//指针就有意思了 首先p是指针 const 只会修饰它 而不是修饰它的底层
		double d1 = 12.4;
		const p p1= &d1;
		const p *p2 = &p1;
		
		//auto 对象 可以通过这种方式查看字面量类型
		const auto &auto_value = 214;//因为后面其实创建了这个临时常量 来保存这个字面量
		//decltype 类型推断
		decltype(1) x;
		//decltype([=] {return 1; }) x;//看来并不能通过lambda 推断返回值啊
		auto func1 = [&](int x1) -> decltype(x1){return 1; };//通过类型推断指定返回类型
		//对诶 为啥指针的取值叫做 “解引用”而不是叫“解指针”呢?
		//decltype(*p) 里面的解引用操作之后变成了一个 引用！ 而不是值类型
		decltype((d1)) dd1 = d1;//双重括号比为引用
	}
	//2.6 自定义数据类型
	{
		
		//定义完成后有分号 因为友元的原因，定义在上面了
		Sale_data  sale_data1,sale_data2; 
		ifstream fin("sale_data.txt");
		ofstream fout("sale_data2.txt");
		fin >> sale_data1;
		fout << sale_data1;
	}
	//2.7 定义自己的头文件
#ifndef XXX_XXX_H
#define XXX_XXX_H
	//编写自己的头文件 这个就是简单的防重定义的保护
	//预处理器变量 无视作用域规则 其实只是说包含范围内就有效，相当于是这个文件的全局变量范围，不是说这个就真的全局了，还是要包含才有的
#endif
}


