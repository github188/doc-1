/*
 * pimpl.cpp -- test pimpl
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/29 18:24:35
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

#include "pimpl.hpp"
#include <iostream>
using namespace std;

class  Mypimpl
{
private:
    static const int i = 10;
public:
    void print_myi();

};

void Mypimpl::print_myi()
{
    cout << "i: " << i << endl;
}

A::A() :pimpl(new Mypimpl)
{

}
A::~A()
{

}

void A::print_i()
{
    pimpl->print_myi();
}
int main(int argc, char *argv[])
{
    A a;
    a.print_i();
    return 0;
}
