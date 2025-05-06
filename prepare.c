
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTS 5
#define MAX_NAME_LEN 50

// Faculty structure for linked list
struct Faculty {
    char name[MAX_NAME_LEN];
    int id;
    char specialization[50];
    struct Faculty* next;
};

// Department array with linked lists
struct Faculty* departments[MAX_DEPTS] = {NULL};
const char* dept_names[MAX_DEPTS] = {"CSE", "ECE", "Civil", "Mech", "EEE"};

// Function prototypes
void add_faculty();
void display_all();
void search_faculty();
void free_memory();

int main() {
    int choice;
    
    do {
        printf("\nCollege Department Management\n");
        printf("1. Add Faculty Member\n");
        printf("2. Display All Departments\n");
        printf("3. Search Faculty\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: add_faculty(); break;
            case 2: display_all(); break;
            case 3: search_faculty(); break;
            case 4: free_memory(); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 4);
    
    return 0;
}

void add_faculty() {
    int dept_choice;
    printf("\nAvailable Departments:\n");
    for(int i = 0; i < MAX_DEPTS; i++) {
        printf("%d. %s\n", i+1, dept_names[i]);
    }
    printf("Select department (1-5): ");
    scanf("%d", &dept_choice);
    
    if(dept_choice < 1 || dept_choice > MAX_DEPTS) {
        printf("Invalid department selection!\n");
        return;
    }

    struct Faculty* new_faculty = (struct Faculty*)malloc(sizeof(struct Faculty));
    if(!new_faculty) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Faculty ID: ");
    scanf("%d", &new_faculty->id);
    printf("Enter Faculty Name: ");
    scanf("%s", new_faculty->name);
    printf("Enter Specialization: ");
    scanf("%s", new_faculty->specialization);
    
    // Insert at beginning
    new_faculty->next = departments[dept_choice-1];
    departments[dept_choice-1] = new_faculty;
}

void display_all() {
    printf("\nDepartment Faculty List:\n");
    for(int i = 0; i < MAX_DEPTS; i++) {
        printf("\n%s Department:\n", dept_names[i]);
        struct Faculty* current = departments[i];
        while(current) {
            printf("ID: %d, Name: %s, Specialization: %s\n",
                   current->id, current->name, current->specialization);
            current = current->next;
        }
    }
}

void search_faculty() {
    char search_name[MAX_NAME_LEN];
    printf("Enter faculty name to search: ");
    scanf("%s", search_name);
    
    for(int i = 0; i < MAX_DEPTS; i++) {
        struct Faculty* current = departments[i];
        while(current) {
            if(strcmp(current->name, search_name) == 0) {
                printf("Found in %s Department:\n", dept_names[i]);
                printf("ID: %d, Specialization: %s\n",
                       current->id, current->specialization);
                return;
            }
            current = current->next;
        }
    }
    printf("Faculty not found!\n");
}

void free_memory() {
    for(int i = 0; i < MAX_DEPTS; i++) {
        struct Faculty* current = departments[i];
        while(current) {
            struct Faculty* temp = current;
            current = current->next;
            free(temp);
        }
        departments[i] = NULL;
    }
    printf("Memory freed. Exiting...\n");
}
