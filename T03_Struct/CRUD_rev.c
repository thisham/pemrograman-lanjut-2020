#include <stdio.h>
#include <string.h>

struct Students
{
    char name[256];
    char npm[16];
    int generation;
    int semester;
    int age;
    char majors[64];
    char faculty[64];
};

// struct student
// {
//     struct Students stu[10]
// };

int menu();
void rd_data();
int rd_menu();

int main(int argc, char const *argv[])
{
    char npm[16];
    int found = 0; int d = 0;
    int opt, max, data = 0;
    printf("Insert max amount of data : "); scanf("%d", &max); 
    struct Students stu[max], srt_stu[max], tmp_stu;

    Repeat:
        opt = menu();
        printf("===================================================\n\n");
        switch (opt) {
            case 1: // create
                printf("Used data storage in array: %d / %d\n\n", data, max);
                if (data < max) {
                    data = data + 1;
                    printf("NPM        : "); scanf("%s", stu[data].npm);
                    printf("Name       : "); scanf(" %[^\n]", stu[data].name);
                    printf("Generation : "); scanf("%d", &stu[data].generation);
                    printf("Major      : "); scanf(" %[^\n]", stu[data].majors);
                    printf("Faculty    : "); scanf(" %[^\n]", stu[data].faculty);
                    printf("Semester   : "); scanf("%d", &stu[data].semester);
                    printf("Age        : "); scanf("%d", &stu[data].age);
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
                        case 1:
                            for (int i = 1; i <= data; i++) {
                                printf("Data number %i : \n", i);
                                rd_data(stu[i]);
                                printf("\n");
                            }
                            break;

                        case 2:
                            printf("Search NPM : "); scanf("%s", npm);
                            printf("\n");
                            for (int i = 1; i <= data; i++) {
                                if (strcmp(stu[i].npm, npm) == 0) {
                                    found = found + 1;
                                    d = i;
                                }
                                
                            }

                            if (found > 0) {
                                rd_data(stu[d]);
                            } else {
                                printf("Data not found!\n");
                            }
                            break;

                        case 3:
                            printf("Coming soon!\n");
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
                for (int i = 1; i <= data; i++) {
                    if (strcmp(stu[i].npm, npm) == 0) {
                        found = found + 1;
                        d = i;
                    }
                }

                if (found > 0) {
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
                for (int i = 1; i <= data; i++) {
                    if (strcmp(stu[i].npm, npm) == 0) {
                        found = found + 1;
                        d = i;
                    }
                }

                if (found > 0) {
                    for (int i = d; i < data; i++) {
                        if (i + 1 > data) {
                            stu[i] = stu[i + 1];
                        }
                    }
                    data = data - 1;
                    printf("Action complete! Data deleted.\n");                 
                } else {
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
        printf("\t[3] Read sorted by NPM\n");
        printf("Your command : "); scanf("%d", &x);
        return x;
    }

    void rd_data(struct Students stu)
    {
        printf("\tNPM        : %s\n", stu.npm);
        printf("\tName       : %s\n", stu.name);
        printf("\tGeneration : %d\n", stu.generation);
        printf("\tMajor      : %s\n", stu.majors);
        printf("\tFaculty    : %s\n", stu.faculty);
        printf("\tSemester   : %d\n", stu.semester);
        printf("\tAge        : %d\n", stu.age);
    }
    