#!/bin/bash
while true; do
    clear
    rm src/main.o
    rm src/main.d
    make run
    read -p ""
done
