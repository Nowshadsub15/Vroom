#!/bin/bash

echo "Compiling Vroom..."

if [ ! -d "assets" ]; then
    echo "Warning: assets/ folder not found — textures will fail to load!"
fi

gcc main.c src/*.c -O1 -Wall -std=c99 -Wno-missing-braces -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
    echo "Build Successful! Launching game..."
    ./game
else
    echo "Build Failed! Check the terminal for errors."
fi