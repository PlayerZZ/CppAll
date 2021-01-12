#pragma once
//一些c++ primer的代码
#include <string>
#include <iostream>
#include "other1.h"
#include <fstream>
#include <initializer_list>
#include <stdarg.h>
#include <sstream>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <array>
#include <stack>
#include <queue>
//#include <concurrent_priority_queue.h> 这是个什么玩意？
//#include <priority_queue> //这个又包含不了
#include <algorithm>
#include <functional>
#include <map>
#include <set>
// #include <multimap>
// #include <mulitset> //居然都不支持
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <memory.h>
//#include <allocators>
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
/**
 * 第四章
 */
inline void chapter4()
{
	//4.1 基础
	{
		//表达式
		//运算对象组成 对表达式求值 得到一个结果 
		//字面量和变量是最简单的表达式
		//运算符 + 多个变量 是复杂的表达式
		//一元运算符 
		//取地址 解引用 
		//二元运算符
		//两边都有变量

		//组合运算符和运算对象
		//运算对象的转换
		//通常转化为相同的对象再做计算 转换规则有点绕
		//整形 <-> 浮点型
		//指针不能转为浮点型
		//重载运算符
		//左值和右值 = 号左边的和 = 号右边的
		//一个类的实例 对象 既可以是左值又可以是右值，所以得具体情况具体分析？
		//右值可以使用左值代替  但是右值不能代替左值
		// a = (b = c) // b = c 的结果也是个左值，但是能被当做右值使用，是这样吧 
			//所以其实是可以写成 (b = c) = a 因为b=c 作为一个左值的话
		// (p = *a) 只能是个右值？
		int a=1, b=2, c=3, *p;
		(a = b) = c;
		(p = &a) = &b;//不是说是一个右值吗？ 因为这个是等式了
		//&a = &b;//这样就不行了 因为&a 返回的是一个右值
		int i = 0;
		//内置解引用 下标 迭代器解引用 求值结果是一个左值
		*p = 10;//所以其实就是*号的都是左值呗
		//内置迭代器的++ -- 操作作用于左值对象也是左值
		//优先级 结合律
		//总之加括号就对了
		//求值顺序 cout <<i << ++i; 是未定操作
		//四种已定义顺序的 && ||  ?:   ,  这四种，逗号是
		//所以这一小节 很多概念都没有对应代码 搞啥子哦
	}
	//4.2 算术运算符
	{
		//+ - * / % +-(正负)
		auto a1 = -11 / 2; //一律去掉小数点 不管正负
		auto a2 = -11 % 2;
		auto b1 = -11 / -2;
		auto b2 = -11 % -2;
		auto c1 = 11 / -2;
		auto c2 = 11 % -2;
		//哈哈 这个c1 *-1 + c2 完全就不等于11了啊
		// 那么应该怎么处理这种情况呢？ 就看m%n 的时候 m n m 为正 n 为符号的时候
		int d=0;
	}
	//4.3逻辑运算符
	{
		//短路求值法
			//当左边已经满足的时候不会求右边的值

	}
	//4.4 赋值运算符
	{
		//左边是一个左值……
		//赋值运算 满足右结合律
		int a, b;
		a = b = 0;
		//运算符 优先级较低 ，所以差不多就是最后执行？
		//复合运算符 --*= &= <<= 位操作符
	}
	//4.5 递增和递减
	{
		int i = 0, j;
		j = ++i;
		string str1 = "test";
		auto str_iter = str1.begin();
		while (str_iter!=str1.end())
		{
			//先递增 在解引用
				//但是呢 是后加所以在这句执行完后才会加完成哈哈
			cout << "iter: " << *str_iter++;
		}
	}
	//4.6 成员访问符运算
	{
		struct TempStruct
		{
			int a;
			int b;
		};
		TempStruct *temp1 = new TempStruct();
		temp1->a = 11;
		temp1->b = temp1->a;
		//解引用优先级太低了 所以*p.size() 都是不对的…… 得(*p).size() 
			//所以才有了p->size() 这种操作吧
		
	}
	//4.7 条件运算符 （三元操作符）
	{
		string name = "zhangsan";
		string name1 = name == "" ? "无名氏" : name;
		//这个最好就不要嵌套了 写着爽看着烦
	}
	//4.8 位运算符
	{
		int a = 110;
		~a;//求反
		a<<2;//左移两位

	}
	//4.9 sizeof 运算符
	{
		int *p;
		sizeof(p);
		sizeof(*p);//地址不需要有效 都是int的大小
		int int_array[10];
		sizeof(int_array);//10 * int 大小 不会转为指针的
	}
	//4.10 逗号运算符
	{
		//优先级低 比等号还低！ 最终的值是最右的表达式
		int a,b=0;
		a = (1 + 1, b+=100, 3 + 1);
		int d = 0;
	}
	//4.11 类型转换
	{
		//类型关联 可以互相转换
		//隐式转换 转换为相同的运算对象 在进行计算 通常会变到数据量大的类型
		float float1 =1.0;
		int a1 = 200;
		auto result1 = a1 / float1;
		//小整形 到 int
			//带符号的转为无符号的
		//判断中转为bool
		//初始化时，转为左侧对象
		//赋值时，转为左侧对象
		//多种类型时，转换为精度最高的那种
		//某些函数调用时

		//数组转为指针
		int array1[10];
		int *p = array1;
			//decltype 取地址& sizeof typeid 四个除外
		//真正转换
		void * p1 = p1;
		const void* p2 = p;
		//父类指针指向子类对象

		//显式转换
		//static_cast<> dynamic_cast<> const_cast<> 
		//reinterpret_cast<> char* 指向int* 这样就可以直接操作里面的内存空间了 ，前提是知道内存构造
	}
}

