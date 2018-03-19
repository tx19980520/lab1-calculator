#include<regex>
#include<iostream>
#include <utility>
#include<string>
#include "filter.h"
using namespace std;




string cleanBlankFilter(string input)//清楚最开始的空格和最后的分号
{
	smatch match;
	regex clean(" (.*);");
	regex_match(input, match, clean, regex_constants::match_default);//这一个主要用于解决附加的ANS的问题，先把ANS替换掉进行下一步的检查
	return match[1];
}
//确定是否有规定范围之外的字符
bool extraCharFilter(string input)
{
	smatch match;
	regex errorRegex1("ANS");
	string replaceANS = regex_replace(input, errorRegex1, "0");//这一个主要用于解决附加的ANS的问题，先把ANS替换掉进行下一步的检查
	regex errorRegex2("([^0-9\\+\\*-/%\\(\\)/!])");   // 对于非规定字符的排除，基于我们已经消除了ANS的影响
	return regex_search(replaceANS, match, errorRegex2);
}
//对于不符合数学逻辑的错误的指出
Final formatCharFilter(string input)
{
	Final result;
	smatch match;
	regex mutipleAdd("\\+{2,}");
	regex doubleMinus("--");
	regex mixAddMinus("(\\+-)|(-\\+)");
	bool mid = 1;
	while (regex_search(input, match, mutipleAdd) || regex_search(input, match, doubleMinus) || regex_search(input, match, mixAddMinus))
	{
		if (regex_search(input, match, mutipleAdd))
			input = regex_replace(input, mutipleAdd, "+");
		if (regex_search(input, match, doubleMinus))
			input = regex_replace(input, doubleMinus, "+");
		if (regex_search(input, match, mixAddMinus))
			input = regex_replace(input, mixAddMinus, "-");
	}//上述while循环实现了将input中的所有冗余的++--缩减，并且处理了输入中（以及处理过程中产生的-+ +-）
	 //逻辑上讲，三个连续的正确运算符已经不存在了，现在只剩下错误的三个及其以上的连续运算符和两个的错误连续运算符
	regex errorRegex("(\\+[\\*%!/])|(-[\\*%!/])|(\\*[\\*/!%])|(/[\\*/!%])|(%[\\*%!])");//去除掉了+/ +* +! -* \! -/ -*
	if (regex_search(input, match, errorRegex))
	{
		mid = 0;
		result.first = mid;
		result.second = "";
		return result;
	}
	//下面的for循环处理括号匹配的问题
	int len = input.length();
	int count = 0;
	for (int i = 0; i<len; ++i)
	{
		if (input[i] == '(')
			count++;
		if (input[i] == ')')
			count--;//整个过程是不可能出现负数的
		if (count <0)
		{
			mid = 0;
			break;
		}
	}
	if (count != 0)
		mid = 0;
	result.first = mid;
	result.second = input;
	return result;
}


string UserInput()
{
	cout << ">" << flush;
	string input;
	getline(cin, input);
	return input;
}

string InputAndFilter()//以上部分的主函数
{
	string input = UserInput();
	input = cleanBlankFilter(input);
	Final result = formatCharFilter(input);
	if (extraCharFilter(input) || !result.first)//表示是异常输入
		return "error";
	else return result.second;
}