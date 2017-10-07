#include "ExpressionTree.cpp"

int main() {

	ExprTree<float> tree;

	tree.build();

	tree.showStructure();

	std::cout << "The evaluation of the tree comes out to: " << tree.evaluate() << std::endl;
}
