# get_next_line

## Overview

The goal of this project is to write a function that reads from a file descriptor and returns one line at a time, making minimal use of static variables, and managing memory and buffer efficiently. This project helps reinforce understanding of file I/O, dynamic memory allocation, buffer handling, and proper resource management in C.

## Features

- Reads from a file descriptor and returns the next line, one at a time.
- Handles multiple file descriptors simultaneously.
- Efficient buffer management.
- No memory leaks—clean allocation and freeing of resources.
- Complies with the 42 school subject requirements.

## Function Prototype

```c
int get_next_line(int fd, char **line);
```

- `fd`: File descriptor to read from.
- `line`: Pointer to a string where the read line will be stored. Memory for *line* must be allocated inside the function and freed by the caller when done.

## Project Structure

- `get_next_line.c` – Main function implementation.
- `get_next_line_utils.c` – Helper functions.
- `get_next_line.h` – Header file with prototypes and definitions.

## Compilation

```sh
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Usage

Example of how to use `get_next_line` in your own C project:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("myfile.txt", O_RDONLY);
    char *line;
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    free(line); 
    close(fd);
    return 0;
}
```

## Notes

- Make sure to free the memory returned for each line.
- The function continues returning lines until the end of the file is reached.
- The function returns:
  - `1` when a line has been read,
  - `0` on EOF (end of file),
  - `-1` on error.

## Subject Requirements (42 School)

- The function must read from a file descriptor, and return a single line at a time.
- Buffer size can be specified at compile time using the macro `BUFFER_SIZE`.
- No memory leaks or forbidden functions.
- Handle multiple file descriptors.

## Testing

To run the example test program, provide a text file as input:

```sh
./gnl
```
