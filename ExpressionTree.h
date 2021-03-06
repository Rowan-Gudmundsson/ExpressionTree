//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
//
//--------------------------------------------------------------------

/**
 * @file ExpressionTree.h
 * @author Rowan Gudmundsson
 * @date 10/06/17
 **/

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

template <typename DataType>
class ExprTree {
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
//	void buildHelper(ExprTreeNode* node);

    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();
    bool isEquivalent(const ExprTree& source) const;

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

	bool isEmpty() const;
    bool isDigit(const char&) const;

  private:

    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };

    // Recursive helper functions for the public member functions -- insert
    // prototypes of these functions here.
    void assignementHelper(ExprTreeNode*&, ExprTreeNode*);
	void buildHelper(ExprTreeNode*&);
    std::string expressionHelper(ExprTreeNode*) const;
    bool isEquivHelper(ExprTreeNode*, ExprTreeNode*) const;
    bool isCommuteHelper(ExprTreeNode*, ExprTreeNode*) const;
    DataType evaluateHelper(ExprTreeNode*) const;
    void commuteHelper(ExprTreeNode*);
	void showHelper(ExprTreeNode*, int) const;
	void clearHelper(ExprTreeNode*);

    // Data member
    ExprTreeNode *root;   // Pointer to the root node
};

#endif		// #ifndef EXPRESSIONTREE_H
