## ft\_printf  
  
*This project has been created as part of the 42 curriculum by dthoo.*  
  
### Description  
This project aims to emulate the printf function from \<stdio.h\>.  
  
##### Format string syntax: ...%\<flags\>\<width\>.\<precision\>\<type\>...  
  
#### Supported types are:  
  
```  
	c		(char)
	s		(string)
	p		(pointer value)
	d, i	(signed integers)
	u		(unsigned integer)
	x, X	(hex numbers, in lower or uppercase)
	%		(literal percent sign)
```  
  
#### Width and precision:  
  
```  
	- width means the minimum string length that an item should take up
		-	if the argument is shorter in length than the given width (0 if unset), it is padded with leading spaces to meet the minimum length
	- precision:
		-	for numbers (decimal or hex), it means the minimum number of digits it should take up. Leading zeros are used to pad if needed
		-	for strings, it means the maximum number of characters to print.
			-		for "(null)", nothing is printed when precision is set and below 6 ("%s", NULL)
```  
  
#### Supported flags are:  
  
```  
	0		(fills width space with 0s instead of spaces)
	-		(left justifies content, instead of the default right justify)
	#		alternate hex form (just puts a prefix, really)
	' '		uses a leading space to indicate a positive decimal number (including 0)
	+		overrides the space flag to use a + to indicate a positive number
```  
  
#### Duplicate flags are tolerated  
  
#### Caveats:  
  
```  
	- using the space flag and setting width is not a good idea. It might as well be a conflict but, as with the standard printf, it is not a conflict
	- the built-in printf enjoys many benefits from being a special function that receives extra care from the compiler. It can detect:
		-	an improper amount of arguments for a given format string
		-	type mismatches
		-	the original base system (decimal, octal, hex) of a number (not in string format) to be considered when parsing %i
		-	conflicting flags
		-	conflicting flags and types
	- we the programmer cannot hope to do half of these items while following standard printf usage.
	- to implement error highlighting for flags would be inconsistent with the rest of the caveats, where we cannot do much
	- instead, we ignore flags and try to print the string anyway:
```  
  
##### Ignoring stuff  
  
```  
	#:			if the type is anything besides x or X, this is ignored
	' ':		if + is specified, ignore this flag
	+:			if the arg is not a signed number, both + and ' ' would be ignored
	0:			if precision is set, or if - is specified, or if the arg is not a number, ignore this flag
	precision:	for %c and %p, ignore this value
```  
  
### Instructions  
  
To compile: make && clang \-Wall \-Wextra \-Werror main.c libftprintf.a  
  
Other make rules:  
	- bonus, clean, fclean, re  
  
### Resources  
  
Honestly, asking AI about the flags was a mistake. I have been discovering quirks and interactions up until the last second  
The very best resource covering these details is the man page `man 3 printf`  
Alternatively, `https://man7.org/linux/man-pages/man3/printf.3.html`  
  
Claude did help troubleshoot my veriadic logic not functioning properly on mobile terminals:  
```  
	- on wsl and on campus, passing around the va_list by value worked fine
	- however, on my phone (Termux) and ipad (iSH), they needed the va_list to be passed via pointer when helper functions were involved
		-	or else they would process the first arg over and over
		-	affected calls: process(q, &va), va_arg(*va, ...)
```  
  
### Function structure  
  
```  
ft_printf
	- printf_tokens
		-    valid
		-    new_str
		-    new_op
			-        type_bus
	- process
		-    grab
			-        *_op
				-            handle_flag
				-            prec_help
				-            str_min
				-            int_help
				-            uint_help
		-    print_strjoin
			-        print_strlen
```  
  
### Technical choices  
  
#### Data structure of choice  
  
Repeatedly handling array index positions is something to be despised above all else  
So, I have made the following adjustments:  
	- designing a system where the format string is iterated over only twice  
	- separating my validation, parsing, and flag ignoring logic  
	- offloading index adjustments to other functions where suitable  
  
