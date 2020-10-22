#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Hamdan Yuwafi Mastu Wijaya (NPM. 19081010092)
 * Judul        : CRUD-C with bubble sort and selection sort
 * GitHub URL   : https://github.com/thisham/pemrograman-lanjut-2020/tree/master/T04_StructSort
 * Note         : Source code ini ditulis di Linux Ubuntu 18.04 dan dikompilasi dengan GCC for Linux.
 */

typedef struct
{
    char name[256];
    char npm[16];
    int generation;
    int semester;
    int age;
    char majors[64];
    char faculty[64];
} Students;

int menu();
void rd_data();
int rd_menu();
void bubble_sort(Students stu[], int length);
void select_sort(Students stu[], int length);
int compareNPM(const void *pa, const void *pb);

int main(int argc, char const *argv[])
{
    char npm[16];
    bool found; int d = 0;
    int opt, max, data = 0;
    printf("Insert max amount of data : "); scanf("%d", &max); 
    Students stu[max], srt_stu[max], tmp_stu;

    Repeat:
        opt = menu();
        printf("===================================================\n\n");
        switch (opt) {
            case 1: // create
                printf("Used data storage in array: %d / %d\n\n", data, max);
                if (data < max) {
                    data = data + 1;
                    printf("NPM        : "); scanf("%s", stu[data - 1].npm);
                    printf("Name       : "); scanf(" %[^\n]", stu[data - 1].name);
                    printf("Generation : "); scanf("%d", &stu[data - 1].generation);
                    printf("Major      : "); scanf(" %[^\n]", stu[data - 1].majors);
                    printf("Faculty    : "); scanf(" %[^\n]", stu[data - 1].faculty);
                    printf("Semester   : "); scanf("%d", &stu[data - 1].semester);
                    printf("Age        : "); scanf("%d", &stu[data - 1].age);
                } else {
                    printf("Error: Out of max amount of struct!\n");
                }
                break;

            case 2: // read
                printf("Total datas: %d\n\n", data);
                if (data != 0) {
                    int a = rd_menu();
                    printf("===================================================\n\n");
                    switch (a) {
                        case 1: // returns all data
                            for (int i = 0; i < data; i++) {
                                printf("Data number %i : \n", i + 1);
                                rd_data(stu[i]);
                                printf("\n");
                            }
                            break;

                        case 2: // returns data on selected npm
                            printf("Search NPM : "); scanf("%s", npm);
                            printf("\n");
                            for (int i = 0; i < data; i++) {
                                // printf("%s == %s", stu[i].npm, npm);
                                if (!strncmp(stu[i].npm, npm, sizeof(npm))) {
                                    rd_data(stu[i]);
                                    found = true;
                                } else {
                                    found = false;
                                }
                            }

                            // printf("%d\n", found);

                            if (!found) {
                                printf("Data not found!\n");
                            }
                            break;

                        case 3: // returns bubble-sorted data by NPM (ASC)
                            bubble_sort(stu, data);
                            break;

                        case 4: // returns selection-sorted data by NPM (ASC)
                            select_sort(stu, data);
                            break;

                        default:
                            printf("Option is unavailable!\n");
                            break;
                    }
                } else {
                    printf("No data can be displayed.\n");
                }
                break;

            case 3: // update
                printf("Search NPM : "); scanf("%s", npm);
                printf("\n");
                for (int i = 0; i < data; i++) {
                    if (!strncmp(stu[i].npm, npm, sizeof(npm))) {
                        found = true;
                    } else {
                        found = false;
                    }
                }

                if (found) {
                    printf("Note: Please don\'t leave this fields blank. Repeat to keep it unchanged.\n");
                    printf("\tNPM        : (%s)\n", stu[d].npm);
                    printf("\tName       : (%s) => ", stu[d].name); scanf(" %[^\n]", stu[d].name);
                    printf("\tGeneration : (%d) => ", stu[d].generation); scanf("%d", &stu[d].generation);
                    printf("\tMajor      : (%s) => ", stu[d].majors); scanf(" %[^\n]", stu[d].majors);
                    printf("\tFaculty    : (%s) => ", stu[d].faculty); scanf(" %[^\n]", stu[d].faculty);
                    printf("\tSemester   : (%d) => ", stu[d].semester); scanf("%d", &stu[d].semester);
                    printf("\tAge        : (%d) => ", stu[d].age); scanf("%d", &stu[d].age);
                    printf("\n");
                    printf("Action complete! Data updated.\n");
                } else {
                    printf("Data not found!\n");
                }
                break;

            case 4: // delete
                printf("Search NPM : "); scanf("%s", npm);
                printf("\n");
                for (int i = 0; i < data; i++) {
                    if (!strncmp(stu[i].npm, npm, sizeof(npm))) {
                        for (int j = i; j < data; j++) {
                            stu[j] = stu[j + 1];
                        }
                        data = data - 1;
                        printf("Action complete! Data deleted.\n"); 
                        found = true;
                    } else {
                        found = false;
                    }
                }

                if (!found) {
                    printf("Data not found!\n");
                }
                break;
            
            default:
                printf("Option is unavailable!\n");
                break;
        }
        printf("===================================================\n\n");
        goto Repeat;
    return 0;
}

