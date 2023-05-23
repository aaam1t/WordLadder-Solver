#ifndef LADDER_WITH_FAKES_HPP_
#define LADDER_WITH_FAKES_HPP_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <utility>

class LadderWithFakes {
 private:
  // add some private member variables if needed
  std::unordered_set<std::string> words {};

  // struct to store word and remaining fake budget
  struct WordFakes {
    int fakes;
    std::string word;
    auto operator<=>(const WordFakes& other) const = default;
  };

  // store the word, fake budget, heuristic distance to destination,
  // and distance to origin
  struct WordFakesDistance {
    int heurDist;
    int realDist;
    WordFakes wf;
    auto operator<=>(const WordFakesDistance& other) const = default;
  };

 public:
  LadderWithFakes();

  // initialise any private member variables you want 
  // in order to be ready to compute shortest paths with fakes
  explicit LadderWithFakes(const std::string&);

  // given two strings and a budget of fake words k, find the shortest 
  // path between the two strings using at most k fake words
  std::vector<std::string>
  shortestPathWithFakes(const std::string&, const std::string&, int k);

 private:
  // add vertex a to the graph with no neighbours if a is
  // not already a vertex.  Otherwise, do nothing.
  void addVertex(const std::string& a);
  // if both a and b are vertices in the graph then add
  // an edge between them.  Otherwise do nothing.
  void addEdge(const std::string& a, const std::string& b);
  // check if there is an edge between words a and b
  bool isEdge(const std::string& a, const std::string& b) const;
  // check if a is a vertex
  bool isVertex(const std::string& a) const;
  // remove vertex a from the graph
  void removeVertex(const std::string& a);
  
  void findNeighbours(const std::vector<std::string>& words);

  std::unordered_map<std::string, int>
  getNeighbours(const WordFakes& wf);

  std::vector<std::string> outputPath(const std::string& origin, const WordFakes& dest,
                                      const std::map<WordFakes, WordFakes>& prev);

  std::vector<std::string> getFakes(const std::string& a);

  int diffLetters(const std::string& a, const std::string& b);
};

#endif      // LADDER_WITH_FAKES_HPP_
