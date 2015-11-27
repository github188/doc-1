/*
 * =====================================================================================
 *
 *       Filename:  test2.cpp
 *
 *    Description:  definitions
 *
 *        Version:  1.0
 *        Created:  06/10/2015 04:00:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyunteng (), li_yunteng@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
int main()
{
#if 0
	int input_value;
	std::cin >> input_value;

	int i = { 3.14 };
	std::cout << i << std::endl;
#endif
	int i = 10;
	int &ri = i;
	int &ri2 = ri;
	int *rp = &ri;	
	int &ri3 = *rp;
	int *rpr = &ri3;
	std::cout << ri << " " << ri2 << std::endl;
	std::cout << *rp << std::endl;
	std::cout << ri3 << std::endl;
	std::cout << *rpr << std::endl;
}

