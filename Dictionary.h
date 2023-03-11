#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    //Function:
    //set up an empty binary search tree
    //Precondition:
    //None
    //Postcondition:
    //Set root to new node and numWords to 0
    Dictionary();
    //~Dictionary();  // I will not require this

    //Function:
    //copies everything into other tree
    //Precondition:
    //root and numWords set to proper parameters
    //Postcondition:
    //copy0ther function should be properly called
    Dictionary(const Dictionary& otherDict);    // copy constructor

    //Function:
    //2nd constructor that loads file
    //Precondition:
    //root and numWords set to proper parameters
    //Postcondition:
    //file is loaded
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    //Function:
    //copies all of otherDict to this
    //Precondition:
    //none
    //Postcondition:
    //copied all to this
    Dictionary& operator=(const Dictionary& otherDict);

    //Function:
    //loads file
    //Precondition:
    //ifstream variable is called
    //Postcondition:
    //file is properly loaded into a tree
    void LoadDictionaryFile(string filename);

    //Function:
    //saves content into file
    //Precondition:
    //ofstream variable is called
    //Postcondition:
    //conent is saved into a file
    void SaveDictionaryFile(string filename);

    //Function:
    //adds words into the binary tree
    //Precondition:
    //start at root node and checks for length of word
    //Postcondition:
    //IsWord flag is set to true after adding the word into tree
    void AddWord(string word);

    //Function:
    //Makes tree empty except for root node
    //Precondition:
    //destroy helper is called
    //Postcondition:
    //tree is empt except for root node and numwords is set back to 0
    void MakeEmpty();

    //Function:
    //checks if path down tree is a word
    //Precondition:
    //none
    //Postcondition:
    //flag at end of path is set to true to signal that it is a word
    bool IsWord(string word);

    //Function:
    //checks if path down tree ends at a prefix
    //Precondition:
    //none
    //Postcondition:
    //flag at end of path is set to false to signal that it is a prefix
    bool IsPrefix(string word);

    //Function:
    //returns total number of words
    //Precondition:
    //none
    //Postcondition:
    //return number of words
    int WordCount();  // Returns total number of words in dictionary

private:

    class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.
        struct Node* children[NUM_CHARS]; //each index represents a character
        bool IsWord;
        bool IsPrefix;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* next;
        //create object of Node
        Node(){
            IsWord = false;
            for(int i = 0; i < NUM_CHARS; i++){ //Make all nodes to null
                children[i] = nullptr;
            }
        }
        // It is strongly recommended you create a constructor
        // to set default values

    };

    Node* root;
    int numWords;

    //Function:
    //copies values from otherdict to this
    //Precondition:
    //called by makeempty function or copy constructor
    //Postcondition:
    //none
    // This function is used by the
    // copy constructor and the assignment operator.
    void copyOther(const Dictionary& otherDict);

    //Function:
    //destroy function
    //Precondition:
    //called by makeempty or copyother function
    //Postcondition:
    //none
    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    void destroyHelper(Node* thisTree);

    //Function:
    //copy helper function that does most of the copying
    //Precondition:
    //none
    //Postcondition:
    //contents copied into this
    void copyHelper(Node*& thisTree, Node* otherTree);

    //Function:
    //save function that does most of the saving
    //Precondition:
    //none
    //Postcondition:
    //saves the words into new dictionary
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
