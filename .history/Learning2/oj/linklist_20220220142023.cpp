/*
 * @Date: 2022-02-20 14:17:17
 * @LastEditors: js
 * @LastEditTime: 2022-02-20 14:20:23
 * @FilePath: \code\Learning2\oj\linklist.cpp
 */


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