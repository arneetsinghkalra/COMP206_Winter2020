#!/bin/bash

#User-created variables 
file=$1
tarfile=$2

#Check if both paramaters are present first
if [[ $# -lt 2 ]] 
	then echo "Usage ./tarzan.sh filename tarfile"
	exit 1

#Verification that TAR file exists
elif [[ ! -r $tarfile ]]
	then echo "Error cannot find tar file $tarfile"
	exit 2


#Check if file is not in the tar file using grep search
elif [[ $(tar -tvf $tarfile | grep "$file") == "" ]] 
	then echo "$file does not exist in $tarfile"
else 
	echo "$file exists in $tarfile"
fi


