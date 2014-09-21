#!/usr/bin/python
import sys

print(dir())
def foo():
    """
    this is  doc string
    """
    return True


"""
print('hello')

a=33

if a > 50:
    print('a>50')
elif a > 30:
    print('a>30 and a<=50')
else:
    print('a<=30')


b=1
while b<20:
    print('welcome %d' % b)
    b += 1



f_path=input('Enter file name:')

try:
    f = open(f_path, 'r+')
    for line in f:
        print(line)
    f.seek(0)
    f.truncate()
    print('write 1-100 to file', file=f)
    i = [x for x in range(1, 101)]
    print(i, file=f)
except IOError as e:
    print(e)
finally:
    f.close()
"""

def addMe2Me(x=1):
    """
    addMe2Me
    """
    return(x+x)


print(__name__)
