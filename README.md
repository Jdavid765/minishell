*This project has been created as part of the 42 curriculum by jcano-du and nfiora-d.*

# Minishell - As beautiful as a shell 🐚

*This project was created as part of the 42 curriculum by jcano-du and nfiora-d.*

> 🤖 **AI Disclaimer:** Artificial Intelligence was used during this project to help sort and organize our files/folders, as well as to draft and format this README file.

## 📖 Description

**Minishell** is a project aimed at creating a simple shell—your very own little bash. This project is an excellent opportunity to get familiar with strictly controlled APIs, process creation, and file descriptor management.

The goal is to implement a functional command-line interpreter that mimics the behavior of `bash` (the Unix shell). It parses user input, executes commands, manages environment variables, as well as pipelines and redirections.

**Key Objectives:**
* In-depth understanding of **processes** and file descriptors.
* Mastery of the `fork`, `execve`, `wait`, and `pipe` system calls.
* Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
* Parsing and tokenization of complex user inputs.

## ✨ Features

This shell supports the following features:

* **Prompt**: Displays a prompt when waiting for a new command.
* **History**: A fully functional command history.
* **System Executables**: Searches for and launches the correct executable (based on the `PATH` variable or using a relative/absolute path).
* **Quotes Handling**:
  * `'` (single quotes): Prevents the shell from interpreting meta-characters within the quoted sequence.
  * `"` (double quotes): Prevents the shell from interpreting meta-characters, except for `$`.
* **Redirections**:
  * `<` redirects input.
  * `>` redirects output.
  * `<<` heredoc (reads input until a delimiter is encountered).
  * `>>` redirects output in append mode.
* **Pipes**: `|` The output of each command in the pipeline is connected to the input of the next command via a pipe.
* **Environment Variables**: Handles expansion with `$` and exit status with `$?`.
* **Signals**:
  * `Ctrl-C`: Displays a new prompt on a new line.
  * `Ctrl-D`: Exits the shell.
  * `Ctrl-\`: Does nothing (matches standard bash behavior).

### 🛠️ Implemented Builtins
* `echo` (with the `-n` option)
* `cd` (with relative or absolute paths)
* `pwd` (with no options)
* `export` (with no options)
* `unset` (with no options)
* `env` (with no options or arguments)
* `exit` (with no options)

## 🚀 Usage Instructions

### 1. Compilation
To compile the project, run the following command at the root of the repository:
```bash
make

### 2. Execution
To run the minishell, execute:
```bash
./minishell
```

### 3. Cleaning
To remove only object files (`.o`):
```bash
make clean
```
To remove object files AND the executable:
```bash
make fclean
```

### 🧪 Tests
A God-Mode test script (`test_leak`) is included to check for memory leaks (using Valgrind) and compare return codes with the real Bash.
```bash
./test_leak
```

---

## 📚 Sources & Useful Resources

Here is the list of resources, documentation, and tutorials that helped us build this project:

### 📖 Documentation & Basic Concepts
* **Roadmap shell/bash**: https://roadmap.sh/shell-bash
* **Comprehensive Bash Manual (thanks Théo)**: https://www.gnu.org/software/bash/manual/bash.html
* **Writing Your Own Shell (Doc Nassim)**: Chapter 5 - Purdue University
* **Minishell Gitbook (42 Cursus)**: https://42-cursus.gitbook.io/guide/3-rank-03/minishell
* **Minishell Advice (Mostafa Omrane)**: Mes conseils si je devais recommencer minishell
* **Théo's Notion Page (Cave sur ssbu)**: Minishell

### 🧠 Parsing, Tokenization & Redirections
* **Tokenization (Parsing)**: *Cours_Tokenisation_Minishell.pdf*
* **Here-doc**: Medium - Here-doc & Chapter 3.6.6 of man bash.
* **End-of-file (EOF)**: Wikipedia - EOF

### ⚙️ Signals, IOCTL & Exit Status
* **Signals (PDF A. Dragut)**: Cours Signaux
* **IOCTL Concept (Medium)**: The Linux Concept Journey - IOCTL
* **Exit Codes & Pipefail (Medium)**: Bash Scripting Exit Codes
* **Exit in Bash**: https://linuxize.com/post/bash-exit/
* **errno Return Values**: Chromium OS - errnos

### 🛠️ Compilation & Tools (Makefile & Git)
* **Makefile Debug Mode**: Reddit - Compiling a program in debug mode
* **Learn Git Branching**: https://learngitbranching.js.org/
* **GitHub Pull Request Tutorial**: YouTube - PR

### 🎬 Explanatory Videos
* **Nelson's Video Advice**: YouTube Live
* **Shell program more detail**: YouTube Playlist
* **Signals in C**: YouTube Playlist
* **Océano Simple Shell**: YouTube Video
* **Understanding Core Dumped**: YouTube Video