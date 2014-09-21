#!/usr/bin/env python

def a(start=0):
    count = start
    while True:
        val = yield count
        if val is not None:
            count = val
        else:
            print(val)
            count += 1

   
