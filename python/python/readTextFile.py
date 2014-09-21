#!/usr/bin/env python

"""
readTextFile.py -- read and display text file!
"""

#get filename
fname = input('Enter filename:')

try:
    fobj = open(fname, 'r')
except IOError as e:
    print('*** file open error:', e)
else:
    for eachLine in fobj:
        print(eachLine)
    fobj.close()

def main():
    pass
    
if __name__ == '__main__':
        main()


