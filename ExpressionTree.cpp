/**
 * @file ExpressionTree.cpp
 * @author Rowan Gudmundsson
 * @date 10/10/17
 **/

#include "ExpressionTree.h"

/** 
 * \brief Node constructor, fills data, sets pointers to assigned value
 *
 * Sets both left and right pointer to parameter passed, also sets data to parameter passed
 * 
 * @param Data item, left pointer, right pointer
 * @return None, constructor
 * @pre None, constructor
 * @post Node will be initialized and ready for use
 **/
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char newDataItem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr) { 

	dataItem = newDataItem;
	left = leftPtr;
	right = rightPtr;
}

/**
 * \brief Constructor, sets root to NULL
 * 
 * Initializes the expression tree, setting the root pointer to NULL
 *
 * @param None, default constructor
 * @return None, constructor
 * @pre None, constructor
 * @post Expression tree will be ready to be built
 **/
template <typename DataType>
ExprTree<DataType>::ExprTree() : root(NULL) {
}

/**
 * \brief Copy constructor, sets this to other
 * 
 * Utilizes the assignment operator to set this equal to parameter tree
 *
 * @param Other tree
 * @return None, constructor
 * @pre Other must be initialized
 * @post This will contain all data within other
 **/
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree<DataType>& other) : root(NULL) {

	(*this) = other;
}

/** 
 * \brief Assignment operator, assigns this to other
 * 
 * Makes use of assignmentHelper to assign this to other, calls assignment helper with root.
 *
 * @param Other tree
 * @return this, allows for a = b = c
 * @pre Other must be initialized
 * @post This will hold the data of other 
 **/
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>& other) {

	if(this == &other) return (*this);

	clear();

	assignementHelper(root, other.root);

	return (*this);
}

/**
 * \brief Recursive function, traverses other, creates new nodes to this containing data of other
 *
 * Creates new node containing the data of otherNode, checks if it is a digit; if it is, return.
 * If not, call the function again on the left and right node.
 *
 * @param Node, otherNode
 * @return Base cases don't return a value
 * @pre Must be called with valid trees
 * @post Trees will be equivalent
 **/
template <typename DataType>
void ExprTree<DataType>::assignementHelper(ExprTreeNode*& node, ExprTreeNode* otherNode) {

	node = new ExprTreeNode(otherNode->dataItem, NULL, NULL);

	if(isDigit(otherNode->dataItem)) return;

	assignementHelper(node->left, otherNode->left);
	assignementHelper(node->right, otherNode->right);
}

/** 
 * \brief Destructor, calls clear
 *
 * @param None
 * @return None
 * @pre Tree must have been initialized
 * @post Memory will be deallocated
 **/
template <typename DataType>
ExprTree<DataType>::~ExprTree() {

	clear();
}

/**
 * \brief Build calls build helper with root
 *
 * @param None
 * @return None, void function
 * @pre Tree must be initialized
 * @post Tree will be populated by input values
 **/
template <typename DataType>
void ExprTree<DataType>::build() {

	buildHelper(root);
}

/**
 * \brief Recursive function, pre order build
 *
 * Gets user input for data item, creates a new node with that data. If the data is a digit return;
 * if not, build the left and right node
 *
 * @param Current node
 * @return Base cases do not return a value
 * @pre Tree must be initialized
 * @post Current node will be populated
 **/
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

/** 
 * \brief Prints the tree in infix notation
 * 
 * Checks if it is a single digit and outputs it; if not, prints a string created from expressionHelper()
 * 
 * @param None
 * @return None, void function
 * @pre Tree must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
void ExprTree<DataType>::expression() const {

	if(isEmpty()) return;

	if(isDigit(root->dataItem)) {

		std::cout << root->dataItem;
		return;
	}

	std::cout << expressionHelper(root);
}

/**
 * \brief Creates a string using left and right and the data in the current node
 *
 * Returns the digit as a string if it is a digit. If not, recursively adds left then data of the current node
 * then right to a string and returns it.
 *
 * @param Current node
 * @return String of output
 * @pre Tree must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
std::string ExprTree<DataType>::expressionHelper(ExprTreeNode* node) const {

	if(isDigit(node->dataItem)) return std::string(1, node->dataItem);

	std::string left, right;

	left = expressionHelper(node->left);
	right = expressionHelper(node->right);

	return "(" + left + node->dataItem + right + ")";
}

/**
 * \brief Calls evaluateHelper with root to find the value of the tree
 *
 * @param None
 * @return Value of the tree 
 * @pre Tree must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw(logic_error) {

	if(isEmpty()) throw(logic_error("evaluate() empty tree"));

	return evaluateHelper(root);
}

/** 
 * \brief Finds the value of the current node
 *
 * Checks if it is a digit, returns the digit as DataType type. If not, finds the value
 * of the left subtree, the right subtree and returns the value of right +-/* left depending
 * on the value of the current nodes data item
 * 
 * @param Current node
 * @return Value of the node
 * @pre Tree must be initialized
 * @post Constant, no change
 **/
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