//语句
inline void chapter5()
{
	//5.1 简单语句
	{
		//表达式语句
		int a = 9;
		//空语句
		;
		//复合语句

	}
	//5.2 语句作用域
	{
		int a = 0;//花括号内 而且swtich if 是每个case都算是一个花括号，所以……case最好加花括号
	}
	//5.3 条件语句
	{
		//当有垂悬else的时候，最好还是用花括号，毕竟不像python 是通过缩进控制范围的
		if (false)
			if (false)
				int i = 0;
		else
			int t = 0;
			
		//不过这个也看编译器 vs的话强制你不能换行哈哈
		//swtich 语句
// 		char contorl = 'c';
// 		switch (contorl)
// 		{
// 		case 'a': case 'b':case 'c':
// 			cout << "contrl type";
// 			int a = 0;
// 			break;
// 		case 'd':case'f':
// 			a = 10;
// 			cout << "hehe";
// 			break;
// 		default:
// 			a = 100;
// 			break;
// 		}
		//直接编译不过
		// case d中知道a ，但是没有a的初始值，没有被正确初始化，需要加个初始化 ，最后就是直接用花括号，避免名字冲突
		// 因为反正都用不了 a 中的变量值
	}
	//5.4 迭代语句
	{
		//while 语句
		int num;
		ifstream fin("sale_data.txt");
		string text;
		while (fin >> num) {
			cout << num;//如果读失败 其实是返回一个ostream 但是可以转换为bool 对象，提供了相应的转换操作的
		}
		//for 循环
		for (int i = 0; i < 10; i++) {
			i += 5;
		}
		//范围for 循环
		string str("hello");
		for (auto &c : str) {
			c += 1;//当做整数类型计算
		}
		//do .. while 先干上一遍再说
		do {
			string str = { "stupid" };
		} while (false);
	}
	//5.5跳转语句
	{
		//相当于非顺序执行
		// break; 只能跳出当前循环 或者switch case的case
			//如果想连续跳出 又不跳出最外层，可以使用某个变量来控制
		// continue 不继续执行 直接下一个轮回吧哈哈
		//goto 语句 因为太不安全 就一直不用了哈哈
			//因为跳过了声明，直接使用那个代码段就会报错……
	}
	//5.6 try 语句块和异常处理 
	{
		try {
			throw("just try try throw a exception");
		}
		catch (exception e){
			cout << "let me see see,what exception:" << e.what();
		}
		//c++ 中没有finally哦 所以得利用析构函数的特性去做一些关闭应该做的事情
// 		finally {
// 			
// 		}
		//标准异常库
		//exception 最常见异常
		//runtime_error 在运行时才能检测出的错误
		//range_error 运行时错误，计算超过范围
		//overflow_error 运算上溢
		//underflow_error 运算下溢
		//logic_error 程序逻辑错误
		//domin_error 参数结果不存在?
		//invalid_argument 无效参数
		//length_error 超过最大的长度
		//out_of_range 使用超过有效范围的值

	}


}
//函数
inline void chapter6()
{
	//6.1 函数基础
	{
		// 	int func(int a, int b) {
		// 		return a + b;
		// 	};
			//函数1 返回值 参数 函数体
		auto functiona = [&](const int &a, const int &b) ->decltype(a + b) {return a + b; };
		//主调函数和 被调函数
		auto functionb = [&] {return functiona(10, 20); };
		//形参和实参 调用的时候外面的参数是实参，但是调用的函数名内部是形参
		int i1 = 100, i2 = 200;
		auto i3 = functiona(i1, i2);//i1,i2 是实参，a,b 是形参
		//函数不能返回 数组 和 函数类型 ，但是可以返回其指针(数组指针和函数指针)
		//局部对象
		//生命周期
		//形参和函数体内部的参数 都是局部变量 
			//但是动态分配的对象通过指针可以在外层一直存在
		//局部对象对外层是隐藏的
		//自动对象
			//只存在局部 调用完自动销毁的对象
			//形参也属于这个范畴
		//局部静态变量
		auto functionc = [&]() {static int cnt = 1; return cnt++; };
		functionc();//第一次执行时初始化
		functionc();//之后只会调用，不会再进行初始化操作
		auto cnt = functionc();
		//函数声明 头文件中进行函数声明
		//函数原型 
		// 分离式编译 
		//编译和链接多个文件
		//有main 函数可以生成可执行文件
		//单独编译为.o 文件 cc -c xxx.cc
		//cc xxx.o 依赖.o -o main//生成main.exe 或者linux的执行文件
	}
	//6.2 参数传递
	{
		//参数为 引用时 引用传递 被引用调用
			//可以避免拷贝发生
			//返回额外的值
				//毕竟函数只能返回一个值
		//参数为 普通传值 值传递 传值调用
			//不会改变外层的实参的值
				//不过也看那个对象有没有实现深拷贝之类的
				//如果对象内部有指针形式的 还是会改变值的
		//指针形参 也可以改变外层的值
		//const 形参
		// 顶层const 会被忽略，认为是同一函数，不会构成重构，会报错
		//指针或引用与const
// 		int *p1 = 1;//不行
// 		const int *const p2 = 1;
		const int &yinyong = 1;//因为右侧会形成一个const 对象
		//数组形参 只能表示期望，并不能一定接受到这么大的数组 等价于一个指针
			//指定某个元素作为结尾
				//字符串就是 \0 结尾
			//使用begin end 函数
			//传递长度作为参数
		//数组可以作为引用…… 只是写起来有点麻烦
		auto functiona = [](int(&arr)[10]) {
			for (auto &a : arr) {
				cout << a;
			} 
		};
		//所以也可以是const的 引用
		//多维数组 忽略第一维度 为指针
		auto functionb = [](int(&arr)[10][20]) {
			//所以其实也可以用引用?
		};
		//main 函数 中处理命令参数
		//int main(int argc,**argv); //其实就是我们说的第三种 传递了一个长度argc 进来
		//含有可变形参的参数
		initializer_list<int> a1{1,2,3};
		auto s1= a1.size();
		auto s2 = a1.begin();
		initializer_list<int> a2 = a1;//元素将会共享 不会拷贝,因为是常量，反正不会修改，拷贝也没意义哈哈
		//局限性，只能使用一种值
		
		//使用省略符 https://my.oschina.net/SHIHUAMarryMe/blog/793155
		//c++ primer 就这么点 网上找到一个博客基本满足需求了
		auto functionc = [](const int& num, ...) {
			//但是这个...如何解析呢？ 好像要使用递归来着
			va_list args;//相当于是一个内存池，然后里面各种类型都有
			int a = 0;
			va_start(args, a);
			va_list args2;
			va_copy(args2,args);
			va_end(args);//复制为0 表示不可调用了
			//关键是还得自己来推断到底是什么类型…… 恐怕不用模板是不好用的了
		};
	}
	//6.3 返回类型和return 语句
	//返回值为引用或者指针的时候，要想一下是否这个值只是函数内部的，如果是就不行，如果不是可以
	//返回引用的时候可以看作一个左值
	//可以返回 return {"",""} 这样的
	//返回数组的指针  写起来超绕 尾置返回类型
	//auto func() -> int(*)[10] {} //范湖一个 int[10] 的指针
	
	//6.4 函数重载
	{
		//const_cast在非常函数中 使用常函数，并且返回非常变量（通常为引用）的时候还是有用的。
		//最佳匹配和 二义性
		// 名字冲突 不同的作用域会造成名字覆盖 无法构成函数重载

	}
	//6.5 特殊语言特性
	{
		//默认参数
		//内联函数和 constexpr
		//调试帮助 
		assert(11 == 11);
		//NDEBUG宏
	}
	//6.6函数匹配
	{
		//有二义性性的时候，可以指定函数类型来消除二义性 写起来有点麻烦就是了

	}
	//6.7 函数指针
	{
		//bool (*p)(int,int)
		//重载函数对根据函数指针的声明 来匹配对应的参数
		//所以上面其实就是转为特定的函数指针就行了
		//static_cast<void(*QMaincWindow::)(int)>(&MainWindow::clicked) 
			//因为clicked 有两个信号 所以得这样的来声明
		//返回 函数指针的 函数 这个就更绕了
		//int (*p(int))(int)
			//写成尾置返回类型 就清楚了
			// auto p(int) -> int(*)(int)
		//decltype 作用域函数 返回的是函数类型 而非指针…… 所以还得自己解一下

	}
}

class NormalClass {
public:
	int add(const int& a, const int& b) const { return a + b; };
	//难道内联的不能这么用?
	int add(const int& a, const int& b) {
		//使用const 形的 为啥要转为引用呢？ 而不转为常指针呢 因为太长了啊……
		//return static_cast<const NormalClass *const>(this)->add(a, b);
		//通常还要加一个const_cast
		return static_cast<const NormalClass &>(*this).add(a, b);
	};
	int sum = 10;
};

