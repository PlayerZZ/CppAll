#pragma once
//һЩc++ primer�Ĵ���
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
//#include <concurrent_priority_queue.h> ���Ǹ�ʲô���⣿
//#include <priority_queue> //����ְ�������
#include <algorithm>
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
	//unsigned units_sold = 0;//���ڳ�ʼֵ
	//unsigned units_sold(0);//����ʽ ������{}
	unsigned units_sold{ 0 };//���ڳ�ʼֵ,����ֻ�Ƿ�Χ�仯��û�о��ȶ�ʧ ����Ҳ������
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
		//������Χ�ı�ʾ����δ�������Ϊ
		//�޷���תΪ�з��� ������ΧҲ��δ�������Ϊ
		//��֪ʶ int��λ��ȡ���ڲ���ϵͳ ��ν���16λ ���32λ��2���ֽڣ�4���ֽڣ�
		//����ֵ���� ���ε�����ֵ������ �з�����
		// \n \t ����ת������ Ҳ������ascii���ʾ \123 \x3a ��������ʽ
		auto l1 = L'a';
		auto l2 = u8"hhh";
		auto l3 = 46ULL;
		auto l4 = 1E-3F;//��ѧ���㷨?
		auto l5 = 15.5L;
	}
	//2.2 ����
	{
		//�б��ʼ��
		auto v1 = { 0 };
		int v2 = { 3 };
		//float v3{ 1.1 };//���о�����Ϊ����ȱʧ
		double v3{ 1.3 };
		//�����ں����ڲ��ı��� ���ᱻ��ʼ��Ϊ0
		//�ᱨ����
// 		int o;
// 		std::cout << "o value:" << o << std::endl;
		//�����Ͷ������
		extern int i;//˵����Ҫ�������ط���i
		//�����i����externҲ����ֱ��������Ϊֱ�Ӿ����ļ����� �������dll ��̬������Ͳ�����
		cout << "extern i:" << i;
	}
	//2.3 �������� ָconst & * ��Щ
	{
		//����
		int int1 = 123;
		int &int2 = int1;
		//ָ��
		int *int3 = &int2;//���õĵ�ַ���������ö���ĵ�ַ
		assert(*int3 == int1);//������
		//void * ��ָ�����ָ���������
		int *p = nullptr;//�������������
		int *p1, int6;//ǰ����һ��ָ�� �����Ǳ���
		int **pp1;//ָ��ָ���ָ��
	}
	//2.4 const �޶���
	{
		const int a = 10;
		//������ļ���ͬʱ����const ������ʱ����ʵ�Ǹ��Բ���ͬ��
		//���ʹ����extern �Ļ��Ϳ��Լ���Ƿ��ض�����
		//const ������
		int a1 = 20;
		const int &a2 = a1;
		const int &b = a;
		//ָ���const
		//int *const c1 = &a;// ���� �����const ֻ��˵������󲻿��޸�Ϊ����ֵ
		//�ײ�const ���Եײ���ʵ�������㡱��//������const ��������ߵĶ���
		int * const const_diceng = &a1;
		//����const
		int const* c1 = &a;//���ָ���ָ���ǿ����޸ĵ�
		int const* const c2 = &a;//������ Ҳ�����޸�
		const int *const c3 = &a;//�ȼ��ڵ�һ��д�� ��������д����淶 �����
		//����const ����д������
		//constexpr ����ı��ʽ��ʵҲ�ǳ������ڱ�����������ɵļ������
		//������ vs2015�ǲ�֧�ֵĹ���
		//const constexpr ��Ϊ�������Ͷ������� ���Կ���˵������ֵ���� literal type ������˵����ʲô����
		nullptr;
	}
	//2.5���ݴ���
	{
		//���ͱ��� type alias
		typedef double wages;
		typedef wages base,*p;
		{
			//��Ч��
			typedef double wages, base, *p;
		}
		{
			//�ȼ���
			using wages = double;
		}
		//ָ�������˼�� ����p��ָ�� const ֻ�������� �������������ĵײ�
		double d1 = 12.4;
		const p p1= &d1;
		const p *p2 = &p1;
		
		//auto ���� ����ͨ�����ַ�ʽ�鿴����������
		const auto &auto_value = 214;//��Ϊ������ʵ�����������ʱ���� ���������������
		//decltype �����ƶ�
		decltype(1) x;
		//decltype([=] {return 1; }) x;//����������ͨ��lambda �ƶϷ���ֵ��
		auto func1 = [&](int x1) -> decltype(x1){return 1; };//ͨ�������ƶ�ָ����������
		//���� Ϊɶָ���ȡֵ���� �������á������ǽС���ָ�롱��?
		//decltype(*p) ����Ľ����ò���֮������һ�� ���ã� ������ֵ����
		decltype((d1)) dd1 = d1;//˫�����ű�Ϊ����
	}
	//2.6 �Զ�����������
	{
		
		//������ɺ��зֺ� ��Ϊ��Ԫ��ԭ�򣬶�����������
		Sale_data  sale_data1,sale_data2; 
		ifstream fin("sale_data.txt");
		ofstream fout("sale_data2.txt");
		fin >> sale_data1;
		fout << sale_data1;
	}
	//2.7 �����Լ���ͷ�ļ�
#ifndef XXX_XXX_H
#define XXX_XXX_H
	//��д�Լ���ͷ�ļ� ������Ǽ򵥵ķ��ض���ı���
	//Ԥ���������� ������������� ��ʵֻ��˵������Χ�ھ���Ч���൱��������ļ���ȫ�ֱ�����Χ������˵��������ȫ���ˣ�����Ҫ�������е�
#endif
}

