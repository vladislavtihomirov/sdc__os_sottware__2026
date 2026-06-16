# Lab 3

Dynamic memory and growth strategies in C.

## Run

```powershell
cd C:\os-software
docker compose build lab3
docker compose run --rm lab3
```

Inside the container:

```bash
gcc -Wall -Wextra -g run.c -o run
./run
```

## Trace Allocations

```bash
ltrace -e malloc+realloc+free ./run
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

The program compares three strategies for filling a dynamic array of `100000` integers:

- Linear growth with `realloc`, capacity `+100`.
- Exponential growth with `realloc`, capacity `*2`.
- Manual exponential growth with `malloc`, `memcpy`, and `free`.
