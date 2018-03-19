#include<string>
#include<cmath>
#include "calculator.h"
#include "filter.h"

int main()
{
	while (true)
	{
		string input = InputAndFilter();//输入控件，详见filter.h
		if (input == "error")
		{
			cout << "error" << endl;
			continue;
		}
		else {
			Calc *cal = new  Calc(input);
			double result = cal->result();
			if (result > 999999)
			{
				cout << "error" << endl;
				calcError = false;//不知道助教测一次开一次程序还是一次测完，每次算完这个值都弄成false
				continue;
			}
			else {
				cout << "= " << result << endl;
			}
		}
	}
}