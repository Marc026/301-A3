#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:

    //Function:
    //Default constructor that assigns a string and loads the dictionary file
    //Precondition:
    //none
    //Postcondition:
    //a visited board all assigned to 0
    Boggle();  // load "dictionary.txt" into dict

    //Function:
    //loads a file
    //Precondition:
    //default constructor variables assigned properly
    //Postcondition:
    //constructor is initialized and file needed for test is made
    explicit Boggle(string filename);  // load filename into dict

    //Function:
    //copies the board into a deep copy and makes sure its the proper size
    //Precondition:
    //none
    //Postcondition:
    //there are 2 copies of the board
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    //Function:
    //Resets wordsFound Dictionary and calls SBH
    //Precondition:
    //order, orderCounter, step, and prefix is initalized
    //Postcondition:
    //words in all directions on the board has been checked
    void SolveBoard(bool printBoard, ostream &output);

    //Function:
    //Saves all words from last solve
    //Precondition:
    //SaveDictionaryFile is properly coded
    //Postcondition:
    //all words from the current solve is saved before deleting
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    //Function:
    //gets dictionary of all words
    //Precondition:
    //none
    //Postcondition:
    //none
    Dictionary GetDictionary();

    //Function:
    //makes wordsfound dictionary for boggle game
    //Precondition:
    //none
    //Postcondition:
    //none
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    //Function:
    //prints board if user inputs it to be displayed
    //Precondition:
    //visited at position is either 0 or 1
    //Postcondition:
    //2 boards marking the visited positions with quotes and incrementing numbers is displayed
    void PrintBoard(ostream& output, string prefix);

    //Function:
    //checks all positions around the current position to see if it is a word in the dictionary
    //Precondition:
    //SolveBoard has been initialized
    //Postcondition:
    //all words possible on the board has been found and marked visited(1 or true)
    void SolveBoardHelper(int row, int col, string prefix, int step,  ostream& output, bool printBoard, int orderCounter);
};

#endif //BOGGLE_BOGGLE_H
