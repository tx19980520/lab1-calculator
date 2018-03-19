// calculator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<regex>
#include<iostream>
#include <utility>
#include<cmath>
#include<string>
#include<sstream>
#include "calculator.h"
using namespace std;

double ans = 0;
const double spe = pow(10, -6);
const double MAX = 99999999999.0;
bool calcError = false;



double fac(double x)
{
	int i, f = 1;  //����Ĵ�������
	double check = abs(floor(x) - x);
	if (check > spe)
	{
		return -1;
	}
	if (x < 0)
	{
		return -1;
	}
	if (x == 0) {
		return 1.0;
	}
	x = (int)x;
	for (i = 1; i <= x; i++)
		f *= i;
	return f;
}
double Calc::result(Calc::node *root)
{
	if (calcError)
	{
		return MAX;
	}
	if (root->character != NUM)//����ط�����Ϊ�˲���NUMȥ����������������
	{
		double num1, num2;
		num1 = result(root->left);
		num2 = result(root->right);
		switch (root->character)
		{
		case ADD: {
			root->value = num1 + num2;
			break;
		}
		case SUB: {
			root->value = num1 - num2;
			break;
		}
		case MULTI: {
			root->value = num1 * num2;
			break;
		}
		case DIV: {
			if (abs(num2 - 0) < spe)
			{
				return MAX;
				calcError = true;
			}
			root->value = num1 / num2;
			break;
		}
		case MOD: {
			bool n1 = false;
			bool n2 = false;
			bool n3 = false;
			if (abs(num1 - (int)num1) < spe)
			{
				n1 = true;
			}
			if (abs(num2 - (int)num2) < spe)
			{
				n2 = true;
			}
			if ((int)num2 != 0)
			{
				n3 = true;
			}
			if (n1 && n2 && n3)
			{
				root->value = (int)num1 % (int)num2;
			}
			else {
				return MAX;
			}
			break;
		}
		}//switch
	}
	if (root->isFac>0)//����buff�����Ŵ���������-(5+3)���������ǵĽ׳��Ǳ������һ�������
	{
		while(root->isFac>0)
		{
			root->value = fac(root->value);
			root->isFac--;
		}
		if (root->value == -1)
		{
			return MAX;
		}
	}
	if (root->buff)
	{
		root->value = root->value *-1;
	}
	return root->value;
		
};



double Calc::getValue(string s) {//��sstream����ֵ
	istringstream stream(s);
	double value;
	stream >> value;
	if (stream.fail())
	{
		cout << "error";
		calcError = true;
		return MAX;
	}
	return value;
}
void Calc::deleteNode(node *t)//Ϊ����������׼��
{
	node *l = t->left;
	node *r = t->right;
	delete t;
	if (l != NULL)
	{
		deleteNode(l);
	}
	if (r != NULL)
	{
		deleteNode(r);
	}
};
Calc::node* Calc::create(string &input, int& position)//������������֮��
{
	//todo��Ҫ���ǵ����ǵ���ѧ����
	Calc::node *p, *root,*latest,*forIn;//latest��Ҫ��Ϊ�׳˷��񣬼�¼��һ����㣨!�Ǳ��������ǰ���������
	p = NULL;
	root = NULL;
	latest = NULL;
	forIn = NULL;
	Token nowToken;
	int len = input.length();
	static bool buff = false;
	while (position < len)
	{
		Token nowToken = getToken(input, position);
		latest = p;//��¼��һ��
		switch (nowToken.first) {
		case NUM:case OPAREN:
		{
			if (nowToken.first == NUM)
			{
				p = new Calc::node(NUM,getValue(nowToken.second));
				p->buff = buff;
				buff = false;//
			}
			else//�����������Ƕ����һ�����
			{
				forIn = new Calc::node(MULTI);
				p = create(input, position);
				forIn->left = new Calc::node(NUM, 1.0);
				forIn->right = p;
				p = forIn;
				p->buff = buff;//������Ϊ��û��ֵ��ֻ���ȸ�Ū��buff�У������쵽���������buff
				buff = false;
			}
			if (root != NULL)
			{
				if (root->right == NULL)
				{
					root->right = p;
				}
				else {
					Calc::node *rchild = root->right;
					if (rchild == NULL)
					{
						root->right = p;
					}
					else {
						rchild->right = p;
					}
				}
			}
			else
			{
				root = p;
			}
			break;
		}//NUM and (
		case NEGA: {
			buff = true;
			break;
		}
		case POS:{
			break;//���������ø������ù�
		}
		case EOL: case CPAREN: {
			return root;
		}//"" and )

		case ADD:case SUB: {
			p = new Calc::node(nowToken.first);
			if (root == NULL) root = p;
			else {
				p->left = root;
				root = p;//ԭ��������ʽ��Ϊ��������ʽ��������
			}
			break;
		}//+ -

		case MULTI : case DIV:case MOD:{
			p = new Calc::node(nowToken.first);
				if (root == NULL)
				{
					root = p;
				}
				else {
					if (root->character == SUB || root->character == ADD)
					{
						p = new Calc::node(nowToken.first);
						p->left = root->right;
						root->right = p;
					}
					else if (root->character == MULTI || root->character == DIV || root->character == MOD || root->character == NUM)
					{
						p = new Calc::node(nowToken.first);
						p->left = root;
						root = p;
					}

				}
				break;
		}//*%/
		case FAC: {
			latest->isFac++;

			break;
		}//��
		case ANS: {
			p = new Calc::node(NUM, ans);
			p->buff = buff;
			buff = false;//
			if (root != NULL)
			{
				if (root->right == NULL)
				{
					root->right = p;
				}
				else {
					Calc::node *rchild = root->right;
					if (rchild == NULL)
					{
						root->right = p;
					}
					else {
						rchild->right = p;
					}
				}
			}
			else
			{
				root = p;
			}
			break;
		}
		}//switch
	}//while
	return root;
};//create

