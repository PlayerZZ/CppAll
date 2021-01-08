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
		j == ++i;
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
		char contorl = 'c';
		switch (contorl)
		{
		case 'a': case 'b':case 'c':
			cout << "contrl type";
			int a = 0;
			break;
		case 'd':case'f':
			a = 10;
			cout << "hehe";
			break;
		default:
			break;
		}
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