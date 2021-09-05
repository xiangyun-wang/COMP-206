#!/bin/bash

exec 2> /dev/null

if [[ $# -ne 1 ]] ; then    # check number of inputs
    echo "Usage: ./dataformatter.sh sensorlogdir"
    exit 1

elif [[ ! -d $1 ]] ; then   # check if the input directory is valid
    echo "Error!! $1 is not a valid directory name"
    exit 1
fi

# find files with the desired name in the input directory and sub-directory
for FileName in $(find $1 -name "sensordata-*.log" -type f)

do
    echo "Processing sensor data set for $FileName"   #output format
    echo "Year,Month,Hour,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5"  #output format
    # for files with desired name, get the desired lines(lines with sensor readouts)
    # then reformating each lines, so that desired data can be easily extracted
    # change the first two "-" to ",", change the first space to ",", and change the first ":" to space
    # so that the first field of the line would be the time with the desired format

    # then the desired data can be extracted and printed using awk
    # set field separater to " ", and initialize 5 variables to store previous values
    # if current value is "ERROR", then change it to the previous values
    # if current value is not "ERROR", then update previous variable

    # finally, print out the data in the desired format
     grep -e "sensor readouts" $FileName | sed -e 's/-/,/' -e 's/-/,/' -e 's/ /,/' -e 's/:/ /' |
    awk 'BEGIN {FS = " ";prev1=0;prev2=0;prev3=0;prev4=0;prev5=0}
    {if ($5=="ERROR") {$5=prev1} else {prev1=$5}}
    {if ($6=="ERROR") {$6=prev2} else {prev2=$6}}
    {if ($7=="ERROR") {$7=prev3} else {prev3=$7}}
    {if ($8=="ERROR") {$8=prev4} else {prev4=$8}}
    {if ($9=="ERROR") {$9=prev5} else {prev5=$9}}
    {print $1 "," $5 "," $6 "," $7 "," $8 "," $9}'
    echo "==========================================="

    echo "Readout statistics" # output format
    echo "Year,Month,Hour,MaxTemp,Sensor,MinTemp,MinSenor" # output format
    # start with the same implementation as the previous section, reformat data
    # then use awk to find the min and max of each lines
    # initialize Min and Max to -100 and 100, and initialize the MaxSen and MinSen to 0 (they are used to track which sensor has the min and max value)
    # the sensor data starts from the fifth field, so the for loop starts from 5 and ends at 9
    # if data is not "ERROR" and if the data is min or max, update min or max, and also from which sensor the min or max measured
    # finally, output the desired data
     grep -e "sensor readouts" $FileName | sed -e 's/-/,/' -e 's/-/,/' -e 's/ /,/' -e 's/:/ /' |
    awk 'BEGIN {FS = " "; S="Sensor"; Max=-100; Min=100; MaxSen=0; MinSen=0}
    {for (i=5;i<10;i++) {
        if($i!="ERROR"){
            {if($i>Max){ Max = $i; MaxSen=i-4}} 
            {if($i<Min) {Min = $i; MinSen=i-4}}
        } 
    }}
    {print $1 "," Max ",Sensor" MaxSen "," Min ",Sensor" MinSen} {Max = -100; Min = 100}'
    echo "=========================================="

done

echo "Sensor error statistics" # output format
echo "Year,Month,Day,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Total" # output format

for FileName2 in $(find $1 -name "sensordata-*.log" -type f)  #loop over all qualified files
do
    # initialize 5 variables for error count
    # for each line, check for the readings from each sensor
    # if the sensordata is "ERROR", increase the corresponding error count by 1
    # finally, output the data with desired format
     grep -e "sensor readouts" $FileName2 | sed -e 's/-/,/' -e 's/-/,/' |
    awk 'BEGIN {FS = " "; s1=0; s2=0; s3=0; s4=0; s5=0}
    {if ($5=="ERROR") {s1=s1+1}}
    {if ($6=="ERROR") {s2=s2+1}}
    {if ($7=="ERROR") s3=s3+1}
    {if ($8=="ERROR") s4=s4+1}
    {if ($9=="ERROR") s5=s5+1}
    END {print $1 "," s1 "," s2 "," s3 "," s4 "," s5 "," s1+s2+s3+s4+s5}'
    
    # separate feilds by "," (-t ,)
    # sort by key 9 in reverse (normally, -k sort from smallest to largest)
    # if error number the same, sort using key 1 to 3 (time)
done | sort -t , -k9,9r -k1,3
echo "=========================================="
exit 0
