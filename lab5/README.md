# Lab 5

Processes and signals in Linux.

## Run

```powershell
cd C:\os-software
docker compose build lab5
docker compose run --rm lab5
```

Inside the container:

```bash
gcc -Wall -Wextra -g run.c -o run
```

## Modes

```bash
./run tree
./run exec
./run zombie
./run zombie-fixed
./run server
```

## Observe Processes

While `./run tree` or `./run zombie` is running:

```bash
ps -e -o pid,ppid,stat,comm
pstree -p <parent-pid>
ps aux | awk '$8 ~ /Z/'
```

## Test Signals

```bash
./run server &
SERVER_PID=$!
sleep 3
kill -SIGUSR1 $SERVER_PID
sleep 2
kill -SIGINT $SERVER_PID
wait $SERVER_PID
```

## Debug

```bash
gdb ./run
break main
run tree
next
quit
```
