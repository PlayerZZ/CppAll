#pragma once
//һЩc++ primer�Ĵ���
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
		j == ++i;
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