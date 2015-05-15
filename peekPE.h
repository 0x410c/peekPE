#include<winnt.h>
#define DEBUG 1
class PE{
	IMAGE_DOS_HEADER dosMZ;
	char *dosStub;
	IMAGE_NT_HEADERS peHead;
	IMAGE_SECTION_HEADER *secHead;
	char *sections;

};
class PEIO
{
		char *peBuffer,*peName;
		HANDLE peHandle;
		unsigned long n;
		int peSize;
		PE file;
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
			if(!ReadFile(host,(void*)&dosMZ,sizeof(dosMZ),&d,NULL))
			{
				printf("\nRead Fail");
				return 0;
			}
			if(!(dosMZ.e_magic==IMAGE_DOS_SIGNATURE))
			{
				printf("\nNot a Valid PE");
				return 0;
			}
			printf("\nDos Signature Found");
			SetFilePointer(host,dosMZ.e_lfanew,NULL,FILE_BEGIN);
			if(!ReadFile(host,(void*)&peHead,sizeof(peHead),&d,NULL))
			{
				printf("\nRead Fail");
				return 0;
			}
			if(!(peHead.Signature==IMAGE_NT_SIGNATURE))
			{
				printf("\nNot Valid PE");
				return 0;
			}
			return 1;
		}
};