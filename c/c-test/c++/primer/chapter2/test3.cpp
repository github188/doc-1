/*
 * =====================================================================================
 *
 *       Filename:  test3.cpp
 *
 *    Description:  value and pointer and reference
 *
 *        Version:  1.0
 *        Created:  06/10/2015 05:38:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyunteng (), li_yunteng@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
void Func1(int x)
{
	x = x + 10;
}

void Func2(int *x)
{
	*x = *x + 10;
}

void Func3(int &x)
{
	x = x + 10;
}

int main()
{
	int  a1, a2, a3;
	a1 = a2 = a3 = 0;
	Func1(a1);
	Func2(&a2);
	Func3(a3);

	std::cout << "a1: " << a1      << " a2: "
	          << a2     << " a3: " << a3
	          << std::endl;
	return 0;
}

