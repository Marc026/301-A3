#include "Dictionary.h"
#include "Boggle.h"
using namespace std;

// Your code here

// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;                    //dict Dictionary in Boggle
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;              //wordsFound Dictionary in Boggle
}

Boggle::Boggle() {                                      //default constructor
    dict.LoadDictionaryFile("dictionary.txt");  //load dictionary file
    visited[BOARD_SIZE][BOARD_SIZE] = {0};              //make a visit board all in 0
    string board = " ";                                 //make board string
}

Boggle::Boggle(string filename) {                       //load file constructor
    dict.LoadDictionaryFile(filename);                  //load file needed
    visited[BOARD_SIZE][BOARD_SIZE] = {0};              //make a visit board all in 0
    string board = " ";                                 //make board string
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {        //set size of board
        for (int col = 0; col < BOARD_SIZE; col++) {
            this->board[row][col] = board[row][col];    //deep copy of board
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    wordsFound.MakeEmpty(); // reset wordsFound dictionary

    for(int i=0; i<BOARD_SIZE; i++) {                   //checks every position of board
        for(int j=0; j<BOARD_SIZE; j++) {
            // Call SolveBoardHelper for current position on the board
            int order[BOARD_SIZE][BOARD_SIZE] = {0};    //order board of whats been visited
            int orderCounter = 0;                       //set order of visited to 0
            string prefix;                              //prefix
            int step = 0;
            SolveBoardHelper(i, j, prefix, 1, output, printBoard, orderCounter);
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);        //save output to filename
}

void Boggle::PrintBoard(ostream &output, string prefix) { //prints board to output
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (visited[i][j] > 0) {            //if position has been visited
                output << " '" << board[i][j] << "' " ;     //put quotes around letter
            } else {
                output << "  " << board[i][j] << "  ";  //else just put spaces
            }
        }
        output << "\t";     //tab
        for(int k = 0; k < BOARD_SIZE; k++){    //same as previous board but instead
            output << "  " << visited[i][k] << "  " ;   //a board of 0 and
        }                                       //incremented visited positions
        output << endl;
    }
    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, string prefix, int step, ostream& output, bool printBoard, int orderCounter) {

    // Check if current position is valid
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return;
    }

// Check if current position has already been visited
    if (visited[row][col] > 0) {
        return;
    }

// Add current letter to prefix
    prefix += board[row][col];

// Check if prefix is a valid prefix
    if (!dict.IsPrefix(prefix)) {
        return;
    }

    //increment in which it has visited that position
    orderCounter++;
    // Mark current position as visited
    visited[row][col] = orderCounter;

// Check if prefix is a valid word
    if (dict.IsWord(prefix)) {
        // Check if word is already found
        if (!wordsFound.IsWord(prefix)) {
            // Add word to wordsFound dictionary
            wordsFound.AddWord(prefix);

            // Output word to ostream object with its index in the dictionary
            if(wordsFound.WordCount() > 0 && printBoard != true){
                output << wordsFound.WordCount() << "\t" << prefix << endl;
            }
            if (printBoard == true) {   //if user wants to display board
                output << "Word: " << prefix << endl;   //output the info
                output << "Number of Words: " << wordsFound.WordCount() << endl;    //output info
                PrintBoard(output, prefix);
            }
        }
    }

// Recursively check surrounding positions
    SolveBoardHelper(row - 1, col, prefix, step++, output, printBoard,  orderCounter);     // North
    SolveBoardHelper(row - 1, col + 1, prefix, step++, output, printBoard,  orderCounter); // Northeast
    SolveBoardHelper(row, col + 1, prefix, step++, output, printBoard,  orderCounter);     // East
    SolveBoardHelper(row + 1, col + 1, prefix, step++, output, printBoard,  orderCounter); // Southeast
    SolveBoardHelper(row + 1, col, prefix, step++, output, printBoard,  orderCounter);     // South
    SolveBoardHelper(row + 1, col - 1, prefix, step++, output, printBoard,  orderCounter); // Southwest
    SolveBoardHelper(row, col - 1, prefix, step++, output, printBoard,  orderCounter);     // West
    SolveBoardHelper(row - 1, col - 1, prefix, step++, output, printBoard,  orderCounter); // Northwest
// Mark current position as unvisited
    visited[row][col] = false;

}