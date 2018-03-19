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
typedef pair<Type, string> Token;//我们在这个地方需要我们在token保存一个type，type是一个string,另外的一个部分为具体的数据，主要是为了数字准备的，在不是数据是字符串的时候我们选择为“”
								 //到这一步已经是到了只有计算错误的时候了，就是得有数字参与才会有错误的时候
extern double ans;//为日后实现ANS功能来做准备
extern const double spe;
extern const double MAX;//在计算过程中出错一律返回MAX，之后我们会check一下，看输出什么
extern bool calcError;
double fac(double x);


class Calc {
	struct node {
		Type character;
		node *left;
		node *right;
		double value;
		bool buff;//确保是有一个符号
		int isFac;//确保是否是有一个阶乘的buff
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