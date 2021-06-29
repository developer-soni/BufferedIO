/**************************************************************
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.c
*
* Description: This .c file initiates buffer and creates a file descriptor 
*				using Linux open, read, close functions.
*
**************************************************************/

#include "b_io.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define B_CHUNK_SIZE 512

// You will create your own file descriptor which is just an integer index into an array
// that you maintain for each open file.  You will need to use the Linux open, read, close
// functions.  So you will need to store the Linux file descriptor, but that value should
// never be exposed to the caller.
// Hint - create a structure (struct) that contains fields like the LinuxFileDescriptor
//    Pointer to the file's buffer, length of data in the buffer, and index into the buffer
// Hint 2: No where in this code should you be assuming on the size of the read (i.e. there
//         should NOT be any reference to 80 or BUFFERCNT

#define MAX_OPEN_FILES 20

typedef struct bOFT
{
	char *buffer;	// buffer to allocate 512 bytes
	int linuxFD;	// linux file descriptor
	char *position; // position of buffer
	bool inUse;		// file in use or not
	int remaining;	// track remaining bytes in buffer
} bOFT;

// bOFT *oft = malloc(sizeof(bOFT) * 20);

struct bOFT oft[MAX_OPEN_FILES];
int hasInit = 0;

void b_init() //function to initialize the struct variables in all open files
{
	hasInit = 1;
	for (int i = 0; i < MAX_OPEN_FILES; i++)
	{
		oft[i].buffer = (char *)malloc(B_CHUNK_SIZE);
		oft[i].linuxFD = 0;
		oft[i].position = oft[i].buffer;
		oft[i].inUse = false;
		oft[i].remaining = B_CHUNK_SIZE;
	}
}

b_io_fd b_open(char *filename)
{
	//*** TODO ***:  Write open function to return your file descriptor
	//               The returned file descriptor CAN NOT be the Linux file descriptor
	//               You must use the Linux System Calls (open)
	//				 You may want to allocate the buffer here as well
	//				 But make sure every file has its own buffer

	if (hasInit == 0) //calls the initialze function from above
	{
		b_init();
	}

	int indexFD;
	for (int i = 0; i < MAX_OPEN_FILES; i++)
	{
		if (oft[i].inUse == false) //returns the index of file control block not in use
		{
			indexFD = i;
			break;
		}
	}
	//int indexFD = temp;

	oft[indexFD].linuxFD = open(filename, O_RDONLY);
	oft[indexFD].inUse = true;

	//returns the index from the loop above
	return indexFD;
}

int b_read(b_io_fd fd, char *buffer, int count)
{
	//*** TODO ***:  Write buffered read function to return the data and # bytes read
	//               You must use the Linux System Calls (read) and you must buffer the data
	//				 in 512 byte chunks. i.e. your linux read must be in B_CHUNK_SIZE
	// 1st arg: linux fd, 2nd is the buffer inside ur struct, 3d is the count must follw comments above

	int readValue;

	//if the postion is at the beginning of the buffer
	if (oft[fd].position == oft[fd].buffer)
	{
		read(oft[fd].linuxFD, oft[fd].buffer, B_CHUNK_SIZE);
	}

	//if buffer count < 512 bytes, read next 80 bytes
	if ((oft[fd].position + count) < (oft[fd].buffer + B_CHUNK_SIZE))
	{
		memcpy(buffer, oft[fd].position, count);
		oft[fd].position += count;
		oft[fd].remaining -= count;
	}
	else //else reload buffer and get remaining bytes
	{
		//if < requested bytes, copy remaining bytes
		memcpy(buffer, oft[fd].position, oft[fd].remaining);
		readValue = read(oft[fd].linuxFD, oft[fd].buffer, B_CHUNK_SIZE);
		oft[fd].buffer[readValue] = '\0';

		if (readValue == 0) //checking end of file
		{
			return readValue;
		}

		//reset buffer position to the beginning and copy remaining bytes
		oft[fd].position = oft[fd].buffer;
		memcpy(buffer + oft[fd].remaining, oft[fd].position, (count - oft[fd].remaining));

		//increment buffer position by 'count-rem.' bytes
		oft[fd].position += (count - (oft[fd].remaining));

		//reset the remaining to '512-rem.' bytes
		oft[fd].remaining = B_CHUNK_SIZE - (count - oft[fd].remaining);
	}
	return count;
}

void b_close(b_io_fd fd)
{
	//*** TODO ***:  Close the file and release the buffer
	//				 You must use Linux System Calls (close)
	//
	free(oft[fd].buffer);
	close(oft[fd].linuxFD);
}
