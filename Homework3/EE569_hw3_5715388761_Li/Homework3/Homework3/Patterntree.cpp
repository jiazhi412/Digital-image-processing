// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#include "Patterntree.h"
#include <vector>

using namespace std;

Bnode* Tree::create_tree(queue<int> q) {
	if (q.empty()){
		return NULL;
	}
	else {	
		Bnode* node = root;		
		int data = q.front();
		q.pop();

		if (data == 1 && node->left == NULL) {
			node->left = new Bnode(data);
			Tree temp(node->left);
			node->left = temp.create_tree(q);
		}
		else if (data == 1 && node->left != NULL) {
			Tree temp(node->left);
			node->left = temp.create_tree(q);
		}
		else if (data == 0 && node->right == NULL) {
			node->right = new Bnode(data);
			Tree temp(node->right);			
			node->right = temp.create_tree(q);
		}
		else if (data == 0 && node->right != NULL) {
			Tree temp(node->right);
			node->right = temp.create_tree(q);
		}
		else if (data == 5 && node->right == NULL && node->left == NULL) {			
			node->right = new Bnode(0);
			Tree temp_right(node->right);
			node->right = temp_right.create_tree(q);

			node->left = new Bnode(1);
			Tree temp_left(node->left);
			node->left = temp_left.create_tree(q);
		}		
		else if (data == 5 && node->right != NULL && node->left == NULL) {			
			Tree temp_right(node->right);
			node->right = temp_right.create_tree(q);

			node->left = new Bnode(1);
			Tree temp_left(node->left);
			node->left = temp_left.create_tree(q);
		}
		else if (data == 5 && node->right == NULL && node->left != NULL) {
			node->right = new Bnode(0);
			Tree temp_right(node->right);
			node->right = temp_right.create_tree(q);
			
			Tree temp_left(node->left);
			node->left = temp_left.create_tree(q);
		}
		else if (data == 5 && node->right != NULL && node->left != NULL) {			
			Tree temp_right(node->right);
			node->right = temp_right.create_tree(q);
			
			Tree temp_left(node->left);
			node->left = temp_left.create_tree(q);
		}
		return node;
	}	
}

Tree::Tree(Bnode* r) {
	root = r;
}

Tree::~Tree() {

}

void Tree::reconstruct(Bnode* b) {
	root = b;
}

bool Tree::compare(queue<int> q) {
	// Method A loop
	Bnode* node = root;
	while (!q.empty()) {
		int data = q.front();
		q.pop();				
		if (data == 1 && node->left == NULL) {
			return false;
		}
		else if (data == 1 && node->left != NULL) {
			node = node->left;			
		}
		else if (data == 0 && node->right == NULL) {
			return false;
		}
		else if (data == 0 && node->right != NULL) {
			node = node->right;
		}		
	}
	return true;

	// Method B recursion
	/*if (q.empty()) {
		return true;
	}	
	else {
		Bnode* node = root;

		int data = q.front();
		q.pop();

		if (data == 1 && node->left == NULL) {
			return false;
		}
		else if (data == 1 && node->left != NULL) {
			Tree temp(node->left);
			return temp.compare(q);
		}
		else if (data == 0 && node->right == NULL) {
			return false;
		}
		else if (data == 0 && node->right != NULL) {
			Tree temp(node->right);
			return temp.compare(q);
		}
	}*/
}