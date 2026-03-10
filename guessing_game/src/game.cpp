#include <iostream>
#include "game.h"

Game::Game(): remaining_guess{3}, last_guess{0}, guessed_numbers{} {
  //std::cout << "Start Guessing !!\nAttempts Left = " << remaining_guess << "\n";
}

bool Game::is_guess_correct(int guess) {
  if (guess == magic.get_number()) {
    return true;
  }

  // Wrong guess : Update members
  remaining_guess --;
  last_guess = guess;
  guessed_numbers.push_back(guess);

  return false;
}

int Game::get_remaining_guess() {
  return remaining_guess;
}

bool Game::is_game_over() {
  if (remaining_guess <= 0){
    return true;
  }

  return false;
}

int Game::get_magic_number() {
  if(!is_game_over()) {
    std::cout << "Game is still in progress, magic number will not be revealed until game over !!\n";
    return -1;
  }

  return magic.get_number();
}

std::string Game::get_hint() {
  if (remaining_guess >= 3 || remaining_guess <= 0) {
    return "Game just started or Already Finished, no hints available\n";
  }

  int delta = magic.get_number() - last_guess;

  if (delta < 0){
    // Gussed number is higher than actual number
    delta = 0 - delta;
    return "Your guess is Higher than actual number and " + delta_message(delta);
  } else {
    return "Your guess is Lesser than actual number and " + delta_message(delta);
  }
}

std::string delta_message(int delta) {

  if (delta > DELTA_HIGH) {
    return "Far Away\n";
  } else if (delta > DELTA_MID) {
    return "Relatively closer\n";
  } else if (delta > DELTA_NEAR){
    return "Much closer\n";
  }

  return "Almost reached\n";
}



