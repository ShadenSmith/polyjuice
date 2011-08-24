
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <map>

#include "Node.h"

class Huffman
{
	public:
		Huffman();
		~Huffman();
	
		// Set a new frequency file for our encoding
		void setFreqFile(std::string filename);
		
		// Read frequencies
		void readFreqFile();

	protected:
		// root of binary tree
		Node *root;

		// priority queue of nodes for our tree
		std::priority_queue<Node*> pq;

		// A map of each character and their respective bit string.
		std::map<char, std::string> encodingHash;

		// name of frequency file
		std::string freqFile;

		// actual encoded string
		std::string encoding;

		Node* makeNode(Node *l, Node *r, float f, char sym, bool leaf);

		// To be called by readFreqFile(). Once leaf information is read, form
		// tree structure within pq.
		void formTree();

		// Called by formTree.
		// traverse our tree and fill encoding information
		void fillEncodingHash(Node *start, std::string path);

		// deallocate tree memory
		void deleteTree(Node *curr);
		
};

#endif
