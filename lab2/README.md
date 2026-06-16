# Lab 2

Process memory anatomy and pointers in C.

## Run

```powershell
cd C:\os-software
docker compose build lab2
docker compose run --rm lab2
```

Inside the container:

```bash
gcc -Wall -Wextra -g -O0 run.c -o run
```

## Modes

```bash
./run addresses
./run addresses-pause
./run stack 20
./run endian
./run leak
./run fixed
```

## Check Process Memory Map

Run:

```bash
./run addresses-pause
```

In another shell in the same container:

```bash
cat /proc/<pid>/maps
```

Compare printed addresses with `[heap]`, `[stack]`, and executable mappings.

## Check Memory Leaks

Intentional leak:

```bash
valgrind --leak-check=full ./run leak
```

Fixed version:

```bash
valgrind --leak-check=full ./run fixed
```
