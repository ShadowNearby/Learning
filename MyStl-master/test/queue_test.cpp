/*
 * test queue
 */
 
#include <iostream>
#include "queue.h"
#include "list.h"

using namespace MyStl;
using std::cout;
using std::endl;

int main()
{
	queue<int> que1;
	queue<int, list<int>> que2; // 用户指定比较器
	for (int i = 0; i != 10; ++i)
	{
		i % 2 ? que1.push(i) : que2.push(i);
	}
	cout << "after push, size of que1 is: " << que1.size()
		<< ", size of que2 is: " << que2.size() << endl;
	cout << "front of que1 is: " << que1.front()
		<< ", front of que2 is: " << que2.front() << endl;

	que1.pop();
	que2.pop();
	cout << "after pop, size of st1 is: " << que1.size()
		<< ", size of st2 is: " << que2.size() << endl;
	cout << "front of st1 is: " << que1.front()
		<< ", front of st2 is: " << que2.front() << endl;

	std::system("pause");

}