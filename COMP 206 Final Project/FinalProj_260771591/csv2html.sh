#!/bin/bash

if [[ $# -ne 2 ]] ; then    # if number of inputs is not correct
    echo "Usage fixformat.sh <dirname> <opfile>"
    exit 1

elif [[ ! -f $1 ]] ; then   # if file does not exist
    echo "Error $1 is not a file"
    exit 1
fi
# for each line, add <TD> and </TD> at beginning and end
# then, add <TR> and </TR> at beginning and end of each line
# then, repalce all comma with </TD><TD>
# finally, add <TABLE> and </TABLE> at beginning and end of the file
sed -e 's/^/<TD>/' -e 's/$/<\/TD>/' -e 's/^/<TR>/' -e 's/$/<\/TR>/' -e 's/,/<\/TD><TD>/g' -e '1 i <TABLE>' -e '$a <\/TABLE>' $1 > $2

exit 0