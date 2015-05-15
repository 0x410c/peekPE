#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<winnt.h>
#define DEBUG 1
class PE{
	IMAGE_DOS_HEADER dosMZ;
	char *dosStub;
	IMAGE_NT_HEADERS peHead;
	IMAGE_SECTION_HEADER *secHead;
	char *sections;
};
class peReader
{
		char *peBuffer,*peName;
		HANDLE peHandle;
		unsigned long n;
		int peSize;
public:
		peFile()
		{
			peBuffer	=	NULL;
			peName		=	NULL;
		}
		~peFile()
		{
		}
		int load(char *file)
		{	
			peName = file;
			peHandle = CreateFile( peName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if(peHandle == INVALID_HANDLE_VALUE)
			{
				if(DEBUG)	
					printf("Can't Load File.\nExiting.");
				return 0;
			}
			peSize = GetFileSize(peHandle, NULL);
			if(peSize == INVALID_FILE_SIZE)
			{
				if(DEBUG)
					printf("Invalid File Size.\nExiting.");
				return 0;
			}
			SetFilePointer(peHandle, NULL,NULL, FILE_BEGIN);
			if(!ReadFile(peHandle, peBuffer, peSize, &n,NULL))
			{	
				if(DEBUG)
					printf("Cannot Read File.\nExiting.");
				return 0;
			}
			CloseHandle(peHandle);
			if(isPEValid())
			{

			}
		}
		int isPeValid()
		{
			
			return 0;
		}
};

int main()
{
	printf("peekPE early stage\n");
	
	return 0;
}