#!/usr/bin/env python
#-*- encoding=utf-8 -*-

def my_test(a=1, b=2, c=3):
    print('a=%d b=%d c=%d' % (a, b, c))
def my_t(a, b, c):
    print("a=%s b=%s c=%s" % (a, b, c))


if __name__ == '__main__':
    t=(4,5,6)
    my_test(*t)
    d={a:'aaa', b:'bbbb', c:'cccc'}
    my_t(**d)
