#!/bin/bash

#Get the number of arguments inputted

ARGS=$#

#################### 0 ARGUMENTS or MORE THAN 4 ARGUMENTS  #######################
if [[ $ARGS -eq 0 ]] 
        then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
	exit 0
fi

if [[ $ARGS -gt 4 ]]
        then echo "Error: Too many arguemnts.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
        exit 0
fi


#################### 1 ARGUMENT #######################

	#1A) Checks if only 1 argument is placed and if it is an optional one

if [[ $ARGS -eq 1 ]]  && ([[ $1 = -[ca] ]] || [[ -d $1 ]])  
        then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
	exit 2	

	#1B) Else it means that if theres only 1 argument then it has to be the pattern

elif [[ $ARGS -eq 1 ]]
	then
	pattern1=$1

	   #If no files are found
           if [[ $(ls 2>/dev/null  *$pattern1* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern1 in its name in the current directory, $PWD"
		exit 1
	   
	   else
	   #If file is found, show only one of the results
                 ls  *$pattern1* | head -n 1
           fi
fi

#################### 2 ARGUMENTS #######################


	#2A) Case 2 Arguments: a and c
if [[ $ARGS -eq 2 ]]  && [[  $1 = -[ca] ]] && [[ $2 = -[ca] ]] 
        then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
	exit 3
fi

	#2B) Case 2 Arguments: a|c & path --> Should be illegal
if [[ $ARGS -eq 2 ]] && [[ $1 = -[ca] ]] && [[ -d $2 ]]
	then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
fi
	#2C) Case 2 Arguments: c and pattern
if [[ $ARGS -eq 2 ]] && [[ $1 = "-c" ]] && [[ ! -d $2 ]]
	then
        pattern2C=$2

           #If no files are found
           if [[ $(ls 2>/dev/null  *$pattern2C* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern2C in its name in the current directory, $PWD"
                exit 1

           else
           #If file is found, show all the results
                echo "==== Contents of: $PWD/`ls *$pattern2C* | head -n 1` ====" 
	   	cat `ls *$pattern2C* | head -n 1`
		echo ""
           fi
fi

	#2D) Case 2 Arguments: a and pattern

if [[ $ARGS -eq 2 ]] && [[ $1 = "-a" ]] && [[ ! -d $2 ]] 
        then
        pattern2D=$2

           #If no files are found, /dev/null simply hides the ls error message
           if [[ $(ls 2>/dev/null  *$pattern2D* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern2D in its name in the current directory, $PWD"
                exit 1

           else
           #If file is found, show all the results
                 ls -1 *$pattern2D*
           fi
fi


	#2E) Case 2 Arguments: Pattern and Path

pattern2E=$1      
path2E=$2 #Path will be second argument in this case

#Check if directory exists
if [[ $ARGS -eq 2 ]] && [[ $1 != -[ca] ]] && [[ ! -d $2 ]]
        then echo "Error $path2E is not a valid directory"

	#Is a valid directory, search for the pattern in i
fi
	
#If directory exists
if [[ $ARGS -eq 2 ]] && [[ $1 != -[ca] ]] && [[ -d $2 ]] 
	then
        pattern2E=$1
	path2E=$2

        #If no files are found
        if [[ $(ls 2>/dev/null $path2E/*$pattern2E* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern2E in its name in $path2E"
                exit 1

        else
        #If file is found, show only one of the results
          
            ls  $path2E/*$pattern2E* | head -n 1
		 
        fi
fi 

#################### 3 ARGUMENTS #######################
	#3A) All arguments are optional
if [[ $ARGS = 3 ]] &&  [[  $1 = -[ca] ]] && [[ $2 = -[ca] ]] && [[ -d $3 ]]
	then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
       	exit 30
fi

	#3B) -c -a Pattern 
if [[ $ARGS = 3 ]] &&  [[  $1 = -[ca] ]] && [[ $2 = -[ca] ]] && [[ ! -d $3 ]]  
	then

	 pattern3B=$3

 	#If no files are found, /dev/null simply hides the ls error message
        if [[ $(ls 2>/dev/null *$pattern3B* | wc -l) -eq 0  ]]
        	then echo "Unable to locate any files that has pattern $pattern3B in its name in the current directory, $PWD"
        exit 33

        else
            #If file is found, show all the results AND the contents of each file 
	    	for allfiles in *$pattern3B* 
			do  
                	
				echo "==== Contents of: $PWD/$allfiles  ===="
                		cat $allfiles
		done
           fi

	fi
#3C) Isn't a valid directory (-[ca] Pattern Path)
if [[ $ARGS = 3 ]] &&  [[  $1 = -[ca] ]] && [[ $2 != -[ca] ]] && [[ ! -d $3 ]]  
	then echo "Error $3 is not a valid directory"
	exit 32
fi
	
#3D) -a Pattern Path
if [[ $ARGS = 3 ]] &&  [[  $1 = "-a" ]] && [[ $2 != -[ca] ]] && [[ -d $3 ]]		
	then

        pattern3D=$2
	path3D=$3

           #If no files are found, /dev/null simply hides the ls error message
          if [[ $(ls 2>/dev/null $path3D/*$pattern3D* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern3D in its name in $path3D"
                exit 33

           else
           #If file is found, show all the results
                 ls -1  $path3D/*$pattern3D*
           fi 
       fi	
	#3E) -c Pattern path	
if [[ $ARGS = 3 ]] &&  [[  $1 = "-c" ]] && [[ $2 != -[ca] ]] && [[ -d $3 ]] 
                 then
        pattern3E=$2
        path3E=$3

           #If no files are found, /dev/null simply hides the ls error message
           if [[ $(ls 2>/dev/null $path3E/*$pattern3E* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern3E in its name in $path3E"
                exit 33

           else
	    #If file is found, show all the results
                echo "==== Contents of: `ls $path3E/*$pattern3E* | head -n 1` ====" 
                cat `ls $path3E/*$pattern3E* | head -n 1`
           fi   
        fi
	
#################### 4 ARGUMENTS #######################

#4A)Verify correct order of arguments

if [[ $ARGS -eq 4 ]] && ([[  $1 != -[ca] ]] || [[ $2 != -[ca] ]])
	then echo "Error missing the pattern argument.\n Usage ./seeker.sh [-c] [-a] pattern [path]"
	exit 40
fi

#4B) PATH not a directory case

if [[ $ARGS -eq 4 ]] && [[  $1 = -[ca] ]] && [[ $2 = -[ca] ]] && [[ ! -d $4 ]]
	then echo "Error $4 is not a valid directory"
        exit 41
fi

#4C) All parameters present

if [[ $ARGS -eq 4 ]] && ([[  $1 = -[ca] ]] && [[ $2 = -[ca] ]] && [[ -d $4 ]])
	 then
         pattern4C=$3
	 path4C=$4

	 #If no files are found, /dev/null simply hides the ls error message
           if [[ $(ls 2>/dev/null $path4C/*$pattern4C* | wc -l) -eq 0  ]]
                then echo "Unable to locate any files that has pattern $pattern4C in its name in $path4C"
                exit 42

           else
            #If file is found, show all the results AND the contents of each file
                for allfiles in $path4C/*$pattern4C*
		do
			echo "==== Contents of : $allfiles ===="
			cat $allfiles
                done
           fi
fi
