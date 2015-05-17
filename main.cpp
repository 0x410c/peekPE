#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include "peekPE.h"


int main()
{
	printf("peekPE early stage\n");
	PE file;
    if(file.load(".\\test.exe"))
        printf("Success!!");
	return 0;
}
