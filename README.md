# Vroom 
 
A Hill Climb Racing–style 2D physics driving game, built in **C** with **raylib**.
 
Developed as a course project for **CSE 4202 — Structured Programming 2**.
 
**Team members**
- Sadman Islam — 240041107
- Ismail Hossain — 240041109
- M. Sayem Rahman — 240041103

The physics model is inspired by
[unconv/uphill-racer](https://github.com/unconv/uphill-racer)

## Project Structure
 
```
Vroom/
├── main.c                 
├── build.sh  
├── assets/              
└── src/
    ├── game.h / game.c            
    ├── car.h                      
    ├── car_physics.c              
    ├── car_render.c               
    ├── terrain.h                  
    ├── terrain_physics.c          
    ├── terrain_render.c           
    ├── camera.h / camera.c
```

## Controls
 
| Key | Action |
|---|---|
| `Right Arrow` |  forward  |
| `Left Arrow` |  backward  |

## Requirements
 
- A C compiler (`gcc`)
- [raylib](https://www.raylib.com/) installed, with its dependencies:
  `libGL`, `libpthread`, `libdl`, `librt`, `libX11`
- Linux (tested on Ubuntu and WSL2)

---

## Installing raylib
 
### Linux / WSL2
 
Install raylib itself via the PPA 
 
```bash
sudo add-apt-repository ppa:texus/raylib
sudo apt update
sudo apt install libraylib5-dev
```
 
Install the runtime libraries raylib depends on :
 
```bash
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev \
    libxi-dev libxinerama-dev libxcursor-dev libxkbcommon-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Building and Running
 
### Get the code
 
```bash
git clone https://github.com/Nowshadsub15/Vroom.git
cd Vroom
```
 
### Linux / macOS
Run from the project root directory
 
```bash
./build.sh
```
 
This compiles the game and, if the build succeeds, launches it
automatically. If you only want to build without launching:
 
```bash
gcc main.c src/*.c -O1 -Wall -std=c99 -Wno-missing-braces -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./game
```









 



