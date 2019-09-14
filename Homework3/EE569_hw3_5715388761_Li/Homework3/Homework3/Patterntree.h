// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.1

#pragma once
#ifndef  CPP_PATTERNTREE_H
#define CPP_PATTERNTREE_H

#include <queue>

using namespace std;

class Bnode
{
public:
	int val;
	Bnode *left = NULL, *right = NULL;

	Bnode(int v) {
		val = v;
	}

};

class Tree
{
public:
	Bnode *create_tree(queue<int> s);
	void reconstruct(Bnode* b);
	bool compare(queue<int> q);
	Tree(Bnode* r);
	~Tree();

	Bnode *root;
};
#endif // ! CPP_PATTERNTREE_H