inline void chapter3()
{
	//3.1 ʹ�������ռ�
	{
		using namespace std;
		cout << "";
		//ͷ�ļ��в�Ӧ����using namespace ����Ϊ����������ֳ�ͻ
	}
	//3.2 ʹ��string
	{
		string s1 = "sgsg";
		string s2(10, 'a');
		string s3 = { 10,'b' };
		string s4{ 10,'c' };

		//ֱ�ӳ�ʼ�� ��ָ���� = �ŵĳ�ʼ��
		string s5{ "sgg" };
		//������ʼ����ָ�� = �ŵĳ�ʼ��
		string s6 = "heloo";
		//���ֵһ����һ����ʱ������������ʼ���Ƚ�ֱ�� ����s3
		string s7 = string(10, 'd');
		//string�Ĳ�������
		cout << s1;
		//cin >> s2;
		//getline(cin,s3);
		s4.empty();
		auto size_t1 = s5.size();//��һ��unsigned ���͵�
		s6[0];
		s1 + s2 == s3 + s4;
		"s6" + s6;//��Ϊ�����������ƶ�ǰ���Ϊstring,����Ҫ����������һ��string ����ת��
		//�ַ�������ֵ ������string ����
		//�ַ��Ĳ���
		char c = '0';
		isalnum(c);//is alpha numuber?
		isalpha(c);
		isdigit(c);
		iscntrl(c);
		isgraph(c);//�ǿո��
		isspace(c);//�հ��ַ�
		islower(c);
		isupper(c);
		isprint(c);//�ɴ�ӡ
		isxdigit(c);//16����
		tolower(c);
		toupper(c);
		//��Χfor ѭ��
		for (auto& c:s1)
		{
			c = toupper(c);
		}
		//�±�Խ��Ĳ���δ����

	}
	//3.3 ʹ��vector
	{
		//��ģ�� ֻ�ж���ʱ�Ż���С�ģ�����ʵ����������
		vector<string> v1 = { 10,"abc" };
		vector<string> v2 = { "aaa","bbb","ccc" };
		//vector<string&> v3;//����ʹ�����õ�������������Ϊ�����ڼ�Ż��飬���Ա�д��ʱ���ȻҲ��������
		vector<vector<int> > v4;//c++11֮ǰ��Ҫ���һ���ո���>>�м� ��Ȼ�ᱻ��Ϊ�������������
		//�������ʼ��
		vector<int> t1;
		vector<int> t2(t1);
		vector<int> t3 = t1;
		vector<int> t4(10, 110);//��һ��Ϊ�������ڶ���Ϊ��ʼ������
		vector<int> t5(10);//��ʼ��10 �� 0
		vector<int> t6 = { 10,10 };
		vector<int> t6_1 = { size_t(10),10};//�����᲻�������壿 ������1��2 ����1,2 ����Ԫ�� ���־�������Ԫ�� ԭ����
		//ԭ������ ����Ϊ����ֱ�ӵ����б� ������ִ�в��� �Żᵱ�������� ����(n,value)
		vector<int> t7{ 5,6,7,8 };
		//���Ԫ��
		t6.push_back(9);
		//���Ҫ���Ԫ�� ����ʹ�÷�Χfor ѭ�� ��Ϊ�ڲ���ָ�롰���ܡ���ϵ�
		//vector ����
		t1.empty();
		vector<int>::size_type size_t_3;//��ģ��ʵ���������Զ���
		auto size_t_2 = t2.size();
		t4.push_back(10);
		t5[0];
		t6 = { 10,11,13 };
		//t7 = t5 + t6; //û��+ - ����
		//�������û�ж��� > < �Ȳ�������û��������vector���бȽϲ���
	}
	//3.4 ������
	{
		vector<string> v_s(10, "abc");
		auto b = v_s.begin();
		auto e = v_s.end();//β��
		//��׼���� ����������
		*b;
		b->size();//������ʹ�ó�Ա
		++b;
		--b;
		b == e;
		b != e;
		//���͵�ԭ�� ��== ��!= �Ƚ϶�
		//����������
		vector<string>::iterator it = v_s.begin();
		vector<string>::const_iterator cit = v_s.cbegin();
		it += 5;
		//vector ��string ����������֧�ֵĲ���
		
		it + 2;
		it - 2;
		it += 2;
		it -= 2;
		it - b;
		//���ֱȽ�����
		auto mid = v_s.begin() + v_s.size() / 2;
	}
	//3.5 ����
	{
		//���ӵ���������
		int *ptr[10];// ���������ҽ�ϣ�������������
		//�����ָ�� ����Ҳ��β��ָ��
		//����ʹ��begin
		int array[10] = { 1,2,3,4 };
		auto b = begin(array);
		auto e = end(array);
		//c �ַ���Ҳ������
		char str[20] = "hello";
		char str2[10] = "world";
		strlen(str);
		strcmp(str, str2);
		strcat(str, str2);
		strcpy(str, str2);
		//�����ʼ��vector
		vector<char> vc(begin(str), end(str));//������������ɶ�ء��� ����ܺ��棬��Ϊ������world\0 �ͽ����ˣ�����֮ǰ��Ҳû���������
		int i = 0;
		//��ά���� ʹ�÷�Χfor ѭ�� Ҫʹ��auto & ��Ȼ�ͽ���Ϊָ�룬�Ͳ�������
		//��ά�����ڲ���һ���������ģ�������ʵ���Ƕ������ļ���
	}
}
/**
 * ������
 */
