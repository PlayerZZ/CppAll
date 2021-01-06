#pragma once
//һЩc++ primer�Ĵ���
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
		int o;
		std::cout << "o value:" << o << std::endl;
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

	}
}