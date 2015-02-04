#!/bin/bash
###############################################################################
# Author : liyunteng
# Email : li_yunteng@163.com
# Created Time : 2015-02-03 11:29
# Filename : a.sh
# Description : 
###############################################################################
i2c=`lsmod |awk '{print $1}'| grep i2c_dev`
i2ci801=`lsmod|awk '{print $1}'|grep i2c_i801`
i2cdev=
if [ -z $i2c ]; then
	modprobe i2c-dev
fi
if [ -z $i2ci801 ];then
	modprobe i2c-i801
fi
if [ ! -f /dev/i2c-i801 ]; then
	i2c=`ls /sys/class/i2c-adapter`
	for a in ${i2c}
	do
		if `cat /sys/class/i2c-adapter/${a}/name | grep -q I801`;then
			i2cdev=$a
			break
		fi
	done	

ln -sf /dev/$i2cdev /dev/i2c-i801
fi

