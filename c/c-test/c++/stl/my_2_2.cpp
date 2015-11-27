/*
 * my_2_2.cpp -- my stl program
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/26 17:41:48
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

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    vector<int> num;
    int n;

    while(cin >> n)
        num.push_back(n);

    sort(num.begin(), num.end());

    for(int i=0; i < num.size(); i++)
        cout << num[i] << "\t";
    cout << endl;

    return 0;
}
