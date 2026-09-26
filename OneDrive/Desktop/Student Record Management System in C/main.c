#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50
#define DEPARTMENT_LENGTH 50
#define DATA_FILE "students.txt"

typedef struct Student {
    int id;
    char name[NAME_LENGTH];
    char department[DEPARTMENT_LENGTH];
    float cgpa;
} Student;

typedef struct StudentNode {
    Student record;
    struct StudentNode *next;
} StudentNode;

static StudentNode *head = NULL;

static void discardRestOfLine(void);
static int readInt(const char *prompt, int *value);
static int readFloat(const char *prompt, float *value);
static int readText(const char *prompt, char *buffer, size_t size);
static void freeAll(void);
static void saveToFile(void);
static void loadFromFile(void);

/* Return the first node whose student ID matches, or NULL if none exists. */
StudentNode *searchStudent(int id)
{
    StudentNode *current = head;

    while (current != NULL) {
        if (current->record.id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void addStudent(void)
{
    StudentNode *newNode;
    StudentNode *current;
    int id;

    if (!readInt("Enter student ID: ", &id)) {
        printf("Invalid student ID.\n");
        return;
    }

    if (searchStudent(id) != NULL) {
        printf("A student with that ID already exists.\n");
        return;
    }

    newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->record.id = id;
    if (!readText("Enter name: ", newNode->record.name, NAME_LENGTH) ||
        !readText("Enter department: ", newNode->record.department,
                  DEPARTMENT_LENGTH) ||
        !readFloat("Enter CGPA (0.0 - 10.0): ", &newNode->record.cgpa) ||
        newNode->record.cgpa < 0.0f || newNode->record.cgpa > 10.0f) {
        printf("Invalid student details. Student was not added.\n");
        free(newNode);
        return;
    }

    newNode->next = NULL;

    /* Walk to the final node. Its next pointer is NULL, so it can point to
       the new node without changing any existing record links. */
    if (head == NULL) {
        /* For an empty list, head directly becomes the first node. */
        head = newNode;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Student added successfully.\n");
}

void displayAll(void)
{
    StudentNode *current = head;

    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-24s %-24s %-6s\n", "ID", "Name", "Department", "CGPA");
    printf("-------------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%-10d %-24s %-24s %-6.2f\n",
               current->record.id,
               current->record.name,
               current->record.department,
               current->record.cgpa);
        current = current->next;
    }
}

void updateStudent(int id)
{
    StudentNode *student = searchStudent(id);
    char name[NAME_LENGTH];
    char department[DEPARTMENT_LENGTH];
    float cgpa;

    if (student == NULL) {
        printf("Student ID not found.\n");
        return;
    }

    if (!readText("Enter new name: ", name, NAME_LENGTH) ||
        !readText("Enter new department: ", department, DEPARTMENT_LENGTH) ||
        !readFloat("Enter new CGPA (0.0 - 10.0): ", &cgpa) ||
        cgpa < 0.0f || cgpa > 10.0f) {
        printf("Invalid student details. Record was not updated.\n");
        return;
    }

    strcpy(student->record.name, name);
    strcpy(student->record.department, department);
    student->record.cgpa = cgpa;
    printf("Student updated successfully.\n");
}

void deleteStudent(int id)
{
    StudentNode *current = head;
    StudentNode *previous = NULL;

    while (current != NULL && current->record.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student ID not found.\n");
        return;
    }

    /* If previous is NULL, current is the head. Otherwise, bypass current by
       linking the previous node directly to current's successor. */
    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    /* current is now detached from the list, so its allocated memory is safe
       to release. This also handles deleting the only node. */
    free(current);
    printf("Student deleted successfully.\n");
}

static void saveToFile(void)
{
    FILE *file = fopen(DATA_FILE, "w");
    StudentNode *current = head;

    if (file == NULL) {
        printf("Could not open %s for writing.\n", DATA_FILE);
        return;
    }

    while (current != NULL) {
        fprintf(file, "%d %s %s %.2f\n",
                current->record.id,
                current->record.name,
                current->record.department,
                current->record.cgpa);
        current = current->next;
    }

    fclose(file);
    printf("Records saved to %s.\n", DATA_FILE);
}

static void loadFromFile(void)
{
    FILE *file = fopen(DATA_FILE, "r");
    Student record;

    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%d %49s %49s %f",
                  &record.id, record.name, record.department,
                  &record.cgpa) == 4) {
        StudentNode *newNode = malloc(sizeof(*newNode));
        StudentNode *current;

        if (newNode == NULL) {
            printf("Memory allocation failed while loading records.\n");
            break;
        }

        newNode->record = record;
        newNode->next = NULL;

        /* Append loaded nodes using the same links as interactive insertion;
           this preserves file order and keeps head correct for the first node. */
        if (head == NULL) {
            head = newNode;
        } else {
            current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    fclose(file);
}

static void freeAll(void)
{
    StudentNode *current = head;

    while (current != NULL) {
        StudentNode *next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}

static void discardRestOfLine(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* Discard invalid or excess input before the next prompt. */
    }
}

static int readInt(const char *prompt, int *value)
{
    int result;

    printf("%s", prompt);
    result = scanf("%d", value);
    discardRestOfLine();
    return result == 1;
}

static int readFloat(const char *prompt, float *value)
{
    int result;

    printf("%s", prompt);
    result = scanf("%f", value);
    discardRestOfLine();
    return result == 1;
}

static int readText(const char *prompt, char *buffer, size_t size)
{
    size_t length;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        discardRestOfLine();
    }

    return buffer[0] != '\0';
}

int main(void)
{
    int choice;
    int id;

    loadFromFile();
    printf("Student Record Management System\n");

    do {
        printf("\n1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search student\n");
        printf("4. Update student\n");
        printf("5. Delete student\n");
        printf("6. Save records\n");
        printf("0. Exit\n");

        if (!readInt("Choose an option: ", &choice)) {
            printf("Invalid menu choice.\n");
            continue;
        }

        switch (choice) {
        case 1:
            addStudent();
            saveToFile();
            break;
        case 2:
            displayAll();
            break;
        case 3: {
            StudentNode *student;

            if (!readInt("Enter student ID to search: ", &id)) {
                printf("Invalid student ID.\n");
                break;
            }
            student = searchStudent(id);
            if (student == NULL) {
                printf("Student ID not found.\n");
            } else {
                printf("ID: %d\nName: %s\nDepartment: %s\nCGPA: %.2f\n",
                       student->record.id, student->record.name,
                       student->record.department, student->record.cgpa);
            }
            break;
        }
        case 4:
            if (readInt("Enter student ID to update: ", &id)) {
                updateStudent(id);
                saveToFile();
            } else {
                printf("Invalid student ID.\n");
            }
            break;
        case 5:
            if (readInt("Enter student ID to delete: ", &id)) {
                deleteStudent(id);
                saveToFile();
            } else {
                printf("Invalid student ID.\n");
            }
            break;
        case 6:
            saveToFile();
            break;
        case 0:
            saveToFile();
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid menu choice. Please choose a listed option.\n");
        }
    } while (choice != 0);

    freeAll();
    return 0;
}
