#!/usr/bin/env python
###############################################################################
# Author : liyunteng
# Email : li_yunteng@163.com
# Created Time : 2015-01-27 12:37
# Filename : img.py
# Description : 
###############################################################################
# -*- coding: utf-8 -*-
import os
import re
import urllib.request

urlfile=open('./download/html.utf-8','r')
reg=re.findall(r'<img.*?data-lazyload=["|\']http://(.+?)\.(jpg|gif|png)["|\'].*?>',urlfile.read())

if os.path.exists('./img') == False:
    os.mkdir('./img')
x = 1
for url,format in reg:
    url = 'http://'+url
    format = '.'+format
    path = './img/'+str(x)+format
    urllib.request.urlretrieve(url+format, path)
    if os.path.getsize(path) < 5*1024:
        print('Waring: '+url+format+' size ' + str(os.path.getsize(path)) + ' remove')
        os.remove(path)
        continue
    print(str(x)+': '+url+format + ' size ' + str(os.path.getsize(path)))
    x += 1
print('total: ' + str(x-1))
