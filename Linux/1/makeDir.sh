#!/bin/bash

read -p "Enter dir: " dir

read -p "Enter folder name: " f_name
read -p "Enter folders count: " f_count

read -p "Enter subfolder name: " sf_name
read -p "Enter subfolders count: " sf_count

read -p "Enter file_name: " fl_name
read -p "Enter files count: " fl_count

eval mkdir -p $dir/$f_name\_{01..$(($f_count))}/$sf_name\_{01..$(($sf_count))}
eval touch $dir/$f_name\_{01..$(($f_count))}/$sf_name\_{01..$(($sf_count))}/$fl_name\_{01..$(($fl_count))}

echo Created.
