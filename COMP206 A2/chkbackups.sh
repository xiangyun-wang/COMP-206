#!/bin/bash

exec 2>/dev/null       # suppress other errors and exceptions

CurrentDir=$(pwd)       # get current directory

if [[ $# -eq 2 ]] ; then    # if there is a source directory specified
   if [[ ! -d $2 ]] ; then  # if the source directory does not exist
        echo "Error!! $2 is not a valid directory"
        exit 1
    else                    # if the specified source directory exists
        cd $2               # navigate to source directory 
        SourceDir=$(pwd)    # get the absolute directory of source directory
        cd $CurrentDir      # navigate back to the original directory
    fi
elif [[ $# -eq 1 ]] ; then  # if the source directory is not specified
   SourceDir=$(pwd)         # set the source directory to current folder
else               # else the number of input is not corrent
    echo "Usage: ./chkbackups.sh backupdirname [sourcedir]"
    exit 1;
fi

if [[ ! -d $1 ]] ; then     # if the backup directory does not exist
    echo "Error!! $1 is not a valid directory"
    exit 1
else                        # if backup directory exists
    cd $1                   # navigate to backup directory
    BackupDir=$(pwd)        # get the absolute backup directory
    cd $CurrentDir          # navigate back to original directory
fi

if [[ $(ls $SourceDir | wc -l) -eq 0 ]] ; then  # if number of files in source directory is zero
    echo "Error!! $SourceDir has no files"
    exit 1
fi

Date=$(date +"%Y%m%d")      # get date in the desired format
AllBackedUp=1               # set a flag for whether all the files are backed up

for FileName in $(ls $SourceDir)    # for all the files in the source directory
do
    if [[ ! -f "$BackupDir/$FileName.$Date" ]] ; then   # check in the back directory if the backup file exists
        echo "$FileName does not have a backup for today"
        AllBackedUp=0       # if not, set the all backup flag to 0
    fi
done

if [[ $AllBackedUp -eq 1 ]] ; then      # if all files are backed up
    echo "All files in $SourceDir have backups for today in $BackupDir"
fi

exit 0