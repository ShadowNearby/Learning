/*
 * test set
 */
 
#include <iostream>
#include "set.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	set<int> set1;
	set<int> set2{ 1,2,3,4,5,6,7,8,9 };
	cout << "size of set1: " << set1.size() << endl;
	cout << "size of set2: " << set2.size() << endl;

	for (int i = 0; i != 10; ++i)
	{
		set1.insert(i);
	}
	cout << "after insert, size of set1: " << set1.size() << endl;
	cout << "now set1 has elements: \n";
	for (set<int>::iterator iter = set1.begin(); iter != set1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	set1.clear();
	cout << "after clear, size of set1: " << set1.size() << endl;

	auto iter = set2.find(2); //使用成员函数find()
	if (iter) set2.erase(iter);
	cout << "after erase, size of set2: " << set2.size() << endl;
	cout << "after erase, elements of set2 are: \n";
	for (auto e : set2)
	{
		cout << e << " ";
	}
	cout << endl;

	std::system("pause");
}