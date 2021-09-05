/*
Program to generate a report on the sutdents having the top top cgpas
*********************************************************************
* Author              Dept.           Date            Notes
*********************************************************************
* Xiangyun W.    Electrical Eng.   Apr. 04 2021        Initial Version
* Xiangyun W.    Electrical Eng.   Apr. 06 2021        Comments
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFSIZE 100 // buffer size

// linked list node
struct StudentRecord{
    long sid;
    char email[30];
    char lname[20];
    char fname[20];
    float cgpa;
    struct StudentRecord* next;
};

// linked list insertion
void insert(struct StudentRecord** head, struct StudentRecord** tail, struct StudentRecord* element){
    if(*head == NULL){    // if there is not a list
        (*head) = element;
        (*tail) = element;
    }else{
        int added = 0;
        if((*head)->cgpa<=element->cgpa){
            //add before head
            element->next = (*head);
            // update head
            (*head) = element;
        }else{  // add after head
            struct StudentRecord* compare = (*head);
            while(compare->next != NULL){ // if next node is not null
                if(element->cgpa>=compare->next->cgpa){ // compare if next node smaller
                    // add to list
                    element->next = compare->next;
                    compare->next = element;
                    added = 1;
                    break;
                }
                compare = compare->next;
            }
            if (!added){  // if not added, add to tail
                // add to tail
                (*tail)->next = element;
                // update tail
                (*tail) = element;
            }
        }
    }
}

// linked list free
void linked_list_free(struct StudentRecord* head){
    struct StudentRecord* to_be_cleared = head;
    struct StudentRecord* next_to_be_cleared = NULL;
    while(to_be_cleared != NULL){
        next_to_be_cleared = to_be_cleared->next;
        free(to_be_cleared);
        to_be_cleared = next_to_be_cleared;
    }

}

// insert tester, just for testing
void test_insert(struct StudentRecord* head){
    struct StudentRecord* next = head;
    if(head == NULL){
        puts("Empty");
    }
    while(next != NULL){
        printf("%lf\n",next->cgpa);
        next = next->next;
    }
}

int main (int argc, char* argv[]){
    // check if num of arguments is correct
    if(argc != 3){
        printf("Usage ./topcgpas <sourcescv> <outputcsv>\n");
        return 1;
    }
    // check if file can be opened
    FILE *rfp = fopen(argv[1],"r");
    if(rfp == NULL){
        printf("Error! Unable to open the input file %s\n", argv[1]);
        return 1;
    }

    char buffer[BUFSIZE] = {0}; // read in buffer
    // check if file is empty
    if(fgets(buffer,BUFSIZE,rfp)==NULL){
        printf("Error! Input CSV file %s is empty\n", argv[1]);
        return 1;
    }
    // check if file only has one line
    if(fgets(buffer,BUFSIZE,rfp)==NULL){
        printf("Error! Input CSV file %s is empty\n", argv[1]);
        return 1;
    }

    // construct linked list
    struct StudentRecord* head = NULL;
    struct StudentRecord* tail = NULL;
    while(1){
        struct StudentRecord* current = (struct StudentRecord*)malloc(sizeof(struct StudentRecord));
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
        // get the first token, seperated by ","
        char* token = strtok(buffer,",");
        current->sid = strtol(token,NULL,10);
        // second token
        token = strtok(NULL, ",");
        strcpy(current->email,token);
        // third token
        token = strtok(NULL, ",");
        strcpy(current->lname,token);
        // fourth token
        token = strtok(NULL, ",");
        strcpy(current->fname,token);
        // fifth token
        token = strtok(NULL, ",");
        current->cgpa = strtof(token,NULL);
        // insert the new node to the list
        insert(&head,&tail,current);
        // if no more line, break
        if(fgets(buffer,BUFSIZE,rfp)==NULL){
            break;
        }
    }

    // contruct output file
    FILE* wfp = fopen(argv[2],"w");
    if (wfp==NULL){
        printf("Error! Unable to open the output file %s\n",argv[2]);
        return 1;
    }
    // write header to output file
    fprintf(wfp,"sid,email,cgpa\n");
    int keep_writing = 1;
    int counter = 0;
    struct StudentRecord* tmp = NULL;
    // if keep writing is true or if number of counter is less than 5
    while(keep_writing||counter<5){
        tmp = head;
        if(tmp != NULL){
            if(counter == 0){ // for the format of output file, first line is a special case
                fprintf(wfp,"%ld,%s,%.1f",tmp->sid,tmp->email,tmp->cgpa);
            }else{  // starting from the second line, add "/n" before each line
                fprintf(wfp,"\n%ld,%s,%.1f",tmp->sid,tmp->email,tmp->cgpa);
            }
            counter++;
            if(tmp->next!=NULL){  // if next node is not null
                if(tmp->cgpa == tmp->next->cgpa){ // if next gpa is the same as current gpa
                    keep_writing = 1; // set keep writing to 1
                }else {
                    keep_writing = 0; // otherwise, set to 0
                }
            }
        }else{ // if no next node, break
            break;
        }
        head = head->next;  // update head
        free(tmp);  // free memory
    }

    fclose(wfp);  // close file
    fclose(rfp);  // close file
    linked_list_free(head); // free linked list
    return 0; // exit with 0
}
