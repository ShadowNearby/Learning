/*
 * test deque
 */
 
#include <iostream>
#include "deque.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	deque<int> d1;
	deque<int> d2(10, 1); //超过一个缓冲区大小（8）
	deque<int> d3{ 1,2,3,4,5,6,7,8,9 };
	cout << "size of d1: " << d1.size() << endl;
	cout << "size of d2: " << d2.size() << endl;
	cout << "size of d3: " << d3.size() << endl;

	for (int i = 0; i != 10; ++i)
	{
		d1.push_back(i);
	}
	cout << "after push_back, size of d1: " << d1.size() << endl;
	cout << "now d1 has elements: \n";
	for (deque<int>::iterator iter = d1.begin(); iter != d1.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	d1.clear();
	cout << "after clear, size of d1: " << d1.size() << endl;

	d2.insert(d2.begin(), 2);
	cout << "after insert, size of d2: " << d2.size() << endl;
	cout << "after insert, now front of d2 is:  " << d2.front() << endl;

	auto iter = find(d3.begin(), d3.end(), 2);
	if (iter) d3.erase(iter);
	cout << "after erase, size of d3: " << d3.size() << endl;
	cout << "after erase, elements of d3 are: \n";
	for (auto e : d3)
	{
		cout << e << " ";
	}
	cout << endl;

	std::system("pause");
}