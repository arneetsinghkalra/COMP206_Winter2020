#!/bin/bash
#If the a3config file is not found, give custom error
if [[ ! -f a3config ]] 
	then 
		echo "Error cannot find a3config"
		exit 1
fi

#File exits, use it as source
source a3config

if [[ -z "$DIRNAME" || -z "$EXTENSION" ]] 
then
	echo "Error DIRNAME and EXTENSION must be set"
	exit 2
fi

#Check if directory does not exist
if [[ ! -d $DIRNAME ]]
then
	echo "Error directory $DIRNAME does not exist"
	exit 3
fi

#Check if file does not exist at that directory
#If not found, redirect ls error code and give personal error message
#Check if number of files is 0, if so then no files exist
if [[ $(ls 2>/dev/null $DIRNAME/*.$EXTENSION | wc -l) -eq 0  ]]
then
	echo "Unable to locate any files with extension $EXTENSION in $DIRNAME"
	exit 0
fi

#File does exist at directory, now check SHOW variable
if [[ $SHOW = "true" ]]
then
	#List names of files with contents of each, exit 0 code
	for allfiles in $DIRNAME/*.$EXTENSION
		do
			echo $allfiles
			cat $allfiles
	done

	exit 0
else
	#Otherwise don't show contents, exit 0 code
	ls $DIRNAME/*.$EXTENSION | cat
	exit 0
fi
