#!/usr/bin/env python

from time import ctime, sleep

def decoFun(func):
    def wrapper():
        try:
            f = open('deco_log.txt', 'a')
        except IOError as e:
            print('open deco_log.txt failed: %s' % e)
        else:
            f.writelines("[%s] %s() open deco_log\n" %  (ctime(), func.__name__))
        finally:
            f.close()
        return func() #注意是返回的方法，不是方法名 fun = decoFun(fun)

    return wrapper

@decoFun
def fun():
    print('[%s] %s() in fun' % (ctime(), __name__))
    

fun()
