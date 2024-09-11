#include <stdio.h>
#include <string.h>

#define MAX_COURSES 50
#define MAX_SUBJECTS 100
#define MAX_STUDENTS 100
#define MAX_FACULTIES 50

struct Course {
    char id[10];
    char name[50];
};

struct Subject {
    char id[10];
    char name[50];
    char courseId[10];
};

struct Student {
    char id[10];
    char name[50];
    char courseId[10];
    int attendance[MAX_SUBJECTS];  // Initialize to -1
    int marks[MAX_SUBJECTS];        // Initialize to -1
};

struct Faculty {
    char id[10];
    char name[50];
    char courseId[10];
};

void addCourse(struct Course courses[], int *courseCount) {
    printf("Enter Course ID: ");
    scanf("%s", courses[*courseCount].id);
    printf("Enter Course Name: ");
    scanf(" %[^\n]", courses[*courseCount].name);  // Read full line including spaces
    (*courseCount)++;
    printf("Course added successfully!\n");
}

void addSubject(struct Subject subjects[], int *subjectCount, struct Course courses[], int courseCount) {
    printf("Enter Subject ID: ");
    scanf("%s", subjects[*subjectCount].id);
    printf("Enter Subject Name: ");
    scanf(" %[^\n]", subjects[*subjectCount].name);  // Read full line including spaces
    printf("Enter Course ID for the Subject: ");
    scanf("%s", subjects[*subjectCount].courseId);

    int courseFound = 0;
    for (int i = 0; i < courseCount; i++) {
        if (strcmp(subjects[*subjectCount].courseId, courses[i].id) == 0) {
            courseFound = 1;
            break;
        }
    }
    if (courseFound) {
        (*subjectCount)++;
        printf("Subject added successfully!\n");
    } else {
        printf("Error: Course not found for the specified Course ID.\n");
    }
}

void addStudent(struct Student students[], int *studentCount, struct Course courses[], int courseCount) {
    printf("Enter Student ID: ");
    scanf("%s", students[*studentCount].id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[*studentCount].name);  // Read full line including spaces
    printf("Enter Course ID for the Student: ");
    scanf("%s", students[*studentCount].courseId);

    int courseFound = 0;
    for (int i = 0; i < courseCount; i++) {
        if (strcmp(students[*studentCount].courseId, courses[i].id) == 0) {
            courseFound = 1;
            break;
        }
    }
    if (courseFound) {
        // Initialize attendance and marks for each subject
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            students[*studentCount].attendance[i] = -1; // -1 represents NA
            students[*studentCount].marks[i] = -1; // -1 represents NA
        }
        (*studentCount)++;
        printf("Student added successfully!\n");
    } else {
        printf("Error: Course not found for the specified Course ID.\n");
    }
}

void addFaculty(struct Faculty faculties[], int *facultyCount, struct Course courses[], int courseCount) {
    printf("Enter Faculty ID: ");
    scanf("%s", faculties[*facultyCount].id);
    printf("Enter Faculty Name: ");
    scanf(" %[^\n]", faculties[*facultyCount].name);  // Read full line including spaces
    printf("Enter Course ID for the Faculty: ");
    scanf("%s", faculties[*facultyCount].courseId);

    int courseFound = 0;
    for (int i = 0; i < courseCount; i++) {
        if (strcmp(faculties[*facultyCount].courseId, courses[i].id) == 0) {
            courseFound = 1;
            break;
        }
    }
    if (courseFound) {
        (*facultyCount)++;
        printf("Faculty added successfully!\n");
    } else {
        printf("Error: Course not found for the specified Course ID.\n");
    }
}

