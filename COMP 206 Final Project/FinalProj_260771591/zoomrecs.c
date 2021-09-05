/*
methods to form student linkedlist and form output attendance file
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

struct ZoomRecord* addZoomRecord(struct ZoomRecord** head, struct ZoomRecord* element){
    if(*head == NULL){    // if there is not a list
        (*head) = element;
    }else{
        int added = 0;
        if(strcmp((*head)->email,element->email)>0){
            //add before head
            element->next = (*head);
            return element;
        }else{  // add after head or find the same email
            struct ZoomRecord* compare = (*head);
            while(compare != NULL){ // if next node is not null
                if(strcmp(compare->email,element->email)==0){ // compare if email the same
                    // add to list (not creating a new node, just add to duration array)
                    for(int i = 0; i<9; i++){
                        compare->durations[i] = compare->durations[i] + element->durations[i];
                    }
                    free(element);  //free element
                    added = 1;
                    break;
                } else if(compare->next != NULL && strcmp(compare->next->email,element->email)>0){  // compare if next node larger, if larger, add before
                    element->next = compare->next;
                    compare->next = element;
                    added = 1;
                    break;
                }
                if(compare->next == NULL){  // if no next node, break
                    break;
                }
                compare = compare->next;
            }
            if (!added){  // if not added, add to tail
                // add to tail
                compare->next = element;
            }
        }
    }
    return (*head);
}

void generateAttendance(struct ZoomRecord* head, FILE* wfp){
    // print header
    fprintf(wfp,"User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)\n");
    struct ZoomRecord* current = head;
    double sum = 0;
    while (current != NULL){
        // reset and get sum of the qualified attendance
        sum = 0;
        for (int i=0;i<9;i++){
            if(current->durations[i] >= 45){
                sum=sum+1;
            }
        }
        // print to the file
        fprintf(wfp,"%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n",
        current->email,current->name,current->durations[0],current->durations[1],current->durations[2],
        current->durations[3],current->durations[4],current->durations[5],current->durations[6],
        current->durations[7],current->durations[8],sum/9.0*100);
        // update current (print next node)
        current = current->next;
    }
}