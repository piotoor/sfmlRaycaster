## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Features](#features)
* [Status](#status)

## General info
This project is a simple raycaster engine written in C++ using SFML library.

![game](screenshots/screen1.png)

### Assets
Currently I'm using slightly modified Wolfenstein 3D textures.

## Technologies
* C++
* SFML

## Setup
### Linux
Clone the repo:
```
git clone https://github.com/piotoor/sfmlRaycaster.git
```
Install SFML library:
```
sudo apt-get install libsfml-dev
```

You may also need to install make and cmake:
```
sudo apt-get install build-essential
sudo apt-get install cmake
```

Go to the root directory of sfmlRaycaster project and build:
```
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
```

Now you can run the engine:
```
cd src
./sfmlRaycaster_run
```

### Windows
Prerequisites:

* [git](https://git-scm.com/download/win)
* [cmake](https://cmake.org/download/)
* [mingw](https://sourceforge.net/projects/mingw-w64/)

Clone the repo:
```
git clone https://github.com/piotoor/sfmlRaycaster.git
```

Update the submodules:
```
cd sfmlRaycaster/lib
git submodule update --init --recursive
```

Go to the root directory of the sfmlRaycaster project and build:

```
cd ..
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make.exe
```

Now you can run the engine:
```
cd src
sfmlRaycaster_run.exe
```

## Features
You can walk around the map using arrow keys.

## Status
Project is being refactored.
