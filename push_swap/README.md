*This project has been created as part of the 42 curriculum by dthoo*  
  
## Push\_swap  
  
### Prelude  
  
```  
me: to get target distance from top to use heuristics, I need relative placements
	to use the radix method, I need relative placements
	to use chunking algorithmsm, I also need relative placements

me: the only way to get relative placements...is to sort the number sequence beforehand isnt it

Perplexity: yes.

me: bruh
```  
  
### Description  
  
My goal: use stack instructions to sort the numbers in stack A in ascending order  
Ascending order means that the lowest number sits at the top  
  
Seeing as this is a stack organisation excercise, there is a merge sorted duplicate array at the start  
that has then been reverted to replace the actual values with relative placements \(i.e. 0 to 100\)  
  
First, a list of problems with sorting numbers between two stacks:  
	- no random access, although I can browse the stacks whenever  
	- my actions are:  
		-	swap the top two items of a stack: sa, sb, ss  
		-	transfer stuff from the top of one stack to the other in reverse order: pa, pb  
		-	yeet the first or last items of a stack to the other end, in same order: ra, rb, rr, rra, rrb, rrr  
  
For my project, I use radix methods and greedy insertion  
  
n = 100 benchmark: 600  
n = 500 benchmark: 3900 ~ 4300  
  
There is also a checker here to verify if the stack was sorted. This and the push swap program reject:  
	- non integer inputs  
	- integer over/underflows  
	- empty arguments  
	- duplicate numbers  
  
Arguments containing multiple numbers are fine  
  
### Instructions  
  
'make' builds push\_swap  
  
`./push_swap 1 2 3 -1 ...`
  
'make bonus' builds the checker  

`./push_swap 1 2 3 | ./checker 1 2 3`
or  
`./push_swap 1 "2 3" | ./checker 1 "2 3"`
or  
`ARG="1 2 3"; ./push_swap $ARG | ./checker $ARG`
or  
```
./push_swap 1 2 3 > out.txt
cat out.txt | ./checker 1 2 3
```
or  
```
./checker 2 1 3
sa
(ctrl-d)
```
  
### Overview of the program  

The numbers are first reindexed to reduce the range of numbers while preserving their order

#### for fewer than 5000 numbers

Step 1, push numbers to stack b until there are 3 or less numbers left in stack a
If there are 50 or more numbers, chunk the contents of stack b
- stack b is partially sorted in descending order

Step 2, sort the numbers in stack a

Step 3, scan stack b to find the number that can be inserted into stack a using the least moves and do that
Repeat step 3 until stack b is empty

Step 4, rotate stack a so that the lowest number is at the top of the stack

#### for 5000 or more numbers

Step 1: determine bit_max, which is the maximum number of bits that can be meaningfully compared

Step 2: find the representation for each number in binary

Step 3: push all numbers that have a 0 in the lowest bit to stack b

Step 4: find the longest sequence of increasing numbers starting from 0 in stack b

Step 5: push numbers that have a 1 in the next bit and are not in the above sequence are pushed back to stack a

Repeat steps 3 to 5 until bit_max is reached

Step 6: rotate stack b the right way around and push its contents to stack a

### Resources and notes  
  
greedy insertion: (https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0)  
greedy insertion optimisation: toss that 'bound' integer out the window and search for candidates from either side of stack b. Automatic butterfly chunking!  
  
lsd radix: (https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e)  
lsd radix keep-in-b idea: (https://github.com/hu8813/push_swap/blob/main/src/sort.c)  

  
msd radix: my idea actually. It serves as a rather lazy method of chunking that:  
	- does no delta calculations, almost half of the numbers are in good chunks. The other half is split between the smallest and second smallest number chunks  
	- uses what I imagine as rather few moves to achieve what it does  
