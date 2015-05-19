#include<winnt.h>
#define DEBUG 1
class pEImage
{
protected:
    IMAGE_DOS_HEADER dosMZ;
    char *dosStub;
    IMAGE_NT_HEADERS peHead;
    IMAGE_SECTION_HEADER *secHead;
    char **sections;

};
class PE : public pEImage
{
    char *peName;
    HANDLE peHandle;
    unsigned long n;
    int peSize;
    int dosStubSize;
public:
    PE()
    {
        peName		=	NULL;
        peSize		=	0;
    }
    ~PE()
    {
    }
    int numberOfSections()
    {
        return peHead.FileHeader.NumberOfSections;
    }
    void printImportedFunctions()
    {
       //rva
    }
    int nameOfSection(char *arr,int n)
    {
        if(n>peHead.FileHeader.NumberOfSections)
            return 0;
        else
        {
            strcpy(arr, (const char*)secHead[n].Name);
            return 1;
        }
    }
    void printCodeSectionDump()
    {
        for(int i=0; i<secHead[0].SizeOfRawData; i++)
        {
            printf("%c",sections[0][i]);
        }
        printf("%x",secHead[0].SizeOfRawData);
    }
    int load(char *file)
    {
        try
        {
            peName          =   file;
            peHandle        =   CreateFile( peName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if(peHandle == INVALID_HANDLE_VALUE)
                throw "Can't Load File.\nExiting.";
            peSize          =   GetFileSize(peHandle, NULL);
            if(peSize == INVALID_FILE_SIZE)
                throw "Invalid File Size.\nExiting.";
            SetFilePointer(peHandle, NULL,NULL, FILE_BEGIN);
            if(!ReadFile(peHandle, (void*)&dosMZ, sizeof(dosMZ), &n,NULL))
                throw "Cannot Read File.\nExiting.";
            if(dosMZ.e_magic != IMAGE_DOS_SIGNATURE)
                throw "Invalid Dos Signature";
            SetFilePointer(peHandle, dosMZ.e_lfanew,NULL,FILE_BEGIN);
            ReadFile(peHandle, (void*)&peHead, sizeof(peHead), &n, NULL);
            if(peHead.Signature != IMAGE_NT_SIGNATURE)
                throw "Invalid PE Signature";

            secHead         =   (IMAGE_SECTION_HEADER*)GlobalAlloc(GPTR, (peHead.FileHeader.NumberOfSections)*sizeof(IMAGE_SECTION_HEADER));
            ReadFile(peHandle,(void*)secHead,sizeof(IMAGE_SECTION_HEADER) *peHead.FileHeader.NumberOfSections,&n,NULL);
            sections        =   (char**)GlobalAlloc(GPTR, peHead.FileHeader.NumberOfSections*sizeof(int));
            for(int i=0; i<peHead.FileHeader.NumberOfSections; i++)
            {
                sections[i] =   (char*)GlobalAlloc(GPTR, secHead[i].SizeOfRawData);
                SetFilePointer(peHandle,secHead[i].PointerToRawData,NULL,FILE_BEGIN);
                ReadFile(peHandle, (void*)sections[i],secHead[i].SizeOfRawData,&n,NULL);
            }
            dosStubSize		=	dosMZ.e_lfanew - sizeof(dosMZ);
            dosStub			=	(char*)GlobalAlloc(GPTR,dosStubSize);
            SetFilePointer(peHandle, sizeof(dosMZ), NULL, FILE_BEGIN);
            ReadFile(peHandle, (void*)dosStub, dosStubSize, &n, NULL);
            CloseHandle(peHandle);
            return 1;
        }
        catch(const char *msg)
        {
            if(DEBUG)
                printf("%s",msg);
            return 0;
        }
    }
};
