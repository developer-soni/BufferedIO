# Buffered IO

## DESCRIPTION
In this program, I created my own file descriptor which is just an integer index into an array and I maintain that for each open file. I, then use the Linux open, read and close functions and store the Linux file descriptor value and doesn’t expose it to the caller. The main file executes the program and reads the file and passes it to the buffer accordingly.

## What I did
I created my own file descriptor which is used to store the index of the File Control Block that we will be returning from b_open function. First, I initialize all the variables from the struct and return the index of file control block which is not in use. I also see if there is any error opening the file and print the respective code. Then I added the buffered read function to return the data and number of bytes read. I also check if the position of my file descriptor is at the beginning of the buffer and also if buffer count is less than 512 bytes. If it is, then go ahead to read the next 80 bytes, else reload the buffer and get the remaining bytes. If the remaining bytes are less than requested bytes, then just copy the former and call read() function to print the rest within the 80 byte buffer. Then we also check we reached the end of file. Then resetting the buffer position to the beginning and copying the remaining bytes. Incrementing and resetting buffer position is done respectively. Finally after everything is executed and displayed, close the file and release the buffer using Linux System Calls.

# Please refer to WriteUp for more information and output