/** 
 * \brief Calls clearHelper, sets root back to NULL
 *
 * @param None
 * @return None, void function
 * @pre Tree must be initialized
 * @post Tree will be empty
 **/
template <typename DataType>
void ExprTree<DataType>::clear() {

	if(isEmpty()) return;

	clearHelper(root);

	root = NULL;
}

/** 
 * \brief Post order recursive clear
 *
 * Checks if left and right are empty, deletes node. If not, clears the left, clears the right
 * then deletes current node
 *
 * @param Current node
 * @return None, void function
 * @pre Tree must be initialized
 * @post Node will be deleted
 **/
template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode* node) {

	if(node->left == NULL && node->right == NULL) {

		delete [] node;
		return;
	}
	else {

		clearHelper(node->left);
		clearHelper(node->right);
		delete [] node;
		return;
	}
}

/** 
 * \brief Calls commuteHelper with root
 * 
 * @param None
 * @return None, void function
 * @pre Tree must be initialized
 * @post Tree will be commuted
 **/
template <typename DataType>
void ExprTree<DataType>::commute() {

	if(isEmpty()) return;
	if(isDigit(root->dataItem)) return;

	commuteHelper(root);
}

/** 
 * \brief Switches every right pointer and left pointer
 * 
 * If node is digit return else switch left pointer with right pointer, calls recursively
 *
 * @param Current node
 * @return Base cases don't return a value
 * @pre Tree must be initialized
 * @post Node will be commuted
 **/
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

/** 
 * \brief Checks if normally equivalent, if not checks if commuted and equivalent
 *
 * @param Other tree
 * @return True if equiv, false if not
 * @pre Both trees must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const {

	bool result;

	if(root == NULL && source.root == NULL) return true;
	if((root == NULL && source.root != NULL) || (root != NULL && source.root == NULL)) return false;
	if((root->dataItem == source.root->dataItem) && isDigit(root->dataItem)) return true;

	result = isEquivHelper(root, source.root);
	if(!result) result = isCommuteHelper(root, source.root);

	return result;
}

/**
 * \brief Checks each node against other node, calls recursively if not digit
 * 
 * If data items are both digits and equivalent return true, if both digits but not equivalent
 * return false. Then checks left and right and sets result to true only if both are true
 * then returns true only if current nodes data items are quivalent as well as left and right
 * 
 * @param Node, other node
 * @return True if equiv, false if not
 * @pre Trees must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
bool ExprTree<DataType>::isEquivHelper(ExprTreeNode* node, ExprTreeNode* otherNode) const {

	bool result;

	if((node->dataItem == otherNode->dataItem) && isDigit(node->dataItem)) return true;
	if((node->dataItem != otherNode->dataItem) && isDigit(node->dataItem)) return false;

	result = isEquivHelper(node->left, otherNode->left) && isEquivHelper(node->right, otherNode->right);

	return ((node->dataItem == otherNode->dataItem) && result);
}

/** 
 * \brief Same as isEquivHelper() just recursively calls (left and right) and (right and left)
 * 
 * Extra thing, checks if the operator is - or / as they are non-commutable operators
 *
 * @param Node, other node
 * @return True if equiv, false if not
 * @pre Trees must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
bool ExprTree<DataType>::isCommuteHelper(ExprTreeNode* node, ExprTreeNode* otherNode) const {

	bool result;

	if((node->dataItem == otherNode->dataItem) && isDigit(node->dataItem)) return true;
	if((node->dataItem != otherNode->dataItem) && isDigit(node->dataItem)) return false;
	if(node->dataItem == '-' || node->dataItem == '/') return false;
	
	result = isEquivHelper(node->left, otherNode->right) && isEquivHelper(node->right, otherNode->left);

	return (node->dataItem == otherNode->dataItem) && result;

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

/**
 * \brief Checks if empty
 *
 * If the root is NULL then tree is empty
 *
 * @param None
 * @return True if empty, false if not
 * @pre Tree must be initialized
 * @post Constant, no change
 **/
template <typename DataType>
bool ExprTree<DataType>::isEmpty() const {

	if(root == NULL) return true;
	else return false;
}

/** 
 * \brief Checks if character is a digit
 *
 * Checks if the character is between '0' and '9' on the ASCII table
 *
 * @param Character being checked 
 * @return True if digit, false if not 
 * @pre None
 * @post Constant, no change
 **/
template <typename DataType>
bool ExprTree<DataType>::isDigit(const char& character) const {

	if(character <= '9' && character >= '0') return true;
	else return false;
}
