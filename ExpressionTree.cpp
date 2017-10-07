#include "ExpressionTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char newDataItem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr) { 

	dataItem = newDataItem;
	left = leftPtr;
	right = rightPtr;
}

template <typename DataType>
ExprTree<DataType>::ExprTree() : root(NULL) {
}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree<DataType>& other) {


}

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>& other) {


}

template <typename DataType>
ExprTree<DataType>::~ExprTree() {

	clear();
}

template <typename DataType>
void ExprTree<DataType>::build() {

	char newDataItem;

	std::cin >> newDataItem;

	root = new ExprTreeNode(newDataItem, NULL, NULL);

	buildHelper(root->left);

	buildHelper(root->right);
}

template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& node) {

	char newDataItem;

	std::cin >> newDataItem;

	node = new ExprTreeNode(newDataItem, NULL, NULL);

	if(newDataItem <= '9' && newDataItem >= '0') return;

	else {

		buildHelper(node->left);
		buildHelper(node->right);
	}
}

template <typename DataType>
void ExprTree<DataType>::expression() const {


}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw(logic_error) {

	if(root->dataItem <= '9' && root->dataItem >= '0') return root->dataItem;

	DataType leftData, rightData;

	leftData = (DataType)(evaluateHelper(root->left) - '0');
	rightData = (DataType)(evaluateHelper(root->right) - '0');

	std::cout << leftData << std::endl;
	std::cout << rightData << std::endl;
	std::cout << root->dataItem << std::endl;

	switch(root->dataItem) {

		case '+': return (leftData + rightData);
		case '-': return (leftData - rightData);
		case '*': return (leftData * rightData);
		case '/': return (leftData / rightData);
	}

	throw (logic_error("evaluate() Not valid operator."));
}

template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(ExprTreeNode* node) const {

	if(node->dataItem <= '9' && node->dataItem >= '0') return node->dataItem;

	DataType leftData, rightData;

	leftData = (DataType)(evaluateHelper(node->left) - '0');
	rightData = (DataType)(evaluateHelper(node->right) - '0');

	std::cout << leftData << std::endl;
	std::cout << rightData << std::endl;
	std::cout << node->dataItem << std::endl;

	switch(node->dataItem) {

		case '+': return (leftData + rightData);
		case '-': return (leftData - rightData);
		case '*': return (leftData * rightData);
		case '/': return (leftData / rightData);
	}

	throw (logic_error("evaluate() Not valid operator."));
}

template <typename DataType>
void ExprTree<DataType>::clear() {

	if(isEmpty()) return;

	clearHelper(root->left);
	clearHelper(root->right);

	delete [] root;

	root = NULL;
}

template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode* node) {

	if(node->left == NULL && node->right == NULL) {

		delete [] node;
		return;
	}
	else {

		clearHelper(node->left);
		clearHelper(node->right);
	}
}
template <typename DataType>
void ExprTree<DataType>::showStructure() const {

    if (isEmpty()) cout << "Empty tree" << endl;

    else {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != NULL )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const {

	if(root == NULL) return true;
	else return false;
}
