#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

Student *add_student(Student *s, int *count, int *cap, int id, const char *name, float marks) {
    if (*count == *cap) {
        Student *temp = realloc(s, (*cap * 2) * sizeof(Student));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(s);
            return NULL;
        }
        s = temp;
        *cap *= 2;  
    }

    s[*count].id = id;
    snprintf(s[*count].name, sizeof(s[*count].name), "%s", name);
    s[*count].marks = marks;
    (*count)++;
    return s;
}

Student *search(Student *s, int count, int id) {
    for(int i=0;i<count;i++){
        if(s[i].id == id){
            return &s[i];
        }
    }
    return NULL;
}

Student *highest(Student *s, int count){
    if (count == 0) {
        return NULL;  
    }

    Student *top = &s[0];
    for(int i=1;i<count;i++){
        if(s[i].marks > top->marks){
            top = &s[i];
        }
    }
    return top;
}

int main(){ 
    int cap=2;
    int count=0;
    int choice;
    Student *s = malloc(cap * sizeof(Student));

    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    FILE *f = fopen("students.txt", "r");

    if (f == NULL) {
        fprintf(stderr, "Could not open file for reading\n");
        return 1;
    }

    Student temp;
    while(fscanf(f, "%d %49s %f", &temp.id, temp.name, &temp.marks) == 3){
        s = add_student(s, &count, &cap, temp.id, temp.name, temp.marks);
        if (s == NULL) {  
            fclose(f);
            return 1;  
        }
    }
    fclose(f);

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
                
                printf("Enter Student ID: ");
                scanf("%d", &temp.id);
                printf("Enter Student Name: ");
                scanf("%s", temp.name);
                printf("Enter Student Marks: ");
                scanf("%f", &temp.marks);

                s = add_student(s, &count, &cap, temp.id, temp.name, temp.marks);
                if (s == NULL) {   
                    return 1;  
                }
                
                break;

            case 2:
                printf("Student List:\n");
                for(int i = 0; i < count; i++){
                    printf("ID: %d, Name: %s, Marks: %.2f\n", s[i].id, s[i].name, s[i].marks);
                }
                break;

            case 3:
                printf("Enter Student ID to search: ");
                int id;
                scanf("%d", &id);
                Student *found = search(s, count, id);
                if (found != NULL) {
                    printf("Student found: ID: %d, Name: %s, Marks: %.2f\n", found->id, found->name, found->marks);
                } else {
                    printf("Student not found.\n");
                }
                break;

            case 4:
                printf("Enter Student ID to update marks: ");
                scanf("%d", &id);
                found = search(s, count, id);
                if (found != NULL) {
                    printf("Enter new marks for %s: ", found->name);
                    scanf("%f", &found->marks);
                    printf("Marks updated successfully.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;

            case 5:

                Student *top = highest(s, count);
                if (top == NULL) {  
                    printf("No students available to find top scorer.\n");
                    break;
                }
                printf("Top Scorer: ID: %d, Name: %s, Marks: %.2f\n", top->id, top->name, top->marks);
                break;

            case 6:
                f = fopen("students.txt", "w");
                if (f == NULL) {
                    fprintf(stderr, "Could not open file for writing\n");
                    free(s);
                    return 1;
                }
                for(int i = 0; i < count; i++){
                    fprintf(f, "%d %s %.2f\n", s[i].id, s[i].name, s[i].marks);
                }
                free(s);
                fclose(f);
                return 0;

        }
    }
}