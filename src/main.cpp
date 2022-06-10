#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../include/assembly.h"

int main(int argc, char* argv[])
{
  try {
    if (argc < 3)
      throw std::runtime_error("Use: dot86 <assembly file> <output binary>");

    std::ofstream b(argv[2], std::ios::binary);
    std::ifstream f(argv[1]);
    std::string line;
    while(std::getline(f, line)) {
      auto v = dot86::assembly(line);
      for (auto i = v.begin(); i != v.end(); i++)
        b << *i;
    }
    b.flush();
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
