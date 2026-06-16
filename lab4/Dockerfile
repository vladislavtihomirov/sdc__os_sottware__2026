FROM debian:stable-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential gdb nano strace valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
