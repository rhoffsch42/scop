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

cmd2="./scop resources/*.obj resources/*.mtl textures/*.xpm"
cmd="./scop resources/*.obj -d resources/ -d assets -d textures -d Makefile"

i="1"
target="1000"

while [ $i -lt $target ]
do
	mytest $cmd
	ret=$?
	echo $ret
	if [ $ret -ne 1 ]
	then
		echo "failed crash test at $i"
		exit $i
	fi
	i=$[$i+1]
done
echo "passed $target crash_test" 
