/*
 * @Date: 2022-02-20 14:17:17
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 14:17:17
 * @FilePath: \code\Learning2\Linklist\oj\linklist.cpp
 */
# include <iostream>
# include <stdio.h>
using namespace std;

struct LinkList {
  // TODO: Define some variables of struct LinkList here.
  void Initialize(int *a, int n) {
    // TODO: use a[0 ... n-1] to initialize the link list.
  }
  void Insert(int i, int x) {
    // TODO: insert element x after i-th element.
  }
  void Delete(int i) {
    // TODO: delete element i
  }
  void EvenOddSwap() {
    // TODO: Swap the even-indexed element with the corresponding odd-indexed element.
  }
  void Query(int i) {
    // TODO: Print the value of the i-th element on the screen.
  }
  void QueryAll() {
    // TODO: Print the link list on the screen.
  }
  void ClearMemory() {
    // TODO: Clear the memory.
  }
};

LinkList L;

int main() {
    ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  int n, *a;
  cin >> n;
  a = new int [n];
  for (int i = 0; i < n; ++ i) cin >> a[i];
  L.Initialize(a, n);
  delete [] a;

  int m, op, i, x;
  cin >> m;
  while(m --) {
    cin >> op;
    switch(op) {
      case 1: 
        cin >> i >> x;
        L.Insert(i, x);
          break;
      case 2:
        cin >> i;
        L.Delete(i);
        break;
      case 3:
        L.EvenOddSwap();
           break;
      case 4:
        cin >> i;
        L.Query(i);
        break;
      case 5:
        L.QueryAll();
        break;
    }
  }

  L.ClearMemory();
  return 0;
}