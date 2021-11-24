/*
 * test list
 */
 
#include<iostream>
#include "list.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	list<int> list1;
	list<int> list2(5, 1);
	list<int> list3{1, 2, 3};
	cout << "size of list1: " << list1.size() << endl;
	cout << "size of list2: " << list2.size() << endl;
	cout << "size of list3: " << list3.size() << endl;

	for (int i = 0; i != 5; ++i)
	{
		list1.push_back(i);
	}
	cout << "after push_back, size of list1: " << list1.size() << endl;
	cout << "now list1 has elements: \n";
	for (list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	list1.clear();
	cout << "after clear, size of list1: " << list1.size() << endl;

	list2.insert(list2.begin(), 2);
	cout << "after insert, size of list2: " << list2.size() << endl;
	cout << "after insert, now front of list2 is:  " << list2.front() << endl;
	
	auto iter = find(list3.begin(), list3.end(), 2);
	if (iter) list3.erase(iter);
	cout << "after erase, size of list3: " << list3.size() << endl;
	cout << "after erase, elements of list3 are: \n";
	for (auto e : list3)
	{
		cout << e << " ";
	}
	cout << endl;

	std::system("pause");
}