//第7章 类
inline void chapter7() {
	//数据抽象
		//接口
			//对外暴露的可调用函数
		//实现 分离式编程
			//成员变量 函数体
	//封装
		//实现了这种分离
	//7.1 定义抽象数据类型
	//类的用户是程序员
	//程序的用户才是真的用户
	//const 成员函数
	//函数返回this指针，返回值为为它的引用 这样就可以使用链式调用 a.b().c().d() 这样的

	//类的非成员函数
		//需要输入 输出这样的，毕竟不是每个成员都需要自我介绍之类的对吧
		//这类函数的特点呢 就是不止作用这个类
		//具有普遍性
	
	//构造函数
		//默认构造函数
			//没有其他构造函数会生成一个无参数的默认构造函数
			// = default 也可以直接生成这个函数
	//友元 即使是外部对象也可以访问类内部的方法，或者函数，或者类
	//拷贝 赋值 和 析构
	//todo 具体的生成方法 应该后面会有的
	//7.2访问控制与封装
	{
		//访问控制符 public private protect
		//strurct 和class 在c++ 里面只是默认的访问权限不同	
			//然而struct 却会生成一个通过整体成员的 构造函数
		//
	}
	//7.3 类的其他特性
	{
		//类成员再探
		//类的专属类型
		class Screen {
		public:
			typedef std::string::size_type pos;
		private:
			pos cursor = 0;
			mutable pos mutable_asset=0;//即使在const 中也是可以修改的值，叫做可变数据成员
		};
		//screen 的成员函数
		//const 和非 const 函数的代码复用 
			//抽象成一个真正的do_sth 函数,然后它是const的
				//在非const 内部调用时，会发生隐式类型转换
		//类对象的生成
			//前向申明 头文件中只用到了其指针或者引用，没有具体的使用的时候，可以先告诉头文件有这么名字，之后会看到的
				//class classa; //放在头文件前面 不用先include 这个类
		//友元再探
		//类之间的友元关系
		//但是这种友元是单向关系，A 是 B的友元，A 怎么知道，B 至少是知道的
		//我知道了 B 知道 然后A include B  然后A就知道了
		//类成员函数 申明为友元其实也是一样的套路
			//所以这样的话 其实A 也要include B 才行了？
		//友元作用域 其实也就是要先知道这个名字才能申明为友元的
	}
	//7.4 类的作用域
	{
		//其实就是头文件和 源文件中实现时要添加类名
		//this 指针可以避免 形参和成员变量名重复的问题
		// 所以类内初始化 列表初始化 同时存在时 类内初始化还执行不
		//如果含有const 或者引用 必须要赋值 所以通常得自己写一个
		//初始化顺序与定义的一致

	}
	//转换构造函数 ，有一步是发生了隐式类型转换的
		//explicit 必须显示的调用构造函数才能变成这个对象
		//还可以使用static_cast<class> 转换过去
	//字面值常量类
		//含有至少一个constexpr 构造函数

	//类的静态成员
	//加上static 关键字即可
	//如果要类内初始化 要使用constexpr 但是这样又不可修改了
	//静态成员函数 可以作为成员函数的默认参数
	//委托构造函数 就是可以使用别的构造函数进行委托生成类
}

//第八章 IO库
inline void chapter8()
{
	//iostream fstream cin,cout,cerr >>  << getline
	//读写宽字符
	//sstream 与字符串相关的流 wcin wcout wcerr wstring 呢，有没有？
	//继承机制 ifstream istringstream
	//io 对象无拷贝 或者赋值操作
	ofstream out1, out2;
	//out1 = out2;//错误的
	ofstream& out_yinyong = out1;//正确的，或者使用指针解引用？
	//条件状态 
	istream::iostate;
	ofstream::badbit;//流崩溃 为啥呢
	ofstream::failbit;//操作失败
	ofstream::eofbit;//达到了文件结束
	ofstream::goodbit;//正常状态 返回0
	out1.eof();//其实就是iseof 是否是到达了末尾
	out1.fail();
	out1.bad();
	out1.clear();//将所有state 置位 这样的话就能继续用了，当然如果还有的话 如果在eof 肯定不能继续用了哇
	auto flags = out1.rdstate();//返回流的状态
	out1.setstate(flags);//设置流状态 为啥不直接Clear呢
	//failbit 是可恢复的错误 badbit 是不可恢复的错误 末尾eof 和 failbit 都会有
	//管理流缓存 系统io很慢，所以一次性读到一个buffer 然后再慢慢解析是比较好的，写入文件其实也是一样的，最好自己写到buffer里面再一次性的写入比较好
	//unitbuf() 设置流内部状态
	cout << unitbuf; //立即输出  但是很烦的就是它本身是一个函数 所以总是会被联想成一个括号
	//以后还是使用doxygen 好了 但是qt是不是不可以用这个呢？

	//输入和输出流绑定 想了下还是使用stringstream 比较好
	string str = "12315 hehe";
	string str1;
	istringstream scin;
	scin.tie(&cout);//关联 输出和输出 会被同时输出也会被 记录到这个流里面去 但是看不到 还是记录到文件中直观一些
	//这个有点问题 看解决方案好像是直接使用stringstream
	//https://bytes.com/topic/c/answers/63884-stringstream-tie-problem
	ofstream fout("outfile.txt");
	scin.tie(&fout);
	scin.str(str);
	int a;
	scin >> a;
	scin >> str1;
	fout << unitbuf;
	//文件流 ios::in out app ate trunc //截断 binary 二进制
	//其实就是几个状态操作 和打开方式之类的 但是如何直接输出到buffer 其实也没有说诶
}

//示例的容器对象
class Data1 {
public:
	Data1() { cout << "默认构造函数被调用"<<endl; };
	Data1(const int& n) :data(n) { cout << "int 构造函数被调用" << endl; };
	bool operator<(const Data1& data1) {
		return this->data < data1.data;
	}
	bool operator==(const Data1& data1) {
		return data1.data == this->data;
	}
	~Data1() {cout << "析构函数被调用"<<endl;}
	int data = 0;
};