inline void chapter4()
{
	//4.1 ����
	{
		//���ʽ
		//���������� �Ա��ʽ��ֵ �õ�һ����� 
		//�������ͱ�������򵥵ı��ʽ
		//����� + ������� �Ǹ��ӵı��ʽ
		//һԪ����� 
		//ȡ��ַ ������ 
		//��Ԫ�����
		//���߶��б���

		//�����������������
		//��������ת��
		//ͨ��ת��Ϊ��ͬ�Ķ����������� ת�������е���
		//���� <-> ������
		//ָ�벻��תΪ������
		//���������
		//��ֵ����ֵ = ����ߵĺ� = ���ұߵ�
		//һ�����ʵ�� ���� �ȿ�������ֵ�ֿ�������ֵ�����Եþ���������������
		//��ֵ����ʹ����ֵ����  ������ֵ���ܴ�����ֵ
		// a = (b = c) // b = c �Ľ��Ҳ�Ǹ���ֵ�������ܱ�������ֵʹ�ã��������� 
			//������ʵ�ǿ���д�� (b = c) = a ��Ϊb=c ��Ϊһ����ֵ�Ļ�
		// (p = *a) ֻ���Ǹ���ֵ��
		int a=1, b=2, c=3, *p;
		(a = b) = c;
		(p = &a) = &b;//����˵��һ����ֵ�� ��Ϊ����ǵ�ʽ��
		//&a = &b;//�����Ͳ����� ��Ϊ&a ���ص���һ����ֵ
		int i = 0;
		//���ý����� �±� ������������ ��ֵ�����һ����ֵ
		*p = 10;//������ʵ����*�ŵĶ�����ֵ��
		//���õ�������++ -- ������������ֵ����Ҳ����ֵ
		//���ȼ� �����
		//��֮�����žͶ���
		//��ֵ˳�� cout <<i << ++i; ��δ������
		//�����Ѷ���˳��� && ||  ?:   ,  �����֣�������
		//������һС�� �ܶ���û�ж�Ӧ���� ��ɶ��Ŷ
	}
	//4.2 ���������
	{
		//+ - * / % +-(����)
		auto a1 = -11 / 2; //һ��ȥ��С���� ��������
		auto a2 = -11 % 2;
		auto b1 = -11 / -2;
		auto b2 = -11 % -2;
		auto c1 = 11 / -2;
		auto c2 = 11 % -2;
		//���� ���c1 *-1 + c2 ��ȫ�Ͳ�����11�˰�
		// ��ôӦ����ô������������أ� �Ϳ�m%n ��ʱ�� m n m Ϊ�� n Ϊ���ŵ�ʱ��
		int d=0;
	}
	//4.3�߼������
	{
		//��·��ֵ��
			//������Ѿ������ʱ�򲻻����ұߵ�ֵ

	}
	//4.4 ��ֵ�����
	{
		//�����һ����ֵ����
		//��ֵ���� �����ҽ����
		int a, b;
		a = b = 0;
		//����� ���ȼ��ϵ� �����Բ��������ִ�У�
		//��������� --*= &= <<= λ������
	}
	//4.5 �����͵ݼ�
	{
		int i = 0, j;
		j = ++i;
		string str1 = "test";
		auto str_iter = str1.begin();
		while (str_iter!=str1.end())
		{
			//�ȵ��� �ڽ�����
				//������ �Ǻ�����������ִ�����Ż����ɹ���
			cout << "iter: " << *str_iter++;
		}
	}
	//4.6 ��Ա���ʷ�����
	{
		struct TempStruct
		{
			int a;
			int b;
		};
		TempStruct *temp1 = new TempStruct();
		temp1->a = 11;
		temp1->b = temp1->a;
		//���������ȼ�̫���� ����*p.size() ���ǲ��Եġ��� ��(*p).size() 
			//���Բ�����p->size() ���ֲ�����
		
	}
	//4.7 ��������� ����Ԫ��������
	{
		string name = "zhangsan";
		string name1 = name == "" ? "������" : name;
		//�����þͲ�ҪǶ���� д��ˬ���ŷ�
	}
	//4.8 λ�����
	{
		int a = 110;
		~a;//��
		a<<2;//������λ

	}
	//4.9 sizeof �����
	{
		int *p;
		sizeof(p);
		sizeof(*p);//��ַ����Ҫ��Ч ����int�Ĵ�С
		int int_array[10];
		sizeof(int_array);//10 * int ��С ����תΪָ���
	}
	//4.10 ���������
	{
		//���ȼ��� �ȵȺŻ��ͣ� ���յ�ֵ�����ҵı��ʽ
		int a,b=0;
		a = (1 + 1, b+=100, 3 + 1);
		int d = 0;
	}
	//4.11 ����ת��
	{
		//���͹��� ���Ի���ת��
		//��ʽת�� ת��Ϊ��ͬ��������� �ڽ��м��� ͨ����䵽�������������
		float float1 =1.0;
		int a1 = 200;
		auto result1 = a1 / float1;
		//С���� �� int
			//�����ŵ�תΪ�޷��ŵ�
		//�ж���תΪbool
		//��ʼ��ʱ��תΪ������
		//��ֵʱ��תΪ������
		//��������ʱ��ת��Ϊ������ߵ�����
		//ĳЩ��������ʱ

		//����תΪָ��
		int array1[10];
		int *p = array1;
			//decltype ȡ��ַ& sizeof typeid �ĸ�����
		//����ת��
		void * p1 = p1;
		const void* p2 = p;
		//����ָ��ָ���������

		//��ʽת��
		//static_cast<> dynamic_cast<> const_cast<> 
		//reinterpret_cast<> char* ָ��int* �����Ϳ���ֱ�Ӳ���������ڴ�ռ��� ��ǰ����֪���ڴ湹��
	}
}

