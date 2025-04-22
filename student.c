#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char first_name[20];
    char last_name[20];
    int roll_no;
    char Class[10];
    char Vill[20];
    float per;
};

void addstudent();
void studentrecord();
void searchstudent();
void Delete();

int main() {
    int choice = 0;
    while (choice != 5) {
        printf("\n\t\t\t========= Student Management System =========\n\n");
        printf("\t\t\t1. Add Student Record\n");
        printf("\t\t\t2. Student Record\n");
        printf("\t\t\t3. Search Student\n");
        printf("\t\t\t4. Delete Record\n");
        printf("\t\t\t5. Exit\n");
        printf("\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
                studentrecord();
                break;
            case 3:
                searchstudent();
                break;
            case 4:
                Delete();
                break;
            case 5:
                printf("\t\t\tExiting Program...\n");
                break;
            default:
                printf("\t\t\tInvalid choice! Please enter a valid number.\n");
        }
    }
    return 0;
}

void addstudent() {
    char another = 'Y';
    FILE *fp;
    struct student info;

    fp = fopen("student_info.txt", "ab");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCan't open file.\n");
        return;
    }

    while (another == 'Y' || another == 'y') {
        printf("\n\t\t\t======= Add Student Info =======\n");

        printf("\t\t\tEnter First Name: ");
        scanf("%s", info.first_name);
        printf("\t\t\tEnter Last Name: ");
        scanf("%s", info.last_name);
        printf("\t\t\tEnter Roll No: ");
        scanf("%d", &info.roll_no);
        printf("\t\t\tEnter Class: ");
        scanf("%s", info.Class);
        printf("\t\t\tEnter Address: ");
        scanf("%s", info.Vill);
        printf("\t\t\tEnter Percentage: ");
        scanf("%f", &info.per);

        fwrite(&info, sizeof(struct student), 1, fp);
        printf("\t\t\tRecord stored successfully!\n");

        printf("\t\t\tDo you want to add another record? (Y/N): ");
        scanf(" %c", &another);  // Space before %c to skip newline
    }

    fclose(fp);
}

void studentrecord() {
    FILE *fp;
    struct student info;

    fp = fopen("student_info.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCan't open file.\n");
        return;
    }

    printf("\t\t\t========= Student Records =========\n\n");
    while (fread(&info, sizeof(struct student), 1, fp)) {
        printf("\n\t\t\tStudent Name: %s %s", info.first_name, info.last_name);
        printf("\n\t\t\tRoll No: %d", info.roll_no);
        printf("\n\t\t\tClass: %s", info.Class);
        printf("\n\t\t\tAddress: %s", info.Vill);
        printf("\n\t\t\tPercentage: %.2f", info.per);
        printf("\n\t\t\t-----------------------------\n");
    }

    fclose(fp);
}

void searchstudent() {
    FILE *fp;
    struct student info;
    int roll_no, found = 0;

    fp = fopen("student_info.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCan't open file.\n");
        return;
    }

    printf("\t\t\tEnter Roll No to Search: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) {
        if (info.roll_no == roll_no) {
            found = 1;
            printf("\n\t\t\tStudent Found:\n");
            printf("\t\t\tName: %s %s\n", info.first_name, info.last_name);
            printf("\t\t\tRoll No: %d\n", info.roll_no);
            printf("\t\t\tClass: %s\n", info.Class);
            printf("\t\t\tAddress: %s\n", info.Vill);
            printf("\t\t\tPercentage: %.2f\n", info.per);
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\tRecord Not Found.\n");
    }

    fclose(fp);
}

void Delete() {
    FILE *fp, *fp1;
    struct student info;
    int roll_no, found = 0;

    fp = fopen("student_info.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCan't open file.\n");
        return;
    }

    fp1 = fopen("temp.txt", "wb");
    if (fp1 == NULL) {
        fclose(fp);
        fprintf(stderr, "\t\t\tCan't create temp file.\n");
        return;
    }

    printf("\t\t\tEnter Roll No to Delete: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) {
        if (info.roll_no == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");
        printf("\t\t\tRecord Deleted Successfully.\n");
    } else {
        remove("temp.txt");
        printf("\t\t\tRecord Not Found.\n");
    }
}