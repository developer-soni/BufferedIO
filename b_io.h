/**************************************************************
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.h
*
* Description: This is the header file for b_io.c
*
**************************************************************/

#ifndef _B_IO_H
#define _B_IO_H

typedef int b_io_fd;

b_io_fd b_open(char *filename);
int b_read(b_io_fd fd, char *buffer, int count);
void b_close(b_io_fd fd);

#endif