//第九章 顺序容器
inline void chapter9()
{
	//控制元素存储和顺序访问的能力
	//vector deque list forward_list array string
		//string vector 内部是连续的内存空间
			//使用下标访问很快
			//插入和删除操作比较慢
		//list forward_list 内部是链表形式
			//插入和删除比较快
			//下标访问需要遍历 会比较慢
			//额外内存开销 存放指针等
		//dequeue 较复杂
			//也支持 随机访问，很快
			//插入 删除比较慢 但是两端很快
				//估计是因为它是像两端扩展的，都有部分扩展空间
		//array 是c的数组的升级版，多了一个size 对象的样子……
	//容器选择 方式
	//默认vector即可
	//小元素 char int 之类的排除 list forward_list
	//随机访问 使用vector deque
	//中间插入 选forward_list 或者list
	//头尾插入比较多 使用deque
	//一开始需要使用插入，之后都是随机访问
		//如果是有序的，使用vector 然后排序操作
		//如果不是 直接使用list 插入 然后转为vector
			//如果只有一次输入 那这种方式肯定是最好的了
	//顺序容器 关联容器 无序容器
	//容器限制
		//顺序容器 要求可以使用默认构造函数
		//无序容器要能比较大小
			//最少也要实现 < 小于符号的重载
	
	//容器操作
	//类型别名
	vector<string> vs{ 10,"hello" };
	vector<string>::iterator it = vs.begin();
	vector<string>::const_iterator cit = vs.cbegin();
	vector<string>::size_type s1 = vs.size();
	vector<string>::difference_type d_ = vs.begin() - (vs.begin() + 2);
	vector<string>::reference vsr = vs[0];//是它内部类型的引用 ,所以为什么它变成了cv::Cstring呢？ 难道造成了名字污染？
	vector<string>::const_reference cvsr = vs[0];//const引用的写法
	//构造函数
	vector<string> vs2;
	vector<string>vs3(vs2);
	vector<string> vs4(vs.begin(), vs.end());//直接值拷贝，不过想来citerator 也是可以的
	vector<string> vs5(vs.cbegin(), vs.cend());//看吧，毕竟它内部不会对其进行修改
	vector<string> vs6{ "what","fuck","day","is","today" };
	//赋值与 swap
	vs3 = vs2;
	vs3 = { "he","he","ha","ha"};//相当于右边是发生了隐式类型转换的吧 变成了一个临时变量，然后再赋值给vs3
	vs3.swap(vs2);//直接使用交换函数 所以这个算是值拷贝还是内部的指针进行了交换？
	swap(vs3, vs);//等价上面那种
	//大小
	vs2.size();
	vs2.max_size();//是不是 已经申请的内存呢？应该不是只是这个容器的限制
	vs3.empty();//is_empty 的缩写，我发现还是写成is 比较好，虽然知道clear 才是清空，不过还是觉得不爽呢 empty 可能因为只是个形容词吧，所以就不需要is?
	//添加 删除 元素
	vs.insert(vs.end(),"??");//这个函数，每个的实现不同应该是 
		//插入肯定是得指定一个后项，为什么？不然我怎么插入到它首位置
	vs.emplace(vs.end(),"!!");//类似插入，但是不调用构造函数，直接使用参数 等到插入的时候再内部使用new 之类的东西 这样的话可以更优化
	vs.erase(--vs.end());//清除某个元素 毕竟如果是最后一个元素 肯定是没办法删除的吧喂
	vs.clear();//直接就清空了 不过应该只是计数器清零了 
	//关系运算符、
		//前提是内部的对象有至少实现了
			// < (小于)操作符
	vs == vs2;
	vs != vs2;
	vs < vs2;
	vs >= vs3;
	//迭代器获取
	vs.begin();
	vs.cbegin();//返回const 迭代器
	//反向迭代器的额外成员 forward_list 不支持
	vector<string>::reverse_iterator rit = vs2.rbegin();
	vector<string>::const_reverse_iterator crit = vs2.crbegin();//但是这个begin 其实就是吧 注意不是尾后哦
	//迭代器
	//迭代器范围 
	//左闭合区间 左取右不取
	//其实就是[begin,end)
	//如果begin == end 就是空的
	{
		vector<string> vs = { "heelo","workr" };
		for (auto it = vs.cbegin();it!=vs.cend();++it)
		{
			cout << *it;//迭代器也是使用类似解引用的操作 ，不过应该是重载的了
		}
		//反向遍历一遍
		for (auto it= vs.crbegin();it!=vs.crend();it++)
		{
			cout << "reverse  " << *it;
		}
		//不过如果是容器内部的类型 一般也是使用auto 来获取的吧，毕竟没事谁需要知道它的类型啊 只要有这么个概念即可了
		//实现需要申明的时候，直接使用decltype 来申明变量即可了…… 虽然我是没怎么用过啦
		//容器定义和初始化
		vector<string> vs1(vs.begin() + 1, vs.end());//使用迭代器进行初始化，这样的话其实相当于截取操作了，你看c++ 的截取操作其实就是初始化操作……
		vector<string> vs2(100);//使用内部对象的默认构造函数 初始化100个
		vector<string> vs3(10, "hehe");//使用它的构造函数进行构造，我突然想到它的构造函数好像可以是两个
		string str(10, 'c');
		//vector<string> vs4(20, (10, 'c'));//哈哈，不行的 不能使用多参数的初始化？ 如果如果有多个参数的构造函数如何使用呢?
		vector<string> vs4(20, string(10, 'c'));
		vector<string> vs5 = { 20,{10,'c'} };//这样通过{} 来初始化strig  这样居然也行？不过这样除了让自己和别人都看不懂外好像也没什么好处……

		//列表初始化

	}
	{
		//使用assign 操作 相当于可以使用相容的操作 ，不一定一样
		vector<double> vd = { 1.1,1.2,1.3 };
		vector<int> vi;
		//vi = vd;//这个是错误的对吧
		//vi = vector<int>(vd.begin(), vd.end());//这个操作也可以？
		//vi.assign(vd.begin(), vd.end());//反正这两个操作都会warning 估计是因为类型截断？
		
		//swap 操作相当于是内部的指针指向发生了改变
			//所以原先的指针 和 迭代器都能用，不过它们的意义变了，是另一个对象的了。
			//相当于它们换了个主人，哈哈 虽然还是在那儿，相当于卖房子一样的 里面的家具已经换了个主人
		//容器的 == 需要元素能有判等操作
			//其他才是需要 < 操作
	}
	{
		//顺序容器操作
		//添加元素
		vector<string> vs1 = { "hello","world" ,"giaogiao"};
		vs1.push_back("233");
			//使用的是对象的拷贝
				//所以这里233 会变成string 然后又被拷贝一遍 所以得是两次构造函数的调用，还有一次析构函数哈哈
		vs1.emplace_back("!!!");//这个就是一个比较节省内存的版本 好像不支持插入多个的操作
		deque<string> ds1 = { "hell" };
		ds1.push_front("what");//只有部分容器支持哈 vector 因为头插入比较慢就不支持 不过可以使用insert 完成这个操作就是了
		vs1.insert(vs1.begin(), "haha");//这个相当于Vector的 push_front 不过不推荐这么用所以就不实现
		vs1.insert(vs1.end(), 10, "hehe");//插入10个hehe
			//n 为 0 则返回其pos 的迭代器
		vs1.insert(vs1.end(), ds1.begin(), ds1.end());//把deque 中的元素插入进来
		vs1.insert(vs1.end(), { "hello","world","again" });//插入多个不同元素
		vector<Data1> vdata = {};
		vdata.push_back(1);//为什么没有显示的调用两次构造函数呢 因为内部的优化？那为什么调用两次析构函数？
		vdata.emplace_back(10);//不过确实 emplace 就只调用了一次
		//元素访问
		auto &data1 = vdata.back();
		auto &data2 = vdata.front();
		try
		{
			auto &data3 = vdata.at(3);//如果失败返回啥？ 会抛出异常 但是下面那种就没有抛出异常 直接崩！
		}
		catch (out_of_range e)
		{
			string what = e.what();
			cout << what;
		}
		
		
		auto &data4 = vdata[0];
		//删除元素
		vs1.pop_back();
		ds1.pop_front();
		//vs1.erase(vs1.end());//行为未定义
		vs1.erase(vs1.end() - 1);//返回end()
		vs1.clear();

		//forward_list的额外操作
		//其他的容器的插入其实都是 insert_before 就是在某个元素之前插入 forward_list 是在某个元素之后插入 insert_after
		//所有有一个before_begin的迭代器
		forward_list<string> fstr = { "11","22","33" };
		//fstr.insert_after(fstr.end(),"hehe");// 它的迭代器不提供加操作 只能从前往后遍历 所以也不支持--操作 估计只能++
			//这个以为是后插 所以不能这样用
		//只之前前面的各种操作 后面不支持 但是我在想就算是支持后面的应该也不费事才对啊……
		//改变容器大小
		vs1.resize(15,"oo");//多出来的元素都用这个来代替 如果想要全部变成某个元素 就只能拷贝赋值了

		//容器操作可能让迭代器失效
			//vector 和 string 是顺序存储，所以呢可能分配了新的内存空间，导致这个迭代器失效了
			//deque 使用的应该是部分连续空间， 再加上list 链表啥的
				//类似多维数组这么个东西，哈哈
		//编写改变容器操作的循环程序
			//删除和新增之后 需要更新这个迭代器 毕竟删除 和 insert 都会返回一个指针的
			//判断的时候也不要用对象来保存这个end 需要直接使用对象的end
			//虽然增加了函数调用的开销，不过这个开销其实并不大就是了
		//vector的增长
			//当需要重新分配的时候 通常会多分配一些内存 这样就不用每次都去分配内存空间了
		auto t1 = vs1.capacity();//可以现在可以装多少个对象哈哈 跟size()不一样
		vs1.shrink_to_fit();//瘦身，跟它整得跟size一样大
		vs1.reserve(t1+100);//分配至少可以装x个的空间
			//如果比当前size 小应该不会有所作为吧
		//string 的额外操作
		{
			const char* cp = "what the hell";
			string str1(cp,7);
			string str2(str1, 1);//拷贝从str1 [1,-1) 如果长度不满足的话，是会抛出异常的
			string str3(str1, 1, 3); //拷贝从str1[1, 1+3] 如果超过也不会多拷贝的 很安全
			auto str4 = str1.substr(1, -3); //后面一个是长度 如果是负数会怎样？ 看样子会被当做一个很大的正数……
			str4.insert(str4.size(), 10,'c');//可以直接使用下标 而不是迭代器
			str4.insert(str4.size(), "heiheihei");
			//appen 和 repalce 操作
			//append 和 + 是等价的吧
			str4.replace(0, 3, "hehehehehehehh");//把前三个字母换成这么大一串
				//没有直接的替换字符串操作 需要先查找？
			//string 搜索
			auto pos1 = str4.find("hehe"); //如果要替换 可以使用，等价于
			auto pos2 = str4.find("hehe",0);//pos 要不要+1呢
			auto pos3 = str4.find_first_not_of("hehe", 0);//我倒是好奇这个是怎么查找的
			auto pos4 = str4.find_last_of("he",0);//但是这个第二个参数 应该也是从前往后的pos
			auto pos5 = str4.rfind("hh");//逆向搜索 是不是从后往前的位置就不知道了

			//比较函数 类似 strcmp
			str1.compare(1,4,str2,1,4);//最复杂的版本 const char* 因为是指针，所以没有pos2 参数，毕竟可以直接直接+n 哈哈
			//数值转换
			auto dstr = to_string(10086.1123);
			stoi(dstr,0,10);//第二个存放非数值下表 第三个表示进制 str的进制 可以是16进制这样子的
			stod(dstr,0);
		}
	}
	{
		//容器适配器 把容器再封装一次
		//stack queue priority_queue 三个
	
		deque<string> str_deq = { "he","wa","hehe","heihei" };
		stack<string> str_stack(str_deq);
		//priority_queue 使用vector 所以 难怪能使用 所以有什么用呢……
		queue<string> str_queue(str_deq);
		str_queue.front();//队首
		str_stack.top();//栈顶 嗯 因为两个的形容词不一样
		str_stack.pop();
		str_stack.push("gsg");
		str_queue.pop();
		str_queue.push("???");
		//嗯 有点类似流操作的样子。 执行看看 但是并没有改变str_deq 的值啊，所以其实这个就是一个初始化？
		//栈可以指定实现……
		vector<string> str_vec1 = { "h","hehe" };
		stack<string,vector<string>> str_stack1(str_vec1);
	}
}

