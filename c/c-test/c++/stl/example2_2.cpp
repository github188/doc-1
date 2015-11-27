/*
 * example2_2.cpp -- the first stl program
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/26 17:39:15
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

int main(int argc, char *argv[])
{
    vector<int> num;            /* STL中的vector容器 */
    int element;

    /* 从标准输入设备读入整数 */
    /* 知道输入的是非整形数据为止 */
    while(cin >> element)
        num.push_back(element);

    /* STL中的排序算法 */
    sort(num.begin(), num.end());

    /* 将排序结果输出到标准输出设备 */
    for (int i = 0; i < num.size(); i++)
        cout << num[i] << "\t";
    cout << endl;
    return 0;
}
