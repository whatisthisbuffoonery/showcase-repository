*This project has been created as part of the 42 curriculum by dthoo and achew*  

## Minishell
  
### Description  
  
Minishell is an emulation of a small subset of Bash. This subset includes:  
- env variables, not including positional parameters  
- basic working history, not including history expansion  
- execution of binaries, either directly or through PATH  
- echo, pwd, cd, env, export, unset, and exit as builtins  
- handling for SIGINT, SIGQUIT, and ctrl d  
- checking exit status through $?  
- single and double quote handling, except for unclosed quotes  
- redirections: >, >>, <, <<  
- pipelines  
  
The bonus part includes:  
- wildcards for the current directory  
- conditional execution: ||, &&  

I should note that the project did not define that this should be tested against a particular
version of bash; I was shown the following during our project evaluation:
```
bash --posix
```
This would have been helpful for us, but oh well.
  
### Instructions  
  
Compile in the root directory with
```
make
```
Run the executable without arguments or with --version
```
./minishell
```
Conditional operators and wildcards are included in the bonus compilation
```
make bonus
```
which yields the bonus executable
```
./minishell_bonus
```
  
### A not so brief overview of what subset of bash we emulated
  
#### command syntax
Bash takes a command and executes it.
This command takes the format of
```
[redirects] [command name] [args and more redirects]
```

A valid command contains at least a command name or an outgoing redirect

If it just has redirects, it creates or opens the files in order.
If such an operation fails, the remaining input is not executed.
The exit status is updated to reflect the last such operation attempted.

The above constitutes a command. The conditional operators && and || are placed
between commands to conditionally execute depending on the exit status of the command before.

Args and redirects may be interleaved:
```
ls ./ > a ../ > b
```
but it is not very useful; all of the output would appear in file b.

#### pipelines

Command pipelines using | redirect output from the
command on the left to the command on the right.

Any other redirects will overshadow this effect.

In relation to the above conditional operators, a pipeline is considered one command whose 
exit code is that of the last command in the pipeline.

#### subshells

Subshells using \(\) group any number of commands and pipelines together to be considered as one command.
- a conditional operator may skip the whole subshell.
- redirects applied to the subshell affect all commands inside that do not have their own redirects or piping.
	-	a pipeline would redirect the stdin and stdout of the whole subshell.
- a sigquit signal will cancel all the commands in the currently running subshell, where the signal
	is otherwise similar to sigint.

### String features

#### wildcards

Unquoted asterisks may be substituted for a number of filenames in the directory
using the wildcard sequence to match the names.
For example, \*\.c can be substituted for:
```
main.c utils.c
```
if the files exist.

If no such files match the wildcard sequence, no substitution will occur.
For this project, we implemented it to work for just the current working directory.

#### quotes

Single quotes prevent any of the text within from being altered.
Double quotes are similar, but allow env vars to be expanded.

#### environment variables

Environment variables take the form of:
```
$NAME
```
where NAME contains alphanumeric characters and underscores.

For our project scope, NAME is also restricted to starting with an alphabet letter.

Quotes and wildcards that result from env expansion will have their usual effect.

Env expansion is also the usual culprit for word splitting.

#### word splitting

If an env variable containing whitespace in its value is used, bash will perform word splitting:
- characters separated by whitespace will be separated unless they are in quotes \(i.e. "$a"\)
- non whitespace characters at the start and end of adjacent env variables will be joined together, if there is no whitespace between the variables

#### heredocs

Here-documents collect input from the user to pass into a command.
Heredocs take the form of:
```
<<LIM
```
where LIM is a word that does not undergo env or wildcard expansion.

The contents of the heredoc will not undergo wildcard expansion.
It will undergo env expansion unless LIM contains any quotes \(i.e. EOF""\).

The heredoc stops capturing input when the user enters a line containing only LIM.
This line is not included in the data sent to the command.

### PATH searching

The shell will attempt to search the PATH string to match command binaries if the command is not a builtin.
It will search from the leftmost item, and stop when a valid binary can be run.
If a matching binary is found earlier but could not be run, an error is only raised if the shell could not run the command.
The error raised corresponds to the first such occurence.

### Resources  
  
- [The Bash Manual](https://www.gnu.org/software/bash/manual/html_node/index.html#SEC_Contents)  
- [Darren's pipex README for pipeline and PATH semantics without considering signals](https://github.com/whatisthisbuffoonery/temp/blob/main/uwu/pipex/README.md)  
- Pipeline behaviour under signals: I think this was in the bash manual somewhere, but it is quite vague. We tested everything manually.  
- [Behaviour of export with no args, cd, pwd, and unset](https://man7.org/linux/man-pages/man1/bash.1.html#:~:text=SHELL%20BUILTIN%20COMMANDS%20%C2%A0): way way down in the man page for Bash, starting at around line 2500.  
- [Behaviour of env with no args](https://www.gnu.org/savannah-checkouts/gnu/coreutils/manual/html_node/env-invocation.html): 'info env' will show the relevant documentation.  
- [Behaviour of exit](https://man7.org/linux/man-pages/man1/exit.1p.html)  
- [Basic signal semantics](https://beej.us/guide/bgc/html/split-wide/signal-handling.html#signal-handling)  
- AI was used in various places for refactoring, squeezing ioctl and the termios functions into the picture, and finding silly semantic errors.  
