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

inline void chapter3()
{
	//3.1 使用命名空间
	{
		using namespace std;
		cout << "";
		//头文件中不应该用using namespace ，因为可能造成名字冲突
	}
	//3.2 使用string
	{
		string s1 = "sgsg";
		string s2(10, 'a');
		string s3 = { 10,'b' };
		string s4{ 10,'c' };

		//直接初始化 是指不用 = 号的初始化
		string s5{ "sgg" };
		//拷贝初始化是指用 = 号的初始化
		string s6 = "heloo";
		//多个值一般用一个临时对象来拷贝初始化比较直观 比如s3
		string s7 = string(10, 'd');
		//string的操作函数
		cout << s1;
		//cin >> s2;
		//getline(cin,s3);
		s4.empty();
		auto size_t1 = s5.size();//是一个unsigned 类型的
		s6[0];
		s1 + s2 == s3 + s4;
		"s6" + s6;//因为操作符可以推断前面的为string,但是要两侧至少有一个string 才能转换
		//字符串字面值 并不是string 类型
		//字符的操作
		char c = '0';
		isalnum(c);//is alpha numuber?
		isalpha(c);
		isdigit(c);
		iscntrl(c);
		isgraph(c);//非空格符
		isspace(c);//空白字符
		islower(c);
		isupper(c);
		isprint(c);//可打印
		isxdigit(c);//16进制
		tolower(c);
		toupper(c);
		//范围for 循环
		for (auto& c:s1)
		{
			c = toupper(c);
		}
		//下标越界的操作未定义

	}
	//3.3 使用vector
	{
		//类模板 只有定义时才会进行“模板类的实例化操作”
		vector<string> v1 = { 10,"abc" };
		vector<string> v2 = { "aaa","bbb","ccc" };
		//vector<string&> v3;//不能使用引用的容器，而且因为编译期间才会检查，所以编写的时候居然也不报错……
		vector<vector<int> > v4;//c++11之前都要多加一个空格在>>中间 不然会被认为是流输出符哈哈
		//定义与初始化
		vector<int> t1;
		vector<int> t2(t1);
		vector<int> t3 = t1;
		vector<int> t4(10, 110);//第一个为个数，第二个为初始化参数
		vector<int> t5(10);//初始化10 个 0
		vector<int> t6 = { 10,10 };
		vector<int> t6_1 = { size_t(10),10};//这样会不会有歧义？ 到底是1个2 还是1,2 两个元素 发现就是两个元素 原因不明
		//原因明了 是因为它会直接当成列表 除非是执行不了 才会当作其他的 比如(n,value)
		vector<int> t7{ 5,6,7,8 };
		//添加元素
		t6.push_back(9);
		//如果要添加元素 不能使用范围for 循环 因为内部的指针“可能”会断掉
		//vector 操作
		t1.empty();
		vector<int>::size_type size_t_3;//是模板实例化的属性对象
		auto size_t_2 = t2.size();
		t4.push_back(10);
		t5[0];
		t6 = { 10,11,13 };
		//t7 = t5 + t6; //没有+ - 操作
		//如果对象没有定义 > < 等操作，就没法对两个vector进行比较操作
	}
	//3.4 迭代器
	{
		vector<string> v_s(10, "abc");
		auto b = v_s.begin();
		auto e = v_s.end();//尾后
		//标准容器 迭代器运算
		*b;
		b->size();//解引用使用成员
		++b;
		--b;
		b == e;
		b != e;
		//泛型的原因 用== 和!= 比较多
		//迭代器种类
		vector<string>::iterator it = v_s.begin();
		vector<string>::const_iterator cit = v_s.cbegin();
		it += 5;
		//vector 和string 迭代器另外支持的操作
		
		it + 2;
		it - 2;
		it += 2;
		it -= 2;
		it - b;
		//各种比较运算
		auto mid = v_s.begin() + v_s.size() / 2;
	}
	//3.5 数组
	{
		//复杂的数组声明
		int *ptr[10];// 变量名的右结合，除非遇到括号
		//数组和指针 数组也有尾后指针
		//可以使用begin
		int array[10] = { 1,2,3,4 };
		auto b = begin(array);
		auto e = end(array);
		//c 字符串也是数组
		char str[20] = "hello";
		char str2[10] = "world";
		strlen(str);
		strcmp(str, str2);
		strcat(str, str2);
		strcpy(str, str2);
		//数组初始化vector
		vector<char> vc(begin(str), end(str));//但是这个结果是啥呢…… 结果很好玩，因为它本身到world\0 就结束了，所以之前的也没有清零哈哈
		int i = 0;
		//多维数组 使用范围for 循环 要使用auto & 不然就降级为指针，就不好用了
		//多维数组内部不一定是连续的，所以其实就是多个数组的集合
	}
}

