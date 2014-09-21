#!/usr/bin/env bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH
clear
Url="http://mirrors.cnnic.cn/apache/"
DownListFile="/tmp/downlist.txt"
DownListTmpFile="/tmp/tmplist.txt"
DownFileType="zip$|gz$"
Downlist=""
UrlBack="$Url"
[ ! -f $DownListFile ] && touch $DownFileType || echo > $DownListFile
[ ! -f $DownListTmpFile ] && touch $DownListTmpFile || echo > $DownListTmpFile
CURL_CURLS() {
    Urls=`curl $UrlBack | awk -F "a href=\"" '{printf "%s\n", $2}' | awk -F "\"" '{printf "%s\n", $1}' | grep -vE "^$|^\?|^http:\/\/|^#"`
}

URL_LIST() {
    CURL_CURLS
    for i in $Urls; do
        echo "$UrlBack$i" >> $DownListTmpFile
    done
}

RECURSIVE_SEARCH_URL(){
    UrlBackTmps=`cat $DownListTmpFile`
    [[ "$UrlBackTmps" == "" ]] && echo "no more page for search" && exit 1
    for j in $UrlBackTmps; do
        if [[ "${j##*\/}" != "" ]];then
            echo "$j" >> $DownListFile
        else
            UrlBack="$j"
            URL_LIST
        fi
        UrlTmps=`grep -vE "$j$" $DownListTmpFile`
        echo "$UrlTmps" > $DownListTmpFile
        RECURSIVE_SEARCH_URL
    done
}

DOWNLOAD_FILE() {
    DownList=`grep -E "$DownFileType" $DownListFile`
    for k in $DownList; do
        FilePath=/tmp/${k#*\/\/}
        [ ! -d `dirname $FilePath` ] && mkdir -p `dirname $FilePath`
        [ ! -f $FilePath ] && cd `dirname $FilePath` && curl -O $k
    done
}

URL_LIST $Urls
RECURSIVE_SEARCH_URL
