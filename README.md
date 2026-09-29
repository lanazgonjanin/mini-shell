# Mini Shell

A lightweight Unix-style command-line shell implemented in C. The program executes user commands through process creation and management, and includes a circular command history with support for repeating previous commands.

Developed as part of COMPSCI 3SH3: Operating Systems at McMaster University under Dr. Neerja Mhaskar, in collaboration with Thaneesha Sivasithambaram.

## Features

* **Command Execution:** Executes external programs using `execvp()`.
* **Process Creation:** Creates child processes using `fork()`.
* **Process Synchronization:** Uses `waitpid()` to wait for foreground processes to finish.
* **Background Execution:** Supports commands ending in `&` without waiting for the child process.
* **Command History:** Stores the five most recent commands using a circular array.
* **History Display:** Displays previously entered commands using `history`.
* **Command Repetition:** Re-executes the most recent command using `!!`.

## Operating Systems Concepts

This project demonstrates:

* Process creation and management
* Parent-child process relationships
* System calls
* Process synchronization
* Foreground and background execution
* Program execution using the `exec` family of functions

## Implementation

The shell is implemented in C using POSIX process-management functions and standard C libraries.

A fixed-size circular array is used to maintain command history, allowing older commands to be overwritten as new commands are entered.

## Compilation and Execution

Compile using GCC:

```bash
gcc shell.c -o mini-shell
```

Run:

```bash
./mini-shell
```

Replace `shell.c` with the actual source filename if different.

## Example Commands

```text
osh> pwd
osh> ls
osh> history
osh> !!
osh> sleep 5 &
osh> exit
```

## Technologies

* **Language:** C
* **Operating Systems:** POSIX
* **Concepts:** Process management, system calls, circular arrays, string manipulation
* **Libraries:** `stdio.h`, `unistd.h`, `string.h`, `sys/wait.h`
