# WordLadder-Solver
A solver for the popular word game Word Ladder

## About the game
Word Ladder is a popular word game invented by Lewis Carroll. You are given two words and must transform one into the other by changing one letter at a time, such that each change resutls in a valid word. You can play the game online at [fourword.xyz](https://fourword.xyz).

## About the program
The program computes the minimum number of moves it takes to transform one word into another, or determine that it is not possible to do so. The program also allows the user to enter a budget of fake words that may be used to transform one word to the other.

This program was part of an assignment I submitted for 31251 Data Structures and Algorithms at UTS. The assignment explored the use of graphs and shortest parth algorithms, such as the A* algorithm used here.

- The word list used is from [fourword.xyz](https://fourword.xyz)
- vector-of-bool's [cmrc](https://github.com/vector-of-bool/cmrc) was used to compile the word list (as a .txt) into the program
