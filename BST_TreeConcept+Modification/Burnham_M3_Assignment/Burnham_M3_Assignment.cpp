// Burnham_M3_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*Utilizing geeks for geeks and tutorialspoint for coding assistance with this project https://www.tutorialspoint.com/binary-tree-with-array-implementation-in-cplusplus 
and https://www.geeksforgeeks.org/binary-tree-array-implementation/ and https://www.techiedelight.com/deletion-from-bst/ */
#include <iostream>
#include <string>

using namespace std;

string tree[10];
struct Node
{
	string data;
	Node* left = nullptr, * right = nullptr;

	Node() {}
	Node(string data) : data(data) {}
};
 
void inorder(Node* root)
{
	if (root == nullptr) {
		return;
	}

	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

Node* getMinimumKey(Node* curr)
{
	while (curr->left != nullptr) {
		curr = curr->left;
	}
	return curr;
}
 
Node* insert(Node* root, string key)
{
	// if the root is null, create a new node and return it
	if (root == nullptr) {
		return new Node(key);
	}

	// if the given key is less than the root node, recur for the left subtree
	if (key < root->data) {
		root->left = insert(root->left, key);
	}

	// if the given key is more than the root node, recur for the right subtree
	else {
		root->right = insert(root->right, key);
	}

	return root;
} 

void searchKey(Node*& curr, string key, Node*& parent)
{
	 
	while (curr != nullptr && curr->data != key)
	{
		// update the parent to the current node
		parent = curr;

		// if the given key is less than the current node, go to the left subtree;
		// otherwise, go to the right subtree
		if (key < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
}

int root(string key) {
	if (tree[0] != "\0")
	{
		cout << "The tree already has a root.";
	}
	else
	{
		tree[0] = key;
	}
	
	return 0;
}

int set_left(string key, int parent) {
	if (tree[parent] == "\0")
	{
		cout << "\nCan't set child at "
			<< (parent * 2) + 1
			<< " , no parent found";
	}
	else
	{
		tree[(parent * 2) + 1] = key;
	}
		return 0;
}

int set_right(string key, int parent) {
	if (tree[parent] == "\0")
	{
		cout << "\nCan't set child at "
			<< (parent * 2) + 2
			<< " , no parent found";
	}
	else
	{
		tree[(parent * 2) + 2] = key;
	}
		return 0;
}

void deleteNode(Node*& root, string key)
{
	// pointer to store the parent of the current node
	Node* parent = nullptr;

	// start with the root node
	Node* curr = root;

	// search key in the BST and set its parent pointer
	searchKey(curr, key, parent);

	// return if the key is not found in the tree
	if (curr == nullptr) {
		return;
	}

	// Case 1: node to be deleted has no children, i.e., it is a leaf node
	if (curr->left == nullptr && curr->right == nullptr)
	{
		// if the node to be deleted is not a root node, then set its
		// parent left/right child to null
		if (curr != root)
		{
			if (parent->left == curr) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		// if the tree has only a root node, set it to null
		else {
			root = nullptr;
		}
		 
	}

	// Case 2: node to be deleted has two children
	else if (curr->left && curr->right)
	{
		// find its inorder successor node
		Node* successor = getMinimumKey(curr->right);

		// store successor value
		string val = successor->data;

		// recursively delete the successor. Note that the successor
		// will have at most one child (right child)
		deleteNode(root, successor->data);

		// copy value of the successor to the current node
		curr->data = val;
	}

	// Case 3: node to be deleted has only one child
	else 
	{
		// choose a child node
		Node* child = (curr->left) ? curr->left : curr->right;

		// if the node to be deleted is not a root node, set its parent
		// to its child
		if (curr != root)
		{
			if (curr == parent->left) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}

		// if the node to be deleted is a root node, then set the root to the child
		else {
			root = child;
		}

		// deallocate the memory
		free(curr);
	}
}

int print_tree() {
	cout << "\n";
	for (int x = 0; x < 10; x++) 
	{
		if (tree[x] != "\0")
		{
			cout << tree[x];
			cout << "\n";
		}		
		else
		{
			cout << "-";
		}
	}
	return 0;
}

int main()
{
	string keys[] = { "Jose", "Deepaku", "Quiang", "Anton", "Elisa", "Mia", "Zoe" };
	/* Temporarily commented out as doing two seperate array version broke the code
	root("Jose. ");
	set_left("Deepak. ", 0);
	set_right("Qiang. ", 0);
	set_left("Anton. ", 1);
	set_right("Elisa. ", 1);
	set_left("Mia. ", 2);
	set_right("Zoe. ", 2);
	cout << "Printing Array Tree: \n";
	print_tree();
	*/

	
	Node* y = nullptr;
	for (string key : keys)
	{
		y = insert(y, key);
	}
	insert(y, "Doug");
	deleteNode(y, "Mia");
	deleteNode(y, "Deepak");
	insert(y, "Samara");
	

	cout << "\nPrinting bst tree after adding and deleting nodes: \n";
	inorder(y);

	/*commenting out this section of code so nothing goes awry*/
	
	root("Qiang. ");
	set_left("Jose. ", 0);
	set_right("Zoe. ", 0);
	set_left("Deepak. ", 1);
	set_right("Mia. ", 1);
	set_left("Anton. ", 3);
	set_right("Elisa. ", 3);
	
	cout << "Printing Array Tree: \n";
	print_tree();
	
	string key2[] = { "Quiang", "Jose", "Zoe", "Deepak", "Mia", "Anton", "Elisa"};
	Node* x = nullptr;
	for (string key : key2)
	{
		x = insert(x, key);
	}
	insert(x, "Doug");
	deleteNode(x, "Mia");
	deleteNode(x, "Deepak");
	insert(x, "Samara");


	cout << "\nPrinting bst tree after adding and deleting nodes: \n";
	inorder(x);


	return 0;
}