int my_add1(int a, int b) { return a + b; }
int my_add2(int &a, int b) { return a + b; }
//第十章 泛型算法
inline void chapter10(){
	//概述 直接在algorithm 头文件里面
	//不直接操作容器 需要迭代器范围
		//但是我觉得用容器就不用了记忆这些了 不是很爽吗……
	{
		vector<string> str_vec = { "111","222","333" };
		auto it = find(str_vec.begin(), str_vec.end(), "222");
		string result = it == str_vec.end() ? "success" : "failed";

		//迭代器 令算法不依赖于容器

		//但是 依赖于容器 元素的 某些操作
			//必须实现一些特定的操作才能使用这些算法
			//find 需要 元素有 ==
			//其他基本都需要 < 操作符重载
		vector<Data1> data1{1,2,3,4};
		auto dit1 = find(data1.begin(), data1.end(), 4);
		//算法不依赖于容器实现
			//但是它的迭代器的累加 累减呢？
				//所以还是要看它的迭代器的实现？ 嗯迭代器其实也分为好几个，所以其实内部还是有个迭代器的继承什么的
					//如果能够插入或者删除 也是因为迭代器做的…… emmm
	}
	{
		//100 个算法
		// 我在想就没法提供一个Qt 和 c++ 通用的算法嘛？ 每次都要转过来转过去很麻烦的
			//我知道了 得自己写两个函数，能够接受c++ 和Qt 的不同的就行了，或者提供一个隐式转换，把string转到QString
				//不行啊，std::string 是已经定义好了的， 所以不能直接转换为QString 所以呢 使用一个中间类还是直接重写Qt？
				//那也没有QString 到 string的转换啊，重新写一个中间类？
		{
			// 只读算法
				//求和
			vector<string> str_vec1 = { "111","222","333" };
			vector<string> str_vec2 = { "111","111","222","333" };
			vector<string> str_vec3 = { "111" };
			string sum_str1 = accumulate(str_vec1.begin(), str_vec1.end(), string(""));//没法用lambda 表达式来进行计算哇？
			string sum_str2 = accumulate(str_vec1.begin(), str_vec1.end(),string(""), [](const string& sum,const string& num) {return sum + num; });
				//报错是因为allocator 的原因 原来使用string 初始化它就行了…… 因为内部不会调用它的构造函数 而且貌似有点 explict那味儿 有可能是因为const 的原因?
			//	操作两个序列 第二个序列至少比第一个 一样或者更长 
			auto equal_result1 = equal(str_vec1.begin(), str_vec1.end(), str_vec2.begin()/*, str_vec2.end()*/);//不带这个参数的话 比较到一样长即可
			auto equal_result2 = equal(str_vec1.begin(), str_vec1.end(), str_vec3.begin(), str_vec3.end());//定义了这个就不会判断它够不够长了？
			try
			{
				//auto equal_result3 = equal(str_vec1.begin(), str_vec1.end(), str_vec3.begin()); //会直接报错
				//而且还catch 不到？ 
			}
			catch (out_of_range e) {
				string str = e.what();
			}
			catch (std::exception e)
			{
				//todo 都捕获不到 看了下 是所谓的严重错误
				string str = e.what();
			}

		}
		//写容器操作
		{
			vector<int> vec_int1 = { 1,2,3,4,5 };
			fill_n(vec_int1.begin(), vec_int1.size(), 10);//全部置为0
			//插入迭代器 迭代器提供了插入的功能……
			
			vector<int> vec_int2;
			auto bi_it = back_inserter(vec_int2);
			fill_n(back_inserter(vec_int2), 10, 20);//这个就相当于插入操作了 因为迭代器具有的是插入功能……
			//拷贝算法
			//copy(vec_int1.begin(), vec_int1.end(), vec_int2);//这个不用迭代器了 ？所以还是有直接使用容器的操作吗
			copy(vec_int1.begin(), vec_int1.end(), vec_int2.begin());//所以怎样都可以？
			//反正加上back_inserter 就不一样了
			//替换操作
			replace(vec_int1.begin(), vec_int1.end(), 0, 40);//更换为
			replace_copy(vec_int1.begin(),vec_int1.end(),vec_int2.begin(),3,40);//将替换后的结果存放在vec_int2 中，但是呢其大小并没有改变吧
			replace_copy_if(vec_int1.begin(), vec_int1.end(), vec_int2.begin(), [](const int& num) { return num == 10; },100);//替换后的值在最后一个
			//还是那句话 如果使用back_inster 就不一样了
		}
		{
			//重排操作
			vector<int> v_i = { 1,2,3,4,6,7,57,5,25,2,2,4,6,7 };
			sort(v_i.begin(), v_i.end());
			auto it_unique = unique(v_i.begin(), v_i.end());
			v_i.erase( it_unique, v_i.end());//删除重复元素 
		}
	}
	{
		//10.3 定制操作
		// 谓词 predicate 其实就是动词 其实就是函数
		vector<int> v_i = { 1,2,3,4,5,6 };
		//排序为 偶数比较大
		sort(v_i.begin(), v_i.end(), [](const int& i1, const int& i2) {
			if (i1%2)
			{
				if (i2%2)
				{
					return i1 < i2;
				}
				return false;
			}
			else if (i2 % 2)
			{
				return true;
			}
			else {
				return i1 < i2;
			}
		});
		//返回{2,4,6,1,3,5} 但是如何倒序呢？ 传一个大于操作符就去就行了 true 的意思是排在前面
		for_each(v_i.begin(), v_i.end(), [](const int& i) {
			//其实就是一个范围for 循环 有区别吗？ 如果使用引用的话，其实没有区别
		});
		//所谓的lambda 表达式 值捕获 其实就是[]中的东西 ，反正啊，一般都是直接使用& 当然如果是局部对象，使用= 
			//如果是内里面，嘿嘿，使用this 指针就行了
			//比较麻烦的值捕获 [&,p1,p2] 除了p1,p2 用拷贝，其余用引用 [=,p1,p2] 同理
			//默认是const 捕获拷贝的变量
				//所以得使用 [p1] () muable {return ++p1;}; 这样的写法
		//参数绑定 据说不是很好用 c++11 之后都直接使用lambda 完成参数绑定了
			//但是万一写模板类的时候要用呢？ 还是看一下好了
// 		auto test_func = [](int a,int b) {return a + b; };
// 		auto test_func2 = [](int& a, int b) {return a + b; };
		auto func1 = bind(my_add2, 1, placeholders::_1);//原来这个placeholders 是调用的时候，外层的第几个参数……
		//绑定引用对象
		func1(1);//绑定了个寂寞？
		int a = 10;
		//auto func2 = bind(my_add2, a, placeholders::_1);//这里做了一个拷贝动作 不想要这个拷贝 直接引用就得使用ref
		auto func2 = bind(my_add2, ref(a), placeholders::_1);
		auto val1 = func2(100);
	}
	{
		
		//再探迭代器
			//倒也不是说迭代器无用吧 至少说这种思路是可以的，自己以后写代码可以参照这种思路
		//插入迭代器
		{
			vector<int> vi;
			auto it = back_inserter(vi);
			it = 10;
			it = 101;
			it = 102;
			auto value1 = *it; 
			auto value2 = ++it;
			auto value3 = it++;//这三个操作都只是返回它本身 不会真的加 也不会
// 			if (value1 == value2 == value3)
// 			{
//				//还没有判等操作……
// 				string str = "yes";
// 			} 
// 			auto front_it =front_inserter(vi); //这个必须要有push_front 的容器才能用
// 			front_it = 99;
			inserter(vi, vi.begin() + 2) = 88;//其实就是内部调用 insert 方法吧喂
		}
		//流迭代器
		{
			//iostream 居然也有迭代器？
			istringstream istr("hello world what fuck");
			//干 空值就是eof
			istream_iterator<string> in(istr),eof;
			//所以怎么判断它到了结尾没有呢？
			//用不了啊 
// 			istream_iterator<string>::end;//莫得这个 所以这个是没有实现迈
// 			for (in != eof)
// 			{
// 				string str = *in;
// 			}
 			string str = *in++; 
			str = *in++;
			//auto sum = accumulate(in, eof, 0); 还是不行 因为压根不能判等

			ostream_iterator<string> oit(cout," !!!\n");
			oit = "what";
			oit = "the";
			oit = "hello";
		}
		//反向迭代器
		{
			//需要迭代器支持-- 操作
			//一切都要反着来
			string str1("hellom,world");
			auto rpos = find(str1.rbegin(), str1.rend(), ',');
			string str2(str1.rbegin(), rpos);
		}
		//移动迭代器	不在这一章讲
		

	}
	//泛型算法结构
	{
		//分类

		//输入迭代器
			//只读 不写 单遍扫描 只能递增
			//解引用只能取值 不能当做左值
		//输出迭代器
			//只写 不读 单遍扫描 只能递增
			//解引用只能作为左值
		//前向迭代器
			//可读写 多遍扫描 只能递增
		//双向迭代器
			//可读写 多遍扫描 可递增，可递减
		//随机访问迭代器
			//可读写 多遍扫描 支持全部迭代器操作
				//意思是可以 +n操作
		//算法形参模式
		//算法的命名
			//要么通过重载 支持自定义函数
			//要么通过_if 版本支持
			//还有带_copy 版本的会赋值给另外一个对象
	}
	//10.6 特定容器算法
	{
		//sort 要求随机访问迭代器
		list<int> list1{ 1,2,3,4,5 };
		list<int> list2{ 6,7,8,9,10 };
		list1.splice(list1.end(),list2);
		//相当于 inster 只不过是链表的 有点像move函数哈哈
	}
}

