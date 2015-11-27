/*
 * example2_3.cpp -- aesthetic version
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/26 17:49:38
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
#include <iterator>


using namespace std;

int main(int argc, char *argv[])
{
    typedef vector<int>                 int_vector;
    typedef istream_iterator<int>       istream_itr;
    typedef ostream_iterator<int>       ostream_itr;
    typedef back_insert_iterator<int_vector>    back_ins_itr;

    int_vector num;

    copy (istream_itr(cin), istream_itr(), back_ins_itr(num));

    sort(num.begin(), num.end());

    copy(num.begin(), num.end(), ostream_itr(cout, "\n"));

    return 0;
}
