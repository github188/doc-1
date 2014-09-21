#!/usr/bin/env python
#-*- encoding:utf-8 -*-

from urllib.request import urlretrieve

def firstNonBlank(lines):
    for eachLine in lines:
        if not eachLine.strip():
            continue
        else:
            return eachLine

def firstLast(webpage):
    f = open(webpage)
    lines = f.readlines()
    f.close()

    print(firstNonBlank(lines))
    #lines.reverse()
    #print(firstNonBlank(lines), end=',')

def download(url='http://www.baidu.com', process=firstLast):
    try:
        retval = urlretrieve(url)[0]
    except IOError:
        retval = None
    if retval:
        process(retval)

if __name__ == '__main__':
    download('http://www.msn.com')
