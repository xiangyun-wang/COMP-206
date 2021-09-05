#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ZoomRecord
{
    char email[60]; // email fo the student
    char name[60]; // name of the student
    int durations[9]; // duration for each lab
    struct ZoomRecord *next;
};

struct ZoomRecord* addZoomRecord(struct ZoomRecord** head, struct ZoomRecord* element);
void generateAttendance(struct ZoomRecord* head, FILE* wfp);