[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/minishell/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/minishell/blob/master/README.fr.md)

# Minishell

## Summary

This project is about creating a little bash to learn about processes and file descriptors.

## Usage

```shell
git clone git@github.com:nfauconn/minishell.git
cd minishell/Project
make
```

```shell
./minishell
```

## Description


| Program name | minishell |
|--|--|
Language | C
Turn in files | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re` 
External functs. | `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

**Handled Bash POSIX features**:
- Displays a prompt when waiting for a new command.
- Has a working history.
- Search and launch the right executable (based on the `PATH` variable or using a relative or an absolute path).
- No use of more than one global variable (to indicate a received signal). This approach ensures that the signal handler will not access the main data structures.  
- `’` (single quote) which prevent the shell from interpreting the metacharacters in the quoted sequence.
- `"` (double quote) which prevent the shell from interpreting the metacharacters in the quoted sequence except for `$` (dollar sign).
- Redirections:
	- `<` redirects input.
	- `>` redirects output.
	- `<<` heredoc: redirects input from a string following the command.
    - `>>` redirects output in append mode.
- `|` (pipe character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- `$`: Environment variables (`$` followed by a sequence of characters which should expand to their values).
- `$?` which should expand to the exit status of the most recently executed foreground pipeline.
- In interactive mode:
    - `ctrl-C` displays a new prompt on a new line.
    - `ctrl-D` exits the shell.
    - `ctrl-\` does nothing.
- The following builtins:
    - `echo` with option `-n`
    - `cd` with only a relative or absolute path
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

> The `readline()` function can cause memory leaks.

## Skills

- **Understanding of Shell Operations**:
   - In-depth knowledge of how shell commands are executed
   - Familiarity with the functionalities of a standard shell

- **Process Management**:
   - Understanding of process creation and management using system calls like `fork`, `execve`, `wait`, and `signal`
   - Knowledge of inter-process communication and how to handle multiple processes

- **File Descriptor and Redirection**:
   - Managing file descriptors for I/O operations
   - Proficiency in implementing redirection (`>`, `>>`, `<`, `<<`) and pipes (`|`)

- **Signal Handling**:
   - Skills in managing signals for process control (`ctrl-C`, `ctrl-D`, `ctrl-\`)
   - Understanding of how to write robust programs that handle signals gracefully

- **Parsing and Command Execution**:
    - Skills in parsing user input and executing commands accordingly
    - Understanding of how to handle different types of user input, including environment variable expansion and quoting

- **Interactive and Non-Interactive Mode Handling**:
    - Experience in managing shell behavior in both interactive and non-interactive modes

- **Programming in C**:
   - Proficiency in C language, understanding of its syntax and semantics. We really deepened our rigor in programming in C with this project
   - Ability to write efficient, maintainable, and reusable code

- **Memory Management**:
   - Deep understanding of dynamic memory allocation and deallocation
   - Ability to prevent and handle memory leaks and ensure efficient memory usage

- **Error Handling and Norm Compliance**:
   - Ability to write code that robustly handles errors and exceptional cases
   - Adherence to coding standards and norms for readability and maintainability.
