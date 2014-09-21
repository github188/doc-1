#!/usr/bin/env python

def foo(a=0):
    """
    foo() -- properly created doc  string
    """
    def bar():
        nonlocal a
        a += 1
        return a
        
    return bar

def foo1():
    a = [0]
    def bar1():
        a[0] += 1
        return a[0]

    return bar1
