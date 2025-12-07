#include <iostream>
#include <vector>
#include "Tree.h"
using namespace std;

Tree::Tree(int w, char c) {
    weight = w;
    this->c = c;
    left = NULL;
    right = NULL;
}

Tree::Tree(int w, Tree* t1, Tree* t2) {
    weight = w;
    left = t1;
    right = t2;
    c = '\0';  // Internal nodes do not hold a character
}

Tree::~Tree(){
    
}

int Tree::getWeight() const {
    return weight;
}

void Tree::printTree(vector<char>& bitString) const {
    if (left == NULL && right == nullptr) {
        // Leaf node
        for (char bit : bitString) {
            cout << bit;
        }
        cout << ": " << c << endl;
        return;
    }
    if (left != NULL) {
        bitString.push_back('0');
        left->printTree(bitString);
        bitString.pop_back();
    }
    if (right != NULL) {
        bitString.push_back('1');
        right->printTree(bitString);
        bitString.pop_back();
    }
}