#!/bin/bash


function menu {
	echo \"MENU\" >&2
        echo 1. Run process >&2
        echo 2. Print processes >&2
        echo 3. Detect process >&2
        echo 4. Kill process >&2
        echo 5. Exit >&2
}

function printActiveProcesses {
	ps -axr
}

function inputTime {
	min=*; hour=*; day=*; month=*; dow=*

	echo -e "\n\"Repeat menu\"" >&2
	echo 1. Hourly >&2
	echo 2. Daily >&2
        echo 3. Select time >&2
        read -p "Select item: " answer
		
	case $answer in
		1) min=$(date +%M); ((++min));;
        	2) min=$(date +%M); ((++min))
	   	   hour=$(date +%H)
		   dow=*;;
                3) echo -e "\nNOTE: * - each value of field;" >&2
		   echo "      You can enter particular values separated by commas." >&2
		   read -p "Enter hour (0-23): " hour
		   read -p "Enter minutes (0-59): " min
		   read -p "Enter day of week (1-7): " dow
		   read -p "Enter month (1-12): " month;;
	esac
   
	echo "$min $hour $day $month $dow"
}

function staticTime {
	min=$(date +%M); ((++min))
	hour=$(date +%H)
	day=$(date +%d) 
	month=$(date +%m)
	dow=$(date +%w)

	echo "$min $hour $day $month $dow"
}

function runProcess {
	path_name=$(which $process)
	echo "$path_name"	
}

function repeatProcess {
	read -p "Repeat [y/n]?: " repeat
	
	case $repeat in 
		Y|y) time=$(inputTime);;
		N|n) time=$(staticTime);;
	esac

	crontab -l > cron.txt
	echo -e "$time $1" >> cron.txt
	crontab cron.txt
	rm cron.txt
}

function detectProcess {
	echo "" && read -p "Enter process name: " process

	if ps ax | grep -v grep | grep "$process" > /dev/null
	then
    		echo -n "Running: "
		place=$(ps ax | sed -n "/[/]$process/p" | wc -l)
	
		case $place in
			0) echo -e "executed in terminal!\n" >&2;;
			*) echo -e "executed in crontab!\n" >&2;;
		esac

		cur_date=$(date '+%Y-%m-%d %H:%M:%S')
		echo "Process $process is runing at $cur_date" >> disp.log
	else
    		echo "Stopped"
		#repeatProcess $(runProcess $process)
	fi
}

function killProcess {
	ps -ef | grep $1 | grep -v grep | awk '{print $2}' | xargs kill -9
}

answer=1

while [ $answer -ne 5 ]; do
        menu
        read -p "Select item: " answer

        case $answer in
                1) echo "" && read -p "Enter process name: " process
		   repeatProcess $(runProcess $process);;
                2) printActiveProcesses;;
                3) detectProcess;;
                4) echo "" && read -p "Enter process name: " process
		   killProcess;;
                5) answer=5;;
        esac
done







