#pragma once

#include "magic_number.h"
#include <string>
#include <vector>


#define DELTA_HIGH 50
#define DELTA_MID  25
#define DELTA_NEAR 10

std::string delta_message(int delta);

class Game {
private:
  Magic_Number      magic;
  int               remaining_guess;
  int               last_guess;
  std::vector<int>  guessed_numbers;

public:
  Game();

  bool          is_guess_correct(int guess);
  std::string   get_hint ();
  bool          is_game_over();
  int           get_remaining_guess();
  int           get_magic_number(); // Get the random generated number, Only works after gameover.
};
