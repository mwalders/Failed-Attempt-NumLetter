#include "matrixNode.h"


using namespace std;

int main()
{
	matrixNode root;
	matrixCipher cipher;
	ofstream File;

	File.open("./page66-68.txt");

	root.Number = -1;
	root.outputFile = &File;

	cout << "Evaluating Zeroes\n";
	root.grow();
	cout << "Evaluating Ones\n";
	for (auto it = root.children.begin(); it != root.children.end(); it++)
	{
		it->grow();
	}
	cout << "Trimming Unused Ones\n";
	for (auto it = root.children.begin(); it != root.children.end(); it++)
	{
		it->trim();
	}

	cout << "Evaluating Twos\n";
	for (auto it0 = root.children.begin(); it0 != root.children.end(); it0++)
	{
		for (auto it1 = it0->children.begin(); it1 != it0->children.end(); it1++)
		{
			it1->grow();
		}
	}
	cout << "Trimming Unused Twos\n";
	for (auto it0 = root.children.begin(); it0 != root.children.end(); it0++)
	{
		for (auto it1 = it0->children.begin(); it1 != it0->children.end(); it1++)
		{
			it1->trim();
		}
		it0->trim();
	}
	cout << "Evaluating Threes\n";
	for (auto it0 = root.children.begin(); it0 != root.children.end(); it0++)
	{
		for (auto it1 = it0->children.begin(); it1 != it0->children.end(); it1++)
		{
			for (auto it2 = it1->children.begin(); it2 != it1->children.end(); it2++)
			{
				it2->grow();
			}
		}
	}
	cout << "Trimming Unused Threes\n";
	for (auto it0 = root.children.begin(); it0 != root.children.end(); it0++)
	{
		for (auto it1 = it0->children.begin(); it1 != it0->children.end(); it1++)
		{
			for (auto it2 = it1->children.begin(); it2 != it1->children.end(); it2++)
			{
				it2->trim();
			}
			it1->trim();
		}
		it0->trim();
	}
	cout << "Evaluating Fours\n";
	for (auto it0 = root.children.begin(); it0 != root.children.end(); it0++)
	{
		for (auto it1 = it0->children.begin(); it1 != it0->children.end(); it1++)
		{
			for (auto it2 = it1->children.begin(); it2 != it1->children.end(); it2++)
			{
				for (auto it3 = it2->children.begin(); it3 != it2->children.end(); it3++)
				{
					it3->grow();
				}
			}
		}
	}

	File.close();
}