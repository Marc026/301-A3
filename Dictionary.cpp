#include "Dictionary.h"
// Your code here

class Node {                    //default constructor for Node
public:
    bool IsWord;                //IsWord variable
    Node* children[NUM_CHARS];  //Make NUMCHARs children

    Node() {
        IsWord = false;         //set the flag to false
        for (int i = 0; i < NUM_CHARS; i++) {   //make new children nodes
            children[i] = nullptr;      //set them to nullptr
        }
    }
};

Dictionary::Dictionary() {      //default constructor
    root = new Node;            //root to new node
    numWords = 0;               //0 words
    Node();                     //call node constructor
}

Dictionary::Dictionary(const Dictionary &otherDict) {   //copy constructor
    root = new Node;            //root to new node
    numWords = 0;               //0 words
    copyOther(otherDict);       //call copy0ther function with parameter otherDict
}

Dictionary::Dictionary(string filename) {   //2nd constructor
    root = new Node;            //root to new node
    numWords = 0;               //0 words
    LoadDictionaryFile(filename);   //loads file
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if (this != &otherDict) {
        copyOther(otherDict);   // Copy contents of other into *this.
    }

    // return self
    return *this;
}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream infile;          //ifstream variable/object
    string content = "";      //empty string to input content into
    infile.open(filename); //Inserts each word into the dictionary

    while(!infile.eof())     //while not at end of file
    {
        getline(infile,content);    //get the content in the file
        AddWord(content);            //add the words into the data structure
    }
    infile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream outFile(filename);     //ofstream variable/object into filename
    if (!outFile.is_open()) {         //if not open, throw error
        throw DictionaryError(filename + " failed to open");
    }
    SaveDictionaryHelper(root, "", outFile);    //save into file
}

void Dictionary::AddWord(string word) {
    Node* node = root;          //set node to root
    for (int i = 0; i < word.length(); i++) {   //check how long each word is
        char c = word[i];       //set one letter of the word to the index of the word
        if (c < 'a' || c > 'z') {   //check if it is not a character
            throw DictionaryError("Invalid character"); //throw error
        }
        int index = c - 'a';    //find its position in the word
        if (node->children[index] == nullptr) {     //if getting to the end of the word is null
            node->children[index] = new Node();     //make a new node
        }
        node = node->children[index];               //set node to the length of the indexed word
    }
    node->IsWord = true;         //set IsWord to true to say it is a word
    numWords++;                 //bookkeeping
}

void Dictionary::MakeEmpty() {  //clears data structure
    destroyHelper(root);    //calls destroy function
    root = new Node;        // Rebuild root
    numWords = 0;           //and reset number of words
}

bool Dictionary::IsWord(string word) {
    Node* node = root;      //set node to root
    for (int i = 0; i < word.length(); i++) {   //checks length of word
        char c = word[i];       //sets one letter of the word to the index of the word
        if (c < 'a' || c > 'z') {   //check if it is not a character
            throw DictionaryError("Invalid character"); //throw error
        }
        int index = c - 'a';    //find its position in the word
        if (node->children[index] == nullptr) {     //if getting to the end of the word is null
            return false;
        }
        node = node->children[index];   //set node to the length of the indexed word
    }
    return node->IsWord;    //returns that it is a word
}

bool Dictionary::IsPrefix(string word) {
    Node* node = root;      //set node to root
    for (int i = 0; i < word.length(); i++) {   //checks length of word
        char c = word[i];   //sets one letter of the word to the index of the word
        if (c < 'a' || c > 'z') {   //check if it is not a character
            throw DictionaryError("Invalid character");     //throw error
        }
        int index = c - 'a';    //find its position in the word
        if (node->children[index] == nullptr) {     //if getting to the end of the word is null
            return false;
        }
        node = node->children[index];       //set node to the length of the indexed word
    }
    return true;    //returns it is a prefix

}

int Dictionary::WordCount() {
    return numWords;        //returns number of words
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();    //calls make empty function

    // copy over the number of words from otherDict
    numWords = otherDict.numWords;

    // recursively copy the tree
    copyHelper(root, otherDict.root);

    return;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if (thisTree == nullptr){   //if tree already empty/nullptr
        return;     //return
    }

    destroyHelper(thisTree->left);      //destroy left tree
    destroyHelper(thisTree->right);     //destroy right tree
    delete thisTree;                            //delete
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if (otherTree == nullptr) {     //if tree already empty/nullptr
        thisTree = nullptr;         //set thisTree to nullptr
        return;
    }

    thisTree = new Node;            //make new node
    thisTree->IsWord = otherTree->IsWord;   //point this tree to other tree

    for (int i = 0; i < NUM_CHARS; i++) {   //start copying over characters
        copyHelper(thisTree->children[i], otherTree->children[i]);
    }
}


void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr) {  // base case: reached a null node
        return;
    }

    if (curr->IsWord) {     //if currently on a word
        outFile << currPrefix << endl;      //cout
    }

    for (int i = 0; i < NUM_CHARS; ++i) {       //for length of word
        char letter = 'a' + i;      //find its indexed position
        string next_prefix = currPrefix + letter;   //add letter
        SaveDictionaryHelper(curr->children[i], next_prefix, outFile);
    }
}