//11 章 关联容器
inline void chapter11() {
	//使用关联容器
	//map 关联数组 ？
	map<string, int> map1;
	map1["hello"] = 10;
	//可以用来做计数器 因为初始化为0
	istringstream str_in("hello hello world");
	string str_temp;
	while (str_in>>str_temp)
	{
		map1[str_temp]++;
	}
	//使用set 用来排除重复
	str_in.str("hehe hehe heihei haha ha gs");
	set<string> set_str;
	//这里没有重复的数据
	while (str_in>>str_temp)
	{
		set_str.insert(str_temp);
	}
	{
		//关联容器不支持 位置相关操作
			//push_back/front 都不行
		//迭代器都是双向的
		//multimap 支持多个相同键值
		//multiset 就离谱了 本来不应该唯一吗？ 
		//关键字类型要求 
			//需要能够比较 < 操作
				//严格若序
					//说了很多 其实即使定义一个 < 即可
					//了不起再定义一个==
				//这特么其实定义一个 < 就行了
		//这个multiset 就没有个计算操作 ？还不如使用vector呢，虽然不排序
		struct TempStruct
		{
			int a;
			int b;
		};
// 		//a 作为10 位 b作为个位
		auto compare_func = [](const TempStruct& a1, const TempStruct& a2) {return a1.a*10 + a1.b < a2.a*10+a2.b; };
		multiset< TempStruct, decltype(compare_func)* > a(&compare_func);//这也太麻烦了吧 而且没法初始化？
		pair<string, int> p1 = {"hello",1};
		p1.first; p1.second;
		auto p2 = make_pair("", "");//自省推断
		pair<string,string> p3 = make_pair("", "");//自省推断
		p3 = p2;//应该是它的元素的构造函数兼容即可
	}
	{
		//关联容器操作
		map<string, int>::key_type i1 = "hello";
		map<string, int>::value_type i2 = { "10",10 };
		map<string, int>::mapped_type i3 = 10;

		//迭代器
		map<string, int> map1 = { {"h",1},{"a",2},{"aa",3} };
		auto it = map1.begin();
		while (it!=map1.end())
		{
			it->first;
			it->second;
		}
		//insert 不能做update 操作
		auto result = map1.insert({ "h",2 });
		if (result.second==false)
		{
			cout << "插入失败,key:" << (result.first)->first << ",value:"<<(result.first)->second<<endl;
		}
		//删除元素
		auto re1 = map1.erase("h");//map 只有 0 1 mulitmap 有0 n
		//下标操作 插入和更新
			//mulitmap 没有下标操作
		map1["giogio"] = 10;
		//访问元素
		auto find_result = map1.find("giogio");
		auto count_result = map1.count("giogio");//multimap 就不一样了，因为访问的时候相当于是访问二维数组一样的

		//遍历multimap
		multimap<int, int> map2 = { {1,2},{1,3},{1,4},{1,5},{1,3},{2,3} };
		//方法1 使用count find
		auto find_result2 = map2.find(1);
		auto count_result2 = map2.count(1);
		while (count_result2--) {
			cout << find_result2->first << " : " << find_result2->second << endl;
			find_result2++;
		}
		//方法2 使用lower_bound upper_bound
		auto beg = map2.lower_bound(1);
		auto end = map2.upper_bound(1);
		for (auto beg = map2.lower_bound(1),end = map2.upper_bound(1);
			beg!=end;
			++beg)
		{
			beg->first;
			beg->second;
		}
		//方法3 使用equal_range
		for (auto pos = map2.equal_range(1);pos.first!=pos.second;pos.first++)
		{
			pos.first->first;
			pos.second->second;
		}
	}
	{
		//无序容器
		unordered_map<int, int> unorder_map1;
		//背后是一堆桶 bucket
			//根据key的hash 值映射到不同的桶里
			//但是桶管理 太多不也一样和ordered 一样嘛
		//map 背后是红黑树 查找可能相对麻烦
		//unodered_map 背后是哈希表 emmm 遍历hash表？遍历能快到哪儿去嘛
			//想到了一种情况 就是直接对hash值求余，就可以让它能够取到这个值了
				//这是最傻的实现方式 不过想来也差不多吧 关键它还是要判断它是否存在吧？怎么判断？
				//直接看找到的那个地址有没有想要的东西就行了?
				//类似取余 就有9个 然后后面看有没有这个行了 所以只有这张表是顺序存储的，其余都是可以
					//但是要更新这张表就行了
		//桶其实就是那个哈希表的大小吧……
		unorder_map1.bucket_count();
		unorder_map1.bucket_size(0);//从0开始还是从1开始呢
		unorder_map1.bucket(1);//在哪个桶中
		//桶内还有迭代器
		//之前就觉得直接下标访问就行了 现在发现还真麻烦啊
	}
}

