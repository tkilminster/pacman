# Pac-Man
Pac-Man in C++ using OpenGL. The current version only supports Linux based systems. For any additional information or just for interest-sake please view the [full report](https://github.com/tkilminster/pacman/blob/master/pacman_report.pdf "View Report").

**DISCLAIMER: First C++ program I ever wrote. Does not follow proper programming practices. Here for nostalgia and interest of others.**

## Dependencies
* **libpng** used for the binding and viewing of the PNG sprites.

## How To Compile
> ln -fs Makefile.linux Makefile

> make pacman -B

## How To Run
> ./pacman

## How To Play
The aim of Pac-Man is to eat all the pills to advance to the next level, without being caught by the ghosts.

If Pac-Man eats a super pill the ghosts will turn frightened and Pac-Man will be able to eat them to gain bonus points. Otherwise, if Pac-Man encounters a ghost he will lose a life.

Pac-Man can also gain bonus points by eating the bonus fruit which appears randomly in the maze once a certain amount of pills have been eaten.

### Controls
#### Movement
* Arrow Keys - Left, Up, Right, Down

#### Game
* P - Pause/ Unpause the game
* Q - Quit the game
* R - Only when "Game Over" is showing R will start a new game

## Notes
* This was made for university coursework and is therefore no longer being actively updated.
