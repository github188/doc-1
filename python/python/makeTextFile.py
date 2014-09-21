#!/usr/bin/python

"""
makeTextFile.py -- create text file
"""
import os

ls = os.linesep

#get filename
while True:
    fname = input('Enter filename:')
    if os.path.exists(fname):
        print('Error: "%s" alread exist' % fname)
    else:
        break
        
#get file context (text) lines
all = []
print("\nEnter lines('.' by itself to quti). \n")

#loop until user terminates input
while True:
    entry = input('>')
    if entry == '.':
        break
    else:
        all.append(entry)

#write lines to file while proper line-ending
fobj = open(fname, 'w')
fobj.writelines(['%s%s' % (x, ls) for x in all])
fobj.close()
print('DONE!')

