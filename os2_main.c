/**************************************************************
* Project: Assignment 2 – Buffered I/O
*
* File: os_2_main.c
*
* Description: This main file executes the program and reads the file and passes
*				it to the buffer accordingly.
*
**************************************************************/

#include <stdio.h>
#include "b_io.h"
#include <stdlib.h>

#define BUFFERCNT 80

/*** ToDo: Add comments to the code.  ***/

int main(int argc, char *argv[]) //argc to count number of arguments
{								 //argv[] to store each argument
	int readCount;
	char *buffer;
	b_io_fd fd;

	if (argc != 2) //remove this to open multiple files
	{
		printf("Proper usage is: command filename\n");
		return -1;
	}

	buffer = malloc(BUFFERCNT + 2); //allocate a little extra space, need at least one for the null.

	/***  ToDo:  Check if malloc succeeds  ***/
	if (buffer == NULL) //malloc doesnt succeed when buffer is null
	{
		printf("! malloc unsuccessful !");
		return -1;
	}

	//for (int i = 1; i < argc; i++) //loop to handle multiple files
	//{

	fd = b_open(argv[1]);

	/***  ToDo:  Check if b_open succeeds  ***/
	if (fd < 0)
	{
		printf("! b_open unsuccessful !");
	}

	do
	{
		readCount = b_read(fd, buffer, BUFFERCNT); //read the buffer as per BUFFERCNT
		buffer[readCount] = '\0';
		printf("%s\n", buffer); //print the respective buffer
	} while (readCount > 0);

	/***  TODO add b_close and free anything that needs freeing  ***/
	b_close(fd);
	//	}

	return 0;
}
