#include "Starbucks.h"

class bakersc3Starbucks : public Starbucks {
public:
	virtual void build(Entry* c, int n);
    virtual Entry* getNearest(double x, double y);

	bakersc3Starbucks();
	~bakersc3Starbucks();
	int num;
	Entry* arr;
};

class Node{
public:
	Node();
	Node(Entry* entry);

	Entry* data;
	Node* left;
	Node* right;
};

class Tree{
public: 
	Tree();
	static Tree* tree;
	Node* root;
	static Node* treeBuilder(Entry* arr, int n);
};

Entry* chooseMid(Entry* stores, int n);
Node* insertX(Entry* toAdd, Node* root);
Node* insertY(Entry* toAdd, Node* root);

Entry* nearest(double x, double y, Entry* arr, int n);