/*
 * =====================================================================================
 *
 *       Filename:  test1.c
 *
 *    Description: signed and unsigned
 *
 *        Version:  1.0
 *        Created:  06/10/2015 02:53:25 PM
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
	unsigned u = 10;
	int i      = -42;

	std::cout << i + i << std::endl;
	std::cout << u + i << std::endl;
	
	unsigned u1 = 42, u2 = 10;
	std::cout << u1 - u2 << std::endl;
	std::cout << u2 - u1 << std::endl;
	
	for (int i = 10; i >= 0; --i)
		std::cout << i << std::endl;

	std::cout << "\vi\ri\ti\bi\?i\fi\ai" << std::endl;
}

