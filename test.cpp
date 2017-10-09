#include "ExpressionTree.cpp"

int main() {

	ExprTree<float> tree;

	tree.build();

	tree.showStructure();

	ExprTree<float> tree2;

	tree2 = tree;

	tree2.showStructure();

	tree.expression();

	std::cout << "The evaluation of the tree comes out to: " << tree.evaluate() << std::endl;

	//std::cout << tree2.evaluate() << std::endl;
}