void markAttendance(struct Student students[], int studentCount, struct Subject subjects[], int subjectCount) {
    char studentId[10], subjectId[10];
    int present;
    printf("Enter Student ID: ");
    scanf("%s", studentId);
    printf("Enter Subject ID: ");
    scanf("%s", subjectId);

    // Find the student
    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentId) == 0) {
            studentIndex = i;
            break;
        }
    }

    // Find the subject
    int subjectIndex = -1;
    for (int i = 0; i < subjectCount; i++) {
        if (strcmp(subjects[i].id, subjectId) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (studentIndex != -1 && subjectIndex != -1) {
        printf("Is the student present? (1 for Yes, 0 for No): ");
        scanf("%d", &present);
        if (subjectIndex < MAX_SUBJECTS) {
            students[studentIndex].attendance[subjectIndex] = present;
            printf("Attendance marked successfully!\n");
        } else {
            printf("Error: Subject index out of bounds.\n");
        }
    } else {
        printf("Error: Student or Subject not found.\n");
    }
}

void enterMarks(struct Student students[], int studentCount, struct Subject subjects[], int subjectCount) {
    char studentId[10], subjectId[10];
    int marks;
    printf("Enter Student ID: ");
    scanf("%s", studentId);
    printf("Enter Subject ID: ");
    scanf("%s", subjectId);

    // Find the student
    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentId) == 0) {
            studentIndex = i;
            break;
        }
    }

    // Find the subject
    int subjectIndex = -1;
    for (int i = 0; i < subjectCount; i++) {
        if (strcmp(subjects[i].id, subjectId) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (studentIndex != -1 && subjectIndex != -1) {
        printf("Enter Marks: ");
        scanf("%d", &marks);
        if (subjectIndex < MAX_SUBJECTS) {
            students[studentIndex].marks[subjectIndex] = marks;
            printf("Marks entered successfully!\n");
        } else {
            printf("Error: Subject index out of bounds.\n");
        }
    } else {
        printf("Error: Student or Subject not found.\n");
    }
}

void printReportCard(struct Student students[], int studentCount, struct Subject subjects[], int subjectCount) {
    char studentId[10];
    printf("Enter Student ID: ");
    scanf("%s", studentId);

    // Find the student
    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentId) == 0) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex != -1) {
        printf("Report Card for Student: %s - %s\n", students[studentIndex].id, students[studentIndex].name);
        printf("Course ID: %s\n", students[studentIndex].courseId);
        printf("Attendance:\n");
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            if (students[studentIndex].attendance[i] != -1) {
                               printf("Subject: %s, Present: %s\n", subjects[i].name, students[studentIndex].attendance[i] ? "Yes" : "No");
            }
        }
        printf("Marks:\n");
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            if (students[studentIndex].marks[i] != -1) {
                printf("Subject: %s, Marks: %d\n", subjects[i].name, students[studentIndex].marks[i]);
            }
        }
    } else {
        printf("Error: Student not found.\n");
    }
}

int main() {
    struct Course courses[MAX_COURSES];
    struct Subject subjects[MAX_SUBJECTS];
    struct Student students[MAX_STUDENTS];
    struct Faculty faculties[MAX_FACULTIES];
    int courseCount = 0;
    int subjectCount = 0;
    int studentCount = 0;
    int facultyCount = 0;
    int choice;

    do {
        printf("\nCollege Management System\n");
        printf("1. Add Course\n");
        printf("2. Add Subject\n");
        printf("3. Add Student\n");
        printf("4. Add Faculty\n");
        printf("5. Mark Attendance\n");
        printf("6. Enter Marks\n");
        printf("7. Print Report Card\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCourse(courses, &courseCount);
                break;
            case 2:
                addSubject(subjects, &subjectCount, courses, courseCount);
                break;
            case 3:
                addStudent(students, &studentCount, courses, courseCount);
                break;
            case 4:
                addFaculty(faculties, &facultyCount, courses, courseCount);
                break;
            case 5:
                markAttendance(students, studentCount, subjects, subjectCount);
                break;
            case 6:
                enterMarks(students, studentCount, subjects, subjectCount);
                break;
            case 7:
                printReportCard(students, studentCount, subjects, subjectCount);
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);

    return 0;
}
