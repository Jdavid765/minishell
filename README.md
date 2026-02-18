*This project has been created as part of the 42 curriculum by jcano-du and nfiora-d.*

# Minishell - As beautiful as a shell

## Description

**Minishell** is a project aimed at creating a simple shell. Yes, your own little bash. This project is a great opportunity to get to grips with strictly controlled APIs, process creation, and file descriptors.

The goal is to implement a functional command-line interpreter that mimics the behavior of `bash` (Unix shell). It parses user input, executes commands, handles environment variables, and manages pipelines and redirections.



**Key objectives:**
* Deep understanding of **processes** and file descriptors.
* Mastering `fork`, `execve`, `wait`, and `pipe`.
* Handling signals (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
* Parsing and tokenizing complex user input.

## Features

This shell supports the following features:

* **Prompt**: Display a prompt when waiting for a new command.
* **Command History**: A working history.
* **System Executables**: Search and launch the right executable (based on the `PATH` variable or using a relative/absolute path).
* **Quotes Handling**:
    * `'` (single quotes): Prevents the shell from interpreting meta-characters in the quoted sequence.
    * `"` (double quotes): Prevents the shell from interpreting meta-characters in the quoted sequence except for `$`.
* **Redirections**:
    * `<` redirect input.
    * `>` redirect output.
    * `<<` heredoc (read input until a delimiter is seen).
    * `>>` redirect output in append mode.
* **Pipes**: `|` The output of each command in the pipeline is connected to the input of the next command via a pipe.
* **Environment Variables**: Handles `$` expansion and exit status `$?`.
* **Signals**:
    * `Ctrl-C`: Displays a new prompt on a new line.
    * `Ctrl-D`: Exits the shell.
    * `Ctrl-\`: Does nothing (like in bash).

### Builtins
The following builtins are implemented:
* `echo` with option `-n`.
* `cd` with only a relative or absolute path.
* `pwd` with no options.
* `export` with no options.
* `unset` with no options.
* `env` with no options or arguments.
* `exit` with no options.

## Instructions

### 1. Compilation
To compile the project, run the following command at the root of the repository:

```bash
make
```
### 2. Execution
For execute the minishell you need to write this command:

```bash
./minishell
```
### 3. Clean
For remove just the object files:
```bash
make clean
```

### 4. Clean All
For remove object files with the executable:

```bash
make fclean
```