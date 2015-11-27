/*
 * test_protected.cpp -- test protected
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/29 13:57:48
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

using namespace std;

class A
{
public:
    int i = 1;
    void print_i() {cout << "a i: " << i << endl; print_j(); print_k();}
protected:
    int j = 2;
    void print_j() {cout<< "a j: " << j << endl;}
private:
    int k = 3;
    void print_k() {cout << "a k: " << k << endl;}
};


class B : public A
{
    /* friend class A; */
public:
    void B_print_j(A*);

};

void B::B_print_j(A *a)
{
    cout << "b a->i: "<< a->i << endl;
    a->print_i();
    print_j();

}
int main(int argc, char *argv[])
{
    A a;
    B b;
    a.print_i();
    b.print_i();
    b.B_print_j(&a);

    return 0;
}