//Blob 其实就是二进制的封装
//但是它想实现的 其实就是一个shared_ptr 要做的事情啊 只不过上层封装了？有意思？
class StrBlobPtr;//前置声明 类似extern 之类的吧
class StrBlob {
public:
	using size_type = vector<string>::size_type;
	StrBlob() {};
	StrBlob(initializer_list<string> i1) :data(make_shared<vector<string>>(i1)) {};
	friend class StrBlobPtr;
	size_type size() { return data->size(); };
	bool empty() { return data->empty(); };
	void push_back(const string& t) { data->push_back(t); };
	void pop_back() {
		check(0, "back on empty StrBlob");
		data->pop_back();
	};
	string& front() {
		check(0, "front on empty StrBlob");
		return data->front();
	};
	string& back() {
		check(0, "back on empty StrBlob");
		return data->back();
	};
	//这里StrBlobPtr 对于StrBlob 来说还是未定义 只不过它名字先显示出来了 除非就把这两个函数定义在后面 嘿嘿
	// 			StrBlobPtr begin() { return StrBlobPtr(*this); };
	// 			StrBlobPtr end() { return StrBlobPtr(*this,data->size()); };
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const std::string &msg) const {
		//直接报错啊
		if (i >= data->size() == 0)
		{
			throw out_of_range("msg");
		}
	};
};

class StrBlobPtr {
public:
	StrBlobPtr() = default;
	StrBlobPtr(StrBlob& sb, size_t sz = 0) :wptr(sb.data), curr(sz) {};//编译器非要说我错了
	std::string operator[](const int& index) const //解引用
	{
		auto p = check(index, "dereference past end");//解引用到最后了
		curr = index;//不改为mutable 是会报错的
		return (*p)[index];
	};
	StrBlobPtr& incr() //前向递增
	{
		auto p = check(curr, "increment end of StrBlobPtr");//已经是尾后指针了
		++curr;
		return *this;
	};
private:
	shared_ptr<vector<string>> check(size_t i, const string& msg) const {
		auto ret = wptr.lock();
		if (!ret)
		{
			throw runtime_error("unbound StrBlob");//已经销毁了 访问个球
		}
		if (i >= ret->size())
		{
			throw out_of_range(msg);
		}
		return ret;
	};
	weak_ptr<vector<string>> wptr;
	size_t mutable curr = 0;//即使是const 函数也可以修改的对象
};

