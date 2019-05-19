#!/bin/bash

process="cron"
#read -p "Enter process name: " process 
read -p "Enter process time/date: " time

folder=$(sudo find /var/log -type d -name "$process*")

if [ -n "$folder" ]; then
	ls "$folder" | awk -v pref="/var/log/$process/" '{print pref $0}' > search.txt
else
	file=$(sudo find /var/log -type f -name "$process*")

	if [ -n "$file" ]; then
		echo "$file" > search.txt
	else
		sudo find /var/log -maxdepth 1 -type f -name "syslog*" > search.txt
	fi
fi

found_count=0

while read line; do
	gzip -t "$line" 2>/dev/null

	if [ "$?" -eq "0" ]; then
		if zcat "$line" | grep -E ".*$time.*[ ./(]$process.*|.*[ ./(]$process.*$time.*"; then ((found_count++)); fi
	else
		if cat "$line" | grep -E ".*$time.*[ ./(]$process.*|.*[ ./(]$process.*$time.*"; then ((found_count++)); fi
	fi
done < search.txt
rm search.txt

if [ "$found_count" -eq "0" ]; then
	echo "Nothing found!"
fi

