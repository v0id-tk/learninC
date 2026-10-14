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
    int choice;
    Student *s = malloc(cap * sizeof(Student));

    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    while(1){
        printf("1. Add a Student\n");
        printf("2. Display all Students\n");
        printf("3. Search a Student by ID\n");
        printf("4. Update Student Marks\n");
        printf("5. Find top scorer\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                if(count == cap){
                    Student *temp = realloc(s, (cap * 2) * sizeof(Student));
                    if (temp == NULL) {
                        fprintf(stderr, "Memory reallocation failed\n");
                        free(s);
                        return 1;
                    }
                    s = temp;
                    cap *= 2;  
                }

                printf("Enter Student ID: ");
                scanf("%d", &s[count].id);
                printf("Enter Student Name: ");
                scanf("%s", s[count].name);
                printf("Enter Student Marks: ");
                scanf("%f", &s[count].marks);
                count++;
                break;

            case 2:
                printf("Student List:\n");
                for(int i = 0; i < count; i++){
                    printf("ID: %d, Name: %s, Marks: %.2f\n", s[i].id, s[i].name, s[i].marks);
                }
                break;

            case 3:
        }
    }
}