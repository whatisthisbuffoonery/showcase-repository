*This project has been created as part of the 42 curriculum by achew*

**Description:**  
The goal of this project is to recode the printf function from libc and discover variadic functions.  
The scope is limited to handle "cspdiuxX%" specifiers with field minimum width and "-0.# +" flags.  

**Instructions:**  
To make the library, run:  
*make*  

Include the library in your program:  
*#include "ft_printf.h"*  
  
Compile your program and link:  
*cc -Wall -Werror -Wextra <your_program.c> -L\<path-to-lib-dir\> -lftprintf*  

To suppress any warnings (from using flags that override each other):  
*gcc -Wno-format-extra-args <your_program.c> -L\<path-to-lib-dir\> -lftprintf*  

Run the output executable:  
*./a.out*  

**Resources**:  
https://man7.org/linux/man-pages/man3/printf.3.html  
AI was used in generating some test cases to test my program.  

**Example usage**:  
*#include "ft_printf.h"  
...  
ft_printf("|%+ i|\n", 42);  
...  
-------output------:  
|+42|*  

**Algorithm and data structure**:  
The program parses the input string for valid formats.
For this project valid formats are a group of consecutive characters that start with '%', then 0 or more flags in any order, then/or 0 or more digits (which specify the minimum field width), then/or an optional '.' followed by 0 or more digits (which specify the precision), then/or exactly 1 format specifier character.  
If a character is not a starting character of a valid format, it is written to stdout. Everytime a valid format is found, its properties including the data type, actual data (a string/number, etc.), flags, min width, and precision are all stored in a struct, for logical grouping of the varied information required to retrieve, convert, and format the data.  
To retrieve the arguments that follow the format string (which are of variable number and type), it uses macros from <stdarg.h>, specifically va_list, va_start, va_arg, and va_end.  
Since the project requires not to implement the original printf's buffer management, the converted and formatted data is printed according to the stored properties before checking the next character during the string parsing.
