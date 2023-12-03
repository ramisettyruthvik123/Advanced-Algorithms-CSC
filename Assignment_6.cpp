#include <iostream>
#include <queue>
#include <vector>

// Definition for a binary tree node.
struct Node {
    char inputString;
    unsigned repeatFrequency;
    Node *leftNode, *rightNode;

    // Constructor
    Node(char inputData, unsigned repetition, Node* leftN = nullptr, Node* rightN = nullptr)
        : inputString(inputData), repeatFrequency(repetition), leftNode(leftN), rightNode(rightN) {}
};

struct Compare {
    bool operator()(Node* leftN, Node* rightN) {
        return (leftN->repeatFrequency > rightN->repeatFrequency);
    }
};

// Function to print the Huffman code for each character.
void printOutputCodes(Node* rootNode, std::string strValue) {
    if (!rootNode)
        return;

    if (rootNode->inputString != '$' && rootNode->inputString != '\0') // if the node is a leaf node
        std::cout << rootNode->inputString << ": " << strValue << "\n";

    // traverse the left subtree
    printOutputCodes(rootNode->leftNode, strValue + "0");
    // traverse the right subtree
    printOutputCodes(rootNode->rightNode, strValue + "1");
}

// Function to print the Huffman tree
void huffmanCoding(char dataInput[], int repeatFreq[], int length) {
    Node *leftSide, *rightSide, *topValue;
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;

    for (int i = 0; i < length; ++i)
        minHeap.push(new Node(dataInput[i], repeatFreq[i]));

    while (minHeap.size() != 1) {
        leftSide = minHeap.top();
        minHeap.pop();

        rightSide = minHeap.top();
        minHeap.pop();

        topValue = new Node('$', leftSide->repeatFrequency + rightSide->repeatFrequency, leftSide, rightSide);
        minHeap.push(topValue);
    }

    printOutputCodes(minHeap.top(), ""); // print the Huffman tree
}

int main() {
    int noOfCharacters;

    // Prompting the user to enter the length of the array
    std::cout << "Enter the length of the arrays: ";
    std::cin >> noOfCharacters;

    // Allocating the memory for the arrays
    char *arrValues = new char[noOfCharacters];
    int *repeatFreq = new int[noOfCharacters];

    // Prompting the user to enter the characters in the array
    std::cout << "Enter the characters: ";
    for (int i = 0; i < noOfCharacters; ++i)
        std::cin >> arrValues[i];

    // Prompting the user to enter the frequencies of the characters
    std::cout << "Enter the repeat frequencies: ";
    for (int i = 0; i < noOfCharacters; ++i)
        std::cin >> repeatFreq[i];

    // Calling the Huffman Coding function
    huffmanCoding(arrValues, repeatFreq, noOfCharacters);

    return 0;
}
