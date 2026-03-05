*This project has been created as part of the 42 curriculum by dthoo*  
  
##Description  
  
Pipex aims to emulate file redirection as seen in the shell, taking zsh and bash for reference.  
You may recognise some of the symbols below:  
```
< in cmd1 | cmd2 > out
<< LIM cmd1 | cmd2 | cmd3 >> out
```  
Where in and out are files, and cmd1, cmd2, and cmd3 are shell commands.  
  
##Instructions  
  
To create the pipex program:  
`make`  
  
Usage:  
`./pipex in cmd1 cmd2 out`  
which performs:  
`< in cmd1 | cmd2 > out`  
  
Bonus features include chaining any number of commands, and using heredocs.  
To create the bonus version of pipex:  
`make bonus`  
  
Usage:  
`./pipex in cmd1 cmd2 cmd3 cmd4 ... cmdn out`  
  
Heredoc usage:  
`./pipex here_doc LIM cmd1 cmd2 ... cmdn out`  
which performs:  
`<< LIM cmd1 | cmd2 | ... | cmdn >> out`  
where LIM is any string of choice, which might be "a" for example.  
  
Note that the outfile contents are truncated when not using heredoc, and appended when using heredoc.  
  
##Resources  
  
error codes and messages: perplexity and the testers  
  
what is a pipe: https://www.geeksforgeeks.org/linux-unix/piping-in-unix-or-linux/  
  
how do pipes work: https://effective-shell.com/part-2-core-skills/thinking-in-pipelines/  
  
pipe usage: https://www.geeksforgeeks.org/c/pipe-system-call/  
	this image in particular helps: https://media.geeksforgeeks.org/wp-content/uploads/sharing-pipe.jpg  
  
dup usage: the dup man page, and this: https://www.geeksforgeeks.org/c/dup-dup2-linux-system-call/  
  
fork usage: https://stackoverflow.com/questions/4597893/specifically-how-does-fork-handle-dynamically-allocated-memory-from-malloc  
	mallocs should be freed and fds should be closed in all processes  
  
errno: the man page is good enough, just about every function with a man page has their interactions with errno listed in them  
  
what permissions do: https://linuxconfig.org/im-getting-permission-denied-on-my-bash-script-causes-and-solutions  
  
execve: using it is simple enough, preparing to use it consists of literally everything else in this section  
	https://stackoverflow.com/questions/72513285/using-execve-linux  
  
bash command handling:  
	bash pipe and errno behaviour: https://zfredenburg.medium.com/how-to-detect-errors-in-a-bash-pipe-c05c78ab8994  
	bash errno value: https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html  
	what is PATH: https://askubuntu.com/questions/551990/what-does-path-mean  
	what bash does with PATH: https://linuxize.com/post/linux-which-command/  
	why is ls -l in quotes: https://askubuntu.com/questions/1133173/variable-with-quotation-marks  
  
testers:  
	basic + envp + concurrency testing, which should all pass: https://github.com/vfurmane/pipex-tester  
	bad permissions testing: https://github.com/denisgodoy/pipex-tester.git  
		basic quote parsing capability is included, I throw an error upon seeing unclosed quotes
