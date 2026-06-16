FROM debian:stable-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential gdb nano ltrace \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