//���
inline void chapter5()
{
	//5.1 �����
	{
		//���ʽ���
		int a = 9;
		//�����
		;
		//�������

	}
	//5.2 ���������
	{
		int a = 0;//�������� ����swtich if ��ÿ��case������һ�������ţ����ԡ���case��üӻ�����
	}
	//5.3 �������
	{
		//���д���else��ʱ����û����û����ţ��Ͼ�����python ��ͨ���������Ʒ�Χ��
		if (false)
			if (false)
				int i = 0;
		else
			int t = 0;
			
		//�������Ҳ�������� vs�Ļ�ǿ���㲻�ܻ��й���
		//swtich ���
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
		//ֱ�ӱ��벻��
		// case d��֪��a ������û��a�ĳ�ʼֵ��û�б���ȷ��ʼ������Ҫ�Ӹ���ʼ�� ��������ֱ���û����ţ��������ֳ�ͻ
		// ��Ϊ�������ò��� a �еı���ֵ
	}
	//5.4 �������
	{
		//while ���
		int num;
		ifstream fin("sale_data.txt");
		string text;
		while (fin >> num) {
			cout << num;//�����ʧ�� ��ʵ�Ƿ���һ��ostream ���ǿ���ת��Ϊbool �����ṩ����Ӧ��ת��������
		}
		//for ѭ��
		for (int i = 0; i < 10; i++) {
			i += 5;
		}
		//��Χfor ѭ��
		string str("hello");
		for (auto &c : str) {
			c += 1;//�����������ͼ���
		}
		//do .. while �ȸ���һ����˵
		do {
			string str = { "stupid" };
		} while (false);
	}
	//5.5��ת���
	{
		//�൱�ڷ�˳��ִ��
		// break; ֻ��������ǰѭ�� ����switch case��case
			//������������� �ֲ���������㣬����ʹ��ĳ������������
		// continue ������ִ�� ֱ����һ���ֻذɹ���
		//goto ��� ��Ϊ̫����ȫ ��һֱ�����˹���
			//��Ϊ������������ֱ��ʹ���Ǹ�����ξͻᱨ����
	}
	//5.6 try ������쳣���� 
	{
		try {
			throw("just try try throw a exception");
		}
		catch (exception e){
			cout << "let me see see,what exception:" << e.what();
		}
		//c++ ��û��finallyŶ ���Ե�������������������ȥ��һЩ�ر�Ӧ����������
// 		finally {
// 			
// 		}
		//��׼�쳣��
		//exception ����쳣
		//runtime_error ������ʱ���ܼ����Ĵ���
		//range_error ����ʱ���󣬼��㳬����Χ
		//overflow_error ��������
		//underflow_error ��������
		//logic_error �����߼�����
		//domin_error �������������?
		//invalid_argument ��Ч����
		//length_error �������ĳ���
		//out_of_range ʹ�ó�����Ч��Χ��ֵ

	}


}
//����
inline void chapter6()
{
	//6.1 ��������
	{
		// 	int func(int a, int b) {
		// 		return a + b;
		// 	};
			//����1 ����ֵ ���� ������
		auto functiona = [&](const int &a, const int &b) ->decltype(a + b) {return a + b; };
		//���������� ��������
		auto functionb = [&] {return functiona(10, 20); };
		//�βκ�ʵ�� ���õ�ʱ������Ĳ�����ʵ�Σ����ǵ��õĺ������ڲ����β�
		int i1 = 100, i2 = 200;
		auto i3 = functiona(i1, i2);//i1,i2 ��ʵ�Σ�a,b ���β�
		//�������ܷ��� ���� �� �������� �����ǿ��Է�����ָ��(����ָ��ͺ���ָ��)
		//�ֲ�����
		//��������
		//�βκͺ������ڲ��Ĳ��� ���Ǿֲ����� 
			//���Ƕ�̬����Ķ���ͨ��ָ����������һֱ����
		//�ֲ��������������ص�
		//�Զ�����
			//ֻ���ھֲ� �������Զ����ٵĶ���
			//�β�Ҳ�����������
		//�ֲ���̬����
		auto functionc = [&]() {static int cnt = 1; return cnt++; };
		functionc();//��һ��ִ��ʱ��ʼ��
		functionc();//֮��ֻ����ã������ٽ��г�ʼ������
		auto cnt = functionc();
		//�������� ͷ�ļ��н��к�������
		//����ԭ�� 
		// ����ʽ���� 
		//��������Ӷ���ļ�
		//��main �����������ɿ�ִ���ļ�
		//��������Ϊ.o �ļ� cc -c xxx.cc
		//cc xxx.o ����.o -o main//����main.exe ����linux��ִ���ļ�
	}
	//6.2 ��������
	{
		//����Ϊ ����ʱ ���ô��� �����õ���
			//���Ա��⿽������
			//���ض����ֵ
				//�Ͼ�����ֻ�ܷ���һ��ֵ
		//����Ϊ ��ͨ��ֵ ֵ���� ��ֵ����
			//����ı�����ʵ�ε�ֵ
				//����Ҳ���Ǹ�������û��ʵ�����֮���
				//��������ڲ���ָ����ʽ�� ���ǻ�ı�ֵ��
		//ָ���β� Ҳ���Ըı�����ֵ
		//const �β�
		// ����const �ᱻ���ԣ���Ϊ��ͬһ���������ṹ���ع����ᱨ��
		//ָ���������const
// 		int *p1 = 1;//����
// 		const int *const p2 = 1;
		const int &yinyong = 1;//��Ϊ�Ҳ���γ�һ��const ����
		//�����β� ֻ�ܱ�ʾ������������һ�����ܵ���ô������� �ȼ���һ��ָ��
			//ָ��ĳ��Ԫ����Ϊ��β
				//�ַ������� \0 ��β
			//ʹ��begin end ����
			//���ݳ�����Ϊ����
		//���������Ϊ���á��� ֻ��д�����е��鷳
		auto functiona = [](int(&arr)[10]) {
			for (auto &a : arr) {
				cout << a;
			} 
		};
		//����Ҳ������const�� ����
		//��ά���� ���Ե�һά�� Ϊָ��
		auto functionb = [](int(&arr)[10][20]) {
			//������ʵҲ����������?
		};
		//main ���� �д����������
		//int main(int argc,**argv); //��ʵ��������˵�ĵ����� ������һ������argc ����
		//���пɱ��βεĲ���
		initializer_list<int> a1{1,2,3};
		auto s1= a1.size();
		auto s2 = a1.begin();
		initializer_list<int> a2 = a1;//Ԫ�ؽ��Ṳ�� ���´��,��Ϊ�ǳ��������������޸ģ�����Ҳû�������
		//�����ԣ�ֻ��ʹ��һ��ֵ
		
		//ʹ��ʡ�Է� https://my.oschina.net/SHIHUAMarryMe/blog/793155
		//c++ primer ����ô�� �����ҵ�һ�����ͻ�������������
		auto functionc = [](const int& num, ...) {
			//�������...��ν����أ� ����Ҫʹ�õݹ�����
			va_list args;//�൱����һ���ڴ�أ�Ȼ������������Ͷ���
			int a = 0;
			va_start(args, a);
			va_list args2;
			va_copy(args2,args);
			va_end(args);//����Ϊ0 ��ʾ���ɵ�����
			//�ؼ��ǻ����Լ����ƶϵ�����ʲô���͡��� ���²���ģ���ǲ����õ���
		};
	}
	//6.3 �������ͺ�return ���
	//����ֵΪ���û���ָ���ʱ��Ҫ��һ���Ƿ����ֵֻ�Ǻ����ڲ��ģ�����ǾͲ��У�������ǿ���
	//�������õ�ʱ����Կ���һ����ֵ
	//���Է��� return {"",""} ������
	//���������ָ��  д�������� β�÷�������
	//auto func() -> int(*)[10] {} //����һ�� int[10] ��ָ��
	
	//6.4 ��������
	{
		//const_cast�ڷǳ������� ʹ�ó����������ҷ��طǳ�������ͨ��Ϊ���ã���ʱ�������õġ�
		//���ƥ��� ������
		// ���ֳ�ͻ ��ͬ���������������ָ��� �޷����ɺ�������

	}
	//6.5 ������������
	{
		//Ĭ�ϲ���
		//���������� constexpr
		//���԰��� 
		assert(11 == 11);
		//NDEBUG��
	}
	//6.6����ƥ��
	{
		//�ж������Ե�ʱ�򣬿���ָ���������������������� д�����е��鷳������

	}
	//6.7 ����ָ��
	{
		//bool (*p)(int,int)
		//���غ����Ը��ݺ���ָ������� ��ƥ���Ӧ�Ĳ���
		//����������ʵ����תΪ�ض��ĺ���ָ�������
		//static_cast<void(*QMaincWindow::)(int)>(&MainWindow::clicked) 
			//��Ϊclicked �������ź� ���Ե�������������
		//���� ����ָ��� ���� ����͸�����
		//int (*p(int))(int)
			//д��β�÷������� �������
			// auto p(int) -> int(*)(int)
		//decltype �������� ���ص��Ǻ������� ����ָ�롭�� ���Ի����Լ���һ��

	}
}

