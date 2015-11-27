/*
 * test1.cpp -- test input output
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/06/10 13:21:27
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>

int main()
{
    std::cout << "Enter two numbers： " << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std:: cout <<"the sum of " << v1 << " and " << v2
               <<" is " << v1 + v2 << std::endl;

    std::cout << "/*";
    std::cout << "*/";
    return 0;
}
