#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <fstream>
#include "HuffmanCodes.h"
using namespace std;



string encode(string input) {
    vector<string> symb;
    vector<float> freq;
    vector<TreeNode*> trees;
    vector<string> codes;
    TreeNode* huffTree = nullptr;

    cout << "Input: " << input << endl;

    //Counts the number of occurences of a symbol
    for (int i = 0; i < input.size(); i++) {
        bool symbFound = false;
        for (int j = 0; j < symb.size(); j++) {
            if (input[i] == symb[j].at(0)) {
                freq[j] = freq[j] + 1;
                symbFound = true;
            }

        }
        //Adds new symbols when found in input
        if (!symbFound) {
            freq.push_back(0);
            string s(1, input[i]);
            symb.push_back(s);
            freq[freq.size() - 1] = freq[freq.size() - 1] + 1;
        }
    }
    //Changes number of a symbol to freqency of symbol in input
    for (int i = 0; i < freq.size(); i++) {
        freq[i] = freq[i] / input.size();
    }

    for (int i = 0; i < symb.size(); i++) {
        cout << symb[i] << ": " << freq[i] << endl;
    }

    //Creates a one node tree for each symbol
    for (int i = 0; i < symb.size(); i++) {
        TreeNode* tn = new TreeNode(freq[i], symb[i]);
        trees.push_back(tn);
    }

    TreeNode* leftChild = new TreeNode();
    TreeNode* rightChild = new TreeNode();
    int lAddress;
    int rAddress;
    //Loops through trees until one remains
    while (trees.size() > 1) {
        lAddress = -1;
        rAddress = -1;

        //Finds the two smallest frequencies, placing the smallest in the left child and 2nd smallest in right child
        for (int i = 0; i < trees.size(); i++) {
            if (trees[i]->getFreq() < rightChild->getFreq()) {
                if (trees[i]->getFreq() < leftChild->getFreq()) {
                    rightChild = leftChild;
                    rAddress = lAddress;
                    leftChild = trees[i];
                    lAddress = i;
                }
                else {
                    rightChild = trees[i];
                    rAddress = i;
                }
            }
        }

        cout << "L:" << leftChild->symbol << "(" << leftChild->freq << ") R:" << rightChild->symbol << "(" << rightChild->freq << ")" << endl;

        TreeNode* tn = new TreeNode(leftChild, rightChild);
        trees.push_back(tn);

        //Makes sure that the order the children trees are removed from the trees vector is correct
        if (lAddress < rAddress) {
            if (rAddress != -1) {
                trees.erase(trees.begin() + rAddress);
            }
            if (lAddress != -1) {
                trees.erase(trees.begin() + lAddress);
            }
        }
        else {
            if (lAddress != -1) {
                trees.erase(trees.begin() + lAddress);
            }
            if (rAddress != -1) {
                trees.erase(trees.begin() + rAddress);
            }
        }

        leftChild->setFreq(100);
        rightChild->setFreq(100);
    }


    huffTree = trees[0];
    //Searches the tree for each symbol and pushes the returned code into codes
    for (int i = 0; i < symb.size(); i++) {
        //The searchTree function returns the symbol and its code
        string s = huffTree->searchTree(huffTree, symb[i]).substr(1);
        reverse(s.begin(), s.end());
        codes.push_back(s);
    }
    for (int i = 0; i < symb.size(); i++) {
        cout << symb[i] << ":" << codes[i] << endl;
    }

    
    string returnVal = "";
    //Adds the decode key at the top of the file
    for (int i = 0; i < symb.size(); i++) {
        returnVal += symb[i] + ":" + codes[i] + ",";
    }
    //Encodes the input one character at a time
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < symb.size(); j++) {
            if (input[i] == symb[j].at(0)) {
                returnVal += codes[j];
            }
        }
    }
    return returnVal;

}

