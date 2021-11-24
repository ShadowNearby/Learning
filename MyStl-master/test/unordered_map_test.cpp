/*
 * test unordered_map
 * 未测试unordered_multimap
 */

#include <iostream>
#include <string>
#include "unordered_map.h"

using namespace MyStl;
using std::cout;
using std::endl;
using std::string;

int main()
{
	unordered_map<int, int> map1;
	unordered_map<int, string> map2{ { 192,"abc" },{ 266,"def" },{ 37,"hij" } };
	cout << "size of map1: " << map1.size() << endl;
	cout << "size of map2: " << map2.size() << endl;

	for (int i = 0; i != 10; ++i)
	{
		map1.insert({ i*(i + 196),i*i });
	}
	cout << "after insert, size of map1: " << map1.size() << endl;
	cout << "now map1 has elements: \n";
	for (unordered_map<int, int>::iterator iter = map1.begin(); iter != map1.end(); ++iter)
		cout << "{ " << iter->first << ", " << iter->second << " }  ";
	cout << endl;
	map1.clear();
	cout << "after clear, size of set1: " << map1.size() << endl;

	map2[192] = "modified";
	map2[433] = "new1";
	map2[524] = "new2";
	cout << "after using subscript operator, now size of map2: " << map2.size() << endl;
	cout << "now map2 has elements: \n";
	for (unordered_map<int, string>::iterator iter = map2.begin(); iter != map2.end(); ++iter)
		cout << "{ " << iter->first << ", " << iter->second << " }  ";
	cout << endl;
	cout << "These elements are unordered!" << endl;

	auto iter = map2.find(2); //使用自己的find()成员函数
	if (iter)
	{
		cout << "what we have found is: " << iter->second << endl;
		map2.erase(iter);
	}
	cout << "after erase, size of map2: " << map2.size() << endl;
	cout << "after erase, elements of map2 are: \n";
	for (unordered_map<int, string>::iterator iter = map2.begin(); iter != map2.end(); ++iter)
		cout << "{ " << iter->first << ", " << iter->second << " }  ";
	cout << endl;

	std::system("pause");
}