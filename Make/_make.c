//Open file for reading only
//Read line by line. getline
/*
    if first string not tab then read the string
            leave the first two lines
            
        Repeat until end of file
            get the last access time of the first string
            compare it with the next string after :
            if same then
                skip the next line
                else
                run the next line in execv
        Come to first line 
        check if all the object files are newwr than the source file
        if newer then run the next line command 
*/


#include <asm-generic/errno.h>
#include <stdio.h>
#include <string.h>

typedef struct ms
{
    char objectName[20];
    char sourceName[20];
    char executable[100];
} makeCommandStructure;

struct es 
{
    char exe[20];
    char source[20];
    char executable[100];
};

//Write a function to extract a word ignoring whitespaces, taking deliminater 
void extract(char *lineptr, char **wordptr, char delim, char replace)
{
    char ch;
    while((ch = *lineptr))
    {
        if(ch == delim)
        {
            **wordptr = '\0';
            break;
        }
        if(ch == ' ')
        {
            ++lineptr;
            continue;
        }
        else
        {    *((*wordptr)++) = ch;
            lineptr++;
        }
    }

}

void resolveSource(char **inputString)
{
    char ch;
    while( *((*inputString)++) != '.')
    {
        **inputString = 'c';
    }
}
int main()
{

    printf("In main \n");
    FILE *pFile;
    pFile = fopen("makefile", "r");
    char line[100], word[20];
    char *lineBlock = line;
    char *wordBlock = word;
    size_t blockSize = 100;

    struct es EsInstance;
    makeCommandStructure CsInstance[10];
    int CsIt = 0;

    fgets(line, 20, pFile );
    extract( lineBlock, &wordBlock, ':', '\0' );
    strcpy(EsInstance.exe, word); 
    printf("Source : %s\n", EsInstance.exe);
    
    getline(&lineBlock, &blockSize,pFile);
    getline(&lineBlock, &blockSize,pFile);
    

    strcpy(EsInstance.executable,line );
    printf("line : %s\n", EsInstance.executable);
    

    while(!feof(pFile))
    {
        getline( &lineBlock, &blockSize, pFile);
        if((*line != '\t') && (*line != '\n'))
        {
            fgets(line, 20, pFile );
            extract(line, &wordBlock, ':', '\0');
            strcpy(CsInstance[CsIt].objectName, word);
            resolveSource(&wordBlock);
            strcpy(CsInstance[CsIt].sourceName, word);
            getline(&lineBlock, &blockSize,pFile);
            strcpy(CsInstance[CsIt].executable, line);
        
            printf("Object file : %s\nSource File :%s\nExecutable : %s\n",CsInstance[CsIt].objectName,CsInstance[CsIt].sourceName,CsInstance[CsIt].executable);   
        }
        
        CsIt++;
    }
    fclose(pFile);
}




 //if tab then