#!/bin/bash


function menu {
	echo \"MENU\"
	echo 1. Set the alarm clock
	echo 2. Change the alarm time
	echo 3. Turn off the alarm clock
	echo 4. Print all
	echo 5. Delete all
	echo 6. Exit
}

function inputTime {
	read -p "Enter the hour: " hour
	read -p "Enter the min:  " min

	read -p "Repeat [y/n]?: " repeat	

	day=*
	month=*

	case $repeat in 
		y) echo 1. Daily >&2
		   echo 2. Weekdays >&2
		   echo 3. Select days >&2
		   read -p "Select item: " answer
		
		   case $answer in
			1) dow=*;;
 			2) dow="0-4";;
			3) read -p "Enter days (1-7) separated by commas: " dow;;
		   esac;;
		n) day=$(date +%d) 
		   month=$(date +%m)
		   dow=$(date +%w);;
	esac
		
	echo "$min $hour $day $month $dow"
}

answer=1

while [ $answer -ne 6 ]; do
	menu
	read -p "Select item: " answer

	crontab -l > cron.txt

	case $answer in
		1) time=$(inputTime)  
		   echo "$time /usr/bin/aplay /home/alex/Summer\ school/Linux/Task_2/MLG.wav" >> cron.txt
		   echo Alarm clock is set!
		   crontab cron.txt;;
		2) read -p "Enter replaced alarm clock: " clock
		   read -p "Enter new alarm clock: " n_clock
		   #com="sed -ni \"s/$clock/$n_clock/\""
		   #eval $com
		   cp cron.txt tmp
		   grep -v "$clock" tmp > cron.txt
		   echo "$n_clock /usr/bin/aplay /home/alex/Summer\ school/Linux/Task_2/MLG.wav" >> cron.txt
		   rm tmp
		   crontab cron.txt;;
		3) read -p "Enter deleted alarm clock: " clock
		   cp cron.txt tmp
		   #sed -ni "/$clock/ d" cron.txt
		   grep -v "$clock" tmp > cron.txt
		   rm tmp
		   echo Alarm clock "\"$clock\"" is deleted!
		   crontab cron.txt;;
		4) sed -i '/MLG/s/[/].*$// p' cron.txt
	           cat cron.txt;;
		5) sed -i '/MLG/ d' cron.txt
		   crontab cron.txt;;
		6) answer=6;;
	esac
	
	rm cron.txt
	echo -e $"\n"
done

