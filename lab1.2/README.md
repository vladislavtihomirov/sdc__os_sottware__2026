# Lab 1.2

Types, functions, arrays, and dynamic memory in C.

## Run

```powershell
cd C:\os-software
docker compose build lab1_2
docker compose run --rm lab1_2
```

Inside the container:

```bash
gcc -Wall -Wextra -g run.c -o run
./run
```

## Debug

```bash
gdb ./run
break main
run
next
print count
quit
```

## Example

Input:

```text
5
3 1 4 1 5
```

Output includes:

```text
Sum: 14
Average: 2.80
Minimum: 1
Maximum: 5
Even count: 1
Odd count: 4
Sorted array: 1 1 3 4 5
```
