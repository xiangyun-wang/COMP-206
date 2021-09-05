#!/bin/bash

# exec 2>/dev/null   # suppress all other errors and exceptions

if [[ $# -ne 2 ]] ; then    # if number of inputs is not correct
    echo "Usage fixformat.sh <dirname> <opfile>"
    exit 1

elif [[ ! -d $1 ]] ; then   # if directory does not exist
    echo "Error $1 is not a valid directory"
    exit 1
fi

# header
echo "User Email,Name (Original Name),Lab,Total Duration (Minutes)" > $2
# find files with proper name
for FileName in $(find $1 -name "[Ll][Aa][Bb]-[AaBbCcDdEeFfGgHhIi].csv" -type f)
do
    base_name=$(basename $FileName .csv)    # get base file name
    lab=${base_name:4:5}                    # get lab number (letter)
    # if first line, skip, for each line, check format by the field number
    # for each format, output different fields
    # redirect output to destination file
    awk -v lab_name=$lab 'BEGIN {FS = ",";first=1}{
        if(first==1) {first=0} else{
            if(NF==4){
                print $2 "," $1 "," toupper(lab_name) "," $3;
            }else{
                print $2 "," $1 "," toupper(lab_name) "," $5;
            }
        }
    }' $FileName >> $2

done

exit 0