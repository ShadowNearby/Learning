/*
 * test stack
 */
 
#include <iostream>
#include "stack.h"
#include "list.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	stack<int> st1;
	stack<int, list<int>> st2; //用户指定底层容器
	for (int i = 0; i != 10; ++i)
	{
		i % 2 ? st1.push(i) : st2.push(i);
	}
	cout << "after push, size of st1 is: " << st1.size()
		<< ", size of st2 is: " << st2.size() << endl;
	cout << "top of st1 is: " << st1.top()
		<< ", top of st2 is: " << st2.top() << endl;
	
	st1.pop();
	st2.pop();
	cout << "after pop, size of st1 is: " << st1.size()
		<< ", size of st2 is: " << st2.size() << endl;
	cout << "top of st1 is: " << st1.top()
		<< ", top of st2 is: " << st2.top() << endl;

	std::system("pause");

}