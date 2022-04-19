#ifndef MERKETREE
#define MERKETREE

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>
#include <ctime>
#include <openssl/sha.h>

using namespace std;
typedef unsigned char byte;
string strResult;

string sha256(const string str);

struct Node
{
	int blockID;
	string value, hashValue;
	Node *left, *right, *parent;
};

string sha256(const string str) {
		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256_CTX sha256;
		SHA256_Init(&sha256);
		SHA256_Update(&sha256, str.c_str(), str.size());
		SHA256_Final(hash, &sha256);
		stringstream ss;
		for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			ss << hex << setw(2) << setfill('0') << (int)hash[i];
		}
		return ss.str();
	}

class MerkleTree
{
	Node* root;
	int blockSize, blockNo, levels;

	int HASHSIZE;

public:
	MerkleTree(int bSize) : blockSize(bSize) {
		levels = 0;
		blockNo = -1;
		HASHSIZE = 2 * SHA256_DIGEST_LENGTH;
	}

	MerkleTree() {

	}

	int getBlockNo() {
    	return blockNo;
	}

	bool Build(const char* fileName) {
		ifstream inFile(fileName);
		if (!inFile.good())
			return false;

		vector<Node*>listChild, listParent;
		Node *leftN = NULL, *rightN = NULL;
		const int blockSize_1 = blockSize + 1;
		char buffer[21];
		buffer[blockSize] = '\0';
		while (!inFile.eof()) {
			inFile.read(buffer, blockSize);
			if (!inFile.gcount())
				continue;
			if (inFile.gcount() < blockSize)
				for (int i = inFile.gcount(); i < blockSize; i++)
					buffer[i] = 'E';
			Node* n = new Node;
			n->value = buffer;
			n->hashValue = sha256(buffer);
			n->blockID = ++blockNo;
			n->left = n->right = n->parent = NULL;
			listChild.push_back(n);
		}

		do {
			levels++;
		}
		while (pow((double) 2, levels) <= blockNo);

		do {
			std::vector<Node*>::iterator iterP = listParent.begin();
			std::vector<Node*>::iterator doneP = listParent.end();
			while (iterP != doneP)
				listChild.push_back(*iterP++);
			listParent.clear();

			std::vector<Node*>::iterator iter = listChild.begin();
			std::vector<Node*>::iterator done = listChild.end();
			leftN = rightN = NULL;
			while (iter != done) {
				if (!leftN)
					leftN = *iter++;
				else {
					rightN = *iter++;
					Node *parentN = new Node;
					parentN->value = leftN->value;
					parentN->hashValue = sha256
						(leftN->hashValue + rightN->hashValue);
					parentN->left = leftN;
					parentN->right = rightN;
					parentN->parent = NULL;
					parentN->blockID = -1;
					listParent.push_back(parentN);
					leftN->parent = rightN->parent = parentN;
					leftN = rightN = NULL;
				}
			}
				
			//будуємо новий NULL node
			if (leftN) {
				rightN = new Node;
				rightN->hashValue = "";
				rightN->blockID = -1;
				rightN->left = rightN->right = NULL;

				Node *parentN = new Node;
				parentN->value = leftN->value;
				parentN->hashValue = sha256
					(leftN->hashValue + rightN->hashValue);
				parentN->left = leftN;
				parentN->right = rightN;
				parentN->parent = NULL;
				parentN->blockID = -1;
				listParent.push_back(parentN);
				leftN->parent = rightN->parent = parentN;
				leftN = rightN = NULL;
			}

			listChild.clear();
		}
		while (listParent.size() > 1);

		root = listParent[0];
		return true;
	}

	void UpdateHash(Node* leftN) {
		Node *parentN = leftN->parent, *rightN = NULL;
		while (parentN) {
			if (parentN->left == leftN)
				rightN = parentN->right;
			else {
				rightN = leftN;
				leftN = parentN->left;
			}

			parentN->hashValue = sha256(leftN->hashValue + rightN->hashValue);
			leftN = parentN;
			parentN = parentN->parent;
		}
	}

