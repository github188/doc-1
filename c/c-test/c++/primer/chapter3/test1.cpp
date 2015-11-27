/*
 * test1.cpp -- test string
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/06/11 16:03:05
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

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    string s;
#if 0
    cin >> s;
    cout << s << endl;

    while (cin >> s)
        cout << s << endl;
#endif
    while (getline(cin, s))
        if (!s.empty())
            cout << s << endl;
    cout << toupper(s[0]) << endl;
    return 0;
}
