
#include <string>
#include <fstream>
#include <map>
#include <queue>

#include "Huffman.h"

const std::string DEFAULT_FREQ = "default.freq";

Huffman::Huffman()
{
	// set default frequency file
	freqFile = DEFAULT_FREQ;
}

/*
	Store a non-default freq file in case the user wants to specify their own
*/
void Huffman::setFreqFile(std::string filename)
{
	freqFile = filename;
}

/*
	Read in the frequency file and populate our priority queue with leaves.
*/
void Huffman::readFreqFile()
{
	std::ifstream fin(freqFile.c_str());
	float currFreq;
	char currChar;
	
	std::vector<std::string> lines;
	std::string temp;
	// grab first line
	getline(fin, temp);
	lines.push_back(temp);
	// grab rest of file
	while(!fin.eof())
	{
		getline(fin, temp);
		lines.push_back(temp);
	}

	// Now iterate through each line of the file and generate leaves
	// Last line is done separately because it is blank and represents \n
	for(size_t i = 0; i < lines.size() - 1; i++)
	{
		// Grab character and frequence
		sscanf(lines[i].c_str(), "%c %f", &currChar, &currFreq);
		// Create node and push onto our priority queue
		pq.push(makeNode(NULL, NULL, currFreq, currChar, true));
	}

	// now do the same for \n
	sscanf(lines[lines.size() - 1].c_str(), "%f", &currFreq);
	pq.push(makeNode(NULL, NULL, currFreq, '\n', true));
}

/*
	Fill in data for a new node and return a copy
*/
Node Huffman::makeNode(Node *l, Node *r, float f, char sym, bool leaf)
{
	Node newNode;

	newNode.left = l;
	newNode.right = r;
	newNode.freq = f;
	newNode.symbol = sym;
	newNode.leaf = leaf;
	return newNode;
}
