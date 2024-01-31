[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/minishell/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/minishell/blob/master/README.fr.md)

*C Programming Language* • *Process Management* • *File Descriptors and Redirections* • *Exhaustive Parsing* • *Signal Handling* • *Error Management* • *Memory Management* • *Norm Compliance* • *Compilation Automation with Makefile*

# Minishell

This project is about creating a little bash to learn about processes and file descriptors.

| Key | Value |
|--|--|
| Program name | minishell |
Language | C
Turn in files | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re` 
External functs. | `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

**Handled Bash POSIX features**:
- Display a prompt when waiting for a new command.
- Have a working history.
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

> The `readline()` function can cause memory leaks, but none of the leaks are reachable outside of the `readline()` library itself.
## Usage


```shell
git clone git@github.com:nfauconn/minishell.git
cd minishell/Project
make
```

```shell
./minishell
```