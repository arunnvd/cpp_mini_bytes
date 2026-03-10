#pragma once

#include <random>

#define RANGE_MIN 0
#define RANGE_MAX 100

struct _magic_number {
  private:  
    int number;

  public:
    _magic_number(){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distrib(RANGE_MIN, RANGE_MAX);
      number = distrib(gen);
    }

    int get_number() {
      return number;
    }
};

typedef struct _magic_number Magic_Number ;
