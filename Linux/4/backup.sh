#!/bin/bash


function menu {
	echo \"MENU\" >&2
	echo 1. Make backup record >&2
	echo 2. Print backup records >&2
	echo 3. Delete backup record >&2
	echo 4. Delete all records >&2
	echo 5. Exit >&2
}

function copyFileCommand {
	echo 1. cp >&2
	echo 2. tar >&2
	read -p "Select item: " item

	case $item in
		1) echo "/bin/cp -a $1/$2 $3";;
		2) echo "cd $1 && /bin/tar -czf $3.tar.gz $2";;
	esac
}

function copyDirCommand {
	echo 1. rsync >&2
	echo 2. tar >&2
	read -p "Select item: " item

	case $item in
		1) echo "/usr/bin/rsync -a $1/$2 $3";;
		2) echo "cd $1 && /bin/tar -czf $3.tar.gz $2";;
	esac
}

function copyBlockCommand {
	echo "if=$3 of=$1/$2 &"
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

function fixRecordNumbers {
	awk '/#Backup/{sub(/#Backup_[0-9]*/,"#Backup_"++n)};{print}' cron.txt > cron.tmp
	cat cron.tmp > cron.txt
	rm cron.tmp	
}

function addBackupRecord {
	echo -e "\n\"New backup record\"" >&2
	read -p "Enter file name: " f_name
	read -p "Enter destination folder/file: " dest

	path=$(pwd | sed 's/ /\\ / g')

	if [ -f $f_name ]; then
		echo -e "\nThis is a file. Choose the backup method" >&2
		command=$(copyFileCommand "$path" "$f_name" "$dest")
	else 
		if [ -d $f_name ]; then
			echo -e "\nThis is a folder. Choose the backup method" >&2
			command=$(copyDirCommand "$path" "$f_name" "$dest")
		else 
			if [ -b $file_name ]; then
				echo -e "\nThis is a block file." >&2
				command=$(copyBlockCommand "$path" "$f_name" "$dest")
			fi
		fi	
	fi

	read -p "Repeat [y/n]?: " repeat

	case $repeat in
		Y|y) backup_time=$(inputTime)
			 crontab -l > cron.txt
			 echo -e "$backup_time $command #Backup_" >> cron.txt
			 fixRecordNumbers
			 crontab cron.txt
			 rm cron.txt;;
		N|n) eval $command;;
	esac
	echo -e "New backup record was created!\n" >&2
}

function printBackupRecords {
	echo -e "\nCurrent backup records:" >&2
	crontab -l > cron.txt
	sed -ni '/#Backup/p' cron.txt
	cat cron.txt && echo " "
	rm cron.txt
}

function deleteBackupRecord {
	read -p "Enter backup record number: " number

	crontab -l > cron.txt
	sed -i "/#Backup_$number/d" cron.txt
	fixRecordNumbers
	crontab cron.txt
	rm cron.txt
}

function deleteAllRecords {
	crontab -l > cron.txt
	sed -i "/#Backup/d" cron.txt
	crontab cron.txt
	rm cron.txt
}

answer=1

while [ $answer -ne 5 ]; do
	menu
	read -p "Select item: " answer

	case $answer in
		1) addBackupRecord;;
		2) printBackupRecords;;
		3) deleteBackupRecord;;
		4) deleteAllRecords;;
		5) answer=5;;
	esac
done