class NormalClass {
public:
	int add(const int& a, const int& b) const { return a + b; };
	//�ѵ������Ĳ�����ô��?
	int add(const int& a, const int& b) {
		//ʹ��const �ε� ΪɶҪתΪ�����أ� ����תΪ��ָ���� ��Ϊ̫���˰�����
		//return static_cast<const NormalClass *const>(this)->add(a, b);
		//ͨ����Ҫ��һ��const_cast
		return static_cast<const NormalClass &>(*this).add(a, b);
	};
	int sum = 10;
};

//��7�� ��
inline void chapter7() {
	//���ݳ���
		//�ӿ�
			//���Ⱪ¶�Ŀɵ��ú���
		//ʵ�� ����ʽ���
			//��Ա���� ������
	//��װ
		//ʵ�������ַ���
	//7.1 ���������������
	//����û��ǳ���Ա
	//������û���������û�
	//const ��Ա����
	//��������thisָ�룬����ֵΪΪ�������� �����Ϳ���ʹ����ʽ���� a.b().c().d() ������

	//��ķǳ�Ա����
		//��Ҫ���� ��������ģ��Ͼ�����ÿ����Ա����Ҫ���ҽ���֮��Ķ԰�
		//���ຯ�����ص��� ���ǲ�ֹ���������
		//�����ձ���
	
	//���캯��
		//Ĭ�Ϲ��캯��
			//û���������캯��������һ���޲�����Ĭ�Ϲ��캯��
			// = default Ҳ����ֱ�������������
	//��Ԫ ��ʹ���ⲿ����Ҳ���Է������ڲ��ķ��������ߺ�����������
	//���� ��ֵ �� ����
	//todo ��������ɷ��� Ӧ�ú�����е�
	//7.2���ʿ������װ
	{
		//���ʿ��Ʒ� public private protect
		//strurct ��class ��c++ ����ֻ��Ĭ�ϵķ���Ȩ�޲�ͬ	
			//Ȼ��struct ȴ������һ��ͨ�������Ա�� ���캯��
		//
	}
	//7.3 �����������
	{
		//���Ա��̽
		//���ר������
		class Screen {
		public:
			typedef std::string::size_type pos;
		private:
			pos cursor = 0;
			mutable pos mutable_asset=0;//��ʹ��const ��Ҳ�ǿ����޸ĵ�ֵ�������ɱ����ݳ�Ա
		};
		//screen �ĳ�Ա����
		//const �ͷ� const �����Ĵ��븴�� 
			//�����һ��������do_sth ����,Ȼ������const��
				//�ڷ�const �ڲ�����ʱ���ᷢ����ʽ����ת��
		//����������
			//ǰ������ ͷ�ļ���ֻ�õ�����ָ��������ã�û�о����ʹ�õ�ʱ�򣬿����ȸ���ͷ�ļ�����ô���֣�֮��ῴ����
				//class classa; //����ͷ�ļ�ǰ�� ������include �����
		//��Ԫ��̽
		//��֮�����Ԫ��ϵ
		//����������Ԫ�ǵ����ϵ��A �� B����Ԫ��A ��ô֪����B ������֪����
		//��֪���� B ֪�� Ȼ��A include B  Ȼ��A��֪����
		//���Ա���� ����Ϊ��Ԫ��ʵҲ��һ������·
			//���������Ļ� ��ʵA ҲҪinclude B �����ˣ�
		//��Ԫ������ ��ʵҲ����Ҫ��֪��������ֲ�������Ϊ��Ԫ��
	}
	//7.4 ���������
	{
		//��ʵ����ͷ�ļ��� Դ�ļ���ʵ��ʱҪ�������
		//this ָ����Ա��� �βκͳ�Ա�������ظ�������
		// �������ڳ�ʼ�� �б��ʼ�� ͬʱ����ʱ ���ڳ�ʼ����ִ�в�
		//�������const �������� ����Ҫ��ֵ ����ͨ�����Լ�дһ��
		//��ʼ��˳���붨���һ��

	}
	//ת�����캯�� ����һ���Ƿ�������ʽ����ת����
		//explicit ������ʾ�ĵ��ù��캯�����ܱ���������
		//������ʹ��static_cast<class> ת����ȥ
	//����ֵ������
		//��������һ��constexpr ���캯��

	//��ľ�̬��Ա
	//����static �ؼ��ּ���
	//���Ҫ���ڳ�ʼ�� Ҫʹ��constexpr ���������ֲ����޸���
	//��̬��Ա���� ������Ϊ��Ա������Ĭ�ϲ���
	//ί�й��캯�� ���ǿ���ʹ�ñ�Ĺ��캯������ί��������
}

//�ڰ��� IO��
inline void chapter8()
{
	//iostream fstream cin,cout,cerr >>  << getline
	//��д���ַ�
	//sstream ���ַ�����ص��� wcin wcout wcerr wstring �أ���û�У�
	//�̳л��� ifstream istringstream
	//io �����޿��� ���߸�ֵ����
	ofstream out1, out2;
	//out1 = out2;//�����
	ofstream& out_yinyong = out1;//��ȷ�ģ�����ʹ��ָ������ã�
	//����״̬ 
	istream::iostate;
	ofstream::badbit;//������ Ϊɶ��
	ofstream::failbit;//����ʧ��
	ofstream::eofbit;//�ﵽ���ļ�����
	ofstream::goodbit;//����״̬ ����0
	out1.eof();//��ʵ����iseof �Ƿ��ǵ�����ĩβ
	out1.fail();
	out1.bad();
	out1.clear();//������state ��λ �����Ļ����ܼ������ˣ���Ȼ������еĻ� �����eof �϶����ܼ���������
	auto flags = out1.rdstate();//��������״̬
	out1.setstate(flags);//������״̬ Ϊɶ��ֱ��Clear��
	//failbit �ǿɻָ��Ĵ��� badbit �ǲ��ɻָ��Ĵ��� ĩβeof �� failbit ������
	//���������� ϵͳio����������һ���Զ���һ��buffer Ȼ�������������ǱȽϺõģ�д���ļ���ʵҲ��һ���ģ�����Լ�д��buffer������һ���Ե�д��ȽϺ�
	//unitbuf() �������ڲ�״̬
	cout << unitbuf; //�������  ���Ǻܷ��ľ�����������һ������ �������ǻᱻ�����һ������
	//�Ժ���ʹ��doxygen ���� ����qt�ǲ��ǲ�����������أ�

	//������������ �����»���ʹ��stringstream �ȽϺ�
	string str = "12315 hehe";
	string str1;
	istringstream scin;
	scin.tie(&cout);//���� �������� �ᱻͬʱ���Ҳ�ᱻ ��¼�����������ȥ ���ǿ����� ���Ǽ�¼���ļ���ֱ��һЩ
	//����е����� ���������������ֱ��ʹ��stringstream
	//https://bytes.com/topic/c/answers/63884-stringstream-tie-problem
	ofstream fout("outfile.txt");
	scin.tie(&fout);
	scin.str(str);
	int a;
	scin >> a;
	scin >> str1;
	fout << unitbuf;
	//�ļ��� ios::in out app ate trunc //�ض� binary ������
	//��ʵ���Ǽ���״̬���� �ʹ򿪷�ʽ֮��� �������ֱ�������buffer ��ʵҲû��˵��
}

