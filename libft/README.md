*This Project has been created as part of the 42 curriculum by dthoo*
  
## Libft  
  
### Description  
  
This project is a collection of generic functions. It serves two purposes:  
  
- to document the behaviour of functions available in other common libraries  
- to house custom functionality in one convenient libary and header  
  
these functions, along with the ft_printf and gnl projects, are housed inside of libft.

### Intructions

`make` gets you most of the functionality.  
`make bonus` includes t\_list functionality

### Resources

The following functions from other libraries are shadowed:
- isalpha
- isdigit
- isalnum
- isascii
- isprint
- isspace
- strlen
- memset
- bzero
- memcpy
- memmove
- strlcpy
- strlcat
- toupper
- tolower
- strchr
- strrchr
- strncmp
- strdup
- strndup
- memchr
- memcmp
- strnstr
- atoi
- isxdigit \(ft_ishex\)
- fabsf \(absf\)
- fminf \(minf\)

### The other functions are as follows:  
|||
|---|---|
| max2| finds the maximum between two ints|
| min2| finds the minimum between two ints|
| minf| returns the minimum from two floats|
| ft_swap| swaps two ints using pointers|
| ft_swapf| swaps two floats using pointers|
| ft_abs| convert an int to its absolute value|
| ft_atoi_ind| parses the number at the start of the string, and increments an external string index|
| ft_atohu_ind| parses an unsigned hexadecimal number in a string and increments an external index|
| ft_ftoa| converts a float to a new malloc'd string|
| ft_itoa| convert an int to a new malloc'd string|
| ft_split| takes a string, splits it by a delimiter which is discarded, and returns the remainder as a new string array|
| ft_ptrlen| counts how many pointers there are in a pointer array|
| split_cleanup| frees a null terminated string array|
| ft_strtrim| trims the characters included in set from the start and end of a string|
| ft_substr| duplicates a subset of a string, given a starting point and the length|
| ft_strmapi| creates a copy of its input string and applies function f to each character in the copy|
| ft_striteri| applies function f to each character in its input string, modifying the string|
| ft_putnbr| outputs a number to stdout|
| ft_putstr| outputs a string to stdout|
| ft_putchar| outputs a character to stdout|
| ft_putnbr_fd| outputs a number to file descriptor fd|
| ft_putstr_fd| outputs a string to file descriptor fd|
| ft_putchar_fd| outputs a character to file descriptor fd|
| malloc_cond| combines a malloc call with a success check to reduce vertical scrolling|
| ht_init| initialises a lookup table for use in string manipulation|
| ft_isquote| checks if a character is a single or double quote|
| ft_intset| sets an array of ints to be a given value|
  

#### t_list functions \(t_list nodes function as a linked list\):  
|||
|---|---|
|ft_lstnew|creates a t_list node|
|ft_lstsize|returns the number of nodes in a list of t_list nodes|
|ft_lstadd_front|adds a node, replacing the head of the list|
|ft_lstadd_back|adds a node to the end of a list|
|ft_lstdelone|frees a node using function del on the contents|
|ft_lstclear|frees a whole list using function del on the contents|
|ft_lstlast|returns the last node in a list|
|ft_lstmap|creates a copy of a list and modifies the contents of the copy using function f|
|ft_lstiter_chk| modifies a list using function f, stops when it fails by checking with function chk|
  
  
#### The following projects are stored in the libft folder and exposed as functions in the libft header:  
|||
|---|---|
|ft_printf|an emulation of a subset of printf|
|gnl|reads from file descriptor fd, and returns a malloc string containing the first line it found|
|gnl_b|uses more stack space to read from multiple files seamlessly|
