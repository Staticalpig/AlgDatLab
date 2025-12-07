#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include "TreeWrapper.h"

//declare functions
std::unordered_map<char, int> createLetterFreqTable(const std::string& input);
void printLetterFreqTable(const std::unordered_map<char, int>& freqTable);
TreeWrapper buildTrees(const std::unordered_map<char, int>& freqTable);


int main(){

    std::string input = "aabbbbccccdddddeeeefff";

    std::unordered_map<char, int> freqTable = createLetterFreqTable(input);

    printLetterFreqTable(freqTable);
    TreeWrapper huffmanTree = buildTrees(freqTable);

    //print the result
    std::vector<char> bitString;
    huffmanTree.tree->printTree(bitString);

    return 0;
}

std::unordered_map<char, int> createLetterFreqTable(const std::string& input){
    std::unordered_map<char, int> freqTable;
    for(char c : input){
        freqTable[c]++;
    }
    return freqTable;
}

void printLetterFreqTable(const std::unordered_map<char, int>& freqTable){
    std::cout << "Character Frequencies:\n";
    for(const auto& pair : freqTable){
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

TreeWrapper buildTrees(const std::unordered_map<char, int>& freqTable){
    std::priority_queue<TreeWrapper> pq;

    //Create the base trees for each character and add to the priority queue
    for(const auto& pair : freqTable){
        Tree* newTree = new Tree(pair.second, pair.first);
        pq.push(TreeWrapper(newTree));
    }

    //Now to iterate through the queue and build the trees until there is only one tree left
    while(pq.size() > 1){
        //First, take the two trees with the lowest weights
        TreeWrapper t1 = pq.top();
        pq.pop();
        TreeWrapper t2 = pq.top();
        pq.pop();

        //now we need to create a tree to combine these two
        int weight = t1.tree->getWeight() + t2.tree->getWeight();
        Tree* combinedTree = new Tree(weight, t1.tree, t2.tree); //new tree with weight and the two trees as children
        pq.push(TreeWrapper(combinedTree)); //new tree added to the priority queue
    }
    //once the the loop is done, only one tree shoud remain, so return that
    return pq.top();
}