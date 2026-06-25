# Lab 6

Data races and thread synchronization with POSIX threads.

## Run

```powershell
cd C:\os-software
docker compose build lab6
docker compose run --rm lab6
```

Inside the container:

```bash
gcc -Wall -Wextra -g -O0 run.c -o run -lpthread
```

## Modes

```bash
./run race
./run volatile
./run mutex
./run bench
```

## Stage 1: Reproduce the data race

```bash
./run race
```

Run several times — the result is unstable and usually less than `4000000`.

```bash
./run volatile
```

`volatile` does not fix the race: the counter is still wrong.

## Stage 2: Fix with mutex

```bash
for i in 1 2 3 4 5; do ./run mutex; done
```

Each run should print `4000000` and `Верно!`.

## Stage 3: Measure synchronization cost

```bash
./run bench
```

Compares race, per-iteration mutex, and batch mutex approaches.

## Helgrind

```bash
valgrind --tool=helgrind ./run race
valgrind --tool=helgrind ./run mutex
```

Race mode should report data races. Mutex mode should be clean.

## Debug

```bash
gdb ./run
break main
run race
next
quit
```
