#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "macastillo" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1 
fi
response="Yes"
while [ $response != "No" ]
do
   echo "Enter Radius of Circle: "
   read radius
   pi=3.14159 #defines pi
   area=$(echo $radius \* $radius \* $pi | bc) #finds the area of the circle, bc allows us to mulitply floats
   echo "The area of the circle is $area"
   echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done

