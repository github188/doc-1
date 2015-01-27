#!/bin/bash
###############################################################################
# Author : liyunteng
# Email : li_yunteng@163.com
# Created Time : 2015-01-26 13:42
# Filename : get.sh
# Description : 
###############################################################################
PATH=$PATH:/usr/bin
if [ $# -ne 1 ]; then
	echo "Usage: $0 url"
	exit -1
fi

pid=`ps aux|grep firefox|grep -v grep|awk '{print $2}'`
if [ "x$pid" = "x" ];then 
	firefox &
	sleep 3
	pid=`ps aux|grep firefox|grep -v grep|awk '{print $2}'`
fi
if [ "x$pid" = "x" ]; then
	echo "start firefox failed."
	exit -1
fi

if [ ! -d "./download" ] ; then
	mkdir ./download
fi
if [ -d "./img" ]; then
	files=`ls ./img`
	if [ ! -z "$files" ]; then
		mv ./img ./img_`date +'%Y%m%d%H%M%S'`

	fi
fi
term_id=`xdotool getactivewindow`
id=`xdotool search --name "Mozilla firefox"`
if [ x$id = "x" ];then
	echo "start firefox failed."
	exit -1
fi
xdotool windowfocus $id
xdotool key "ctrl+l"
xdotool type "$1"
xdotool key "Return"
sleep 1
xdotool key "ctrl+s"
xdotool key "ctrl+a"
sleep 1
id=`xdotool search --name "Save As"`
xdotool windowfocus $id
xdotool key "ctrl+a"
path=`pwd`'/download/html'
xdotool type "$path"
xdotool key "Return"
xdotool key "Return"
sleep 3
xdotool windowfocus $term_id

#/usr/bin/wget -e robots=off -np -nH -pk -P $1
#/usr/bin/curl -o html $1
/usr/bin/iconv -f gbk -t utf-8 < ./download/html > ./download/html.utf-8
./b.py
rm -rf ./download

