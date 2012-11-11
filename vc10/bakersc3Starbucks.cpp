#include "bakersc3Starbucks.h"

bakersc3Starbucks::bakersc3Starbucks(){
	num = 0;
}

void bakersc3Starbucks::build(Entry*c, int n){
	num = n;
	arr = new Entry[num];
	for(int i = 0; i < num; i++){
		arr[i] = c[i];
	}
}

//This was going the be the build method I used for the tree.
/*void bakersc3Starbucks::build(Entry* c, int n){
	int m = n;
	Entry* arr = new Entry[m];
	for(int i = 0; i < n; i++){
		(arr + i)->identifier = (c + i)->identifier;
		(arr + i)->x = (c + i)->x;
		(arr + i)->y = (c + i)->y;
	}
		
	//Tree::tree = new Tree();
	//Tree::tree->root = Tree::treeBuilder(arr, m);
}*/

//I keep getting unresolved external errors on this method, and I'm
// not really certain why. I left the code here to see if I could get 
// any feedback on it, because I feel like it's really close to working.
/*Node* Tree::treeBuilder(Entry* arr, int n){
	Node* root = new Node();

	//catch potential errors and easy cases
	if(n == 0 || arr == NULL)
		return NULL;
	if(n == 1)
		return &Node(arr + 1);

	else if ((n % 2) == 0){
		for(int i = 0; i < n; i++){
			Node* node = new Node(arr + i);
			insertX((arr + i), root);
		}
		root->data = (arr + (n/2));
	}
	else{
		for(int i = 0; i < n; i++){
			Node* node = new Node(arr + i);
			insertY((arr + i), root);
		}
		root->data = (arr + ((n-1)/2));
	}
	treeBuilder(root->left->data, n/2);
	treeBuilder(root->right->data, (n-1)/2);

	return root;
}*/

/*Entry* bakersc3Starbucks::getNearest(double x, double y){
	return nearest(x, y, arr, this->num);
}*/

double bakersc3Starbucks::getDistance(double x, double x2, double y, double y2){
	return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2)));
}

Entry* bakersc3Starbucks::getNearest(double x, double y){
	Entry* temp = new Entry();
	Entry nearest = arr[0];
	double shortDis = getDistance(arr[0].x, x, arr[0].y, y);
	for(int i = 1; i < num; i++){
		double tempDis = getDistance(arr[i].x, x, arr[i].y, y);
		if(tempDis < shortDis){
			nearest = arr[i];
			shortDis = tempDis;
		}
	}
	*temp = nearest;
	return temp;
}

//The brute force version to find the nearest neighbor, since
// my tree isn't working right for some reason.
/*Entry* nearest(double x, double y, Entry* arr1, int n){
	Entry* near = arr[1];
	for(int i = 0; i < n; i++){
		if(((arr[i].x - x)*(arr[i].x - x) + (arr[i].y - y)*(arr[i].y - y)) <
			((near->x - x)*(near->x - x) + (near->y - y)*(near->y - y))){
			near = &arr[i];
		}
	}
	return near;
}*/

Entry* chooseMid(Entry* stores, int n){
	if((n % 2) != 0)
		return (stores + (n/2));
	else
		return (stores + (n-1)/2);
}

Node* insertX(Node* toAdd, Node* root){
	//Checks if the x values are the same.
	if(abs(toAdd->data->x - root->data->x) <= 0.00001)
	{
		//If both the x and y values are the same, it's the same store.
		// We don't need stores in the tree twice, so return NULL.
		if(abs(toAdd->data->y - root->data->y) <= 0.00001)
			return NULL;
		//Checks the y values next, and puts the entry on the
		// left if its y is smaller...
		else if(toAdd->data->y < root->data->y)
			root->left = insertX(toAdd, root->left);
		// or on the right if its y is bigger.
		else
			root->right = insertX(toAdd, root->right);
	}
	//If the x values are different, puts the entries with x values smaller 
	// than the root's x value on the left...
	if(toAdd->data->x < root->data->x)
		root->left = insertX(toAdd, root->left);
	// and the ones with x values larger than the root's x value
	// on the right.
	else
		root->right = insertX(toAdd, root->right);

	return root;
}

Node* insertY(Node* toAdd, Node* root){
	//Checks if the y values are the same.
	if(abs(toAdd->data->y - root->data->y) <= 0.00001)
	{
		//If both the x and y values are the same, it's the same store.
		// We don't need stores in the tree twice, so return NULL.
		if(abs(toAdd->data->x - root->data->x) <= 0.00001)
			return NULL;
		//Checks the x values next, and puts the entry on the
		// left if its x is smaller...
		else if(toAdd->data->x < root->data->x)
			root->left = insertY(toAdd, root->left);
		// or on the right if its x is bigger.
		else
			root->right = insertY(toAdd, root->right);
	}
	//If the y values are different, puts the entries with y values smaller 
	// than the root's y value on the left...
	if(toAdd->data->y < root->data->y)
		root->left = insertY(toAdd, root->left);
	// and the ones with y values larger than the root's y value
	// on the right.
	else
		root->right = insertY(toAdd, root->right);

	return root;
}