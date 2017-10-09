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
ExprTree<DataType>::ExprTree(const ExprTree<DataType>& other) : root(NULL) {

	(*this) = other;
}

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>& other) {

	if(this == &other) return (*this);

	clear();

	assignementHelper(root, other.root);

	return (*this);
}

template <typename DataType>
void ExprTree<DataType>::assignementHelper(ExprTreeNode*& node, ExprTreeNode* otherNode) {

	node = new ExprTreeNode(otherNode->dataItem, NULL, NULL);

	if(isDigit(otherNode->dataItem)) return;

	else {

		assignementHelper(node->left, otherNode->left);
		assignementHelper(node->right, otherNode->right);
	}
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

	if(isDigit(newDataItem)) return;

	else {

		buildHelper(node->left);
		buildHelper(node->right);
	}
}

template <typename DataType>
void ExprTree<DataType>::expression() const {

	if(isDigit(root->dataItem)) {

		std::cout << root->dataItem << std::endl;
		return;
	}

	std::cout << expressionHelper(root->left) << ' ' << root->dataItem << ' ' << expressionHelper(root->right) << std::endl;
}

template <typename DataType>
std::string ExprTree<DataType>::expressionHelper(ExprTreeNode* node) const {

	if(isDigit(node->dataItem)) return std::string(1, node->dataItem);

	std::string left, right;

	left = expressionHelper(node->left);
	right = expressionHelper(node->right);

	return "(" + left + " " + node->dataItem + " " + right + ")";
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw(logic_error) {

	if(isDigit(root->dataItem)) return root->dataItem - '0';

	if(typeid(DataType) == typeid(bool)) {

		return boolHelper(root);
	}
	else {
	
		return evaluateHelper(root);
	}
}

template <typename DataType> 
bool ExprTree<DataType>::boolHelper(ExprTreeNode* node) const {

	if(node->dataItem == 1) return true;
	if(node->dataItem == 0) return false;

	switch(node->dataItem) {

		case '+': 
			return boolHelper(node->left) || boolHelper(node->right);
			break;
		case '-': 
			if(node->left == NULL) return !boolHelper(node->right);
			if(node->right == NULL) return !boolHelper(node->left);
			break;
		case '*':
			return boolHelper(node->left) && boolHelper(node->right);
			break;
	} 

	throw(logic_error("evaluate() Not valid operator."));
}
template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(ExprTreeNode* node) const {

	if(isDigit(node->dataItem)) {

		return node->dataItem - '0';
	}

	DataType leftData, rightData;

	leftData = evaluateHelper(node->left);
	rightData = evaluateHelper(node->right);

	switch(node->dataItem) {

		case '+': return (leftData + rightData);
			break;
		case '-': return (leftData - rightData);
			break;
		case '*': return (leftData * rightData);
			break;
		case '/': return (leftData / rightData);
			break;
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
void ExprTree<DataType>::commute() {

	if(isDigit(root->dataItem)) return;

	commuteHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* node) {

	if(isDigit(node->dataItem)) return;

	ExprTreeNode* tmp;
	tmp = node->left;

	node->left = node->right;

	node->right = tmp;

	commuteHelper(node->left);
	commuteHelper(node->right);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const {

	return isEquivHelper(root, source.root);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivHelper(ExprTreeNode* node, ExprTreeNode* otherNode) const {

	bool result = true;

	if(root->dataItem != otherNode->dataItem) return false;

	result = isEquivHelper(node->left, otherNode->left);
	result = isEquivHelper(node->right, otherNode->right);

	return result;
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

template <typename DataType>
bool ExprTree<DataType>::isDigit(const char& character) const {

	if(character <= '9' && character >= '0') return true;
	else return false;
}
