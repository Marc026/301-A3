
#include "Dictionary.h"
#include "Boggle.h"
using namespace std;


// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");
    visited[BOARD_SIZE][BOARD_SIZE] = 0;
    string board = " ";
}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);
    visited[BOARD_SIZE][BOARD_SIZE] = 0;
    string board = " ";
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            this->board[row][col] = board[row][col];
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    wordsFound.MakeEmpty(); // reset wordsFound dictionary

    if(printBoard) {
        output << endl;
    }

    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=0; j<BOARD_SIZE; j++) {
            // Reset visited array for each position on the board
            for(int k=0; k<BOARD_SIZE; k++) {
                for(int l=0; l<BOARD_SIZE; l++) {
                    visited[k][l] = false;
                }
            }

            // Call SolveBoardHelper for current position on the board
            string prefix;
            int step = 0;
            SolveBoardHelper(i, j, prefix, 1, output);
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        output << "  ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (visited[i][j]) {
                output << "'" << board[i][j] << "'" << " ";
            } else {
                output << " " << board[i][j] << "  ";
            }
        }
        output << endl;
    }
    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, string prefix, int step, ostream& output) {

    // Check if current position is valid
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return;
    }

// Check if current position has already been visited
    if (visited[row][col]) {
        return;
    }

// Add current letter to prefix
    prefix += board[row][col];

// Check if prefix is a valid prefix
    if (!dict.IsPrefix(prefix)) {
        return;
    }

// Check if prefix is a valid word
    if (dict.IsWord(prefix)) {
        // Check if word is already found
        if (!wordsFound.IsWord(prefix)) {
            // Add word to wordsFound dictionary
            wordsFound.AddWord(prefix);
        }

        bool printBoard;
        if(printBoard){
            output << prefix << endl;
        }
        // Output word to ostream object with its index in the dictionary
        output << wordsFound.IsWord(prefix) << "\t" << prefix << endl;
    }

// Mark current position as visited
    visited[row][col] = true;

// Recursively check surrounding positions
    SolveBoardHelper(row - 1, col, prefix, step++, output);     // North
    SolveBoardHelper(row - 1, col + 1, prefix, step++, output); // Northeast
    SolveBoardHelper(row, col + 1, prefix, step++, output);     // East
    SolveBoardHelper(row + 1, col + 1, prefix, step++, output); // Southeast
    SolveBoardHelper(row + 1, col, prefix, step++, output);     // South
    SolveBoardHelper(row + 1, col - 1, prefix, step++, output); // Southwest
    SolveBoardHelper(row, col - 1, prefix, step++, output);     // West
    SolveBoardHelper(row - 1, col - 1, prefix, step+1, output); // Northwest

// Mark current position as unvisited
    visited[row][col] = false;

}
