#include <iostream>
#include <cassert>

// TODO: this example is too shallow

template <typename T>
class BinaryTree
{
public:
	struct Node
	{
		Node* Left;
		Node* Right;
		T Data;
	};

	static void PrintAllFrom(Node* node)
	{
		if (!node)
			return;

		std::cout << node->Data << std::endl;

		if (node->Left)
			PrintAllFrom(node->Left);

		if (node->Right)
			PrintAllFrom(node->Right);
	}
};

int main()
{
	using CharNode = BinaryTree<char>::Node;

	CharNode alpha, bravo, charlie, delta, echo, foxtrot;

	alpha.Data = 'A';
	alpha.Left = &bravo;
	alpha.Right = &charlie;

	bravo.Data = 'B';
	bravo.Left = &delta;
	bravo.Right = &echo;

	charlie.Data = 'C';
	charlie.Left = &foxtrot;
	charlie.Right = nullptr;

	delta.Data = 'D';
	delta.Left = nullptr;
	delta.Right = nullptr;

	echo.Data = 'E';
	echo.Left = nullptr;
	echo.Right = nullptr;

	foxtrot.Data = 'F';
	foxtrot.Left = nullptr;
	foxtrot.Right = nullptr;

	BinaryTree<char>::PrintAllFrom(&alpha);

	return 0;
}