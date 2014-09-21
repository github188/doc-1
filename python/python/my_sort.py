#!/usr/bin/env python
#-*- coding:utf-8 -*-

import random

def my_quick_sort(a=[], start=0, end=0):

    if start >= end:
        return

    key = a[start]
    i = start
    j = end
    while True:
        while  j > i:
            if a[j] < key:
                a[i] = a[j]
                a[j] = key
                i += 1
                break
            else:
                j -= 1

        while j > i:
            if a[i] >= key:
                a[j] = a[i]
                a[i] = key
                j -= 1
                break
            else :
                i += 1

        if j <= i:
            break
    my_quick_sort(a, start, i)
    my_quick_sort(a, i+1, end)
            
    

a=[]
for i in range(1, 101):
    a.append(random.randint(1, 1000))
print(a)
my_quick_sort(a, 0, len(a)-1)
print(a)
