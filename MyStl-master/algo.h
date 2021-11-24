/* 
 * 主要算法
 */
#ifndef ALGO_H_
#define ALGO_H_

#include "functional.h"
#include "iterator.h"
#include "algoBase.h"
#include <cstdlib>

namespace MyStl
{
	// 传回 a,b,c 之居中者
	template <class _T>
	inline const _T& _median(const _T& a, const _T& b, const _T& c)
	{
		if (a < b)
			if (b < c) 		// a < b < c
				return b;
			else if (a < c)	// a < b, b >= c, a < c
				return c;
			else
				return a;
		else if (a < c) 	// c > a >= b
			return a;
		else if (b < c)		// a >= b, a >= c, b < c
			return c;
		else
			return b;
	}

	template <class _T, class _Compare>
	inline const _T& _median(const _T& a, const _T& b, const _T& c, _Compare comp)
	{
		if (comp(a, b))
			if (comp(b, c))
				return b;
			else if (comp(a, c))
				return c;
			else
				return a;
		else if (comp(a, c))
			return a;
		else if (comp(b, c))
			return c;
		else
			return b;
	}

	template <class _InputIterator, class _Function>
	_Function for_each(_InputIterator first, _InputIterator last, _Function f)
	{
		for (; first != last; ++first)
			f(*first);
		return f;
	}

	template <class _InputIterator, class _T>
	_InputIterator find(_InputIterator first, _InputIterator last, const _T& value)
	{
		while (first != last && *first != value) ++first;
		return first;
	}

	template <class _InputIterator, class _Predicate>
	_InputIterator find_if(_InputIterator first, _InputIterator last, _Predicate pred)
	{
		while (first != last && !pred(*first)) ++first;
		return first;
	}

	// 搜寻相邻的重复元素。
	//版本一
	template <class _ForwardIterator>
	_ForwardIterator adjacent_find(_ForwardIterator first, _ForwardIterator last)
	{
		if (first == last) return last;
		_ForwardIterator next = first;
		while (++next != last)
		{
			if (*first == *next) return first; // 如果找到相邻的元素值相同，就结束
			first = next;
		}
		return last;
	}

	// 搜寻相邻的重复元素。
	//版本二
	template <class _ForwardIterator, class _BinaryPredicate>
	_ForwardIterator adjacent_find(_ForwardIterator first, _ForwardIterator last,
		_BinaryPredicate binary_pred)
	{
		if (first == last) return last;
		_ForwardIterator next = first;
		while (++next != last)
		{
			// 如果找到相邻的元素符合外界指定条件，就结束
			if (binary_pred(*first, *next)) return first;
			first = next;
		}
		return last;
	}

	template <class _InputIterator, class _T>
	typename iterator_traits<_InputIterator>::difference_type
		count(_InputIterator first, _InputIterator last, const _T& value)
	{
		// 以下宣告一个计数器 n
		typename iterator_traits<_InputIterator>::difference_type n = 0;
		for (; first != last; ++first)	    // 整个范围走一篇
			if (*first == value)			// 如果元素值和 value 相等
				++n;						// 计数器累加1
		return n;
	}

	template <class _InputIterator, class _Predicate>
	typename iterator_traits<_InputIterator>::difference_type
		count_if(_InputIterator first, _InputIterator last, _Predicate pred)
	{
		// 以下宣告一个计数器 n
		typename iterator_traits<_InputIterator>::difference_type n = 0;
		for (; first != last; ++first)	// 整个范围走一篇
			if (pred(*first))			// 如果元素带入pred 的运算结果为 true
				++n;					// 计数器累加1
		return n;
	}


	template <class _ForwardIterator1, class _ForwardIterator2, class _Distance1, class _Distance2>
	_ForwardIterator1 _search(_ForwardIterator1 first1, _ForwardIterator1 last1,
		_ForwardIterator2 first2, _ForwardIterator2 last2, _Distance1*, _Distance2*)
	{
		_Distance1 d1 = 0;
		distance(first1, last1, d1);
		_Distance2 d2 = 0;
		distance(first2, last2, d2);

		if (d1 < d2) return last1;  // 如果第二序列大于第一序列，不可能成为其子序列。

		_ForwardIterator1 current1 = first1;
		_ForwardIterator2 current2 = first2;

		while (current2 != last2) 	        // 走访整个第二序列
		{
			if (*current1 == *current2) // 如果这个元素相同
			{
				++current1;					// 调整，以便比对下一个元素
				++current2;
			}
			else //如果这个元素不等
			{
				if (d1 == d2)//如果两序列一样长
					return last1;//表示不可能成功了
				else //两序列不一样长（至此肯定是序列一大于序列二）
				{
					current1 = ++first1;  //调整第一序列的标兵，
					current2 = first2;	  //准备在新起点上再找一次
					--d1;			      //已经排除了序列一的一个元素，所以序列一的长度要减1
				}
			}
		}
		return first1;
	}

	// 搜寻子序列首次出现地点
	// 版本一
	template <class _ForwardIterator1, class _ForwardIterator2>
	inline 
		_ForwardIterator1 search(_ForwardIterator1 first1, _ForwardIterator1 last1,
		  _ForwardIterator2 first2, _ForwardIterator2 last2)
	{
		return _search(first1, last1, first2, last2, distance_type(first1),
			distance_type(first2));
	}

	template <class _ForwardIterator1, class _ForwardIterator2,
		class _BinaryPredicate, class _Distance1, class _Distance2>
		_ForwardIterator1 _search(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2,
			_BinaryPredicate binary_pred, _Distance1*, _Distance2*) {
		_Distance1 d1 = 0;
		distance(first1, last1, d1);
		_Distance2 d2 = 0;
		distance(first2, last2, d2);

		if (d1 < d2) return last1;

		_ForwardIterator1 current1 = first1;
		_ForwardIterator2 current2 = first2;

		while (current2 != last2)
			if (binary_pred(*current1, *current2)) {
				++current1;
				++current2;
			}
			else {
				if (d1 == d2)
					return last1;
				else {
					current1 = ++first1;
					current2 = first2;
					--d1;
				}
			}
			return first1;
	}

	// 版本二
	template <class _ForwardIterator1, class _ForwardIterator2,
		class _BinaryPredicate>
		inline _ForwardIterator1 search(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2,
			_BinaryPredicate binary_pred) {
		return _search(first1, last1, first2, last2, binary_pred,
			distance_type(first1), distance_type(first2));
	}

	
	// 搜寻「元素 value 连续出现count次」所形成的那个子序列，传回其发生位置。
	// 版本一。
	template <class _ForwardIterator, class _Integer, class _T>
	_ForwardIterator search_n(_ForwardIterator first, _ForwardIterator last,
		_Integer count, const _T& value) {
		if (count <= 0)
			return first;
		else {
			first = find(first, last, value); // 首先找出 value 第一次出现点
			while (first != last) {			// 继续搜寻余下元素
				_Integer n = count - 1;		// value 还应出现 n 次
				_ForwardIterator i = first;	// 从上次出现点接下去搜寻
				++i;
				while (i != last && n != 0 && *i == value) { // 下个元素是value，good.
					++i;
					--n;				// 既然找到了，「value 应再出现次数」便可减1。
				}					// 回到内循环内继续搜寻
				if (n == 0)		// n==0表示确实找到了「元素值出现n次」的子序列。功德圆满。
					return first;
				else			// 功德尚未圆满…
					first = find(i, last, value); // 找value 的下一个出现点，并准备回到外循环。
			}
			return last;
		}
	}

	// 版本二。
	// 搜寻「连续count个元素皆满足指定条件」所形成的那个子序列的起点，传回其发生位置。
	template <class _ForwardIterator, class _Integer, class _T, class _BinaryPredicate>
	_ForwardIterator search_n(_ForwardIterator first, _ForwardIterator last,
		_Integer count, const _T& value,
		_BinaryPredicate binary_pred) {
		if (count <= 0)
			return first;
		else {
			while (first != last) {
				if (binary_pred(*first, value)) break; // 首先找出第一个符合条件的元素
				++first;							// 找到就离开。
			}
			while (first != last) {			// 继续搜寻余下元素
				_Integer n = count - 1;		// 还应有n个连续元素符合条件
				_ForwardIterator i = first;		// 从上次出现点接下去搜寻
				++i;
				// 以下循环确定接下来 count-1 个元素是否都符合条件
				while (i != last && n != 0 && binary_pred(*i, value)) {
					++i;
					--n;	// 既然这个元素符合条件，「应符合条件的元素个数」便可减1。
				}
				if (n == 0) 	// n==0表示确实找到了count个符合条件的元素。功德圆满。
					return first;
				else {		// 功德尚未圆满…
					while (i != last) {
						if (binary_pred(*i, value)) break; 	// 搜寻下一个符合条件的元素
						++i;
					}
					first = i;							// 准备回到外循环
				}
			}
			return last;
		}
	}

