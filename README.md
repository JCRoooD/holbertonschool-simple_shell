# Holberton School- Simple Shell

## Simple Shell
> In this project we developed a simple **UNIX** command interpreter "shell" as part of low-level programming foundation and algorithm-Linux and Unix system programming.
> A shell is an interactive command-line interpreter. We created a shell that would utilize the command line
> interface (CLI).

## Requirements

### General

+ Allowed editors: **vi**, **vim**, **emacs**
+ All your files will be compiled on Ubuntu 20.04 LTS using gcc, Using the options **-Wall** **-Werror** **-Wextra** **-pedantic** **-std=gnu89**
+ All your files should end with a new line
+ A README.md file, at the root of the folder of the project is mandatory
+ Your code should use the **Betty** style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
+ Your shell should not have any memory leaks
+ No more than 5 functions per file
+ All your header files should be include guarded
+ Use system calls only when you need to ([why?](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))


### Synopsis
> This repository holds all the code necessary for our custom simple shell to run.
> Our shell currently handles the executions of executables found in the
> environmental variable PATH, with their full paths. Sample commands
> that our shell supports include  ```/bin/ls```, ```/bin/pwd```. We've also created the following builtins.

### Builtins
* ```exit``` exits shell (```Usage: exit [status]```)
* ```env``` prints environmental variables (Usage: ```env```)

### Functions and sytems calls used
```malloc```,```realloc```, ```free```, ```execve```, ```waitpid```, ```write```, ```exit```

### Description of what each file shows:
```
shell.c ------------------------------ this file reads the line, splits it in tokens, executes and launches the commands given
man_simpleshell -------------------------- custom manpage for our simple shell
header_shell.h -------------------------------------- holds prototypes of functions and headers
```
Helper files
```
execute_command.c ------------------------- performs tokenization, creates child process and handles path
free_stuff.c -------------------------------------- frees the arrays
```
### How To Install, Compile, and Use
Install and Compile
```
(your_terminal)$ git clone https://github.com/gabriel337/simple_shell.git
(your_terminal)$ cd simple_shell
(your_terminal)$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```
Sample Usage
```
$ /bin/ls
 file1.c  file2.c file3.c
$ /bin/pwd
/home/usr/simple_shell
$ man ./man_1_simple_shell (opens our manpage for more information)
```
Stop and return to your original shell
```
$ exit
(your_terminal)$
```
OR
```
$ Ctrl+D
(your_terminal)$
```

### To Do
* More functionality can still be added (e.g. commands without path, handle aliases, pipelines, and redirections)

### Bugs
* when running certain commands, the output is:
```
free(): invalid pointer
Aborted (core dumped)
```
---

### Authors
Juan Rodriguez & Neischaly Ruidiaz
