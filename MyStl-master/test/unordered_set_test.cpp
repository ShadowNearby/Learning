/*
 * test unordered_set
 * 未测试unordered_multiset
 */

#include <iostream>
#include "unordered_set.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	unordered_set<int> set1;
	unordered_set<int> set2{ 101,294,345,433,509,61,7,83,92 };

	cout << "size of set1: " << set1.size() << endl;
	cout << "size of set2: " << set2.size() << endl;

	for (int i = 0; i != 10; ++i)
	{
		set1.insert(i*(i+234));
	}
	cout << "after insert, size of set1: " << set1.size() << endl;
	cout << "now set1 has elements: \n";
	for (unordered_set<int>::iterator iter = set1.begin(); iter != set1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	set1.clear();
	cout << "after clear, size of set1: " << set1.size() << endl;

	auto iter = set2.find(92); //使用成员函数find()
	if (iter) set2.erase(iter);
	cout << "after erase, size of set2: " << set2.size() << endl;
	cout << "after erase, elements of set2 are: \n";
	for (auto e : set2)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "These elements are unordered!" << endl;
	std::system("pause");
}