// View
    int menu()
    {
        int x;
        printf("Welcome to Student Data program! Please choose one:\n");
        printf("\t[1] Create Data\n");
        printf("\t[2] Read Data\n");
        printf("\t[3] Update Data\n");
        printf("\t[4] Delete Data\n");
        printf("Your command : "); scanf("%d", &x);
        printf("\n");
        return x;
    }

    int rd_menu() {
        int x;
        printf("Please choose one : \n");
        printf("\t[1] Read all data\n");
        printf("\t[2] Read data based on NPM\n");
        printf("\t[3] Read bubble-sorted data by NPM (Ascending)\n");
        printf("\t[4] Read select-sorted data by NPM (Ascending)\n");
        printf("Your command : "); scanf("%d", &x);
        return x;
    }

    void rd_data(Students stu)
    {
        printf("\tNPM        : %s\n", stu.npm);
        printf("\tName       : %s\n", stu.name);
        printf("\tGeneration : %d\n", stu.generation);
        printf("\tMajor      : %s\n", stu.majors);
        printf("\tFaculty    : %s\n", stu.faculty);
        printf("\tSemester   : %d\n", stu.semester);
        printf("\tAge        : %d\n", stu.age);
    }

    void bubble_sort (Students stu[], int length) {
        Students loc_stu[length], tmp_stu;
        for (int i = 0; i < length; i++) {
            loc_stu[i] = stu[i];
        }

        for (int i = 0; i < length; i++) {
            for (int j = 1; j < length; j++) {
                if (strcmp(loc_stu[j-1].npm, loc_stu[j].npm) > 0) {
                    tmp_stu = loc_stu[j-1];
                    loc_stu[j-1] = loc_stu[j];
                    loc_stu[j] = tmp_stu;
                }
                                    
            }
        }
                            
        for (int i = 0; i < length; i++) {
            printf("Data number %i :\n", i+1);
            rd_data(loc_stu[i]);
            printf("\n");
        }
    }

    void select_sort (Students stu[], int length) {
        Students tmp_stu, loc_stu[length];

        for (int i = 0; i < length; i++) {
            loc_stu[i] = stu[i];
        }
        
        for (int i = 0; i < length - 1; i++) {
            int p = i;
            for (int j = i + 1; j < length; j++) {
                if (strcmp(loc_stu[j].npm, loc_stu[p].npm) < 0) {
                    p = j;
                }
            }
            tmp_stu    = loc_stu[p];
            loc_stu[p] = loc_stu[i];
            loc_stu[i] = tmp_stu;
        }

        for (int i = 0; i < length; i++) {
            printf("Data number %i :\n", i+1);
            rd_data(loc_stu[i]);
            printf("\n");
        }
    }