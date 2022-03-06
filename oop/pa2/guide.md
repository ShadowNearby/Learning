# PA 2 

`Vector` 是一种动态数组，可以数据储存的过程中动态调整其容量大小。

具体来说，给定 `Vector` 的接口如下：

```c++
class Vector {
private:
    int capacity; // 容量，即该对象最多可以储存多少个元素
    int len;      // 当前元素长度
    Node* array;  // 指向元素数组头的指针
public:
    Vector(int n); // 初始化 Vector，容量设定为 n
    ~Vector();
    Vector(const Vector & other);
    Vector(Vector && other);
    Vector & operator=(const Vector & other);
    Vector & operator=(Vector && other);
    Node& operator [] (int pos);
    void append(int value); // 在数组的尾部添加一个指定值的元素，即 Node(value)
    void insert(int pos, int value); // 在数组的指定位置插入新元素，即 Node(value)
    void swap(int pos1, int pos2);   // 交换数组中指定位置的元素
    void dilatation();               // 将目前 Vector 中的数组容量翻倍
    int getlen();                    // 获取当前 Vector 的长度
};
```

**你只需要实现这些 `Vector` 类的接口，保证操作合法**

`Vector` 类的元素是 `Node` 类的对象，具体可见下载文件中的 `Node.h` 和 `Node.cpp`。

我们将使用测试函数来判断你的实现是否正确，样例测试代码见 `main.cpp` 中 `test1` 函数和 `test2` 函数，从标准输入读入，处理并产生相应输出，最后由输出结果判定你的结果是否正确。

在测试函数结束时，我们会调用 `Node::outputResult()` 函数来输出所有 `Node` 类对象的普通构造1（`Node()`）、普通构造函数2（`Node(int v)`）、拷贝构造、移动构造、拷贝赋值、移动赋值、析构的次数。通过这些次数来验证你的实现的正确性和效率。实现正确的 `Vector` 类不应该存在内存泄露，即满足：

**普通构造1 + 普通构造函数2 + 拷贝构造 + 移动构造 = 析构**

我们假定普通构造函数 1 由于没有进行显式赋值操作（默认值），该函数耗时较短。普通构造 2、拷贝构造和拷贝赋值操作消耗时间较长，移动构造和移动赋值消耗时间较短，我们将使用如下公式简单地验证效率：

**(普通构造2 + 拷贝构造 + 拷贝赋值) ∗ 10 + (普通构造1 + 移动构造 + 移动赋值) <= 参考答案**

提示：只要合理利用移动构造和移动赋值，即可通过效率测试。

## 输入格式

第一行包含一个正整数 `ref_ans`，表示效率的参考值。

第二行包含一个正整数 `n`，表示 `Vector` 的初始容量。

第三行包含一个正整数 `m`。

接下来 `m` 行，每行一个整数，按顺序加入 `Vector` 数组中。

第 `m + 4` 行包含一个正整数 `k`，表示操作的个数。

接下来的 `k` 行，每行1到3个整数：`p (q) (v)`，表示操作的参数。

当 `p = 0` 时，该操作为在尾部添加元素，将 `q` 加入到数组尾部。

当 `p = 1` 时，该操作为插入，将 `v` 插入到数组的第 `q` 个位置。

当 `p = 2` 时，该操作为交换，将数组中第 `q` 个元素和第 `v` 个元素交换位置。

当 `p = 3` 时，该操作为长度加倍。

**你不需要关心输入**，但它们可以帮助你测试。

## 样例输入与输出

输入

```
272
6
5
0
1
2
3
4
4
0 5
3
1 4 8
2 3 0
```

样例解释

```
272      // 效率参考值
6        // 初始容量
5        // 接下来是 5 个初始值，初始值为 0 1 2 3 4
0
1
2
3
4
4        // 接下来是 4 个操作
0 5      // 将 5 加入数组尾部，此时数组为 0 1 2 3 4 5
3        // 容量扩大为原来的两倍
1 4 8    // 将 8 插入数组的第 4 个位置，此时数组为 0 1 2 3 8 4 5
2 3 0    // 将数组的第 3 个元素和第 0 个元素交换位置，此时数组为 3 1 2 0 8 4 5
```

输出

```
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 8 4 5
3 1 2 0 8 4 5
pass
3 1 2 0 8 4 5
pass
3 1 2 0 8 4 5
44 7 0 1 14 17 52
YES
```

## 提交内容

你只需提交 `Vector.cc`
