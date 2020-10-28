#include <stdio.h>

struct Node
{
	char Value;
	struct Node* Head;
	struct Node* Tail;
};

void ForwardPrintFrom(struct Node* node)
{
	for (struct Node* iter = node; iter != NULL; iter = iter->Tail)
	{
		putchar(iter->Value);
	}
}

void BackwardPrintFrom(struct Node* node)
{
	for (struct Node* iter = node; iter != NULL; iter = iter->Head)
	{
		putchar(iter->Value);
	}
}

struct Node* Find(struct Node* node, char value)
{
	for (struct Node* iter = node; iter != NULL; iter = iter->Tail)
	{
		if (iter->Value == value)
		{
			return iter;
		}
	}

	for (struct Node* iter = node; iter != NULL; iter = iter->Head)
	{
		if (iter->Value == value)
		{
			return iter;
		}
	}

	return NULL;
}

int main()
{
	struct Node alpha, bravo, charlie, delta, echo;

	alpha.Value = 'A';
	alpha.Head = NULL;
	alpha.Tail = &bravo;

	bravo.Value = 'B';
	bravo.Head = &alpha;
	bravo.Tail = &charlie;

	charlie.Value = 'C';
	charlie.Head = &bravo;
	charlie.Tail = &delta;
	
	delta.Value = 'D';
	delta.Head = &charlie;
	delta.Tail = &echo;

	echo.Value = 'E';
	echo.Head = &delta;
	echo.Tail = NULL;

	puts("Forwards:");
	ForwardPrintFrom(&alpha);

	puts("\nBackwards:");
	BackwardPrintFrom(&echo);

	struct Node* unknown = Find(&charlie, 'E');

	if (unknown)
	{
		printf("\nFound: '%c' @ %p\n", unknown->Value, unknown);
	}

	unknown = Find(&charlie, 'A');

	if (unknown)
	{
		printf("Found: '%c' @ %p\n", unknown->Value, unknown);
	}

	return 0;
}