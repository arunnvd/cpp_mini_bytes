#include <iostream>
#include "json.h"
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char *argv[]) {
  
  if (argc > 1) {
    std::string filename = argv[1];
    //std::cout << "Name : " << filename << std::endl;

    //Open file in read mode
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()) {
      std::cerr << "Unable to open file : " << filename << std::endl;
      return -1;
    }
    
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    inputFile.close();

    std::string file_contents = buffer.str();
    std::cout << "FileContent : " << file_contents << std::endl;

    std::string Err;
    size_t json_length = file_contents.length();

    JSON json(file_contents, json_length);

    if(json.parse() == false)
    {
      std::cout << "Unable to Parse json " << std::endl;
    }
    else {
      std::cout << "Valid JSON Object \n";
    }
  }
  else {
    std::cout << "Incorrect usage !" << std::endl \
      << "Correct usage : " << argv[0] << " [json file path]\n" ;
  }

  return 0;
}
