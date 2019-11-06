# Quadris (Tetris-like game in c++)
[![Build Status](https://img.shields.io/badge/C%2B%2B-Language-brightgreen)](https://travis-ci.com/username/projectname)
[![Build Status](https://img.shields.io/badge/MVC-design-green)](https://travis-ci.com/username/projectname)
[![Build Status](https://img.shields.io/badge/Observer%20-design-green)](https://travis-ci.com/username/projectname)

This is a Tetris-like game wrote in c++.It is the final project of CS246 in UW and collaborated with other two teammates.

This game employs several design patterns like observer,factory,MVC and etc. 
## Usage
```liunx
User$make
User$./quadris
```

## Command
After lunching the game,we can type commands in command line
```linux
left
```
move the current block left one cell
```linux
right
```
move the current block right one cell
```linux
down
```
move the current block down one cell
```linux
drop
```
drop the current block directly from current position
```linux
clockwise
```
roatate current block clockwise for 90 degrees
```linux
counterclockwise
```
roatate current block counterclockwise for 90 degrees
```linux
restart
```
restart the game
```linux
leveldown
```
level down the current game mode
```linux
levelup
```
level up the current game mode
```linux
hint
```
give the currently best place fot this block
