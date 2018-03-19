#include<regex>
#include<iostream>
#include <utility>
#include<string>
using namespace std;




#ifndef _FILTER_H
#define _FILTER_H
typedef pair<bool, string> Final;
//清楚最开始的空格和最后的分号
string cleanBlankFilter(string input);
//确定是否有规定范围之外的字符
bool extraCharFilter(string input);
//对于不符合数学逻辑的错误的指出
Final formatCharFilter(string input);

//得到输入
string UserInput();

string InputAndFilter();//以上部分的主函数
#endif