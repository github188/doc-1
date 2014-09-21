#!/usr/bin/env python

def convert(func, seq):
    """
    conv. sequence of numbers to sam type
    """
    return [func(eachNum) for eachNum in seq]

myseq = (123, 45.67, -6.2e8, 99999999999)
print(convert(int, myseq))
print(convert(float, myseq))
