#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

int main(){ 
    int cap=2;
    int count=0;
    Student *s = malloc(cap * sizeof(Student));

    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    
}