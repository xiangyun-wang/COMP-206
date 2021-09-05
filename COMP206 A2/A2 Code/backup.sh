#!/bin/bash

exec 2>/dev/null   # suppress all other errors and exceptions

if [[ $# -ne 2 ]] ; then    # if number of inputs is not correct
    echo "Usage: ./backup.sh backupdirname filetobackup"
    exit 1

elif [[ ! -d $1 ]] ; then   # if directory does not exist
    echo "Error!! $1 is not a valid directory"
    exit 1

elif [[ ! -f $2 ]] ; then   # if file does not exist
    echo "Error!! $2 is not a valid file"
    exit 1
fi

FileName=$(basename $2)     # get file name from the directory
Date=$(date +"%Y%m%d")      # get date in the desired format
FileNameWithDate="$FileName.$Date"  # new name for the backup file
BackupName="$1/$FileNameWithDate"   # backup directory with file name

if [[ -f $BackupName ]] ; then      # check if the backup file already existed
    echo "Backup file already exists for $Date"
    exit 1
fi

cp $2 $BackupName       # backup the file to the desired directory
exit 0