//12章 动态内存
inline void chapter12()
{
	//static 对象 在对象第一次使用时初始化，程序退出时销毁
	{
		//动态内存和智能指针
		//以前使用的时候只能new 出来
			//但是忘记delete 就容易内存泄漏
		// shared_ptr
		class ClassA {
		public:
			int _a = 0;
			ClassA() = default;
			ClassA(const int& a):_a(a) {};
			~ClassA() {
				cout << "析构函数被调用" << endl;
			}
		};
		shared_ptr<ClassA> a = make_shared<ClassA>(1);//内部使用初始化 确实是变长了吧 不过也不用担心内存泄漏了
		//实现不行可以
		//typedef shared_ptr<ClassA> aptr; 这个不是很清楚
		//反正typedef 能用的 using 都可以
		//https://zhuanlan.zhihu.com/p/21264013
		using aptr = shared_ptr<ClassA>;
		aptr b = make_shared<ClassA>(2);
		b.get();//返回其指针 不推荐使用 因为使用指针就意味着不会用普通指针了
		swap(a, b);//交换内存
		//
		auto u_r = a.unique();
		auto count_r = a.use_count();
		a = b;//a 原先指向的内存 计数器会减一，减到0 就直接销毁了，这儿因为只有一个引用，所以会立即销毁
		//推荐使用auto 来接收 make_shared<T>()
		auto ret_ptr = make_shared<ClassA>(10);
		//使用动态 生存周期的类
		//1 程序不知道自己需要使用多少对象
			//内存不知道多大
		//2 程序不知道所需对象的具体类型
			//父类 多态
		//3 程序在多个对象间共享数据
			//虽然引用也行吧，终究要在一开始就进行数据绑定，有点不友好

		//这特么就离谱 本身vector就是内部动态内存分配 你这new 又算个啥呢
		vector<int> *pv = new vector<int>{ 1,2,3,4,5 };
		auto p1 = new auto(1); //这特么就离谱对吧 我要写个宏岂不是就是无类型的了？
			//只是后面这个auto 里面必须是单参数的 通常就是这个类型本身，不然有太多可以推断的东西了
		//动态分配 const 对象
		const int* p2 = new int(10);
		//*p2 = 20;
		//内存耗尽 bad_alloc
			//改为不抛出异常的模型……
		int* p3 = new(nothrow) int(20); //如果失败返回空指针
			//定位new 允许传入额外参数
		delete p1, p2;
		//delete 空指针的行为未定义
		//delete 之后重置指针
		p1 = nullptr, p2 = nullptr;

		//shared_ptr 和 new
		shared_ptr<int> p4(new int(30));
		//不能隐式类型转换 因为是explict 的 也就是说你得自己显示的赋值
		shared_ptr<int> p5(p1);//p1 是new 出来的
		//shared_ptr<int> p6 = p1;//其实不应该重复的赋值给一个sharedptr
		//shared_ptr<int> p6(p1);//这样也是不对的，存在doule free
		//普通指针和智能指针不要混着用 因为不知道什么时候就销毁了
		//所以推荐使用make_shared
		auto f = [](shared_ptr<int> p) {};
		//f(shared_ptr<int>(p1));//这样会因为它是临时变量 直接销毁…… 所以也是错误的
		p5.reset(new int(5));//正确的重新复制 而不是直接等于一个普通指针 或者直接一个make_shared 也行，只是没有这个表达清楚
		//并且复制也是一个reset 会有概率销毁以前的对象
		//智能指针因为析构会有 析构操作
			//所以在异常抛出时，是会自动销毁对象的
		// 于c 代码结合的时候
			//需要销毁某些资源文件 可是自定义销毁函数
		auto int_deleter = [](int* p) {cout << "我要释放个P" << endl;/* delete p; */};//这里不是真的删除 因为压根不用删除
		int i = 0;//假设里面有些东西 想在函数结束的时候执行
		{
			shared_ptr<int> int_sp(&i, int_deleter);//但是为什么传入引用呢？而不是动态内存的指针？很迷
			//其实就是用在代码块里 有限范围的那种吧大概 毕竟容易万一传出去了，它本身自己被析构就尴尬了
		}
		//所以其实可以使用智能指针进行日志记录诶……
			//生命周期结束 说明任务结束……
		//注意事项
			//不使用相同的内置指针初始化多个智能指针
				//reset 也不行
			//不用delete get()返回的指针
			//不使用get 来初始化 或者reset 另一个智能指针
			//如果非要用get 记得范围,毕竟万一智能指针无效了就尴尬了
			//如果使用智能指针保存的对象 不是new 分配的，那就得自定义删除器
				//所以其实不用删除的对吧……
				//所以其实就是用来做一些结束操作 经常需要重复的操作
					//那就不是日志操作用得到吗哈哈
		//unique_ptr 
		//一次性的指针 只能独得恩宠
		unique_ptr<int> uni_ptr1(new int(10));
		unique_ptr<int> uni_ptr2 = make_unique<int>(1);
		p1 = uni_ptr1.release();//这个直接就放弃控制权了
		//unique_ptr<int> uni_ptr3(uni_ptr1);//不允许
		//uni_ptr2 = uni_ptr1;//不允许
		//unique_ptr 必须指定 删除类型才能指定删除器
		//这个应该更适合用来答应日志 嘿嘿 不过需要把函数写好
		//不过直接在 构造和 析构中写好不就好了吗 ，可能修修补补的时候 
			//可以直接写lambda 看着比较黑魔法
		auto deletor_i = [](int*) ->void {return; };
		unique_ptr<int, void(*)(int*)> ptr4(new int(1),deletor_i);
		//但是允许作为函数返回值返回
		{
			auto make_unique_m = [](int i) {return unique_ptr<int>(new int(i)); };
			unique_ptr<int> unique_m;
			unique_m = make_unique_m(2);//好像是move 构造函数
		}
		{
			//weak_ptr 可怜的家伙 不能掌握自己对象的生命周期 可能用着用着就没了
				//应该是对get的一种妥协，不让别人来直接使用指针
			weak_ptr<int> p10 = p5;//
			p10.use_count();//返回的p5的count
			auto p100 = p10.lock();//其实是返回shared_ptr 如果没有返回空shared_ptr
			
			
			StrBlob strb = {"aa","bb","ccc"};
			StrBlobPtr strptr(strb);
			auto ts = strptr[1];
		}
	}
	//12.2 动态数组
	{
		//new 和 delete 一次分配一个 可以先多分配点 用的时候再给它
		//allocator 类 先分配 但不初始化的样子
		//但是基本都不用使用动态分配数组 使用vector 基本上就够了
		int *pia = new int[10]{1,2,3,4,5};//返回的都是首地址的指针而已
		new char[0];//合法的非空 指针 但是解引用就会有问题
		//释放
		//delete[] pia;
		//unique 专属 数组版本
		unique_ptr<int[]> pib(pia);
		pib[2];//可以使用下标 但是不能使用.  ->
		//shared_ptr 麻烦一些 没有提供重载版本 得自己管理
		shared_ptr<int> pic(new int[10]{ 1,2,3,4,5 }, [](int* p) {delete[] p; });//毕竟对它来说 它也只是一个首字母而已
			//使用更搞笑了……
		(pic.get() + 5);//相当于[5]的操作
		//allocator 类
		allocator<string> string_alloctor;
		auto p = string_alloctor.allocate(10);//创建了10个未初始化的空间哦
		string_alloctor.construct(p, 10,'c' );//通过它创建1 一个 10 个c的string
		//嗯 p 已经是一个 string了
		string str_b = *p;
		string_alloctor.address(*p);//就很迷 这个只有值能知道地址 ？是一个查找操作？
		//然后又把它析构掉
		str_b = *p;
		string_alloctor.destroy(p);//析构掉了
		//必须先调用destory 再调用deallocate 函数 
			//因为要确保函数被正确析构 这样的话一些收尾工作能被正确的执行到
		//string_alloctor.deallocate(p, 10); //这样也太不安全了吧
		//对于未初始化的部分 还有其他操作
			//但是都需要迭代器 意思是要先有那么一个容器来存储值
				//但是都有容器了 其内部必然也是动态内存 干嘛非要来拷贝到这儿呢，还占用连续内存空间，用vector不香么？属实有病？
		vector<string> data = { "hello","world" };
		uninitialized_copy(data.begin(), data.end(), p);
			//但是这样快啊 不用调用构造函数 直接拷！
			//但是如果内部有指针 那特么不就直接浅拷贝？
		//问题来了 vector 这些为什么用指针？
			//因为啊 赋值的时候是深拷贝
				//除非是QString 是不修改不拷贝
					//因为那些非const 函数吧估计是
			
	}
}

StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end() {
	return StrBlobPtr(*this, data->size());
}