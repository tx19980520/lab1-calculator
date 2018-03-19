#pragma once
#include<regex>
#include<iostream>
#include <utility>
#include<cmath>
#include<string>
#include<sstream>
using namespace std;











#ifndef _CALCULATOR_H
#define _CALCULATOR_H

enum Type { NUM, ADD, SUB, MULTI, DIV, OPAREN, CPAREN, EOL, MOD, ANS, FAC, NEGA, POS };//for switch
typedef pair<Type, string> Token;//����������ط���Ҫ������token����һ��type��type��һ��string,�����һ������Ϊ��������ݣ���Ҫ��Ϊ������׼���ģ��ڲ����������ַ�����ʱ������ѡ��Ϊ����
								 //����һ���Ѿ��ǵ���ֻ�м�������ʱ���ˣ����ǵ������ֲ���Ż��д����ʱ��
extern double ans;//Ϊ�պ�ʵ��ANS��������׼��
extern const double spe;
extern const double MAX;//�ڼ�������г���һ�ɷ���MAX��֮�����ǻ�checkһ�£������ʲô
extern bool calcError;
double fac(double x);


class Calc {
	struct node {
		Type character;
		node *left;
		node *right;
		double value;
		bool buff;//ȷ������һ������
		int isFac;//ȷ���Ƿ�����һ���׳˵�buff
		node(Type t, double d = 0.0, node * lc = NULL, node * rc = NULL, bool b = false, int fac = 0) {
			character = t;
			value = d;
			left = lc;
			right = rc;
			buff = b;
			isFac = fac;
		}
	};
	node *root;
	node *create(string &input, int& position);
	Token getToken(string &s, int& position);
	double result(node *t);
	double getValue(string s);
public:
	Calc(string input) { int position = 0; root = create(input, position); }
	void deleteNode(node *n);
	~Calc()
	{
		deleteNode(root);
	}
	double result() {
		if (root == NULL)
		{
			return 0;
		}
		ans = result(root);
		return ans;
	}
};
#endif