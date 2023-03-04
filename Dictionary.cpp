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
    ofstream dictFile;
    dictFile.open(filename);
    if(!dictFile.is_open()){
        throw DictionaryError("failed to open");
    }
    // Notice we start with the empty string as the prefix.
    SaveDictionaryHelper(root, "", dictFile);
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
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;
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
    copyHelper(thisTree->left, otherTree->left);
    copyHelper(thisTree->right, otherTree->right);
}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr)
        return;

    // If the path to this node is a number, then we write it
    // to the file.
    if (curr->IsWord) {
        outFile << currPrefix << endl;
    }

    // Notice how we add a digit to the currPrefix
    SaveDictionaryHelper(curr->left, currPrefix+"left", outFile);
    SaveDictionaryHelper(curr->right, currPrefix+"right", outFile);
}
