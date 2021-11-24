/*
 * test vector
 */

#include <iostream>
#include "vector.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	vector<int> v1;
	vector<int> v2(5, 1);
	vector<int> v3{ 1,2,3 };
	cout << "size of v1: " << v1.size() << " capacity of v1: " << v1.capacity() << endl;
	cout << "size of v2: " << v2.size() << " capacity of v2: " << v2.capacity() << endl;
	cout << "size of v3: " << v3.size() << " capacity of v3: " << v3.capacity() << endl;

	for (int i = 0; i != 5; ++i)
	{
		v1.push_back(i);
	}
	cout << "after push_back, size of v1: " << v1.size() << " capacity of v1: " << v1.capacity() << endl;
	cout << "after push_back, now v1 has elements: \n";
	for (vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
	v1.clear();
	cout << "after clear, size of v1: " << v1.size() << " capacity of v1: " << v1.capacity() << endl;

	v2.insert(v2.begin(), 3, 2);
	cout << "after insert, size of v2: " << v2.size() << " capacity of v2: " << v2.capacity() << endl;
	cout << "after insert, now front of v2 is: " << v2.front() << endl;

	auto iter = find(v3.begin(), v3.end(), 2);
	if (iter) v3.erase(iter);
	cout << "after erase, size of v3: " << v3.size() << " capacity of v3: " << v3.capacity() << endl;
	cout << "after erase, elements of v3 are: \n";
	for (auto e : v3)
		cout << e << " ";
	cout << endl;
	
	std::system("pause");
}