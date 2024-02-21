#pragma once
#include <vector>
#include <string>
using namespace std;

class TreeNode {
public:
	float freq;
	string symbol = "";
	TreeNode* lChild = nullptr;
	TreeNode* rChild = nullptr;

	TreeNode(TreeNode* lChildIn, TreeNode* rChildIn) {
		lChild = lChildIn;
		rChild = rChildIn;
		freq = lChildIn->getFreq() + rChildIn->getFreq();
	}

	TreeNode(float freqIn, string symbolIn) {
		freq = freqIn;
		symbol = symbolIn;
	}

	TreeNode() {
		freq = 100;
	}

	float getFreq() {
		return freq;
	}

	void setFreq(float freqIn) {
		freq = freqIn;
	}

	string searchTree(TreeNode* tn, string symb) {
		if (tn->symbol == "") {
			string l = searchTree(tn->lChild, symb);
			string r = searchTree(tn->rChild, symb);
			if (l != "") {
				return l + "0";
			}
			else if (r != "") {
				return r + "1";
			}
			else {
				return "";
			}
		}
		if (tn->symbol == symb) {
			return tn->symbol;
		}
		else {
			return "";
		}

	}

};