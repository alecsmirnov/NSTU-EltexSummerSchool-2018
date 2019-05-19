#!/bin/bash


ex=true

while (( $ex == true )); do
	path_file=$(zenity --entry --title="File editor" --text="Enter file name:"); ex=$?

	if (( $ex == true )) && [ -z "$path_file" ]; then
		zenity --error --text="The file name can't be empty!" 
	else 
		if (( $ex == true )); then
			text=$(cat "$path_file")
			edit_text=$(echo -n "$text" | zenity --text-info --editable \
							     --width=550 --height=500)	
			echo -n "$edit_text" > $path_file; ex=1
		fi
	fi
done



