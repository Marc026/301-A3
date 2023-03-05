#include "Dictionary.h"
// Your code here

class Node {
public:
    bool IsWord;
    Node* children[NUM_CHARS];

    Node() {
        IsWord = false;
        for (int i = 0; i < NUM_CHARS; i++) {
            children[i] = nullptr;
        }
    }
};

Dictionary::Dictionary() {
    root = new Node;
    numWords = 0;
    Node();
}

Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;
    numWords = 0;
    copyOther(otherDict);
}

Dictionary::Dictionary(string filename) {
    root = new Node;
    numWords = 0;
    LoadDictionaryFile(filename);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if (this != &otherDict) {
        copyOther(otherDict);   // Copy contents of other into *this.
    }

    // return self
    return *this;
}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream infile;
    string content = "";
    infile.open(filename); //Inserts each word into the dictionary

    while(!infile.eof())
    {
        getline(infile,content);
        AddWord(content);
    }
    infile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw DictionaryError(filename + " failed to open");
    }
    SaveDictionaryHelper(root, "", outFile);
}

void Dictionary::AddWord(string word) {
    Node* node = root;
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        if (c < 'a' || c > 'z') {
            throw DictionaryError("Invalid character");
        }
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }
    node->IsWord = true;
    numWords++;
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);
    // Rebuild root and reset number of words
    root = new Node;
    numWords = 0;
}

bool Dictionary::IsWord(string word) {
    Node* node = root;
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        if (c < 'a' || c > 'z') {
            throw DictionaryError("Invalid character");
        }
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return false;
        }
        node = node->children[index];
    }
    return node->IsWord;
}

bool Dictionary::IsPrefix(string word) {
    Node* node = root;
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        if (c < 'a' || c > 'z') {
            throw DictionaryError("Invalid character");
        }
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return false;
        }
        node = node->children[index];
    }
    return true;
    //return (temp != nullptr && temp->IsPrefix == true);
}

int Dictionary::WordCount() {
    return numWords;
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();

    // copy over the number of words from otherDict
    numWords = otherDict.numWords;

    // recursively copy the tree
    copyHelper(root, otherDict.root);

    return;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if (thisTree == nullptr){
        return;
    }

    destroyHelper(thisTree->left);
    destroyHelper(thisTree->right);
    delete thisTree;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->IsWord = otherTree->IsWord;

    for (int i = 0; i < NUM_CHARS; i++) {
        copyHelper(thisTree->children[i], otherTree->children[i]);
    }
}


void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr) {  // base case: reached a null node
        return;
    }

    if (curr->IsWord) {
        outFile << currPrefix << endl;
    }

    for (int i = 0; i < NUM_CHARS; ++i) {
        char letter = 'a' + i;
        string next_prefix = currPrefix + letter;
        SaveDictionaryHelper(curr->children[i], next_prefix, outFile);
    }
}