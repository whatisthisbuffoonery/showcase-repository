*This project has been created as part of the 42 curriculum by dthoo*  
  
## Get Next Line  
  
### Description  
  
The get\_next\_line function reads a line out of a file, or stdin  
Returns NULL on read error, empty/fully read file, or failure to open a file  
Buffer size can be changed at compile time  
  
### Instructions  
  
cc -Wall -Wextra -Werror get\_next\_line.c get\_next\_line\_utils.c  
use -DBUFFER\_SIZE=42, for example
  
### Resources  
  
None, really  
  
### How it works  
  
Take a file dscriptor number,  
Keep trying to read from it,  
If it makes a list by the end, parse it  
Return null or a string  
Partial reads are accounted for  
  
### Partial reads  
  
Occasions where read() reads less then buf\_size before EOF for whatever reason  
This does not happen very often, but I got to simulate this inadvertently with funny node sizes  
So, I now count each string length individually  
  
### Bonus section  
  
I added a per fd interface to my t\_var struct  
