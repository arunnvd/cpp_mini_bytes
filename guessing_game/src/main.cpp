#include <iostream>
#include "game.h"

int main () {
  Game game;
  int guess;

  std::cout << "New Game initialized!! \n" ;

  while(!game.is_game_over()) {
    std::cout << "Enter your Guesss (Attempts remaining = " << game.get_remaining_guess() << " )\n";

    std::cin >> guess;
    if (game.is_guess_correct(guess)) {
      std::cout << "Congrats !!! Your guess is correct\n";
      return 0;
    }

    std::cout << "Wrong Guess, Try again \n"; 
    std::cout << "*Hint* : " << game.get_hint();

  }

  std::cout << "Game Over :( Correct number was =  " << game.get_magic_number() << " \n";

  return 0;
}
