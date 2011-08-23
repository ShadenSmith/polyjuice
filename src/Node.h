#ifndef NODE_H
#define NODE_H

/*
	Structure to hold frequency, symbol, and tree information for our Huffman
	Encoding.
*/
struct Node
{
	/*
		Used for sorting in in the priority queue. Since the standard
		implementation of <priority_queue> is a max queue, reverse the
		comparison in order to create a minimum one.
	*/
	bool operator<(const Node &a) const
	{
		return (this->freq > a.freq);
	}

	// left and right children in the binary tree
	Node *left;
	Node *right;

	// ASCII character that this node presents. Will not be set if this node
	// is not a leaf.
	char symbol;

	// used for the priority queue in our Huffman Encoding
	float freq;

	bool leaf;
};
#endif
