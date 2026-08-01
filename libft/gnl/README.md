*This project has been created as part of the 42 curriculum by dthoo*  
  
## Get Next Line  
  
Get_next_line has been abbreviated to gnl in the source files for usage convenience.  
These source files expose the functions:  
- gnl_b\(\), for simultaneosly reading from multiple files  
- gnl\(\), for saving space on stack memory  
  
### Description  
  
The get\_next\_line function reads a line out of a file, or stdin  
Returns NULL on read error, empty/fully read file, or failure to open a file  
Buffer size can be changed at compile time  
  
### Instructions  
  
Compilation:
```
cc -Wall -Wextra -Werror get\_next\_line.c get\_next\_line\_utils.c
```
Optional compilation flag to change the internal buffer size
```
-DBUFFER\_SIZE=N
```
where N is a number greater than 0

### Resources  
  
None, really.  
  
### How it works  
  
Take a file descriptor number and read from it,  
Stop reading when encountering a newline or EOF,
Return a string if able, null otherwise.  
Partial reads are accounted for.  
  
### Partial reads  
  
Occasions where read() reads less then buf\_size before EOF for whatever reason.  
This does not happen very often, but I got to simulate this inadvertently with funny node sizes.  
So, I now count each string length individually.  
  
### Bonus section  
  
I added a per fd interface to my t\_var struct  
