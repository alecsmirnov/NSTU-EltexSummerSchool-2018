#!/bin/bash


date_time=$1
#read -p "Enter date and time, separated by space: " date_time

date=$(echo $date_time | grep -o ".*[ ]")
time=$(echo $date_time | grep -o "[ ].*")

#echo $date
#echo $time

dt[0]=$date
dt[1]=$(echo ${dt[0]} | sed -e 's/[.]/-/g')
dt[2]=$(echo ${dt[0]} | sed -e 's/[.]/:/g')
dt[3]=$(echo ${dt[0]} | sed -e 's/[.]/\//g')
dt[4]=$(date -d "${dt[3]}" +%Y-%d-%m)
dt[5]=$(date -d "${dt[4]}" +%Y/%d/%m)
dt[6]=$(date -d "${dt[4]}" +%Y:%d:%m)
dt[7]=$(date -d "${dt[4]}" +%Y.%d.%m)
dt[8]=$(echo ${dt[4]} | sed 's/$/:01Jan02Feb03Mar04Apr05May06Jun07Jul08Aug09Sep10Oct11Nov12Dec/
	   s/.....\(..\).\(.*\):.*\1\(...\).*/\3 \2 /')
dt[9]=$(date -d -R "${dt[0]}" %h%e)

for((i=0; i!=10; ++i)); do
	echo "${dt[i]}"
done

#echo $(date -d "$date" +%F)

#echo $date | sed -e 's/[.]/-/g'
#echo $date | sed -e 's/[.]/:/g'
#echo $date | sed 's/$/:01Jan02Feb03Mar04Apr05May06Jun07Jul08Aug09Sep10Oct11Nov12Dec/
#     s/.....\(..\).\(.*\):.*\1\(...\).*/\3 \2 /'

