# Number Guessing Game

A simple number guessing game based on C++ (Compiled using C++17)  

## How to Play
* Run the executable `./guessinggame`  
* Start guessing numbers between 0 - 100  
* If your guess is matches with the random number generated, You won the game.  
* If not matching, you get another attempt to guess   
* A hint message will be displayed to help for your next guess.
* Total 3 attempts can be made and if number not found, then game over.

## Building the project
```
> cd guessing_game/build   

> cmake ..   
> make

// Clean the project
> make clean      # Remove built objects
> make clean-all  # Remove entire build directory

```
