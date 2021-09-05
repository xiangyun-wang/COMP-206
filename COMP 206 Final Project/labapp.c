/*
Program to generate a report on the sutdents attendance
*********************************************************************
* Author              Dept.           Date            Notes
*********************************************************************
* Xiangyun W.    Electrical Eng.   Apr. 23 2021        Initial Version
* Xiangyun W.    Electrical Eng.   Apr. 26 2021        Comments
*/

#include "zoomrecs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 200 // buffer size

// insert tester, just for testing
void test_insert(struct ZoomRecord* head){
    struct ZoomRecord* next = head;
    if(head == NULL){
        puts("Empty");
    }
    while(next != NULL){
        //printf("%s\n",next->name);
        printf("%s", next->name);
        for (int i = 0; i<9; i++){
            printf("%d, ",next->durations[i]);
        }
        printf("\n");
        next = next->next;
    }
}

// linked list free
void linked_list_free(struct ZoomRecord* head){
    struct ZoomRecord* to_be_cleared = head;
    struct ZoomRecord* next_to_be_cleared = NULL;
    while(to_be_cleared != NULL){
        next_to_be_cleared = to_be_cleared->next;
        free(to_be_cleared);
        to_be_cleared = next_to_be_cleared;
    }

}

int main (int argc, char* argv[]){
    // check if argument number is correct
    if(argc != 3){
        printf("Usage ./labapp <sourcescv> <outputcsv>\n");
        return 1;
    }
    // check if file can be opened
    FILE *rfp = fopen(argv[1],"r");
    if(rfp == NULL){
        printf("Error! Unable to open the input file %s\n", argv[1]);
        return 1;
    }
    
    char buffer[BUFSIZE] = {0}; // read in buffer

    //get first line (header)
    if(fgets(buffer,BUFSIZE,rfp)==NULL){
        printf("Error! Input CSV file %s is empty\n", argv[1]);
        return 1;
    }
    //get second line (data)
    if(fgets(buffer,BUFSIZE,rfp)==NULL){
        printf("Error! Input CSV file %s is empty\n", argv[1]);
        return 1;
    }

    struct ZoomRecord* head = NULL;
    int lab_number = 0;
    while(1){
        struct ZoomRecord* current = (struct ZoomRecord*)malloc(sizeof(struct ZoomRecord));
        memset(current,0,sizeof(struct ZoomRecord));
        // no more memory space, error on malloc will return NULL
        if(current == NULL){
            puts("Error! program ran out of memory\n");
            linked_list_free(head);
            free(current);
            return 1;
        }

        // change the last char to 0
        if(buffer[strlen(buffer)-1]=='\n'){
            buffer[strlen(buffer)-1]=0;
        }
        // get the first token, seperated by ",", email
        char* token = strtok(buffer,",");
        strcpy(current->email,token);
        // second token, name
        token = strtok(NULL, ",");
        strcpy(current->name,token);
        // third token, lab
        token = strtok(NULL, ",");
        lab_number = token[0]-'A';
        // fourth token, duration
        token = strtok(NULL, ",");
        current->durations[lab_number] = atoi(token);   //array to hold all durations
        // insert the new node to the list
        head = addZoomRecord(&head,current);    // update head after new element added to the list
        // if no more line, break
        if(fgets(buffer,BUFSIZE,rfp)==NULL){    // if no more data in file, break
            break;
        }
    }
    fclose(rfp);    // close file

    FILE* wfp = fopen(argv[2],"w"); //open file to write
    // check if can be opened
    if (wfp==NULL){
        printf("Error! Unable to open the output file %s\n",argv[2]);
        return 1;
    }

    // generate output attendance.csv file
    generateAttendance(head, wfp);

    //test_insert(head);

    fclose(wfp);    // close file
    linked_list_free(head);     // free list
    return 0;
}