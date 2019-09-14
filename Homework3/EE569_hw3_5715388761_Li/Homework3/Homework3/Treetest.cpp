#include "Patterntree.h"
#include <stack>

using namespace std;

void main() {
	binaryTree<int> t;
	stack<int> s;
	s.push(1);
	s.push(0);
	s.push(1);
	s.push(0);

	BTNode<int> N(1);
	
	t.createBiTree(N, s);
}