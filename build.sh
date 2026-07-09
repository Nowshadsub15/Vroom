#!/bin/bash

echo "Compiling Vroom..."

# Compile main.c using Linux Raylib flags
gcc main.c -O1 -Wall -std=c99 -Wno-missing-braces -o vroom -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# $? checks the exit status of the gcc command (0 means success)
if [ $? -eq 0 ]; then
    echo "Build Successful! Launching game..."
    ./vroom
else
    echo "Build Failed! Check the terminal for errors."
fi