//ʾ������������
class Data1 {
public:
	Data1() { cout << "Ĭ�Ϲ��캯��������"<<endl; };
	Data1(const int& n) :data(n) { cout << "int ���캯��������" << endl; };
	bool operator<(const Data1& data1) {
		return this->data < data1.data;
	}
	bool operator==(const Data1& data1) {
		return data1.data == this->data;
	}
	~Data1() {cout << "��������������"<<endl;}
	int data = 0;
};

//�ھ��� ˳������
inline void chapter9()
{
	//����Ԫ�ش洢��˳����ʵ�����
	//vector deque list forward_list array string
		//string vector �ڲ����������ڴ�ռ�
			//ʹ���±���ʺܿ�
			//�����ɾ�������Ƚ���
		//list forward_list �ڲ���������ʽ
			//�����ɾ���ȽϿ�
			//�±������Ҫ���� ��Ƚ���
			//�����ڴ濪�� ���ָ���
		//dequeue �ϸ���
			//Ҳ֧�� ������ʣ��ܿ�
			//���� ɾ���Ƚ��� �������˺ܿ�
				//��������Ϊ������������չ�ģ����в�����չ�ռ�
		//array ��c������������棬����һ��size ��������ӡ���
	//����ѡ�� ��ʽ
	//Ĭ��vector����
	//СԪ�� char int ֮����ų� list forward_list
	//������� ʹ��vector deque
	//�м���� ѡforward_list ����list
	//ͷβ����Ƚ϶� ʹ��deque
	//һ��ʼ��Ҫʹ�ò��룬֮�����������
		//���������ģ�ʹ��vector Ȼ���������
		//������� ֱ��ʹ��list ���� Ȼ��תΪvector
			//���ֻ��һ������ �����ַ�ʽ�϶�����õ���
	//˳������ �������� ��������
	//��������
		//˳������ Ҫ�����ʹ��Ĭ�Ϲ��캯��
		//��������Ҫ�ܱȽϴ�С
			//����ҲҪʵ�� < С�ڷ��ŵ�����
	
	//��������
	//���ͱ���
	vector<string> vs{ 10,"hello" };
	vector<string>::iterator it = vs.begin();
	vector<string>::const_iterator cit = vs.cbegin();
	vector<string>::size_type s1 = vs.size();
	vector<string>::difference_type d_ = vs.begin() - (vs.begin() + 2);
	vector<string>::reference vsr = vs[0];//�����ڲ����͵����� ,����Ϊʲô�������cv::Cstring�أ� �ѵ������������Ⱦ��
	vector<string>::const_reference cvsr = vs[0];//const���õ�д��
	//���캯��
	vector<string> vs2;
	vector<string>vs3(vs2);
	vector<string> vs4(vs.begin(), vs.end());//ֱ��ֵ��������������citerator Ҳ�ǿ��Ե�
	vector<string> vs5(vs.cbegin(), vs.cend());//���ɣ��Ͼ����ڲ������������޸�
	vector<string> vs6{ "what","fuck","day","is","today" };
	//��ֵ�� swap
	vs3 = vs2;
	vs3 = { "he","he","ha","ha"};//�൱���ұ��Ƿ�������ʽ����ת���İ� �����һ����ʱ������Ȼ���ٸ�ֵ��vs3
	vs3.swap(vs2);//ֱ��ʹ�ý������� �����������ֵ���������ڲ���ָ������˽�����
	swap(vs3, vs);//�ȼ���������
	//��С
	vs2.size();
	vs2.max_size();//�ǲ��� �Ѿ�������ڴ��أ�Ӧ�ò���ֻ���������������
	vs3.empty();//is_empty ����д���ҷ��ֻ���д��is �ȽϺã���Ȼ֪��clear ������գ��������Ǿ��ò�ˬ�� empty ������Ϊֻ�Ǹ����ݴʰɣ����ԾͲ���Ҫis?
	//��� ɾ�� Ԫ��
	vs.insert(vs.end(),"??");//���������ÿ����ʵ�ֲ�ͬӦ���� 
		//����϶��ǵ�ָ��һ�����Ϊʲô����Ȼ����ô���뵽����λ��
	vs.emplace(vs.end(),"!!");//���Ʋ��룬���ǲ����ù��캯����ֱ��ʹ�ò��� �ȵ������ʱ�����ڲ�ʹ��new ֮��Ķ��� �����Ļ����Ը��Ż�
	vs.erase(--vs.end());//���ĳ��Ԫ�� �Ͼ���������һ��Ԫ�� �϶���û�취ɾ���İ�ι
	vs.clear();//ֱ�Ӿ������ ����Ӧ��ֻ�Ǽ����������� 
	//��ϵ�������
		//ǰ�����ڲ��Ķ���������ʵ����
			// < (С��)������
	vs == vs2;
	vs != vs2;
	vs < vs2;
	vs >= vs3;
	//��������ȡ
	vs.begin();
	vs.cbegin();//����const ������
	//����������Ķ����Ա forward_list ��֧��
	vector<string>::reverse_iterator rit = vs2.rbegin();
	vector<string>::const_reverse_iterator crit = vs2.crbegin();//�������begin ��ʵ���ǰ� ע�ⲻ��β��Ŷ
	//������
	//��������Χ 
	//��պ����� ��ȡ�Ҳ�ȡ
	//��ʵ����[begin,end)
	//���begin == end ���ǿյ�
	{
		vector<string> vs = { "heelo","workr" };
		for (auto it = vs.cbegin();it!=vs.cend();++it)
		{
			cout << *it;//������Ҳ��ʹ�����ƽ����õĲ��� ������Ӧ�������ص���
		}
		//�������һ��
		for (auto it= vs.crbegin();it!=vs.crend();it++)
		{
			cout << "reverse  " << *it;
		}
		//��������������ڲ������� һ��Ҳ��ʹ��auto ����ȡ�İɣ��Ͼ�û��˭��Ҫ֪���������Ͱ� ֻҪ����ô���������
		//ʵ����Ҫ������ʱ��ֱ��ʹ��decltype ���������������ˡ��� ��Ȼ����û��ô�ù���
		//��������ͳ�ʼ��
		vector<string> vs1(vs.begin() + 1, vs.end());//ʹ�õ��������г�ʼ���������Ļ���ʵ�൱�ڽ�ȡ�����ˣ��㿴c++ �Ľ�ȡ������ʵ���ǳ�ʼ����������
		vector<string> vs2(100);//ʹ���ڲ������Ĭ�Ϲ��캯�� ��ʼ��100��
		vector<string> vs3(10, "hehe");//ʹ�����Ĺ��캯�����й��죬��ͻȻ�뵽���Ĺ��캯���������������
		string str(10, 'c');
		//vector<string> vs4(20, (10, 'c'));//���������е� ����ʹ�ö�����ĳ�ʼ���� �������ж�������Ĺ��캯�����ʹ����?
		vector<string> vs4(20, string(10, 'c'));
		vector<string> vs5 = { 20,{10,'c'} };//����ͨ��{} ����ʼ��strig  ������ȻҲ�У����������������Լ��ͱ��˶������������Ҳûʲô�ô�����

		//�б��ʼ��

	}
	{
		//ʹ��assign ���� �൱�ڿ���ʹ�����ݵĲ��� ����һ��һ��
		vector<double> vd = { 1.1,1.2,1.3 };
		vector<int> vi;
		//vi = vd;//����Ǵ���Ķ԰�
		//vi = vector<int>(vd.begin(), vd.end());//�������Ҳ���ԣ�
		//vi.assign(vd.begin(), vd.end());//������������������warning ��������Ϊ���ͽضϣ�
		
		//swap �����൱�����ڲ���ָ��ָ�����˸ı�
			//����ԭ�ȵ�ָ�� �� �����������ã��������ǵ�������ˣ�����һ��������ˡ�
			//�൱�����ǻ��˸����ˣ����� ��Ȼ�������Ƕ����൱��������һ���� ����ļҾ��Ѿ����˸�����
		//������ == ��ҪԪ�������еȲ���
			//����������Ҫ < ����
	}
	{
		//˳����������
		//���Ԫ��
		vector<string> vs1 = { "hello","world" ,"giaogiao"};
		vs1.push_back("233");
			//ʹ�õ��Ƕ���Ŀ���
				//��������233 ����string Ȼ���ֱ�����һ�� ���Ե������ι��캯���ĵ��ã�����һ��������������
		vs1.emplace_back("!!!");//�������һ���ȽϽ�ʡ�ڴ�İ汾 ����֧�ֲ������Ĳ���
		deque<string> ds1 = { "hell" };
		ds1.push_front("what");//ֻ�в�������֧�ֹ� vector ��Ϊͷ����Ƚ����Ͳ�֧�� ��������ʹ��insert ����������������
		vs1.insert(vs1.begin(), "haha");//����൱��Vector�� push_front �������Ƽ���ô�����ԾͲ�ʵ��
		vs1.insert(vs1.end(), 10, "hehe");//����10��hehe
			//n Ϊ 0 �򷵻���pos �ĵ�����
		vs1.insert(vs1.end(), ds1.begin(), ds1.end());//��deque �е�Ԫ�ز������
		vs1.insert(vs1.end(), { "hello","world","again" });//��������ͬԪ��
		vector<Data1> vdata = {};
		vdata.push_back(1);//Ϊʲôû����ʾ�ĵ������ι��캯���� ��Ϊ�ڲ����Ż�����Ϊʲô������������������
		vdata.emplace_back(10);//����ȷʵ emplace ��ֻ������һ��
		//Ԫ�ط���
		auto &data1 = vdata.back();
		auto &data2 = vdata.front();
		try
		{
			auto &data3 = vdata.at(3);//���ʧ�ܷ���ɶ�� ���׳��쳣 �����������־�û���׳��쳣 ֱ�ӱ���
		}
		catch (out_of_range e)
		{
			string what = e.what();
			cout << what;
		}
		
		
		auto &data4 = vdata[0];
		//ɾ��Ԫ��
		vs1.pop_back();
		ds1.pop_front();
		//vs1.erase(vs1.end());//��Ϊδ����
		vs1.erase(vs1.end() - 1);//����end()
		vs1.clear();

		//forward_list�Ķ������
		//�����������Ĳ�����ʵ���� insert_before ������ĳ��Ԫ��֮ǰ���� forward_list ����ĳ��Ԫ��֮����� insert_after
		//������һ��before_begin�ĵ�����
		forward_list<string> fstr = { "11","22","33" };
		//fstr.insert_after(fstr.end(),"hehe");// ���ĵ��������ṩ�Ӳ��� ֻ�ܴ�ǰ������� ����Ҳ��֧��--���� ����ֻ��++
			//�����Ϊ�Ǻ�� ���Բ���������
		//ֻ֮ǰǰ��ĸ��ֲ��� ���治֧�� ���������������֧�ֺ����Ӧ��Ҳ�����²Ŷ԰�����
		//�ı�������С
		vs1.resize(15,"oo");//�������Ԫ�ض������������ �����Ҫȫ�����ĳ��Ԫ�� ��ֻ�ܿ�����ֵ��

		//�������������õ�����ʧЧ
			//vector �� string ��˳��洢�������ؿ��ܷ������µ��ڴ�ռ䣬�������������ʧЧ��
			//deque ʹ�õ�Ӧ���ǲ��������ռ䣬 �ټ���list ����ɶ��
				//���ƶ�ά������ô������������
		//��д�ı�����������ѭ������
			//ɾ��������֮�� ��Ҫ������������� �Ͼ�ɾ�� �� insert ���᷵��һ��ָ���
			//�жϵ�ʱ��Ҳ��Ҫ�ö������������end ��Ҫֱ��ʹ�ö����end
			//��Ȼ�����˺������õĿ������������������ʵ�����������
		//vector������
			//����Ҫ���·����ʱ�� ͨ��������һЩ�ڴ� �����Ͳ���ÿ�ζ�ȥ�����ڴ�ռ���
		auto t1 = vs1.capacity();//�������ڿ���װ���ٸ�������� ��size()��һ��
		vs1.shrink_to_fit();//�����������ø�sizeһ����
		vs1.reserve(t1+100);//�������ٿ���װx���Ŀռ�
			//����ȵ�ǰsize СӦ�ò���������Ϊ��
		//string �Ķ������
		{
			const char* cp = "what the hell";
			string str1(cp,7);
			string str2(str1, 1);//������str1 [1,-1) ������Ȳ�����Ļ����ǻ��׳��쳣��
			string str3(str1, 1, 3); //������str1[1, 1+3] �������Ҳ����࿽���� �ܰ�ȫ
			auto str4 = str1.substr(1, -3); //����һ���ǳ��� ����Ǹ����������� �����ӻᱻ����һ���ܴ����������
			str4.insert(str4.size(), 10,'c');//����ֱ��ʹ���±� �����ǵ�����
			str4.insert(str4.size(), "heiheihei");
			//appen �� repalce ����
			//append �� + �ǵȼ۵İ�
			str4.replace(0, 3, "hehehehehehehh");//��ǰ������ĸ������ô��һ��
				//û��ֱ�ӵ��滻�ַ������� ��Ҫ�Ȳ��ң�
			//string ����
			auto pos1 = str4.find("hehe"); //���Ҫ�滻 ����ʹ�ã��ȼ���
			auto pos2 = str4.find("hehe",0);//pos Ҫ��Ҫ+1��
			auto pos3 = str4.find_first_not_of("hehe", 0);//�ҵ��Ǻ����������ô���ҵ�
			auto pos4 = str4.find_last_of("he",0);//��������ڶ������� Ӧ��Ҳ�Ǵ�ǰ�����pos
			auto pos5 = str4.rfind("hh");//�������� �ǲ��ǴӺ���ǰ��λ�þͲ�֪����

			//�ȽϺ��� ���� strcmp
			str1.compare(1,4,str2,1,4);//��ӵİ汾 const char* ��Ϊ��ָ�룬����û��pos2 �������Ͼ�����ֱ��ֱ��+n ����
			//��ֵת��
			auto dstr = to_string(10086.1123);
			stoi(dstr,0,10);//�ڶ�����ŷ���ֵ�±� ��������ʾ���� str�Ľ��� ������16���������ӵ�
			stod(dstr,0);
		}
	}
	{
		//���������� �������ٷ�װһ��
		//stack queue priority_queue ����
	
		deque<string> str_deq = { "he","wa","hehe","heihei" };
		stack<string> str_stack(str_deq);
		//priority_queue ʹ��vector ���� �ѹ���ʹ�� ������ʲô���ء���
		queue<string> str_queue(str_deq);
		str_queue.front();//����
		str_stack.top();//ջ�� �� ��Ϊ���������ݴʲ�һ��
		str_stack.pop();
		str_stack.push("gsg");
		str_queue.pop();
		str_queue.push("???");
		//�� �е����������������ӡ� ִ�п��� ���ǲ�û�иı�str_deq ��ֵ����������ʵ�������һ����ʼ����
		//ջ����ָ��ʵ�֡���
		vector<string> str_vec1 = { "h","hehe" };
		stack<string,vector<string>> str_stack1(str_vec1);
	}
}

