#!/usr/bin/env bash 

version=`make kernelrelease`
path="/usr/src/linux-headers-$version"

if [ -z $version ]; then
	echo "get kernelversion failed."
	exit -1
fi

rm -rf $path
mkdir $path
cp -r Makefile Kconfig Kbuild .config Module.symvers arch include scripts $path
find $path/arch -type f -name *.[c,o,S] |xargs rm -rf
find $path/arch -type f -name *.o.cmd |xargs rm -rf
rm -rf /lib/modules/$version/build
ln -s $path /lib/modules/$version/build
exit 0

