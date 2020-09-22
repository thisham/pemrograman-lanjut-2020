#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int age;
    char name[128], birthInfo[64], homeAddress[256], school[128];
    strcpy(name, "Hamdan Yuwafi Mastu Wijaya");
    strcpy(birthInfo, "Sidoarjo, December 21, 2001");
    strcpy(homeAddress, "Wadang 03/04, Tempel, Krian 61262, Sidoarjo");
    strcpy(school, "UPN Veteran Jawa Timur");
    age     = 19;
    printf("Hello, this is my biodata: \n");
    printf("    Name        : %s\n", name);
    printf("    Age         : %i\n", age);
    printf("    Birth Info  : %s\n", birthInfo);
    printf("    Study at    : %s\n", school);
    return 0;
}