To do all this, I chose to use a linked list to hold all the args and flags  
  
#### Character matching convenience  
  
There are two tables for matching flags and type identifiers, flag and type respectively  
	- flag is used for validating the format string, and never again  
	- type\_bus uses type to scan for individual flag matches without going past the type specifier  
	- neither of these tables make it to process. They are not needed anymore  
  
#### Type\_bus flag setting  
  
I had to stop the function from reacting to the 0 flag  
The condition for breaking out checks for a \>= 1 && a \<= 9  
  
#### Filling width and precision fields  
  
All argument strings are handled by handle\_flag, which returns a malloc'd string with necessary filler placed, and index placed to fill the correct places with content after  
First, the string length is calculated from max\(width, precision, size\)  
```  
	- size is passed in from the caller, which would be the number of digits or characters that would be printed from the format argument
	- precision is modified by both caller and callee:
		-	for numbers, precision should not consider prefixes for padding leading 0s
		-	for strings, precision is reduced to size if larger
	- for chars and pointer values, precision is disregarded
	- max(width, precision, size) is saved as len
```  
Then, the string is initialised to hold '0' in all spaces  
	- for non\-numbers, precision would be equal to or smaller than size, and this has no effect  
	- for numbers, remaining 0s would be visible  
  
Width is then considered to fill the spaces that precision and size do not occupy  
```  
	- if the 0 flag is in effect, we do not have to do anything
	- remaining spaces are calulated with start and end bounds
		-	for left-justify, start: max(size, precision), end: width
		-	for right-justify, start: 0, end: width - max(size, precision)
```  
Index is set according to the following:  
	- for left\-justify, precision \- size  
	- for right\-justify, max\(width, precision\) \- size  
	- if i is a negative number \(i.e. size was the bigger part of the equation\), i is set to 0  
  
#### Argument handling  
  
Grab takes an argument according to the type specifier. And so, that is how I split up my argument operations  
```  
    - %c takes an int out of the list, as calling va_arg(va, char) leads to undefined behaviour
    - including larger-than-needed containers in the prototypes of my functions causes printing discrepancies with the standard printf, so I have not
    	-	for uint_op, container over/underflow happens either at:
    		-		va_arg(*va, unsigned int) in grab
    		-		or, return (uint_op((unsigned long) src, type, q)) in ptr_op
		-	for int_op, container over/underflow happens at the grab call:
			-		va_arg(*va, int)
```  
#### On handling int\_max, int\_min, long\_max, long\_min, uint\_max, and ulong\_max  
  
I use an iterator t to traverse my number. I always use the same type for t that I do for my number.  
	- for %d and %i, I pass my arg into an unsigned int before working on it  
	- for hex numbers and %u, I use unsigned longs  
  
t increments via: t \*= base  
For a number n, t stops at \(n / t\) \<= base  
  
For positive values:  
```  
	- t is guaranteed to be smaller than the maximum value for a given type
		-	for base 10, t will stop at a multiple of 10, with the same number of digits as, say, int_max
		-	for base 16, the max for a given type is a multiple of 16 (2^31 or 2^32 or 2^63 or 2^64) minus one
			-		so t will stop at (n / t) = 15
```  
For negative values \(pertains to ints\):  
```  
	- the absolute value of a number is 0 - n. The signedness of 0 is insignificant, but we will assume (unsigned int) 0 for clarity
		-	binary 10000000000000000000000000000000 represents int_min, but for uint it is the next number after int max
		-	where a uint would set bits to 1 to add a number, signed ints also add the same number to int min in the same manner
			-		i.e. (int_max + 1) + 3 has the same binary form as int min + 3, but the latter has a different absolute value!
	- so, having the value ((unsigned int) n) on hand, where it should be less than (int_max + 1) by the same amount that it is more than, just subtract the values!
		-	using (unsigned int) 0 acts as uint_max + 1:
			-		0 - n = abs(n)
			-		for n = int_min, (unsigned int) n and 0 - n are the same
```  