	// 将两段等长范围内的元素互换。
	template <class _ForwardIterator1, class _ForwardIterator2>
	_ForwardIterator2 swap_ranges(_ForwardIterator1 first1, _ForwardIterator1 last1,
		_ForwardIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2)
			iter_swap(first1, first2);
		return first2;
	}

	// 版本一
	//范围内元素经op操作后转存入目的地址
	template <class _InputIterator, class _OutputIterator, class UnaryOperation>
	_OutputIterator transform(_InputIterator first, _InputIterator last,
		_OutputIterator result, UnaryOperation op) 
	{
		for (; first != last; ++first, ++result)
			*result = op(*first);
		return result;
	}

	// 版本二
	//两个源序列中对应元素经binary_op操作后转存入目的地址
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class BinaryOperation>
		_OutputIterator transform(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _OutputIterator result,
			BinaryOperation binary_op) {
		for (; first1 != last1; ++first1, ++first2, ++result)
			*result = binary_op(*first1, *first2);
		return result;
	}

	template <class _ForwardIterator, class _T>
	void replace(_ForwardIterator first, _ForwardIterator last, const _T& old_value,
		const _T& new_value) {
		// 将范围内的所有 old_value 都以 new_value 取代
		for (; first != last; ++first)
			if (*first == old_value) *first = new_value;
	}

	template <class _ForwardIterator, class _Predicate, class _T>
	void replace_if(_ForwardIterator first, _ForwardIterator last, _Predicate pred,
		const _T& new_value) {
		for (; first != last; ++first)
			if (pred(*first)) *first = new_value;
	}

	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator replace_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, const _T& old_value,
		const _T& new_value) {
		for (; first != last; ++first, ++result)
			// 如果旧序列上的元素等于 old_value，就放new_value到新序列中，
			// 否则就将元素拷贝一份放进新序列中。
			*result = *first == old_value ? new_value : *first;
		return result;
	}

	template <class _Iterator, class _OutputIterator, class _Predicate, class _T>
	_OutputIterator replace_copy_if(_Iterator first, _Iterator last,
		_OutputIterator result, _Predicate pred,
		const _T& new_value) {
		for (; first != last; ++first, ++result)
			// 如果旧序列上的元素被 pred 评估为true，就放new_value到新序列中，
			// 否则就将元素拷贝一份放进新序列中。
			*result = pred(*first) ? new_value : *first;
		return result;
	}

	template <class _ForwardIterator, class _Generator>
	void generate(_ForwardIterator first, _ForwardIterator last, _Generator gen) {
		for (; first != last; ++first)	// 整个序列范围
			*first = gen();
	}

	template <class _OutputIterator, class _Size, class _Generator>
	_OutputIterator generate_n(_OutputIterator first, _Size n, _Generator gen) {
		for (; n > 0; --n, ++first)	// 只限 n 个元素
			*first = gen();
		return first;
	}

	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator remove_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, const _T& value) {
		for (; first != last; ++first)
			if (*first != value) {		//   如果不相等
				*result = *first;		//   就指派给新容器
				++result;				//   新容器前进一个位置
			}                           //   结果是新容器中序列是原容器中除去value的部分
		return result;
	}

	template <class _InputIterator, class _OutputIterator, class _Predicate>
	_OutputIterator remove_copy_if(_InputIterator first, _InputIterator last,
		_OutputIterator result, _Predicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) {	//   如果pred核定为false，
				*result = *first;	//   就指派给新容器。
				++result;			//   新容器前进一个位置。
			}
		return result;
	}

	template <class _ForwardIterator, class _T>
	_ForwardIterator remove(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		first = find(first, last, value);   // 利用顺序搜索法找出第一个相等元素
		_ForwardIterator next = first;		// 以 next 标示出来
											// 以下利用「remove_copy()允许新旧容器重迭」的性质，做移除动作，
											// 并将结果放到原容器中。
		return first == last ? first : remove_copy(++next, last, first, value);
	}

	template <class _ForwardIterator, class _Predicate>
	_ForwardIterator remove_if(_ForwardIterator first, _ForwardIterator last,
		_Predicate pred) {
		first = find_if(first, last, pred); // 利用顺序搜索法找出第一个吻合者。
		_ForwardIterator next = first;		 // 以 next 标记出来。
											 // 以下利用「remove_copy_if()允许新旧容器重迭」的性质，做移除动作，
											 // 并将结果放到原容器中。
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	// 版本一辅助函式，forward_iterator_tag 版
	template <class _InputIterator, class _ForwardIterator>
	_ForwardIterator _unique_copy(_InputIterator first, _InputIterator last,
		_ForwardIterator result, forward_iterator_tag)
	{
		*result = *first;			// 登录第一个元素
		while (++first != last)		// 走访整个区间
									// 以下，元素不同，就再登录，否则（元素相同），就跳过。
			if (*result != *first) *++result = *first;
		return ++result;
	}

	// 由于 output iterator 为 write only，无法像 forward iterator 那般可以读取，
	// 所以不能有类似 *result != *first 这样的判断动作，所以才需要设计此一版本。
	// 例如，ostream_iterator 就是一个 output iterator.
	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, _T*) {
		// T 为 output iterator 的 value type
		_T value = *first;
		*result = value;
		while (++first != last)
			if (value != *first) {
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	// 版本一辅助函式，output_iterator_tag 版
	template <class _InputIterator, class _OutputIterator>
	inline _OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		output_iterator_tag) {
		// 以下，output iterator有一些功能限制，所以必须先知道其 value type. 
		return _unique_copy(first, last, result, value_type(first));
	}

	// 版本一
	template <class _InputIterator, class _OutputIterator>
	inline _OutputIterator unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result) {
		if (first == last) return result;
		// 以下，根据result 的 iterator category，做不同的处理
		return _unique_copy(first, last, result, iterator_category(result));
	}

	template <class _InputIterator, class _ForwardIterator, class _BinaryPredicate>
	_ForwardIterator _unique_copy(_InputIterator first, _InputIterator last,
		_ForwardIterator result,
		_BinaryPredicate binary_pred,
		forward_iterator_tag) {
		*result = *first;
		while (++first != last)
			if (!binary_pred(*result, *first)) *++result = *first;
		return ++result;
	}

	template <class _InputIterator, class _OutputIterator, class _BinaryPredicate,
		class _T>
		_OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
			_OutputIterator result,
			_BinaryPredicate binary_pred, _T*) {
		_T value = *first;
		*result = value;
		while (++first != last)
			if (!binary_pred(value, *first)) {
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
	inline _OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		_BinaryPredicate binary_pred,
		output_iterator_tag) {
		return _unique_copy(first, last, result, binary_pred, value_type(first));
	}

	// 版本二
	template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
	inline _OutputIterator unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		_BinaryPredicate binary_pred) {
		if (first == last) return result;
		return _unique_copy(first, last, result, binary_pred,
			iterator_category(result));
	}

	// 版本一
	template <class _ForwardIterator>
	_ForwardIterator unique(_ForwardIterator first, _ForwardIterator last) {
		first = adjacent_find(first, last);		// 首先找到相邻重复元素的起点
		return unique_copy(first, last, first);		// 利用 unique_copy 完成。
	}

	// 版本二
	template <class _ForwardIterator, class _BinaryPredicate>
	_ForwardIterator unique(_ForwardIterator first, _ForwardIterator last,
		_BinaryPredicate binary_pred) {
		first = adjacent_find(first, last, binary_pred);
		return unique_copy(first, last, first, binary_pred);
	}

	// reverse 的 bidirectional iterator 版
	template <class _BidirectionalIterator>
	void _reverse(_BidirectionalIterator first, _BidirectionalIterator last,
		bidirectional_iterator_tag) {
		while (true)
			if (first == last || first == --last)
				return;
			else
				iter_swap(first++, last);
	}

	// reverse 的 random access iterator 版
	template <class _RandomAccessIterator>
	void _reverse(_RandomAccessIterator first, _RandomAccessIterator last,
		random_access_iterator_tag) {
		// 以下，头尾两两互换，然后头部累进一个位置，尾部累退一个位置。两者交错时即停止。
		// 注意，以下的 first < last 判断动作，只适用于 random iterators. 
		while (first < last) iter_swap(first++, --last);
	}

	// 分派函式（dispatch function）
	template <class _BidirectionalIterator>
	inline void reverse(_BidirectionalIterator first, _BidirectionalIterator last) {
		_reverse(first, last, iterator_category(first));
	}

	template <class _BidirectionalIterator, class _OutputIterator>
	_OutputIterator reverse_copy(_BidirectionalIterator first,
		_BidirectionalIterator last,
		_OutputIterator result) {
		while (first != last) {	    // 整个序列走一遍
			--last;				    // 尾端前移一个位置
			*result = *last;		// 将尾端所指元素复制到 result 所指位置
			++result;				// result 前进一个位置
		}
		return result;
	}

	// rotate 的 forward iterator 版
	template <class _ForwardIterator, class _Distance>
	void __rotate(_ForwardIterator first, _ForwardIterator middle,
		_ForwardIterator last, _Distance*, forward_iterator_tag) {
		for (_ForwardIterator i = middle; ;) {
			iter_swap(first, i);	// 前段、后段的元素一一交换
			++first;				// 双双前进1
			++i;
			// 以下判断是前段[first, middle)先结束还是后段[middle,last)先结束
			if (first == middle) {		// 前段结束了
				if (i == last) return; 	// 如果后段同时也结束，整个就结束了。
				middle = i;				// 否则调整，对新的前、后段再作交换。
			}
			else if (i == last)	// 后段先结束
				i = middle;			// 调整，准备对新的前、后段再作交换。
		}
	}

	// rotate 的 bidirectional iterator 版
	template <class _BidirectionalIterator, class _Distance>
	void __rotate(_BidirectionalIterator first, _BidirectionalIterator middle,
		_BidirectionalIterator last, _Distance*,
		bidirectional_iterator_tag) {
		reverse(first, middle);
		reverse(middle, last);
		reverse(first, last);
	}

	// 最大公因子，利用辗转相除法。
	// __gcd() 应用于 __rotate() 的 random access iterator 版
	template <class EuclideanRingElement>
	EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
	{
		while (n != 0) {
			EuclideanRingElement t = m % n;
			m = n;
			n = t;
		}
		return m;
	}

	template <class _RandomAccessIterator, class _Distance, class _T>
	void __rotate_cycle(_RandomAccessIterator first, _RandomAccessIterator last,
		_RandomAccessIterator initial, _Distance shift, _T*) {
		_T value = *initial;
		_RandomAccessIterator ptr1 = initial;
		_RandomAccessIterator ptr2 = ptr1 + shift;
		while (ptr2 != initial) {
			*ptr1 = *ptr2;
			ptr1 = ptr2;
			if (last - ptr2 > shift)
				ptr2 += shift;
			else
				ptr2 = first + (shift - (last - ptr2));
		}
		*ptr1 = value;
	}

	// rotate 的 random access iterator 版
	template <class _RandomAccessIterator, class _Distance>
	void __rotate(_RandomAccessIterator first, _RandomAccessIterator middle,
		_RandomAccessIterator last, _Distance*,
		random_access_iterator_tag) {
		// 以下迭代器的相减动作，只适用于 random access iterators
		// 取全长和前段长度的最大公因子。
		_Distance n = __gcd(last - first, middle - first);
		while (n--)
			__rotate_cycle(first, last, first + n, middle - first,
				value_type(first));
	}

	// 分派函式（dispatch function）
	template <class _ForwardIterator>
	inline void rotate(_ForwardIterator first, _ForwardIterator middle,
		_ForwardIterator last) {
		if (first == middle || middle == last) return;
		__rotate(first, middle, last, distance_type(first),
			iterator_category(first));
	}

	template <class _ForwardIterator, class _OutputIterator>
	_OutputIterator rotate_copy(_ForwardIterator first, _ForwardIterator middle,
		_ForwardIterator last, _OutputIterator result) {
		return copy(first, middle, copy(middle, last, result));
	}

	template <class _RandomAccessIterator, class _Distance>
	void __random_shuffle(_RandomAccessIterator first, _RandomAccessIterator last,
		_Distance*) {
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)
			iter_swap(i, first + _Distance(rand() % ((i - first) + 1)));

	}

	template <class _RandomAccessIterator>
	inline void random_shuffle(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		__random_shuffle(first, last, distance_type(first));
	}

	template <class _RandomAccessIterator, class RandomNumberGenerator>
	void random_shuffle(_RandomAccessIterator first, _RandomAccessIterator last,
		RandomNumberGenerator& rand) { // 注意，by reference
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)
			iter_swap(i, first + rand((i - first) + 1));
	}

	template <class _ForwardIterator, class _OutputIterator, class _Distance>
	_OutputIterator random_sample_n(_ForwardIterator first, _ForwardIterator last,
		_OutputIterator out, const _Distance n)
	{
		_Distance remaining = 0;
		distance(first, last, remaining);
		_Distance m = min(n, remaining);

		while (m > 0)
		{
			if (rand() % remaining < m)
			{

				*out = *first;
				++out;
				--m;
			}

			--remaining;
			++first;
		}
		return out;
	}

	template <class _ForwardIterator, class _OutputIterator, class _Distance,
		class RandomNumberGenerator>
		_OutputIterator random_sample_n(_ForwardIterator first, _ForwardIterator last,
			_OutputIterator out, const _Distance n,
			RandomNumberGenerator& rand)
	{
		_Distance remaining = 0;
		distance(first, last, remaining);
		_Distance m = min(n, remaining);

		while (m > 0) {
			if (rand(remaining) < m) {
				*out = *first;
				++out;
				--m;
			}

			--remaining;
			++first;
		}
		return out;
	}

	template <class _InputIterator, class _RandomAccessIterator, class _Distance>
	_RandomAccessIterator __random_sample(_InputIterator first, _InputIterator last,
		_RandomAccessIterator out,
		const _Distance n)
	{
		_Distance m = 0;
		_Distance t = n;
		for (; first != last && m < n; ++m, ++first)
			out[m] = *first;

		while (first != last) {
			++t;
			_Distance M = rand() % t;

			if (M < n)
				out[M] = *first;
			++first;
		}

		return out + m;
	}

	template <class _InputIterator, class _RandomAccessIterator,
		class RandomNumberGenerator, class _Distance>
		_RandomAccessIterator __random_sample(_InputIterator first, _InputIterator last,
			_RandomAccessIterator out,
			RandomNumberGenerator& rand,
			const _Distance n)
	{
		_Distance m = 0;
		_Distance t = n;
		for (; first != last && m < n; ++m, ++first)
			out[m] = *first;

		while (first != last) {
			++t;
			_Distance M = rand(t);
			if (M < n)
				out[M] = *first;
			++first;
		}

		return out + m;
	}

	template <class _InputIterator, class _RandomAccessIterator>
	inline _RandomAccessIterator
		random_sample(_InputIterator first, _InputIterator last,
			_RandomAccessIterator out_first, _RandomAccessIterator out_last)
	{
		return __random_sample(first, last, out_first, out_last - out_first);
	}

	template <class _InputIterator, class _RandomAccessIterator,
		class RandomNumberGenerator>
		inline _RandomAccessIterator
		random_sample(_InputIterator first, _InputIterator last,
			_RandomAccessIterator out_first, _RandomAccessIterator out_last,
			RandomNumberGenerator& rand)
	{
		return __random_sample(first, last, out_first, rand, out_last - out_first);
	}

	// 所有被 pred 判定为 true 的元素，都被放到前段，
	// 被pred 判定为 falise 的元素，都被放到后段。
	// 不保证保留原相对位置。（not stable）
	template <class _BidirectionalIterator, class _Predicate>
	_BidirectionalIterator partition(_BidirectionalIterator first,
		_BidirectionalIterator last,
		_Predicate pred) {
		while (true) {
			while (true)
				if (first == last)		// 头指标等于尾指标
					return first;			// 所有动作结束。
				else if (pred(*first))	// 头指针所指的元素符合不搬移条件
					++first;				// 不搬移；头指标前进1
				else					// 头指针所指元素符合搬移条件
					break;				// 跳出循环
			--last;					// 尾指标回溯1
			while (true)
				if (first == last)		// 头指标等于尾指标
					return first;			// 所有动作结束。
				else if (!pred(*last))	// 尾指针所指的元素符合不搬移条件
					--last;				// 不搬移；尾指标回溯1
				else					// 尾指针所指元素符合搬移条件
					break;				// 跳出循环
			iter_swap(first, last);		// 头尾指针所指元素彼此交换
			++first;					// 头指标前进1，准备下一个外循环迭代
		}
	}

	template <class _ForwardIterator, class _Predicate, class _Distance>
	_ForwardIterator __inplace_stable_partition(_ForwardIterator first,
		_ForwardIterator last,
		_Predicate pred, _Distance len) {
		if (len == 1) return pred(*first) ? last : first;
		_ForwardIterator middle = first;
		advance(middle, len / 2);
		_ForwardIterator
			first_cut = __inplace_stable_partition(first, middle, pred, len / 2);
		_ForwardIterator
			second_cut = __inplace_stable_partition(middle, last, pred,
				len - len / 2);
		rotate(first_cut, middle, second_cut);
		len = 0;
		distance(middle, second_cut, len);
		advance(first_cut, len);
		return first_cut;
	}

	template <class _ForwardIterator, class _Pointer, class _Predicate,
		class _Distance>
		_ForwardIterator __stable_partition_adaptive(_ForwardIterator first,
			_ForwardIterator last,
			_Predicate pred, _Distance len,
			_Pointer buffer,
			_Distance buffer_size) {
		if (len <= buffer_size) {
			_ForwardIterator result1 = first;
			_Pointer result2 = buffer;
			for (; first != last; ++first)
				if (pred(*first)) {
					*result1 = *first;
					++result1;
				}
				else {
					*result2 = *first;
					++result2;
				}
				copy(buffer, result2, result1);
				return result1;
		}
		else {
			_ForwardIterator middle = first;
			advance(middle, len / 2);
			_ForwardIterator first_cut =
				__stable_partition_adaptive(first, middle, pred, len / 2,
					buffer, buffer_size);
			_ForwardIterator second_cut =
				__stable_partition_adaptive(middle, last, pred, len - len / 2,
					buffer, buffer_size);

			rotate(first_cut, middle, second_cut);
			len = 0;
			distance(middle, second_cut, len);
			advance(first_cut, len);
			return first_cut;
		}
	}

	template <class _ForwardIterator, class _Predicate, class _T, class _Distance>
	inline _ForwardIterator __stable_partition_aux(_ForwardIterator first,
		_ForwardIterator last,
		_Predicate pred, _T*, _Distance*) {
		temporary_buffer<_ForwardIterator, _T> buf(first, last);
		if (buf.size() > 0)
			return __stable_partition_adaptive(first, last, pred,
				_Distance(buf.requested_size()),
				buf.begin(), buf.size());
		else
			return __inplace_stable_partition(first, last, pred,
				_Distance(buf.requested_size()));
	}

	template <class _ForwardIterator, class _Predicate>
	inline _ForwardIterator stable_partition(_ForwardIterator first,
		_ForwardIterator last,
		_Predicate pred) {
		if (first == last)
			return first;
		else
			return __stable_partition_aux(first, last, pred,
				value_type(first), distance_type(first));
	}

	// 版本一
	template <class _RandomAccessIterator, class _T>
	_RandomAccessIterator __unguarded_partition(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T pivot) {
		while (true) {

			while (*first < pivot) ++first;	// first 找到 >= pivot 的元素，就停下来
			--last;						// 调整
			while (pivot < *last) --last;	// last 找到 <= pivot 的元素，就停下来
											// 注意，以下first < last 判断动作，只适用于random iterator
			if (!(first < last)) return first;	// 交错，结束循环。
			iter_swap(first, last);				// 大小值交换
			++first;							// 调整
		}
	}

	// 版本二
	template <class _RandomAccessIterator, class _T, class _Compare>
	_RandomAccessIterator __unguarded_partition(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T pivot, _Compare comp) {
		while (1) {
			while (comp(*first, pivot)) ++first;
			--last;
			while (comp(pivot, *last)) --last;
			// 注意，以下的first < last 判断动作，只适用于random iterator
			if (!(first < last)) return first;
			iter_swap(first, last);
			++first;
		}
	}

	const int __stl_threshold = 16;


	// 版本一
	template <class _RandomAccessIterator, class _T>
	void __unguarded_linear_insert(_RandomAccessIterator last, _T value) {
		_RandomAccessIterator next = last;
		--next;
		// insertion sort 的内循环
		// 注意，一旦不出现逆转对（inversion），循环就可以结束了。
		while (value < *next) {	// 逆转对（inversion）存在
			*last = *next;		// 转正
			last = next;			// 调整迭代器
			--next;				// 前进一个位置
		}
		*last = value;
	}

	// 版本二
	template <class _RandomAccessIterator, class _T, class _Compare>
	void __unguarded_linear_insert(_RandomAccessIterator last, _T value,
		_Compare comp) {
		_RandomAccessIterator next = last;
		--next;
		while (comp(value, *next)) {
			*last = *next;
			last = next;
			--next;
		}
		*last = value;
	}

	// 版本一
	template <class _RandomAccessIterator, class _T>
	inline void __linear_insert(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*) {
		_T value = *last;		// 记录尾元素
		if (value < *first) {	// 尾比头还小（那就别一个个比较了，一次做完…）
			copy_backward(first, last, last + 1); // 将整个范围向右递移一个位置
			*first = value;		// 令头元素等于原先的尾元素值
		}
		else
			__unguarded_linear_insert(last, value);
	}

	// 版本二
	template <class _RandomAccessIterator, class _T, class _Compare>
	inline void __linear_insert(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*, _Compare comp) {
		_T value = *last;
		if (comp(value, *first)) {
			copy_backward(first, last, last + 1);
			*first = value;
		}
		else
			__unguarded_linear_insert(last, value, comp);
	}

	// 版本一
	template <class _RandomAccessIterator>
	void __insertion_sort(_RandomAccessIterator first, _RandomAccessIterator last) {
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)  // 外循环
			__linear_insert(first, i, value_type(first));	// first,i形成一个子范围
	}

	// 版本二
	template <class _RandomAccessIterator, class _Compare>
	void __insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Compare comp) {
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)
			__linear_insert(first, i, value_type(first), comp);
	}

	// 版本一
	template <class _RandomAccessIterator, class _T>
	void __unguarded_insertion_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*) {
		for (_RandomAccessIterator i = first; i != last; ++i)
			__unguarded_linear_insert(i, _T(*i));
	}

	// 版本一
	template <class _RandomAccessIterator>
	inline void __unguarded_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		__unguarded_insertion_sort_aux(first, last, value_type(first));
	}

	// 版本二
	template <class _RandomAccessIterator, class _T, class _Compare>
	void __unguarded_insertion_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T*, _Compare comp) {
		for (_RandomAccessIterator i = first; i != last; ++i)
			__unguarded_linear_insert(i, _T(*i), comp);
	}

	// 版本二
	template <class _RandomAccessIterator, class _Compare>
	inline void __unguarded_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_Compare comp) {
		__unguarded_insertion_sort_aux(first, last, value_type(first), comp);
	}

	// 版本一
	template <class _RandomAccessIterator>
	void __final_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		if (last - first > __stl_threshold) {
			__insertion_sort(first, first + __stl_threshold);
			__unguarded_insertion_sort(first + __stl_threshold, last);
		}
		else
			__insertion_sort(first, last);
	}

	// 版本二
	template <class _RandomAccessIterator, class _Compare>
	void __final_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Compare comp) {
		if (last - first > __stl_threshold) {
			__insertion_sort(first, first + __stl_threshold, comp);
			__unguarded_insertion_sort(first + __stl_threshold, last, comp);
		}
		else
			__insertion_sort(first, last, comp);
	}

	// 找出 2^k <= n 的最大值k。例，n=7，得k=2，n=20，得k=4，n=8，得k=3。
	template <class _Size>
	inline _Size __lg(_Size n) {
		_Size k;
		for (k = 0; n > 1; n >>= 1) ++k;
		return k;
	}

	// 版本一
	// 注意，本函式内的许多迭代器运算动作，都只适用于RandomAccess Iterators.
	template <class _RandomAccessIterator, class _T, class _Size>
	void __introsort_loop(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*,
		_Size depth_limit) {
		// 以下，__stl_threshold 是个全局常数，稍早定义为 const int 16。
		while (last - first > __stl_threshold) {
			if (depth_limit == 0) {				// 至此，切割恶化
				partial_sort(first, last, last);	// 改用 heapsort
				return;
			}
			--depth_limit;
			// 以下是 median-of-three partition，选择一个够好的枢轴并决定切割点。
			// 切割点将落在迭代器 cut 身上。
			_RandomAccessIterator cut = __unguarded_partition
			(first, last, _T(_median(*first, *(first + (last - first) / 2),
				*(last - 1))));
			// 对右半段递归进行 sort.
			__introsort_loop(cut, last, value_type(first), depth_limit);
			last = cut;
			// 现在回到while 循环，准备对左半段递归进行 sort.
			// 这种写法可读性较差，效率并没有比较好。
			// RW STL 采用一般教科书写法（直观地对左半段和右半段递归），较易阅读。
		}
	}

	// 版本二
	template <class _RandomAccessIterator, class _T, class _Size, class _Compare>
	void __introsort_loop(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*,
		_Size depth_limit, _Compare comp) {
		while (last - first > __stl_threshold) {
			if (depth_limit == 0) {
				partial_sort(first, last, last, comp);
				return;
			}
			--depth_limit;
			_RandomAccessIterator cut = __unguarded_partition
			(first, last, _T(_median(*first, *(first + (last - first) / 2),
				*(last - 1), comp)), comp);
			__introsort_loop(cut, last, value_type(first), depth_limit, comp);
			last = cut;
		}
	}

	// 版本一
	// 千万注意：sort()只适用于 RandomAccessIterator
	template <class _RandomAccessIterator>
	inline void sort(_RandomAccessIterator first, _RandomAccessIterator last) {
		if (first != last) {
			__introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
			__final_insertion_sort(first, last);
		}
	}

	// 版本二
	// 千万注意：sort()只适用于 RandomAccessIterator
	template <class _RandomAccessIterator, class _Compare>
	inline void sort(_RandomAccessIterator first, _RandomAccessIterator last,
		_Compare comp) {
		if (first != last) {
			__introsort_loop(first, last, value_type(first), __lg(last - first) * 2,
				comp);
			__final_insertion_sort(first, last, comp);
		}
	}


	template <class _RandomAccessIterator>
	void __inplace_stable_sort(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		// 注意，以下的last-first < 15 判断动作，只适用于random iterator
		if (last - first < 15) {
			__insertion_sort(first, last);
			return;
		}
		_RandomAccessIterator middle = first + (last - first) / 2;
		__inplace_stable_sort(first, middle);
		__inplace_stable_sort(middle, last);
		__merge_without_buffer(first, middle, last, middle - first, last - middle);
	}

	template <class _RandomAccessIterator, class _Compare>
	void __inplace_stable_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Compare comp) {
		// 注意，以下的last-first < 15 判断动作，只适用于random iterator
		if (last - first < 15) {
			__insertion_sort(first, last, comp);
			return;
		}
		_RandomAccessIterator middle = first + (last - first) / 2;
		__inplace_stable_sort(first, middle, comp);
		__inplace_stable_sort(middle, last, comp);
		__merge_without_buffer(first, middle, last, middle - first,
			last - middle, comp);
	}

	template <class RandomAccessIterator1, class RandomAccessIterator2,
		class _Distance>
		void __merge_sort_loop(RandomAccessIterator1 first,
			RandomAccessIterator1 last,
			RandomAccessIterator2 result, _Distance step_size) {
		_Distance two_step = 2 * step_size;

		while (last - first >= two_step) {
			result = merge(first, first + step_size,
				first + step_size, first + two_step, result);
			first += two_step;
		}

		step_size = min(_Distance(last - first), step_size);
		merge(first, first + step_size, first + step_size, last, result);
	}

	template <class RandomAccessIterator1, class RandomAccessIterator2,
		class _Distance, class _Compare>
		void __merge_sort_loop(RandomAccessIterator1 first,
			RandomAccessIterator1 last,
			RandomAccessIterator2 result, _Distance step_size,
			_Compare comp) {
		_Distance two_step = 2 * step_size;

		while (last - first >= two_step) {
			result = merge(first, first + step_size,
				first + step_size, first + two_step, result, comp);
			first += two_step;
		}
		step_size = min(_Distance(last - first), step_size);

		merge(first, first + step_size, first + step_size, last, result, comp);
	}

	const int __stl_chunk_size = 7;

	template <class _RandomAccessIterator, class _Distance>
	void __chunk_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Distance chunk_size) {
		while (last - first >= chunk_size) {
			__insertion_sort(first, first + chunk_size);
			first += chunk_size;
		}
		__insertion_sort(first, last);
	}

	template <class _RandomAccessIterator, class _Distance, class _Compare>
	void __chunk_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_Distance chunk_size, _Compare comp) {
		while (last - first >= chunk_size) {
			__insertion_sort(first, first + chunk_size, comp);
			first += chunk_size;
		}
		__insertion_sort(first, last, comp);
	}

	template <class _RandomAccessIterator, class _Pointer, class _Distance>
	void __merge_sort_with_buffer(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_Pointer buffer, _Distance*) {
		_Distance len = last - first;
		_Pointer buffer_last = buffer + len;

		_Distance step_size = __stl_chunk_size;
		__chunk_insertion_sort(first, last, step_size);

		while (step_size < len) {
			__merge_sort_loop(first, last, buffer, step_size);
			step_size *= 2;
			__merge_sort_loop(buffer, buffer_last, first, step_size);
			step_size *= 2;
		}
	}

	template <class _RandomAccessIterator, class _Pointer, class _Distance,
		class _Compare>
		void __merge_sort_with_buffer(_RandomAccessIterator first,
			_RandomAccessIterator last, _Pointer buffer,
			_Distance*, _Compare comp) {
		_Distance len = last - first;
		_Pointer buffer_last = buffer + len;

		_Distance step_size = __stl_chunk_size;
		__chunk_insertion_sort(first, last, step_size, comp);

		while (step_size < len) {
			__merge_sort_loop(first, last, buffer, step_size, comp);
			step_size *= 2;
			__merge_sort_loop(buffer, buffer_last, first, step_size, comp);
			step_size *= 2;
		}
	}

	template <class _RandomAccessIterator, class _Pointer, class _Distance>
	void __stable_sort_adaptive(_RandomAccessIterator first,
		_RandomAccessIterator last, _Pointer buffer,
		_Distance buffer_size) {
		_Distance len = (last - first + 1) / 2;
		_RandomAccessIterator middle = first + len;
		if (len > buffer_size) {
			__stable_sort_adaptive(first, middle, buffer, buffer_size);
			__stable_sort_adaptive(middle, last, buffer, buffer_size);
		}
		else {
			__merge_sort_with_buffer(first, middle, buffer, (_Distance*)0);
			__merge_sort_with_buffer(middle, last, buffer, (_Distance*)0);
		}
		__merge_adaptive(first, middle, last, _Distance(middle - first),
			_Distance(last - middle), buffer, buffer_size);
	}

	template <class _RandomAccessIterator, class _Pointer, class _Distance,
		class _Compare>
		void __stable_sort_adaptive(_RandomAccessIterator first,
			_RandomAccessIterator last, _Pointer buffer,
			_Distance buffer_size, _Compare comp) {
		_Distance len = (last - first + 1) / 2;
		_RandomAccessIterator middle = first + len;
		if (len > buffer_size) {
			__stable_sort_adaptive(first, middle, buffer, buffer_size,
				comp);
			__stable_sort_adaptive(middle, last, buffer, buffer_size,
				comp);
		}
		else {
			__merge_sort_with_buffer(first, middle, buffer, (_Distance*)0, comp);
			__merge_sort_with_buffer(middle, last, buffer, (_Distance*)0, comp);
		}
		__merge_adaptive(first, middle, last, _Distance(middle - first),
			_Distance(last - middle), buffer, buffer_size,
			comp);
	}

	template <class _RandomAccessIterator, class _T, class _Distance>
	inline void __stable_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*, _Distance*) {
		temporary_buffer<_RandomAccessIterator, _T> buf(first, last);
		if (buf.begin() == 0)
			__inplace_stable_sort(first, last);
		else
			__stable_sort_adaptive(first, last, buf.begin(), _Distance(buf.size()));
	}

	template <class _RandomAccessIterator, class _T, class _Distance, class _Compare>
	inline void __stable_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*, _Distance*,
		_Compare comp) {
		temporary_buffer<_RandomAccessIterator, _T> buf(first, last);
		if (buf.begin() == 0)
			__inplace_stable_sort(first, last, comp);
		else
			__stable_sort_adaptive(first, last, buf.begin(), _Distance(buf.size()),
				comp);
	}

	template <class _RandomAccessIterator>
	inline void stable_sort(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		__stable_sort_aux(first, last, value_type(first), distance_type(first));
	}

	template <class _RandomAccessIterator, class _Compare>
	inline void stable_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Compare comp) {
		__stable_sort_aux(first, last, value_type(first), distance_type(first),
			comp);
	}

	template <class _RandomAccessIterator, class _T>
	void __partial_sort(_RandomAccessIterator first, _RandomAccessIterator middle,
		_RandomAccessIterator last, _T*) {
		make_heap(first, middle);
		// 注意，以下的i < last 判断动作，只适用于random iterator
		for (_RandomAccessIterator i = middle; i < last; ++i)
			if (*i < *first)
				__pop_heap(first, middle, i, _T(*i), distance_type(first));
		sort_heap(first, middle);
	}

	// 版本一
	template <class _RandomAccessIterator>
	inline void partial_sort(_RandomAccessIterator first,
		_RandomAccessIterator middle,
		_RandomAccessIterator last) {
		__partial_sort(first, middle, last, value_type(first));
	}

	template <class _RandomAccessIterator, class _T, class _Compare>
	void __partial_sort(_RandomAccessIterator first, _RandomAccessIterator middle,
		_RandomAccessIterator last, _T*, _Compare comp) {
		make_heap(first, middle, comp);
		// 注意，以下的i < last 判断动作，只适用于random iterator
		for (_RandomAccessIterator i = middle; i < last; ++i)
			if (comp(*i, *first))
				__pop_heap(first, middle, i, _T(*i), comp, distance_type(first));
		sort_heap(first, middle, comp);
	}

	// 版本二
	template <class _RandomAccessIterator, class _Compare>
	inline void partial_sort(_RandomAccessIterator first,
		_RandomAccessIterator middle,
		_RandomAccessIterator last, _Compare comp) {
		__partial_sort(first, middle, last, value_type(first), comp);
	}

	template <class _InputIterator, class _RandomAccessIterator, class _Distance,
		class _T>
		_RandomAccessIterator __partial_sort_copy(_InputIterator first,
			_InputIterator last,
			_RandomAccessIterator result_first,
			_RandomAccessIterator result_last,
			_Distance*, _T*) {
		if (result_first == result_last) return result_last;
		_RandomAccessIterator result_real_last = result_first;
		while (first != last && result_real_last != result_last) {
			*result_real_last = *first;
			++result_real_last;
			++first;
		}
		make_heap(result_first, result_real_last);
		while (first != last) {
			if (*first < *result_first)
				__adjust_heap(result_first, _Distance(0),
					_Distance(result_real_last - result_first), _T(*first));
			++first;
		}
		sort_heap(result_first, result_real_last);
		return result_real_last;
	}

	// 版本一
	template <class _InputIterator, class _RandomAccessIterator>
	inline _RandomAccessIterator
		partial_sort_copy(_InputIterator first, _InputIterator last,
			_RandomAccessIterator result_first,
			_RandomAccessIterator result_last) {
		return __partial_sort_copy(first, last, result_first, result_last,
			distance_type(result_first), value_type(first));
	}

	template <class _InputIterator, class _RandomAccessIterator, class _Compare,
		class _Distance, class _T>
		_RandomAccessIterator __partial_sort_copy(_InputIterator first,
			_InputIterator last,
			_RandomAccessIterator result_first,
			_RandomAccessIterator result_last,
			_Compare comp, _Distance*, _T*) {
		if (result_first == result_last) return result_last;
		_RandomAccessIterator result_real_last = result_first;
		while (first != last && result_real_last != result_last) {
			*result_real_last = *first;
			++result_real_last;
			++first;
		}
		make_heap(result_first, result_real_last, comp);
		while (first != last) {
			if (comp(*first, *result_first))
				__adjust_heap(result_first, _Distance(0),
					_Distance(result_real_last - result_first), _T(*first),
					comp);
			++first;
		}
		sort_heap(result_first, result_real_last, comp);
		return result_real_last;
	}

	// 版本二
	template <class _InputIterator, class _RandomAccessIterator, class _Compare>
	inline _RandomAccessIterator
		partial_sort_copy(_InputIterator first, _InputIterator last,
			_RandomAccessIterator result_first,
			_RandomAccessIterator result_last, _Compare comp) {
		return __partial_sort_copy(first, last, result_first, result_last, comp,
			distance_type(result_first), value_type(first));
	}

	// 版本一辅助函式
	template <class _RandomAccessIterator, class _T>
	void __nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last, _T*) {
		while (last - first > 3) {	// 长度超过3
			_RandomAccessIterator cut = __unguarded_partition
			(first, last, _T(_median(*first, *(first + (last - first) / 2),
				*(last - 1))));
			if (cut <= nth)
				first = cut;
			else
				last = cut;
		}
		__insertion_sort(first, last);
	}

	// 版本一
	template <class _RandomAccessIterator>
	inline void nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last) {
		__nth_element(first, nth, last, value_type(first));
	}

	// 版本二辅助函式
	template <class _RandomAccessIterator, class _T, class _Compare>
	void __nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last, _T*, _Compare comp) {
		while (last - first > 3) {
			_RandomAccessIterator cut = __unguarded_partition
			(first, last, _T(_median(*first, *(first + (last - first) / 2),
				*(last - 1), comp)), comp);
			if (cut <= nth)
				first = cut;
			else
				last = cut;
		}
		__insertion_sort(first, last, comp);
	}

	template <class _RandomAccessIterator, class _Compare>
	inline void nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last, _Compare comp) {
		__nth_element(first, nth, last, value_type(first), comp);
	}

	// 这是版本一的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Distance>
	_ForwardIterator __lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);	// 求取整个范围的长度 len
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;			// 除以2
			middle = first;			// 这两行令middle 指向中间位置
			advance(middle, half);
			if (*middle < value) {		// 如果中间位置的元素值 < 目标值
				first = middle;			// 这两行令 first 指向 middle 的下一位置
				++first;
				len = len - half - 1;		// 修正 len，回头测试循环的结束条件
			}
			else
				len = half;				// 修正 len，回头测试循环的结束条件
		}
		return first;
	}

	// 这是版本一的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Distance>
	_RandomAccessIterator __lower_bound(_RandomAccessIterator first,
		_RandomAccessIterator last, const _T& value,
		_Distance*, random_access_iterator_tag) {
		_Distance len = last - first;	// 求取整个范围的长度 len
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;			// 除以2
			middle = first + half;		// 令middle 指向中间位置
			if (*middle < value) {		// 如果中间位置的元素值 < 目标值
				first = middle + 1;		// 令 first 指向 middle 的下一位置
				len = len - half - 1;		// 修正 len，回头测试循环的结束条件
			}
			else
				len = half;				// 修正 len，回头测试循环的结束条件
		}
		return first;
	}

	// 这是版本一
	template <class _ForwardIterator, class _T>
	inline _ForwardIterator lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		return __lower_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// 这是版本二的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Compare, class _Distance>
	_ForwardIterator __lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(*middle, value)) {
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	// 这是版本二的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Compare, class _Distance>
	_RandomAccessIterator __lower_bound(_RandomAccessIterator first,
		_RandomAccessIterator last,
		const _T& value, _Compare comp, _Distance*,
		random_access_iterator_tag) {
		_Distance len = last - first;
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first + half;
			if (comp(*middle, value)) {
				first = middle + 1;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	// 这是版本二
	template <class _ForwardIterator, class _T, class _Compare>
	inline _ForwardIterator lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp) {
		return __lower_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// 这是版本一的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Distance>
	_ForwardIterator __upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);	// 求取整个范围的长度 len
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;			// 除以2
			middle = first;			// 这两行令middle 指向中间位置
			advance(middle, half);
			if (value < *middle)		// 如果中间位置的元素值 > 目标值
				len = half;				// 修正 len，回头测试循环的结束条件
			else {
				first = middle;			// 这两行令 first 指向 middle 的下一位置
				++first;
				len = len - half - 1;		// 修正 len，回头测试循环的结束条件
			}
		}
		return first;
	}

	// 这是版本一的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Distance>
	_RandomAccessIterator __upper_bound(_RandomAccessIterator first,
		_RandomAccessIterator last, const _T& value,
		_Distance*, random_access_iterator_tag) {
		_Distance len = last - first;	// 求取整个范围的长度 len
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;			// 除以2
			middle = first + half;		// 令middle 指向中间位置
			if (value < *middle)		// 如果中间位置的元素值 > 目标值
				len = half;				// 修正 len，回头测试循环的结束条件
			else {
				first = middle + 1;		// 令 first 指向 middle 的下一位置
				len = len - half - 1;		// 修正 len，回头测试循环的结束条件
			}
		}
		return first;
	}

	// 这是版本一
	template <class _ForwardIterator, class _T>
	inline _ForwardIterator upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		return __upper_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// 这是版本二的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Compare, class _Distance>
	_ForwardIterator __upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(value, *middle))
				len = half;
			else {
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}

	// 这是版本二的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Compare, class _Distance>
	_RandomAccessIterator __upper_bound(_RandomAccessIterator first,
		_RandomAccessIterator last,
		const _T& value, _Compare comp, _Distance*,
		random_access_iterator_tag) {
		_Distance len = last - first;
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;
			middle = first + half;
			if (comp(value, *middle))
				len = half;
			else {
				first = middle + 1;
				len = len - half - 1;
			}
		}
		return first;
	}

	// 这是版本二
	template <class _ForwardIterator, class _T, class _Compare>
	inline _ForwardIterator upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp) {
		return __upper_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// 版本一的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Distance>
	pair<_ForwardIterator, _ForwardIterator>
		__equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value,
			_Distance*, forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);
		_Distance half;
		_ForwardIterator middle, left, right;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (*middle < value) {
				first = middle;
				++first;
				len = len - half - 1;
			}
			else if (value < *middle)
				len = half;
			else {
				left = lower_bound(first, middle, value);
				advance(first, len);
				right = upper_bound(++middle, first, value);
				return pair<_ForwardIterator, _ForwardIterator>(left, right);
			}
		}
		return pair<_ForwardIterator, _ForwardIterator>(first, first);
	}

	// 版本一的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Distance>
	pair<_RandomAccessIterator, _RandomAccessIterator>
		__equal_range(_RandomAccessIterator first, _RandomAccessIterator last,
			const _T& value, _Distance*, random_access_iterator_tag) {
		_Distance len = last - first;
		_Distance half;
		_RandomAccessIterator middle, left, right;

		while (len > 0) {		// 整个区间尚未走访完毕
			half = len >> 1;		// 找出中央位置
			middle = first + half;	// 设定中央迭代器
			if (*middle < value) {	// 如果中央元素 < 指定值
				first = middle + 1;	// 将运作区间缩小（移至后半段），以提高效率
				len = len - half - 1;
			}
			else if (value < *middle)	// 如果中央元素 > 指定值
				len = half;				// 将运作区间缩小（移至前半段）以提高效率
			else {		// 如果中央元素 == 指定值
						// 在前半段找 lower_bound
				left = lower_bound(first, middle, value);
				// 在后半段找 lower_bound
				right = upper_bound(++middle, first + len, value);
				return pair<_RandomAccessIterator, _RandomAccessIterator>(left, right);
			}
		}
		// 整个区间内都没有吻合的值，那么应该传回一对迭代器，指向第一个大于value 的元素。
		return pair<_RandomAccessIterator, _RandomAccessIterator>(first, first);
	}

	// 版本一
	template <class _ForwardIterator, class _T>
	inline pair<_ForwardIterator, _ForwardIterator>
		equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value) {
		// 根据迭代器的种类型（category），采用不同的策略。
		return __equal_range(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// 版本二的 forward_iterator 版本
	template <class _ForwardIterator, class _T, class _Compare, class _Distance>
	pair<_ForwardIterator, _ForwardIterator>
		__equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value,
			_Compare comp, _Distance*, forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);
		_Distance half;
		_ForwardIterator middle, left, right;

		while (len > 0) {
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(*middle, value)) {
				first = middle;
				++first;
				len = len - half - 1;
			}
			else if (comp(value, *middle))
				len = half;
			else {
				left = lower_bound(first, middle, value, comp);
				advance(first, len);
				right = upper_bound(++middle, first, value, comp);
				return pair<_ForwardIterator, _ForwardIterator>(left, right);
			}
		}
		return pair<_ForwardIterator, _ForwardIterator>(first, first);
	}

	// 版本二的 random_access_iterator 版本
	template <class _RandomAccessIterator, class _T, class _Compare, class _Distance>
	pair<_RandomAccessIterator, _RandomAccessIterator>
		__equal_range(_RandomAccessIterator first, _RandomAccessIterator last,
			const _T& value, _Compare comp, _Distance*,
			random_access_iterator_tag) {
		_Distance len = last - first;
		_Distance half;
		_RandomAccessIterator middle, left, right;

		while (len > 0) {
			half = len >> 1;
			middle = first + half;
			if (comp(*middle, value)) {
				first = middle + 1;
				len = len - half - 1;
			}
			else if (comp(value, *middle))
				len = half;
			else {
				left = lower_bound(first, middle, value, comp);
				right = upper_bound(++middle, first + len, value, comp);
				return pair<_RandomAccessIterator, _RandomAccessIterator>(left,
					right);
			}
		}
		return pair<_RandomAccessIterator, _RandomAccessIterator>(first, first);
	}

	// 版本二
	template <class _ForwardIterator, class _T, class _Compare>
	inline pair<_ForwardIterator, _ForwardIterator>
		equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value,
			_Compare comp) {
		return __equal_range(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// 版本一
	template <class _ForwardIterator, class _T>
	bool binary_search(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		_ForwardIterator i = lower_bound(first, last, value);
		return i != last && !(value < *i);
	}

	// 版本二
	template <class _ForwardIterator, class _T, class _Compare>
	bool binary_search(_ForwardIterator first, _ForwardIterator last, const _T& value,
		_Compare comp) {
		_ForwardIterator i = lower_bound(first, last, value, comp);
		return i != last && !comp(value, *i);
	}

	// 版本一
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator merge(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		while (first1 != last1 && first2 != last2) { // 两个序列都尚未走完
			if (*first2 < *first1) {	// 序列二的元素比较小
				*result = *first2;		// 登记序列二的元素
				++first2;				// 序列二前进1
			}
			else {					// 序列二的元素不比较小
				*result = *first1;		// 登记序列一的元素
				++first1;				// 序列一前进1
			}
			++result;
		}
		// 最后剩余元素以 copy 复制到目的端。以下两个序列一定至少有一个为空。
		return copy(first2, last2, copy(first1, last1, result));
	}

	// 版本二
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator merge(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2) { // 两个序列都尚未走完
			if (comp(*first2, *first1)) {	// 比较两序列的元素
				*result = *first2;			// 登记序列二的元素
				++first2;					// 序列二前进1
			}
			else {
				*result = *first1;			// 登记序列一的元素
				++first1;					// 序列一前进1
			}
			++result;
		}
		// 最后剩余元素以 copy 复制到目的端。以下两个序列一定至少有一个为空。
		return copy(first2, last2, copy(first1, last1, result));
	}

	template <class _BidirectionalIterator, class _Distance>
	void __merge_without_buffer(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_Distance len1, _Distance len2) {
		if (len1 == 0 || len2 == 0) return;
		if (len1 + len2 == 2) {
			if (*middle < *first) iter_swap(first, middle);
			return;
		}
		_BidirectionalIterator first_cut = first;
		_BidirectionalIterator second_cut = middle;
		_Distance len11 = 0;
		_Distance len22 = 0;
		if (len1 > len2) {
			len11 = len1 / 2;
			advance(first_cut, len11);
			second_cut = lower_bound(middle, last, *first_cut);
			distance(middle, second_cut, len22);
		}
		else {
			len22 = len2 / 2;
			advance(second_cut, len22);
			first_cut = upper_bound(first, middle, *second_cut);
			distance(first, first_cut, len11);
		}
		rotate(first_cut, middle, second_cut);
		_BidirectionalIterator new_middle = first_cut;
		advance(new_middle, len22);
		__merge_without_buffer(first, first_cut, new_middle, len11, len22);
		__merge_without_buffer(new_middle, second_cut, last, len1 - len11,
			len2 - len22);
	}

	template <class _BidirectionalIterator, class _Distance, class _Compare>
	void __merge_without_buffer(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_Distance len1, _Distance len2, _Compare comp) {
		if (len1 == 0 || len2 == 0) return;
		if (len1 + len2 == 2) {
			if (comp(*middle, *first)) iter_swap(first, middle);
			return;
		}
		_BidirectionalIterator first_cut = first;
		_BidirectionalIterator second_cut = middle;
		_Distance len11 = 0;
		_Distance len22 = 0;
		if (len1 > len2) {
			len11 = len1 / 2;
			advance(first_cut, len11);
			second_cut = lower_bound(middle, last, *first_cut, comp);
			distance(middle, second_cut, len22);
		}
		else {
			len22 = len2 / 2;
			advance(second_cut, len22);
			first_cut = upper_bound(first, middle, *second_cut, comp);
			distance(first, first_cut, len11);
		}
		rotate(first_cut, middle, second_cut);
		_BidirectionalIterator new_middle = first_cut;
		advance(new_middle, len22);
		__merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
		__merge_without_buffer(new_middle, second_cut, last, len1 - len11,
			len2 - len22, comp);
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2,
		class _Distance>
		BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first,
			BidirectionalIterator1 middle,
			BidirectionalIterator1 last,
			_Distance len1, _Distance len2,
			BidirectionalIterator2 buffer,
			_Distance buffer_size) {
		BidirectionalIterator2 buffer_end;
		if (len1 > len2 && len2 <= buffer_size) {
			// 缓冲区足够安置序列二（较短）
			buffer_end = copy(middle, last, buffer);
			copy_backward(first, middle, last);
			return copy(buffer, buffer_end, first);
		}
		else if (len1 <= buffer_size) {
			// 缓冲区足够安置序列一
			buffer_end = copy(first, middle, buffer);
			copy(middle, last, first);
			return copy_backward(buffer, buffer_end, last);
		}
		else {
			// 缓冲区仍然不足. 改用 rotate 算法（不需缓冲区）
			rotate(first, middle, last);
			advance(first, len2);
			return first;
		}
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2,
		class BidirectionalIterator3>
		BidirectionalIterator3 __merge_backward(BidirectionalIterator1 first1,
			BidirectionalIterator1 last1,
			BidirectionalIterator2 first2,
			BidirectionalIterator2 last2,
			BidirectionalIterator3 result) {
		if (first1 == last1) return copy_backward(first2, last2, result);
		if (first2 == last2) return copy_backward(first1, last1, result);
		--last1;
		--last2;
		while (true) {
			if (*last2 < *last1) {
				*--result = *last1;
				if (first1 == last1) return copy_backward(first2, ++last2, result);
				--last1;
			}
			else {
				*--result = *last2;
				if (first2 == last2) return copy_backward(first1, ++last1, result);
				--last2;
			}
		}
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2,
		class BidirectionalIterator3, class _Compare>
		BidirectionalIterator3 __merge_backward(BidirectionalIterator1 first1,
			BidirectionalIterator1 last1,
			BidirectionalIterator2 first2,
			BidirectionalIterator2 last2,
			BidirectionalIterator3 result,
			_Compare comp) {
		if (first1 == last1) return copy_backward(first2, last2, result);
		if (first2 == last2) return copy_backward(first1, last1, result);
		--last1;
		--last2;
		while (true) {
			if (comp(*last2, *last1)) {
				*--result = *last1;
				if (first1 == last1) return copy_backward(first2, ++last2, result);
				--last1;
			}
			else {
				*--result = *last2;
				if (first2 == last2) return copy_backward(first1, ++last1, result);
				--last2;
			}
		}
	}

	// 版本一的辅助函式。有缓冲区的情况下。
	template <class _BidirectionalIterator, class _Distance, class _Pointer>
	void __merge_adaptive(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_Distance len1, _Distance len2,
		_Pointer buffer, _Distance buffer_size) {
		if (len1 <= len2 && len1 <= buffer_size) {
			// case1. 缓冲区足够安置序列一
			_Pointer end_buffer = copy(first, middle, buffer);
			merge(buffer, end_buffer, middle, last, first);
		}
		else if (len2 <= buffer_size) {
			// case 2. 缓冲区足够安置序列二
			_Pointer end_buffer = copy(middle, last, buffer);
			__merge_backward(first, middle, buffer, end_buffer, last);
		}
		else {		// case3.  缓冲区空间不足安置任何一个序列
			_BidirectionalIterator first_cut = first;
			_BidirectionalIterator second_cut = middle;
			_Distance len11 = 0;
			_Distance len22 = 0;
			if (len1 > len2) { 	// 序列一比较长
				len11 = len1 / 2;
				advance(first_cut, len11);
				second_cut = lower_bound(middle, last, *first_cut);
				distance(middle, second_cut, len22);
			}
			else {				// 序列二比较不短
				len22 = len2 / 2; 	// 计算序列二的一半长度
				advance(second_cut, len22);
				first_cut = upper_bound(first, middle, *second_cut);
				distance(first, first_cut, len11);
			}
			_BidirectionalIterator new_middle =
				__rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
					len22, buffer, buffer_size);
			// 针对左段，递归调用。
			__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
				buffer_size);
			// 针对右段，递归调用。
			__merge_adaptive(new_middle, second_cut, last, len1 - len11,
				len2 - len22, buffer, buffer_size);
		}
	}

	template <class _BidirectionalIterator, class _Distance, class _Pointer,
		class _Compare>
		void __merge_adaptive(_BidirectionalIterator first,
			_BidirectionalIterator middle,
			_BidirectionalIterator last, _Distance len1, _Distance len2,
			_Pointer buffer, _Distance buffer_size, _Compare comp) {
		if (len1 <= len2 && len1 <= buffer_size) {
			_Pointer end_buffer = copy(first, middle, buffer);
			merge(buffer, end_buffer, middle, last, first, comp);
		}
		else if (len2 <= buffer_size) {
			_Pointer end_buffer = copy(middle, last, buffer);
			__merge_backward(first, middle, buffer, end_buffer, last, comp);
		}
		else {
			_BidirectionalIterator first_cut = first;
			_BidirectionalIterator second_cut = middle;
			_Distance len11 = 0;
			_Distance len22 = 0;
			if (len1 > len2) {
				len11 = len1 / 2;
				advance(first_cut, len11);
				second_cut = lower_bound(middle, last, *first_cut, comp);
				distance(middle, second_cut, len22);
			}
			else {
				len22 = len2 / 2;
				advance(second_cut, len22);
				first_cut = upper_bound(first, middle, *second_cut, comp);
				distance(first, first_cut, len11);
			}
			_BidirectionalIterator new_middle =
				__rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
					len22, buffer, buffer_size);
			__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
				buffer_size, comp);
			__merge_adaptive(new_middle, second_cut, last, len1 - len11,
				len2 - len22, buffer, buffer_size, comp);
		}
	}

	// 版本一的辅助函式
	template <class _BidirectionalIterator, class _T, class _Distance>
	inline void __inplace_merge_aux(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_T*, _Distance*) {
		_Distance len1 = 0;
		distance(first, middle, len1);	// len1 表示序列一的长度
		_Distance len2 = 0;
		distance(middle, last, len2);		// len2 表示序列二的长度

											// 注意，本算法会使用额外的内存空间（暂时缓冲区）
		temporary_buffer<_BidirectionalIterator, _T> buf(first, last);
		if (buf.begin() == 0) 	// 内存配置失败
			__merge_without_buffer(first, middle, last, len1, len2);
		else		// 在有暂时缓冲区的情况下进行
			__merge_adaptive(first, middle, last, len1, len2,
				buf.begin(), _Distance(buf.size()));
	}

	// 版本二的辅助函式
	template <class _BidirectionalIterator, class _T,
		class _Distance, class _Compare>
		inline void __inplace_merge_aux(_BidirectionalIterator first,
			_BidirectionalIterator middle,
			_BidirectionalIterator last, _T*, _Distance*,
			_Compare comp) {
		_Distance len1 = 0;
		distance(first, middle, len1);
		_Distance len2 = 0;
		distance(middle, last, len2);

		temporary_buffer<_BidirectionalIterator, _T> buf(first, last);
		if (buf.begin() == 0)
			__merge_without_buffer(first, middle, last, len1, len2, comp);
		else
			__merge_adaptive(first, middle, last, len1, len2,
				buf.begin(), _Distance(buf.size()),
				comp);
	}

	// 版本一。合并并取代（覆写）
	template <class _BidirectionalIterator>
	inline void inplace_merge(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last) {
		// 只要有任何一个序列为空，就什么都不必做。
		if (first == middle || middle == last) return;
		__inplace_merge_aux(first, middle, last, value_type(first),
			distance_type(first));
	}

	// 版本二。合并并取代（覆写）
	template <class _BidirectionalIterator, class _Compare>
	inline void inplace_merge(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last, _Compare comp) {
		if (first == middle || middle == last) return;
		__inplace_merge_aux(first, middle, last, value_type(first),
			distance_type(first), comp);
	}

	// 版本一。判断区间二的每个元素值是否都存在于区间一。
	// 前提：区间一和区间二都是 sorted ranges. 
	template <class _InputIterator1, class _InputIterator2>
	bool includes(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2) {
		while (first1 != last1 && first2 != last2) // 两个区间都尚未走完
			if (*first2 < *first1)		// 序列二的元素小于序列一的元素
				return false;			  // 「涵盖」的情况必然不成立
			else if (*first1 < *first2) 	// 序列二的元素大于序列一的元素
				++first1;				  //序列一前进1
			else						// *first1 == *first2
				++first1, ++first2;		  // 两序列各自前进1

		return first2 == last2;	// 有一个序列走完了，判断最后一关
	}

	// 版本二。判断序列一内是否有个子序列，其与序列二的每个对应元素都满足二元运算 comp。
	// 前提：序列一和序列二都是 sorted ranges. 
	template <class _InputIterator1, class _InputIterator2, class _Compare>
	bool includes(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2, _Compare comp) {
		while (first1 != last1 && first2 != last2)
			if (comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				++first1;
			else
				++first1, ++first2;

		return first2 == last2;
	}

	// 联集，求存在于[first1,last1) 或存在于 [first2,last2) 的所有元素。
	// 注意，set 是一种 sorted range。这是以下算法的前提。
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_union(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// 当两个区间都不为空白区间时，执行以下动作…
		while (first1 != last1 && first2 != last2) {
			// 在两区间内分别移动迭代器。首先将元素值较小者（假设为A区）记录于目标区，
			// 然后移动A区迭代器使之前进；同时间之另一个区迭代器不动。然后，再进行
			// 新一次的比大小、记录小值、迭代器移动…。直到两区中有一区为空白。
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
			}
			else if (*first2 < *first1) {
				*result = *first2;
				++first2;
			}
			else { // *first2 == *first1
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}

		// 只要两区中有一区成为空白，就结束上述的 while 循环。
		// 以下将剩余的（非空白的）区间的所有元素拷贝到目的端。
		// 此刻的 [first1,last1)和[first2,last2)之中有一个是空白区间。
		return copy(first2, last2, copy(first1, last1, result));
	}

	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator set_union(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
			}
			else if (comp(*first2, *first1)) {
				*result = *first2;
				++first2;
			}
			else {
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		return copy(first2, last2, copy(first1, last1, result));
	}

	// 交集，求存在于[first1,last1) 且存在于 [first2,last2) 的所有元素。
	// 注意，set 是一种 sorted range。这是以下算法的前提。
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_intersection(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// 当两个区间都不为空白区间时，执行以下动作…
		while (first1 != last1 && first2 != last2)
			// 在两区间内分别移动迭代器，直到遇到元素值相同，暂停，将该值记录于目标区，
			// 再继续移动迭代器…。直到两区中有一区为空白。
			if (*first1 < *first2)
				++first1;
			else if (*first2 < *first1)
				++first2;
			else {
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
			return result;
	}

	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator set_intersection(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2)
			if (comp(*first1, *first2))
				++first1;
			else if (comp(*first2, *first1))
				++first2;
			else {
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
			return result;
	}

	// 差集，求存在于[first1,last1) 且不存在于 [first2,last2) 的所有元素。
	// 注意，set 是一种 sorted range。这是以下算法的前提。
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_difference(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// 当两个区间都不为空白区间时，执行以下动作…
		while (first1 != last1 && first2 != last2)
			// 在两区间内分别移动迭代器。当第一区间的元素等于第二区间的元素（表示此值
			// 同时存在于两区），就让两区同时前进；当第一区间的元素大于第二区间的元素，
			// 就让第二区间前进；有了这两种处理，就保证当第一区间的元素小于第二区间的
			// 元素时，第一区间的元素只存在于第一区间中，不存在于第二区间。于是将它
			// 记录于目标区。
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1)
				++first2;
			else {	// *first2 == *first1
				++first1;
				++first2;
			}
			return copy(first1, last1, result);
	}

	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator set_difference(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2)
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1))
				++first2;
			else {
				++first1;
				++first2;
			}
			return copy(first1, last1, result);
	}

	// 对称差集，求存在于[first1,last1) 且不存在于 [first2,last2) 的所有元素，
	// 以及存在于[first2,last2) 且不存在于 [first1,last1) 的所有元素。 
	// 注意，上述定义只有在「元素值独一无二」的情况下才成立。如果将 set 一般化，
	// 允许出现重复元素，那么 set-symmetric-difference 的定义应该是：
	// 如果某值在[first1,last1) 出现n次，在 [first2,last2) 出现m次，
	// 那么它在 result range 中应该出现 abs(n-m) 次。
	// 注意，set 是一种 sorted range。这是以下算法的前提。
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_symmetric_difference(_InputIterator1 first1,
		_InputIterator1 last1,
		_InputIterator2 first2,
		_InputIterator2 last2,
		_OutputIterator result) {
		// 当两个区间都不为空白区间时，执行以下动作…
		while (first1 != last1 && first2 != last2)
			// 在两区间内分别移动迭代器。当两区间内的当值元素相等，就让两区同时前进；
			// 当两区间内的当值元素不等，就记录较小值于目标区，并令较小值所在区间前进。
			if (*first1 < *first2) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1) {
				*result = *first2;
				++first2;
				++result;
			}
			else {	// *first2 == *first1
				++first1;
				++first2;
			}
			return copy(first2, last2, copy(first1, last1, result));
	}

	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator set_symmetric_difference(_InputIterator1 first1,
			_InputIterator1 last1,
			_InputIterator2 first2,
			_InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2)
			if (comp(*first1, *first2)) {
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1)) {
				*result = *first2;
				++first2;
				++result;
			}
			else {
				++first1;
				++first2;
			}
			return copy(first2, last2, copy(first1, last1, result));
	}

	// 版本一
	template <class _ForwardIterator>
	_ForwardIterator max_element(_ForwardIterator first, _ForwardIterator last) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (*result < *first) result = first;
		return result;
	}

	// 版本二
	template <class _ForwardIterator, class _Compare>
	_ForwardIterator max_element(_ForwardIterator first, _ForwardIterator last,
		_Compare comp) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (comp(*result, *first)) result = first;
		return result;
	}

	// 版本一
	template <class _ForwardIterator>
	_ForwardIterator min_element(_ForwardIterator first, _ForwardIterator last) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (*first < *result) result = first;
		return result;
	}

	// 版本二
	template <class _ForwardIterator, class _Compare>
	_ForwardIterator min_element(_ForwardIterator first, _ForwardIterator last,
		_Compare comp) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (comp(*first, *result)) result = first;
		return result;
	}

	// 版本一
	template <class _BidirectionalIterator>
	bool next_permutation(_BidirectionalIterator first,
		_BidirectionalIterator last) {
		if (first == last) return false;	// 空范围
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// 只有一个元素
		i = last;	// i 指向尾端
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// 以上，锁定一组（两个）相邻元素
			if (*i < *ii) {	// 如果前一个元素小于后一个元素
				_BidirectionalIterator j = last;		// 令 j指向尾端
				while (!(*i < *--j));	  	// 由尾端往前找，直到遇上比 *i 大的元素
				iter_swap(i, j);			// 交换 i, j
				reverse(ii, last);		// 将 ii 之后的元素全部逆向重排
				return true;
			}
			if (i == first) {			// 进行至最前面了
				reverse(first, last);		// 全部逆向重排
				return false;
			}
		}
	}

	// 版本二
	template <class _BidirectionalIterator, class _Compare>
	bool next_permutation(_BidirectionalIterator first, _BidirectionalIterator last,
		_Compare comp) {
		if (first == last) return false;	// 空范围
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// 只有一个元素
		i = last;	// i 指向尾端
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// 以上，锁定一组（两个）相邻元素
			if (comp(*i, *ii)) {	// 如果前一个元素与后一个元素满足 comp 条件
				_BidirectionalIterator j = last;		// 令 j指向尾端
				while (!comp(*i, *--j));	// 由尾端往前找，直到遇上符合条件的元素
				iter_swap(i, j);			// 交换 i, j
				reverse(ii, last);		// 将 ii 之后的元素全部逆向重排
				return true;
			}
			if (i == first) {			// 进行至最前面了
				reverse(first, last);		// 全部逆向重排
				return false;
			}
		}
	}

	// 版本一
	template <class _BidirectionalIterator>
	bool prev_permutation(_BidirectionalIterator first,
		_BidirectionalIterator last) {
		if (first == last) return false;	// 空范围
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// 只有一个元素
		i = last;	// i 指向尾端
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// 以上，锁定一组（两个）相邻元素
			if (*ii < *i) {	// 如果前一个元素大于后一个元素
				_BidirectionalIterator j = last;		// 令 j指向尾端
				while (!(*--j < *i));		// 由尾端往前找，直到遇上比 *i 小的元素
				iter_swap(i, j);			// 交换 i, j
				reverse(ii, last);		// 将 ii 之后的元素全部逆向重排
				return true;
			}
			if (i == first) {			// 进行至最前面了
				reverse(first, last);		// 全部逆向重排
				return false;
			}
		}
	}

	// 版本二
	template <class _BidirectionalIterator, class _Compare>
	bool prev_permutation(_BidirectionalIterator first, _BidirectionalIterator last,
		_Compare comp) {
		if (first == last) return false;
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;
		i = last;
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			if (comp(*ii, *i)) {
				_BidirectionalIterator j = last;
				while (!comp(*--j, *i));
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if (i == first) {
				reverse(first, last);
				return false;
			}
		}
	}

	// 版本一
	template <class _InputIterator, class _ForwardIterator>
	_InputIterator find_first_of(_InputIterator first1, _InputIterator last1,
		_ForwardIterator first2, _ForwardIterator last2)
	{
		for (; first1 != last1; ++first1) // 遍访序列一
										  // 以下，根据序列二的每个元素
			for (_ForwardIterator iter = first2; iter != last2; ++iter)
				if (*first1 == *iter)	// 如果序列一的元素等于序列二的元素
					return first1;		// 找到了，结束。
		return last1;
	}

	// 版本二
	template <class _InputIterator, class _ForwardIterator, class _BinaryPredicate>
	_InputIterator find_first_of(_InputIterator first1, _InputIterator last1,
		_ForwardIterator first2, _ForwardIterator last2,
		_BinaryPredicate comp)
	{
		for (; first1 != last1; ++first1) // 遍访序列一
										  // 以下，根据序列二的每个元素
			for (_ForwardIterator iter = first2; iter != last2; ++iter)
				if (comp(*first1, *iter)) // 如果序列一和序列二的元素满足comp 条件
					return first1;			// 找到了，结束。
		return last1;
	}


	// 搜寻[first1, last1) 中的子序列 [first2, last2) 的最后出现点
	// 以下是forward iterators 版
	template <class _ForwardIterator1, class _ForwardIterator2>
	_ForwardIterator1 __find_end(_ForwardIterator1 first1, _ForwardIterator1 last1,
		_ForwardIterator2 first2, _ForwardIterator2 last2,
		forward_iterator_tag, forward_iterator_tag)
	{
		if (first2 == last2)		// 如果搜寻目标是空的，
			return last1;			// 传回 last1 表示该「空子序列」的最后出现点
		else {
			_ForwardIterator1 result = last1;
			while (1) {
				// 以下利用search()搜寻某个子序列的首次出现点。找不到的话传回last1
				_ForwardIterator1 new_result = search(first1, last1, first2, last2);
				if (new_result == last1)	// 没找到
					return result;
				else {
					result = new_result;		// 调动一下标兵，准备下一个搜寻行动
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	template <class _ForwardIterator1, class _ForwardIterator2,
		class _BinaryPredicate>
		_ForwardIterator1 __find_end(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2,
			forward_iterator_tag, forward_iterator_tag,
			_BinaryPredicate comp)
	{
		if (first2 == last2)
			return last1;
		else {
			_ForwardIterator1 result = last1;
			while (1) {
				_ForwardIterator1 new_result = search(first1, last1, first2, last2, comp);
				if (new_result == last1)
					return result;
				else {
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	// 以下是bidirectional iterators 版，需用到partial specialization.
	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator1
		__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			bidirectional_iterator_tag, bidirectional_iterator_tag)
	{
		// 由于搜寻的是「最后出现地点」，因此反向搜寻比较快。利用reverse_iterator.
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter2 rlast2(first2);
		// 搜寻时，序列和子序列统统逆转方向
		reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);

		if (rresult == rlast1)	// 没找到
			return last1;
		else {					// 找到了
			BidirectionalIterator1 result = rresult.base(); // 转回正常（非逆向）迭代器
			advance(result, -distance(first2, last2));	 // 调整回到子序列的起头处
			return result;
		}
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2,
		class _BinaryPredicate>
		BidirectionalIterator1
		__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			bidirectional_iterator_tag, bidirectional_iterator_tag,
			_BinaryPredicate comp)
	{
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter2 rlast2(first2);
		reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2,
			comp);

		if (rresult == rlast1)
			return last1;
		else {
			BidirectionalIterator1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}


	// 分派函式（Dispatching functions） 
	template <class _ForwardIterator1, class _ForwardIterator2>
	inline _ForwardIterator1
		find_end(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2)
	{
		typedef typename iterator_traits<_ForwardIterator1>::iterator_category
			category1;
		typedef typename iterator_traits<_ForwardIterator2>::iterator_category
			category2;
		return __find_end(first1, last1, first2, last2, category1(), category2());

	}

	template <class _ForwardIterator1, class _ForwardIterator2,
		class _BinaryPredicate>
		inline _ForwardIterator1
		find_end(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2,
			_BinaryPredicate comp)
	{
		typedef typename iterator_traits<_ForwardIterator1>::iterator_category
			category1;
		typedef typename iterator_traits<_ForwardIterator2>::iterator_category
			category2;
		return __find_end(first1, last1, first2, last2, category1(), category2(),
			comp);

	}

	template <class _RandomAccessIterator, class _Distance>
	bool __is_heap(_RandomAccessIterator first, _RandomAccessIterator last,
		_Distance*)
	{
		const _Distance n = last - first;

		_Distance parent = 0;
		for (_Distance child = 1; child < n; ++child) {
			if (first[parent] < first[child])
				return false;
			if ((child & 1) == 0)
				++parent;
		}
		return true;
	}

	template <class _RandomAccessIterator>
	inline bool is_heap(_RandomAccessIterator first, _RandomAccessIterator last)
	{
		return __is_heap(first, last, distance_type(first));
	}


	template <class _RandomAccessIterator, class _Distance, class _StrictWeakOrdering>
	bool __is_heap(_RandomAccessIterator first, _RandomAccessIterator last,
		_StrictWeakOrdering comp,
		_Distance*)
	{
		const _Distance n = last - first;

		_Distance parent = 0;
		for (_Distance child = 1; child < n; ++child) {
			if (comp(first[parent], first[child]))
				return false;
			if ((child & 1) == 0)
				++parent;
		}
		return true;
	}

	template <class _RandomAccessIterator, class _StrictWeakOrdering>
	inline bool is_heap(_RandomAccessIterator first, _RandomAccessIterator last,
		_StrictWeakOrdering comp)
	{
		return __is_heap(first, last, comp, distance_type(first));
	}


	template <class _ForwardIterator>
	bool is_sorted(_ForwardIterator first, _ForwardIterator last)
	{
		if (first == last)
			return true;

		_ForwardIterator next = first;
		for (++next; next != last; first = next, ++next) {
			if (*next < *first)
				return false;
		}

		return true;
	}

	template <class _ForwardIterator, class _StrictWeakOrdering>
	bool is_sorted(_ForwardIterator first, _ForwardIterator last,
		_StrictWeakOrdering comp)
	{
		if (first == last)
			return true;

		_ForwardIterator next = first;
		for (++next; next != last; first = next, ++next) {
			if (comp(*next, *first))
				return false;
		}

		return true;
	}
}//end of MyStl
#endif //end of ALOGO_H_