//��ʮ�� �����㷨
inline void chapter10(){
	//���� ֱ����algorithm ͷ�ļ�����
	//��ֱ�Ӳ������� ��Ҫ��������Χ
		//�����Ҿ����������Ͳ����˼�����Щ�� ���Ǻ�ˬ�𡭡�
	{
		vector<string> str_vec = { "111","222","333" };
		auto it = find(str_vec.begin(), str_vec.end(), "222");
		string result = it == str_vec.end() ? "success" : "failed";

		//������ ���㷨������������

		//���� ���������� Ԫ�ص� ĳЩ����
			//����ʵ��һЩ�ض��Ĳ�������ʹ����Щ�㷨
			//find ��Ҫ Ԫ���� ==
			//������������Ҫ < ����������
		vector<Data1> data1{1,2,3,4};
		auto dit1 = find(data1.begin(), data1.end(), 4);
		//�㷨������������ʵ��
			//�������ĵ��������ۼ� �ۼ��أ�
				//���Ի���Ҫ�����ĵ�������ʵ�֣� �ŵ�������ʵҲ��Ϊ�ü�����������ʵ�ڲ������и��������ļ̳�ʲô��
					//����ܹ��������ɾ�� Ҳ����Ϊ���������ġ��� emmm
	}
	{
		//100 ���㷨
		// �������û���ṩһ��Qt �� c++ ͨ�õ��㷨� ÿ�ζ�Ҫת����ת��ȥ���鷳��
			//��֪���� ���Լ�д�����������ܹ�����c++ ��Qt �Ĳ�ͬ�ľ����ˣ������ṩһ����ʽת������stringת��QString
				//���а���std::string ���Ѿ�������˵ģ� ���Բ���ֱ��ת��ΪQString ������ ʹ��һ���м��໹��ֱ����дQt��
				//��Ҳû��QString �� string��ת����������дһ���м��ࣿ
		{
			// ֻ���㷨
				//���
			vector<string> str_vec1 = { "111","222","333" };
			vector<string> str_vec2 = { "111","111","222","333" };
			vector<string> str_vec3 = { "111" };
			string sum_str1 = accumulate(str_vec1.begin(), str_vec1.end(), string(""));//û����lambda ���ʽ�����м����ۣ�
			string sum_str2 = accumulate(str_vec1.begin(), str_vec1.end(),string(""), [](const string& sum,const string& num) {return sum + num; });
				//��������Ϊallocator ��ԭ�� ԭ��ʹ��string ��ʼ���������ˡ��� ��Ϊ�ڲ�����������Ĺ��캯�� ����ò���е� explict��ζ�� �п�������Ϊconst ��ԭ��?
			//	������������ �ڶ����������ٱȵ�һ�� һ�����߸��� 
			auto equal_result1 = equal(str_vec1.begin(), str_vec1.end(), str_vec2.begin()/*, str_vec2.end()*/);//������������Ļ� �Ƚϵ�һ��������
			auto equal_result2 = equal(str_vec1.begin(), str_vec1.end(), str_vec3.begin(), str_vec3.end());//����������Ͳ����ж������������ˣ�
			try
			{
				//auto equal_result3 = equal(str_vec1.begin(), str_vec1.end(), str_vec3.begin()); //��ֱ�ӱ���
				//���һ�catch ������ 
			}
			catch (out_of_range e) {
				string str = e.what();
			}
			catch (std::exception e)
			{
				//todo �����񲻵�
				string str = e.what();
			}

		}
	}
}