Token Calc::getToken(string &input, int& position)
{//������һ���϶�position���п��ƴ�С��ֹԽ��
	Token token;
	int len = input.length();
	if (position == len)
	{
		token.first = EOL;
		token.second = "";
		return token;
	}
	switch (input[position]) {
	case '(': {
		token.first = OPAREN;
		token.second = '(';
		position++;
		return token;
	}
	case ')': {
		token.first = CPAREN;
		token.second = ')';
		position++;
		return token;
	}
	case '+': {//���+���˼ӷ���������
		if (position == 0)
		{
			token.first = POS;
			token.second = "+";
			position++;
			return token;
		}
		else {
			if ((input[position - 1] == '*' || input[position - 1] == '/' || input[position - 1] == '%' || input[position - 1] == '('))
			{
				token.first = POS;
				token.second = "+";
				position++;
				return token;
			}
		}
		token.first = ADD;
		token.second = '+';
		position++;
		return token;
	}
	case '-': {
		if (position == 0)
		{	
			token.first = NEGA;
			token.second = "-";
			position++;
			return token;
		}
		else {
			if ((input[position - 1] == '*' || input[position - 1] == '/' || input[position - 1] == '%' || input[position-1] == '('))
			{
				token.first = NEGA;
				token.second = "-";
				position++;
				return token;
			}
		}
		token.first = SUB;
		token.second = '-';
		position++;
		return token;
	}
	case '*': {
		token.first = MULTI;
		token.second = '*';
		position++;
		return token;
	}
	case '!': {
		token.first = FAC;
		token.second = '!';
		position++;
		return token;
	}
	case '%': {
		token.first = MOD;
		token.second = '%';
		position++;
		return token;
	}
	case '/': {
		token.first = DIV;
		token.second = '/';
		position++;
		return token;
	}
	case 'A': {//����ط�����A����Ϊ���ǻ���ANS�ı��ʽ
		position += 3;
		token.first = ANS;
		ostringstream os;
		os<< ans;
		string str = os.str();
		token.second = str;
		return token;
	}
	case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': {
		int len = input.length();
		string tmp = "";
		bool trueOut = false;
		for (int i = position; i<len; ++i)
		{
			if ((int(input[i]) >= 48 && int(input[i]) <= 57) || input[i] == '.')
			{
				tmp += input[i];
				if (i == len - 1) trueOut = true;
			}
			else {//�ܵ�����ط���һ���Ǹ�����,��������Ѿ����˽�β��û������
				position = i;
				if (input[i] == '!')
				{
					token.first = NUM;
					token.second = tmp;
					return token;
				}
				break;
			}
		}
		if (position == len - 1 || trueOut)//�����ֶ������һλ�ˣ�������Ҫ������������
			position = len;
		token.first = NUM;
		token.second = tmp;
		return token;
	}
	default: {
		token.first = EOL;
		token.second = "";
		return token;
	}
	}

};
