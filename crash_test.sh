#!/bin/sh

function mytest {
	"$@"
	local status=$?
	if [ $status -ne 0 ];
	then
		return 0
	fi
	return 1
}

cmd="./scop resources/*.obj -d resources/ -d textures -d Makefile"

i="1"

while [ $i -lt 100 ]
do
	mytest $cmd
	ret=$?
	echo $ret
	if [ $ret -ne 1 ]
	then
		exit $i
	fi
	i=$[$i+1]
done
