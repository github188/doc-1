#!/usr/bin/env python
# -*- coding: utf-8 -*-
def my_strip(th_str=''):
    tmp=[]
    tmp=list(th_str)
    i = 0
    while tmp[i] == ' ':
        tmp.pop(i)
        

    i = len(tmp)
    while tmp[i-1] == ' ':
        tmp.pop(i-1)
        i = len(tmp)

    return ''.join(tmp)

th_str='   hello world!   '
print(my_strip(th_str))
    
