#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <map>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cassert>
#include <cmrc/cmrc.hpp>
#include "ladderWithFakes.hpp"

CMRC_DECLARE(wl);

// default initialiser does not need to do anything
LadderWithFakes::LadderWithFakes() = default;

LadderWithFakes::LadderWithFakes(const std::string& inputFile) {
  auto fs = cmrc::wl::get_filesystem();
  auto file = fs.open("resources/" + inputFile);
  std::string word;
  for (auto c : file) {
    if (c == '\n') {
      words.insert(word);
      word = "";
    }
    else {
      word += c;
    }
  }
  // now all the words in inputFile are in the set words (declared in header)...
}

// return the number of letters two words differ by
int LadderWithFakes::diffLetters(const std::string& a, const std::string& b) {
  int diff = std::max(a.size(), b.size());
  for (std::size_t i = 0; i < std::min(a.size(), b.size()); i++) {
    if (a[i] == b[i]) {
      diff--;
    }
  }
  return diff;
}

// given two strings and a budget of fake words k, find the shortest 
// path between the two strings using at most k fake words

// A* search algorithm from Week 10 Tutorial (Knight Moves Revisited)
// This is very similar to a regular BFS algorithm, except we prioritise
// exploring nodes that are likely to be closer to the destination
// - see header for the structs used
std::vector<std::string>
LadderWithFakes::shortestPathWithFakes(const std::string& origin,
                                       const std::string& dest,
                                       int k) {
  
  // words are sorted by most letters shared with the destination
  std::priority_queue<WordFakesDistance,
                      std::vector<WordFakesDistance>,
                      std::greater<WordFakesDistance>> queue;

  queue.push({diffLetters(origin, dest), 0, {k, origin}});

  std::map<WordFakes, WordFakes> prev;
  std::map<WordFakes, int> distances{{{k, origin}, 0}};
  std::set<WordFakes> visited;

  while (!queue.empty()) {
    WordFakesDistance current = queue.top();
    queue.pop();
    if (visited.find(current.wf) != visited.end()) {
      continue;
    }
    visited.insert(current.wf);
    if (current.wf.word == dest) {
      return outputPath(origin, current.wf, prev);
    }
    for (auto n : getNeighbours(current.wf)) {
      WordFakesDistance next {current.realDist + 1 + diffLetters(n.first, dest),
                              current.realDist + 1, {n.second, n.first}};
      if (distances.find(next.wf) == distances.end() || next.realDist < distances[next.wf]) {
        // update if we find an unexplored node or a shorter path to a visited node
        distances[next.wf] = next.realDist;
        prev[next.wf] = current.wf;
        queue.push(next);
      }
    }
  }

  return {};
}

// once we've found the destination,
// walk backwards to the origin and output the path
std::vector<std::string>
LadderWithFakes::outputPath(const std::string& origin, const WordFakes& dest,
                            const std::map<WordFakes, WordFakes>& prev) {
  std::vector<std::string> path;
  for (WordFakes wf = dest; wf.word != origin; wf = prev.at(wf)) {
    path.push_back(wf.word);
  }
  path.push_back(origin);
  std::reverse(path.begin(), path.end());
  return path;
}

// get all the neighbours of the given word -
// first we get all possible words that differ to the current word by one letter
// for each, if it is real, add it to neighbours with no penalty in fakes,
// if it is not real and we have fakes left, add it to neighbours with
// a reduction in the number of fakes remaining
std::unordered_map<std::string, int>
LadderWithFakes::getNeighbours(const WordFakes& wf) {
  std::unordered_map<std::string, int> neighbours;
  for (std::string f : getFakes(wf.word)) {
    if (words.find(f) != words.end()) {
      neighbours[f] = wf.fakes;
    } else if (wf.fakes > 0) {
      neighbours[f] = wf.fakes - 1;
    }
  }
  return neighbours;
}

// get all the words, real or fake, that differ to the given word
// by a single letter
std::vector<std::string> LadderWithFakes::getFakes(const std::string& a) {
  std::vector<std::string> fakes {};
  for (std::size_t i = 0; i < a.size(); i++) {
      for (char letter = 'a'; letter <= 'z'; letter++) {
          if (a[i] == letter) {
              continue;
          }
          std::string fake = a;
          fake[i] = letter;
          fakes.push_back(fake);
      }
  }
  return fakes;
}
