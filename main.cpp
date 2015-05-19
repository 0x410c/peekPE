#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include "peekPE.h"


int main()
{
    printf("peekPE early stage\n");
    PE file;
    char name[8];
    if(file.load(".\\test.exe"))
        printf("\nLoad of test.exe Successful.");
    printf("\nListing Section Names");
    for(int i=0;i<file.numberOfSections();i++)
        if(file.nameOfSection(&name[0],i))
            printf("\n%s",name);
    return 0;
}
