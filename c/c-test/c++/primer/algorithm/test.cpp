/*
 * test.cpp -- test algorithm
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/06/12 10:49:43
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
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const int &a, const int &b)
{
    return a > b;
}

void display(int i)
{
    cout << i << " ";
}

bool odd(int i)
{
    return i % 2 != 0;
}

int main()
{
    vector <int> num(10);
    //
    generate(num.begin(), num.end(), rand);
    replace_if (num.begin(), num.end(), odd, 0);
    sort(num.begin(), num.end(), compare);
    for_each(num.begin(), num.end(), display);

    cout << endl;
    return 0;
}
