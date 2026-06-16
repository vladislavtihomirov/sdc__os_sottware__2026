# Lab 4

Dynamic linked lists and file system metadata in C.

## Run

```powershell
cd C:\os-software
docker compose build lab4
docker compose run --rm lab4
```

Inside the container:

```bash
gcc -Wall -Wextra -g run.c -o run
./run
```

When prompted, enter a file name from the printed list, for example:

```text
run.c
```

## Trace System Calls

```bash
strace -e trace=openat,getdents64,statx ./run
```

## Check Memory

```bash
valgrind --leak-check=full --track-fds=yes ./run
```

## Debug

```bash
gdb ./run
break main
run
next
quit
```

## Program

The program scans the current directory, stores file metadata in a linked list, prints node addresses, searches by file name, and frees the list.
