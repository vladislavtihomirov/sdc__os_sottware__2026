# Lab 1.1

Minimal C lab in Docker.

## Run

```powershell
cd C:\os-software
docker compose build
docker compose run --rm lab1_1
```

Inside the container:

```bash
gcc -Wall -Wextra -g lab1_1.c -o lab1_1
./lab1_1
```

## Debug

```bash
gdb ./lab1_1
break main
run
next
print firstName
quit
```

## Program

The program reads student data, validates each field, and prints a student card.
