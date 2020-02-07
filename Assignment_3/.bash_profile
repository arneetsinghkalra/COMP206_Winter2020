echo "Welcome to $HOSTNAME!"

#Show number of login sessions
#From list of active users, find your username and list the total count
sessions=$(who | grep akalra4 | wc -l)
echo "You have $sessions login sessions to this host."

alias comp206="cd ~/Projects/COMP206"

#Run the fortune command
fortune

#Changing the shell prompt
#\u adds your username, \h adds hostname, \t adds time, \w adds pwd
PS1="\[\033[01;32m\]\u@\h\[\033[01;36m\][\t]\[\033[00m\]:\w$ "

#For Part 6 of question 1, I decided to change the colors for the different parts of the prompt:
# The username and hostname are in green due to \[\033[01;32m\]
# The time is in cyan \[\033[01;34m\]
# The rest is in white \[\033[00m\]
