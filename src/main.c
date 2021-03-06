/*********Main.c ******/


#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char usage[] = "Usage: f9 infile [outfile] [-c]\n";

char buff[1000];

//extern char nextChar;

int curType;
FILE* inFile;
FILE* outFile;

char outName[100];
char oFileName[500] = "./bin/";
char cFileName[500] = "./c_src/";

//extern int line, col;
int main(int argc, char** args)
{
	if(argc < 2)
	{
		printf("%s", usage);
		exit(-1);
	}
	inFile = fopen(args[1], "r");

	if(inFile == NULL)
	{
		printf("The source file could not be opened");
		exit(-1);
	}

	if(argc > 2)
	{
		strcpy(cFileName, args[2]);
	}

	// Extract the output file name from 
	else
	{
		char* ext = strstr(args[1], ".f9");
		char* fileStart = args[1];
		
		while(strstr(fileStart, "/"))
		{
			fileStart = strstr(args[1], "/") + 1;
		}
	
		int n = 0;

		if( ext > fileStart)
		{
			n = ext - fileStart;
		}
	
		else
		{
			n = strlen(fileStart);
		}

		strncpy(outName, fileStart, n);
		strcat(cFileName, outName);
		strcat(cFileName, ".c");
		strcat(oFileName, outName);
		strcat(oFileName, ".o");
		outFile = fopen(cFileName, "w");
		if(outFile == NULL)
		{
			printf("an output file could not be opened");
			exit(-1);
		}
	}

	hashInit();
	makeFSM();
	
	nextChar = fgetc(inFile);

	parseAll();
	fclose(outFile);

	// invoke GCC
	char* newArgs[5];
	newArgs[0] = strdup("gcc");
	newArgs[1] = strdup(cFileName);
	newArgs[2] = strdup("-o");
	newArgs[3] = strdup(oFileName);
	newArgs[4] = 0;

	execvp(newArgs[0], &newArgs[0]);
	printf("%s\n", strerror(errno));

}
