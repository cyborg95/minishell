*This project has been created as part of the 42 curriculum by otidahoh, wngambi.*

# Minishell

## Description

Minishell is a **simplified reproduction of a Unix shell**, inspired by the behavior of Bash.  
The goal of this project is to gain a deep understanding of how a command interpreter works by implementing process management, signal handling, environment management, and user input parsing.

This project allows you to explore fundamental concepts in operating systems:
- Process management (`fork`, `execve`, `wait`)
- Redirections and pipes
- Environment variable management
- Command-line parsing and tokenization
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)

Minishell implements a subset of Bash features, including:
- Execution of simple commands
- Pipes (`|`)
- Redirections (`>`, `>>`, `<`, `<<`)
- Environment variables (`$VAR`)
- Built-ins (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)

---

## Resources

Minishell is a very interesting project because it combines many of the concepts mentioned above.

One of the main sources of learning comes from collaboration and knowledge sharing with other students from 42 who have already completed the project.

Additional useful resources include:
- Unix manual pages (`man bash`, `man execve`, `man fork`)
- Bash documentation
- Online tutorials about building a shell in C

---

## Instructions

### Compilation

Inside the repository directory:

```bash
make
```

Cleaning:

```bash
make clean   # Remove object files (.o)
make fclean  # Remove object files and executables
make re      # Recompile everything
```

Execution:

```bash
./minishell
```
