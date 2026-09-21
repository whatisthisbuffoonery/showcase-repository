*This project has been created as part of the 42 curriculum by achew*

**Description:**  
The goal of this project is to write a function that reads from a file descriptor and returns the next line.
A buffer size may be specified from the command line with -D BUFFER_SIZE=n.
This project aims to teach the concept of static variables.

**Instructions:**  
Include the header file in your program where get_next_line() is used:
```
#include get_next_line.h
```

Compile your program: 
```
cc -Wall -Werror -Wextra <your_program.c> get_next_line.c get_next_line_utils.c
```
Run the output with any required arguments:  
```
./a.out poem1.txt poem2.txt
```

**Resources**:  
https://man7.org/linux/man-pages/man2/read.2.html  
AI was used in learning markdown.

**Algorithm**:  
The function works by storing leftover characters into a static 2D array stash. This will ensure that each call will not invoke unecessary reading of the fd, which has a higher time cost than saving the unused characters for subsequent calls through a static array. This will also ensure that when the read function is called again it will read exactly where it left off.

Upon calling the function, the stash will be checked for any non null characters. If there are, they will be moved into a temporary buffer. If not, another read (of the specified buffer size) into the buffer will be performed. The choice of allocating the buffer on the heap was justified by the fact that large memory space could potentially be used if a very large buffer size is chosen. However, stack was also considered for performance and avoiding overhead since data size is already known at compile time.

From the buffer, if a newline character is found, a line can be returned. If not, the function will be called recursively until it is found or the end of file is reached. The line returned is the result of concatenating with the recursive calls. Although an iterative algorithm may have better performance, the choice of recursion was justified by the fact that the problem naturally breaks down into identical subproblems.