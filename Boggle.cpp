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


    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=0; j<BOARD_SIZE; j++) {
            // Reset visited array for each position on the board

            // Call SolveBoardHelper for current position on the board
            string prefix;
            int step = 0;
            SolveBoardHelper(i, j, prefix, 1, output, printBoard);
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (visited[i][j] != 0) {
                output << " '" << board[i][j] << "' ";
            } else {
                output << "  " << board[i][j] << "  ";
            }
        }
        output << endl;
    }
    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, string prefix, int step, ostream& output, bool printBoard) {

    // Check if current position is valid
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return;
    }

// Check if current position has already been visited
    if (visited[row][col] == 1) {
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

            // Output word to ostream object with its index in the dictionary
            if(wordsFound.WordCount() > 0 && printBoard != true){
                output << wordsFound.WordCount() << "\t" << prefix << endl;
            }
            if (printBoard == true) {
                output << "Word: " << prefix << endl;
                output << "Number of Words: " << wordsFound.WordCount() << endl;
                PrintBoard(output);
                //step++;
            }
        }
    }



// Mark current position as visited
    visited[row][col] = true;

// Recursively check surrounding positions
    SolveBoardHelper(row - 1, col, prefix, step++, output, printBoard);     // North
    SolveBoardHelper(row - 1, col + 1, prefix, step++, output, printBoard); // Northeast
    SolveBoardHelper(row, col + 1, prefix, step++, output, printBoard);     // East
    SolveBoardHelper(row + 1, col + 1, prefix, step++, output, printBoard); // Southeast
    SolveBoardHelper(row + 1, col, prefix, step++, output, printBoard);     // South
    SolveBoardHelper(row + 1, col - 1, prefix, step++, output, printBoard); // Southwest
    SolveBoardHelper(row, col - 1, prefix, step++, output, printBoard);     // West
    SolveBoardHelper(row - 1, col - 1, prefix, step++, output, printBoard); // Northwest

// Mark current position as unvisited
    visited[row][col] = false;

}