	// додаємо блок
	bool Append(string strBlock) {
		if (!strBlock.length()) {
			return false;
		}

		blockNo++;
		Node *parentN = NULL, *leftN = NULL, *rightN = NULL;
		if (blockNo == pow((double) 2, levels)) {
			parentN = new Node;
			parentN->value = parentN->hashValue = "";
			parentN->blockID = -1;
			parentN->left = root;
			parentN->right = parentN->parent = NULL;
			root->parent = parentN;
			root = parentN;

			parentN = new Node;
			parentN->value = parentN->hashValue = "";
			parentN->blockID = -1;
			parentN->left = parentN->right = NULL;
			parentN->parent = root;
			root->right = parentN;

			for (int i = 0; i < levels; i++) {
				leftN = new Node;
				leftN->value = "";
				leftN->hashValue = sha256("NULL");
				leftN->blockID = -1;
				leftN->left = leftN->right = NULL;

				rightN = new Node;
				rightN->blockID = -1;
				rightN->value = "";
				rightN->hashValue = sha256("NULL");
				rightN->left = rightN->right = NULL;

				parentN->left = leftN;
				parentN->right = rightN;
				leftN->parent = rightN->parent = parentN;
				parentN = leftN;
			}

			leftN->blockID = blockNo;
			leftN->hashValue = sha256(strBlock);
			levels++;
		}
		else {
			parentN = root;
			int tempN = blockNo;
			if (blockNo % 2) {
				for (int i = levels - 1; i >= 0; i--) {
					if (tempN < pow((double) 2, i)) 
						parentN = parentN->left;
					else {
						tempN -= pow((double) 2, i);
						parentN = parentN->right;
					}
				}

				leftN = parentN;
				leftN->blockID = blockNo;
				leftN->hashValue = sha256(strBlock);
			}
			else {
				int i = levels;
				for (; i >= 0; i--) {
					if (tempN < pow((double) 2, i - 1)) 
						if (parentN->left)
							parentN = parentN->left;
						else
							break;
					else {
						tempN -= pow((double) 2, i - 1);
						if (parentN->right)
							parentN = parentN->right;
						else
							break;
					}
				}

				while (i > 0) {
					leftN = new Node;
					leftN->blockID = -1;
					leftN->value = leftN->hashValue = "";
					leftN->left = leftN->right = NULL;

					rightN = new Node;
					rightN->blockID = -1;
					rightN->value = "";
					rightN->hashValue = sha256("NULL");
					rightN->left = rightN->right = NULL;

					parentN->left = leftN;
					parentN->right = rightN;
					leftN->parent = rightN->parent = parentN;
					parentN = leftN;
					i--;
				}

				leftN->blockID = blockNo;
				leftN->hashValue = sha256(strBlock);
			}
		}

		//апгрейд дерева знизу вгору
		UpdateHash(leftN);
		return false;
	}

	string ReadBlock(int n) {
		if (n > blockNo) {
			return NULL;
		}

		int tempN = n;
		Node* tree = root;
		for (int i = levels; i >= 0; i--) {
			if (tempN < pow((double) 2, i - 1))
			{
				if (tree->left)
					tree = tree->left;
				else {
					return tree->value;
				}
			}
			else {
				tempN -= pow((double) 2, i - 1);
				if (tree->right)
					tree = tree->right;
				else {
					return tree->value;
				}
			}
		}

		return false;
	}

	string ProveBlock(int n) {
		string proof("");
		if (n > blockNo) {
			return proof;
		}

		int tempN = n;
		Node* tree = root;
		for (int i = levels; i >= 0; i--) {
			if (tempN < pow((double) 2, i - 1)) {
				if (tree->left) {
					tree = tree->left;
				}
			} else {
				tempN -= pow((double) 2, i - 1);
				if (tree->right)
					tree = tree->right;
		}
		}

		// підготовка перевірки
		bool bFirst = true;
		Node *leftN = tree, *parentN = leftN->parent, *rightN = NULL;
		while (parentN) {
			if (parentN->left == leftN) {
				rightN = parentN->right;
				if (bFirst) {
					proof += " L:";
					proof += leftN->value;
					proof += "; hash: ";
					proof += leftN->hashValue;
					bFirst = false;
				}

				proof += " R:";
				proof += rightN->hashValue;
			}
			else {
				rightN = leftN;
				leftN = parentN->left;
				if (bFirst) {
					proof += " R:";
					proof += rightN->value;
					proof += "; hash: ";
					proof += rightN->hashValue;
					bFirst = false;
				}

				proof += " L:";
				proof += leftN->hashValue;
			}

			leftN = parentN;
			parentN = parentN->parent;
		}

		return proof;
	}
};


#endif
