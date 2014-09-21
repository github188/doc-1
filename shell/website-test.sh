#!/bin/bash

url=$1/
sltime=$2
if [ [$1] == [""] ];then
    echo "1.use like this:$0 url"
    echo "2.use like this:$0 url timeout"
    echo "3.use like this:$0 url timeout timwait"
elif [ [$2] != [""] ]; then
    for((i=0;i<sltime;i++))
    do
        sleep 1s
        result=`curl -I -m 10 -o /dev/null -s -w %{http_code} $url`
        if [ $result -eq 200 ] || [ $result -eq 302 ]; then
            break;
        fi
    done
else
    result=`curl -I -m 10 -o /dev/null -s -w %{http_code} $url`
fi
if [ [$3] != [""] ]; then
    sleep $3
fi
echo $result
