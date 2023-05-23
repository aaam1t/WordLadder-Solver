#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include "ladderWithFakes.hpp"

int main(int argc, char* argv[]) {
  LadderWithFakes G {"4words.txt"};
  std::string origin;
  std::string dest;
  std::string fakesIn;
  int fakes;

  while (true) {
    std::cout << "Starting word: ";
    std::getline(std::cin, origin);
    while (!std::all_of(origin.begin(), origin.end(), [](char c){ return std::isalpha(c); }) || origin.length() != 4) {
      std::cout << "Please enter a valid four letter word\nStarting word: ";
      std::getline(std::cin, origin);
    }
    std::transform(origin.begin(), origin.end(), origin.begin(), [](unsigned char c){ return std::tolower(c); });

    std::cout << "Ending word: ";
    std::getline(std::cin, dest);
    while (!std::all_of(dest.begin(), dest.end(), [](char c){ return std::isalpha(c); }) || dest.length() != 4) {
      std::cout << "Please enter a valid four letter word\nEnding word: ";
      std::getline(std::cin, dest);
    }
    std::transform(dest.begin(), dest.end(), dest.begin(), [](unsigned char c){ return std::tolower(c); });

    std::cout << "Fakes: ";
    std::getline(std::cin, fakesIn);
    while (!std::all_of(fakesIn.begin(), fakesIn.end(), [](char c){ return std::isdigit(c); }) || fakesIn.length() < 1) {
      std::cout << "Please enter a valid integer\nFakes: ";
      std::getline(std::cin, fakesIn);
    }
    fakes = std::stoi(fakesIn);

    auto path = G.shortestPathWithFakes(origin, dest, fakes);
    if (path.size() > 0) {
      std::cout << "\nPath from '" << origin << "' to '" << dest << "' using " << fakes << " fake(s):";
      for (std::string s : path) {
        std::cout << '\n' << s;
      }
      std::cout << "\nAchievable in " << path.size() - 1 << " steps.";
    }
    else {
      std::cout << "\nNo path found from '" << origin << "' to '" << dest << "' using " << fakes << " fake(s).";
    }
    std::cout << "\n\n";
  }
}
