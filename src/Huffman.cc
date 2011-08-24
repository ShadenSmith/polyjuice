
#include <string>
#include <fstream>
#include <map>
#include <queue>

#include "Huffman.h"

const std::string DEFAULT_FREQ = "default.freq";

Huffman::Huffman()
{
	root = NULL;

	// set default frequency file
	freqFile = DEFAULT_FREQ;
}

Huffman::~Huffman()
{
	deleteTree(root);
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
	// In case the file has already been read, clear memory
	while(!pq.empty())
	{
		pq.pop();
	}

	std::ifstream fin(freqFile.c_str());
	float currFreq;
	char currChar;
	
	// store file in a vector of strings
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

	// now form our tree
	formTree();
}

void Huffman::formTree()
{
	Node *parent;
	// repeatedly grab the top two elements off of pq and form a parent node.
	// once created, push that back onto pq until a root is formed
	while(pq.size() > 1)
	{
		// grab top two elements
		Node *j = pq.top();
		pq.pop();
		Node *k = pq.top();
		pq.pop();

		// create a parent node whose frequency is the sum of its children
		parent = makeNode(j, k, j->freq + k->freq, '~', false);
		// push parent back onto pq
		pq.push(parent);
	}

	// now store root
	root = parent;

	// fill our encoding hash
	fillEncodingHash(root, "");
}

/*
	After our root has been found, traverse the tree and fill in the encoded
	forms of each leaf in our hash.

	Performs a recursive depth-first search on our tree and generates path as 
	it goes.
*/
void Huffman::fillEncodingHash(Node *start, std::string path)
{
	// If we've reached a leaf store and return
	if(start->leaf)
	{
		encodingHash[start->symbol] = path;
		printf("%c: %s\n", start->symbol, path.c_str());
		return;
	}

	// Huffman encoding generates a full binary tree. Always go left and right
	fillEncodingHash(start->left, path + '0');
	fillEncodingHash(start->right, path + '1');
}

/*
	Fill in data for a new node and return a copy
*/
Node* Huffman::makeNode(Node *l, Node *r, float f, char sym, bool leaf)
{
	Node *newNode = new Node;

	newNode->left = l;
	newNode->right = r;
	newNode->freq = f;
	newNode->symbol = sym;
	newNode->leaf = leaf;
	return newNode;
}

/*
	Deallocate all memory in tree
*/
void Huffman::deleteTree(Node *curr)
{
	if(curr->left != NULL)
		deleteTree(curr->left);
	if(curr->right != NULL)
		deleteTree(curr->right);

	delete curr;
}
