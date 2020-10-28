#include <iostream>
#include <cassert>

template <typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		Node* Head;
		Node* Tail;
		T Data;

		Node(Node* head, Node* tail, const T& value) :
			Head(head),
			Tail(tail),
			Data(value)
		{
		}
	};

	DoublyLinkedList() = default;

	~DoublyLinkedList()
	{
		Node* iter = root;

		while (iter)
		{
			Node* tail = iter->Tail;
			delete iter;
			iter = tail;
		}
	}

	Node* Add(const T& value)
	{
		if (!root)
		{
			root = new Node(nullptr, nullptr, value);
			return root;
		}

		Node* lastNode = root;

		while (lastNode->Tail)
		{
			lastNode = lastNode->Tail;
		}

		return Insert(lastNode, nullptr, value);
	}

	Node* InsertBefore(Node* node, const T& value)
	{
		assert(node != nullptr);

		Node* upperNode = node->Head;
		Node* lowerNode = node;

		if (!upperNode)
		{
			root = new Node(nullptr, lowerNode, value);
			lowerNode->Head = root;
			return root;
		}

		return Insert(upperNode, lowerNode, value);
	}

	Node* InsertAfter(Node* node, const T& value)
	{
		assert(node != nullptr);

		Node* upperNode = node;
		Node* lowerNode = node->Tail;

		return Insert(upperNode, lowerNode, value);
	}

	void Remove(Node* node)
	{
		assert(node != nullptr);

		Node* upper = node->Head;
		Node* lower = node->Tail;

		if (!upper && !lower) // It's the root alone
		{
			root = nullptr;
		}
		else if (!upper && lower) // It's the root with a tail
		{
			root = lower;
			root->Head = nullptr;
		}
		else if (upper && !lower) // No tail, it's the last element
		{
			upper->Tail = nullptr;
		}
		else // Somewhere in the middle
		{
			upper->Tail = lower;
			lower->Head = upper;
		}

		delete node;
	}

	void PrintContents() const
	{
		for (Node* iter = root; iter; iter = iter->Tail)
		{
			std::cout << iter->Data << std::endl;
		}
	}

private:
	Node* Insert(Node* upperNode, Node* lowerNode, const T& value)
	{
		auto newNode = new Node(upperNode, lowerNode, value);
		upperNode->Tail = newNode;

		if (lowerNode)
		{
			lowerNode->Head = newNode;
		}

		return newNode;
	}

	Node* root = nullptr;
};

int main()
{
	{
		DoublyLinkedList<char> list;
		auto alpha = list.Add('A');
		list.Add('B');
		auto charlie = list.Add('C');
		list.Add('D');
		list.Add('E');
		auto foxtrot = list.Add('F');

		std::cout << "Start:" << std::endl;
		list.PrintContents();

		std::cout << "InsertBefore('A', 'X'):" << std::endl;
		list.InsertBefore(alpha, 'X');
		list.PrintContents();

		std::cout << "InsertBefore('F', 'Y'):" << std::endl;
		list.InsertBefore(foxtrot, 'Y');
		list.PrintContents();

		std::cout << "InsertBefore('C', 'Z'):" << std::endl;
		list.InsertBefore(charlie, 'Z');
		list.PrintContents();
	}

	{
		DoublyLinkedList<char> list;
		auto alpha = list.Add('A');
		list.Add('B');
		auto charlie = list.Add('C');
		list.Add('D');
		list.Add('E');
		auto foxtrot = list.Add('F');

		std::cout << "Start:" << std::endl;
		list.PrintContents();

		std::cout << "InsertAfter('A', 'X'):" << std::endl;
		list.InsertAfter(alpha, 'X');
		list.PrintContents();

		std::cout << "InsertAfter('F', 'Y'):" << std::endl;
		list.InsertAfter(foxtrot, 'Y');
		list.PrintContents();

		std::cout << "InsertAfter('C', 'Z'):" << std::endl;
		list.InsertAfter(charlie, 'Z');
		list.PrintContents();
	}

	{
		DoublyLinkedList<char> list;
		auto a = list.Add('a');
		auto b = list.Add('b');
		auto c = list.Add('c');
		auto d = list.Add('d');

		std::cout << "After removing 'b'" << std::endl;
		list.Remove(b);
		list.PrintContents();

		std::cout << "After removing 'c'" << std::endl;
		list.Remove(c);
		list.PrintContents();

		std::cout << "After removing 'a'" << std::endl;
		list.Remove(a);
		list.PrintContents();

		std::cout << "After removing 'd'" << std::endl;
		list.Remove(d);
		list.PrintContents();
	}


	return 0;
}