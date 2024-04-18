# Simple Shell (Multi-Processing)


## 1. Objectives

1. Familiarity with system calls in Unix environment.
2. Introduction to processes and multi-processing.
3. Introduction to signal handling in Unix environment.

## 2. Problem Statement

It is required to implement a Unix shell program. A shell is simply a program that conveniently allows you to run other programs. Read up on your favorite shell to see what it does.

Your shell must support the following commands:

1. The internal shell command "exit" which terminates the shell
    * **Concepts**: shell commands, exiting the shell.
    * **System calls**: exit()
2. A command with no arguments
    * **Example**: ls, cp, rm …etc
    * **Details**: Your shell must block until the command completes and, if the return code is abnormal, print out a message to that effect.
    * **Concepts**: Forking a child process, waiting for it to complete and synchronous execution.
    * **System calls**: fork(), execvp(), exit(), waitpid()
3. A command with arguments
    * **Example**: ls –l
    * **Details**: Argument 0 is the name of the command.
    * **Concepts**: Command-line parameters.
4. A command, with or without arguments, executed in the background using &.
    * **Example**: firefox &
    * **Details**: In this case, your shell must execute the command and return immediately, not blocking until the command finishes.
    * **Concepts**: Background execution, signals, signal handlers, processes and asynchronous execution.
    * **Requirements**: You have to show that the opened process will be nested as a child process to the shell program via opening the task manager found in the operating system like the one shown in figure 1. Additionally you have to write in a log file (basic text file) when a child process is terminated (main application will be interrupted by a SIGCHLD signal). So you have to implement an interrupt handler to handle this interrupt and do the corresponding action to it.
5. Shell builtin commands
    * **Commands**: cd & echo
    * **Details**: for the case of:
        * **cd**: Cover all the following cases (**assume no spaces in path**):
            * cd
            * cd ~
            * cd ..
            * cd absolute_path
            * cd relative_path_to_current_working_directory
        * **echo**: Prints the input after evaluating all expressions (**assume input to echo must be within double quotations**).
            * echo "wow" => wow
            * export x=5
            * echo "Hello $x" => Hello 5
6. Expression evaluation
    * **Commands**: export
    * **Details**: Set values to variables and print variables values. No mathematical operations is needed.
    * **Export Details**: Accept input of two forms, either a string without spaces, or a full string inside double quotations.
    * **Example**:
        * export x=-l
        * ls $x => Will perform ls -l
        * export y="Hello world"
        * echo "$y" => Hello world

## Test Case

**Open** your shell.

**Execute** the following commands.

```Shell
ls
mkdir test
ls
ls -a -l -h
export x="-a -l -h"
ls $x
```

**Execute** the following commands in the same session, but **show** that shell is stuck and cannot execute other commands while firefox is open.

**Note:** In order for this test to work correctly, firefox has to be closed before executing this command. Also, if firefox is not available, you may use 'gedit' instead.

```Shell
firefox
```

**Close** the firefox.

**Open** the log file, show us its content, then close it.

**Execute** the following commands in the same session, but **show** that shell is not stuck and can execute other commands while firefox is open.

```Shell
firefox &
```

**Open** the log file, show us its content, then close it

**Open** the system monitor and expand all running processes under your shell process.

**Open** the system monitor and **Search** for all firefox processes.

**Execute** the following command in the same session, it should show us an error message.

```Shell
heyy
```

**Execute** the following command in the same session, it should close the shell from the first time you execute it.

```Shell
exit
```

That's it!

## Lab requirements

* Students will be working individually.
* You can only use C programming language.
* Use Ubuntu operating system for development.
* Submit the deliverables using the submission form provided in your class.
* If the submitted code cannot replicate the same video scenario, then this will be considered cheating and the "cheating and plagiarism" policy will be applied.