string encodePair(string input) {
    vector<string> symb;
    vector<float> freq;
    vector<TreeNode*> trees;
    vector<string> codes;
    TreeNode* huffTree = nullptr;

    //Adds a space to input of the size is odd
    if ((input.size() % 2) == 1) {
        input += " ";
    }

    //Counts the number of occurences of pairs of symbols
    for (int i = 1; i < input.size(); i += 2) {
        bool symbFound = false;
        for (int j = 0; j < symb.size(); j++) {
            if (input.substr(i - 1, 2) == symb[j]) {
                freq[j] = freq[j] + 1;
                symbFound = true;
            }
        }
        //Adds new symbols when found in input
        if (!symbFound) {
            freq.push_back(0);
            symb.push_back(input.substr(i - 1, 2));

            freq[freq.size() - 1] = freq[freq.size() - 1] + 1;
        }
    }

    //Changes number of a symbol to freqency of symbol in input
    for (int i = 0; i < freq.size(); i++) {
        freq[i] = freq[i] / freq.size();
    }

    //Creates a one node tree for each symbol
    for (int i = 0; i < symb.size(); i++) {
        TreeNode* tn = new TreeNode(freq[i], symb[i]);
        trees.push_back(tn);
    }

    int lAddress;
    int rAddress;
    //Loops through trees until one remains
    while (trees.size() > 1) {
        lAddress = -1;
        rAddress = -1;
        TreeNode* leftChild = new TreeNode();
        TreeNode* rightChild = new TreeNode();

        //Finds the two smallest frequencies, placing the smallest in the left child and 2nd smallest in right child
        for (int i = 0; i < trees.size(); i++) {
            if (trees[i]->getFreq() < rightChild->getFreq()) {
                if (trees[i]->getFreq() < leftChild->getFreq()) {
                    rightChild = leftChild;
                    rAddress = lAddress;
                    leftChild = trees[i];
                    lAddress = i;
                }
                else {
                    rightChild = trees[i];
                    rAddress = i;
                }
            }
        }

        TreeNode* tn = new TreeNode(leftChild, rightChild);
        trees.push_back(tn);

        //Makes sure that the order the children trees are removed from the trees vector is correct
        if (lAddress < rAddress) {
            if (rAddress != -1) {
                trees.erase(trees.begin() + rAddress);
            }
            if (lAddress != -1) {
                trees.erase(trees.begin() + lAddress);
            }
        }
        else {
            if (lAddress != -1) {
                trees.erase(trees.begin() + lAddress);
            }
            if (rAddress != -1) {
                trees.erase(trees.begin() + rAddress);
            }
        }

    }

    huffTree = trees[0];
    //Searches the tree for each symbol and pushes the returned code into codes
    for (int i = 0; i < symb.size(); i++) {
        //The searchTree function returns the symbol and its code
        //cout << huffTree->searchTree(huffTree, symb[i]).substr(2) << " ";
        string s = huffTree->searchTree(huffTree, symb[i]).substr(symb[i].size());
        reverse(s.begin(), s.end());
        codes.push_back(s);
        //cout << symb[i] << ":" << codes[i] << " ";
    }

    
    string returnVal = "";
    //Adds the decode key at the top of the file
    for (int i = 0; i < symb.size(); i++) {
        returnVal += symb[i] + ":" + codes[i] + ",";
    }
    //Encodes the input in pairs of characters
    for (int i = 1; i < input.size(); i += 2) {
        for (int j = 0; j < symb.size(); j++) {
            if (input.substr(i - 1, 2) == symb[j]) {
                returnVal += codes[j];
            }
        }
    }
    return returnVal;

}

string encodeAscii(string input) {
    string returnVal = "";
    for (int i = 0; i < input.size(); i++) {
        int dec = int(input[i]);
        bitset<7> bin(dec);
        returnVal += bin.to_string();
    }
    return returnVal;
}

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    return string((istreambuf_iterator<char>(input_file)),istreambuf_iterator<char>());
}

int main() {
    encode("abbacddd123qwabdc");
    /*string ip1 = readFileIntoString("input1.txt");
    string ip2 = readFileIntoString("input2.txt");
    string ip3 = readFileIntoString("input3.txt");    

    ofstream huff1;
    ofstream huffPair1;
    ofstream ascii1;
    huff1.open("huff1.txt");
    huffPair1.open("huffpair1.txt");
    ascii1.open("ascii1.txt");
    huff1 << encode(ip1);
    huffPair1 << encodePair(ip1);
    ascii1 << encodeAscii(ip1);

    ofstream huff2;
    ofstream huffPair2;
    ofstream ascii2;
    huff2.open("huff2.txt");
    huffPair2.open("huffpair2.txt");
    ascii2.open("ascii2.txt");
    huff2 << encode(ip2);
    huffPair2 << encodePair(ip2);
    ascii2 << encodeAscii(ip2);

    ofstream huff3;
    ofstream huffPair3;
    ofstream ascii3;
    huff3.open("huff3.txt");
    huffPair3.open("huffpair3.txt");
    ascii3.open("ascii3.txt");
    huff3 << encode(ip3);
    huffPair3 << encodePair(ip3);
    ascii3 << encodeAscii(ip3);*/
}