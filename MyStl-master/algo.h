/* 
 * ��Ҫ�㷨
 */
#ifndef ALGO_H_
#define ALGO_H_

#include "functional.h"
#include "iterator.h"
#include "algoBase.h"
#include <cstdlib>

namespace MyStl
{
	// ���� a,b,c ֮������
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

	// ��Ѱ���ڵ��ظ�Ԫ�ء�
	//�汾һ
	template <class _ForwardIterator>
	_ForwardIterator adjacent_find(_ForwardIterator first, _ForwardIterator last)
	{
		if (first == last) return last;
		_ForwardIterator next = first;
		while (++next != last)
		{
			if (*first == *next) return first; // ����ҵ����ڵ�Ԫ��ֵ��ͬ���ͽ���
			first = next;
		}
		return last;
	}

	// ��Ѱ���ڵ��ظ�Ԫ�ء�
	//�汾��
	template <class _ForwardIterator, class _BinaryPredicate>
	_ForwardIterator adjacent_find(_ForwardIterator first, _ForwardIterator last,
		_BinaryPredicate binary_pred)
	{
		if (first == last) return last;
		_ForwardIterator next = first;
		while (++next != last)
		{
			// ����ҵ����ڵ�Ԫ�ط������ָ���������ͽ���
			if (binary_pred(*first, *next)) return first;
			first = next;
		}
		return last;
	}

	template <class _InputIterator, class _T>
	typename iterator_traits<_InputIterator>::difference_type
		count(_InputIterator first, _InputIterator last, const _T& value)
	{
		// ��������һ�������� n
		typename iterator_traits<_InputIterator>::difference_type n = 0;
		for (; first != last; ++first)	    // ������Χ��һƪ
			if (*first == value)			// ���Ԫ��ֵ�� value ���
				++n;						// �������ۼ�1
		return n;
	}

	template <class _InputIterator, class _Predicate>
	typename iterator_traits<_InputIterator>::difference_type
		count_if(_InputIterator first, _InputIterator last, _Predicate pred)
	{
		// ��������һ�������� n
		typename iterator_traits<_InputIterator>::difference_type n = 0;
		for (; first != last; ++first)	// ������Χ��һƪ
			if (pred(*first))			// ���Ԫ�ش���pred ��������Ϊ true
				++n;					// �������ۼ�1
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

		if (d1 < d2) return last1;  // ����ڶ����д��ڵ�һ���У������ܳ�Ϊ�������С�

		_ForwardIterator1 current1 = first1;
		_ForwardIterator2 current2 = first2;

		while (current2 != last2) 	        // �߷������ڶ�����
		{
			if (*current1 == *current2) // ������Ԫ����ͬ
			{
				++current1;					// �������Ա�ȶ���һ��Ԫ��
				++current2;
			}
			else //������Ԫ�ز���
			{
				if (d1 == d2)//���������һ����
					return last1;//��ʾ�����ܳɹ���
				else //�����в�һ���������˿϶�������һ�������ж���
				{
					current1 = ++first1;  //������һ���еı����
					current2 = first2;	  //׼���������������һ��
					--d1;			      //�Ѿ��ų�������һ��һ��Ԫ�أ���������һ�ĳ���Ҫ��1
				}
			}
		}
		return first1;
	}

	// ��Ѱ�������״γ��ֵص�
	// �汾һ
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

	// �汾��
	template <class _ForwardIterator1, class _ForwardIterator2,
		class _BinaryPredicate>
		inline _ForwardIterator1 search(_ForwardIterator1 first1, _ForwardIterator1 last1,
			_ForwardIterator2 first2, _ForwardIterator2 last2,
			_BinaryPredicate binary_pred) {
		return _search(first1, last1, first2, last2, binary_pred,
			distance_type(first1), distance_type(first2));
	}

	
	// ��Ѱ��Ԫ�� value ��������count�Ρ����γɵ��Ǹ������У������䷢��λ�á�
	// �汾һ��
	template <class _ForwardIterator, class _Integer, class _T>
	_ForwardIterator search_n(_ForwardIterator first, _ForwardIterator last,
		_Integer count, const _T& value) {
		if (count <= 0)
			return first;
		else {
			first = find(first, last, value); // �����ҳ� value ��һ�γ��ֵ�
			while (first != last) {			// ������Ѱ����Ԫ��
				_Integer n = count - 1;		// value ��Ӧ���� n ��
				_ForwardIterator i = first;	// ���ϴγ��ֵ����ȥ��Ѱ
				++i;
				while (i != last && n != 0 && *i == value) { // �¸�Ԫ����value��good.
					++i;
					--n;				// ��Ȼ�ҵ��ˣ���value Ӧ�ٳ��ִ�������ɼ�1��
				}					// �ص���ѭ���ڼ�����Ѱ
				if (n == 0)		// n==0��ʾȷʵ�ҵ��ˡ�Ԫ��ֵ����n�Ρ��������С�����Բ����
					return first;
				else			// ������δԲ����
					first = find(i, last, value); // ��value ����һ�����ֵ㣬��׼���ص���ѭ����
			}
			return last;
		}
	}

	// �汾����
	// ��Ѱ������count��Ԫ�ؽ�����ָ�����������γɵ��Ǹ������е���㣬�����䷢��λ�á�
	template <class _ForwardIterator, class _Integer, class _T, class _BinaryPredicate>
	_ForwardIterator search_n(_ForwardIterator first, _ForwardIterator last,
		_Integer count, const _T& value,
		_BinaryPredicate binary_pred) {
		if (count <= 0)
			return first;
		else {
			while (first != last) {
				if (binary_pred(*first, value)) break; // �����ҳ���һ������������Ԫ��
				++first;							// �ҵ����뿪��
			}
			while (first != last) {			// ������Ѱ����Ԫ��
				_Integer n = count - 1;		// ��Ӧ��n������Ԫ�ط�������
				_ForwardIterator i = first;		// ���ϴγ��ֵ����ȥ��Ѱ
				++i;
				// ����ѭ��ȷ�������� count-1 ��Ԫ���Ƿ񶼷�������
				while (i != last && n != 0 && binary_pred(*i, value)) {
					++i;
					--n;	// ��Ȼ���Ԫ�ط�����������Ӧ����������Ԫ�ظ�������ɼ�1��
				}
				if (n == 0) 	// n==0��ʾȷʵ�ҵ���count������������Ԫ�ء�����Բ����
					return first;
				else {		// ������δԲ����
					while (i != last) {
						if (binary_pred(*i, value)) break; 	// ��Ѱ��һ������������Ԫ��
						++i;
					}
					first = i;							// ׼���ص���ѭ��
				}
			}
			return last;
		}
	}

	// �����εȳ���Χ�ڵ�Ԫ�ػ�����
	template <class _ForwardIterator1, class _ForwardIterator2>
	_ForwardIterator2 swap_ranges(_ForwardIterator1 first1, _ForwardIterator1 last1,
		_ForwardIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2)
			iter_swap(first1, first2);
		return first2;
	}

	// �汾һ
	//��Χ��Ԫ�ؾ�op������ת����Ŀ�ĵ�ַ
	template <class _InputIterator, class _OutputIterator, class UnaryOperation>
	_OutputIterator transform(_InputIterator first, _InputIterator last,
		_OutputIterator result, UnaryOperation op) 
	{
		for (; first != last; ++first, ++result)
			*result = op(*first);
		return result;
	}

	// �汾��
	//����Դ�����ж�ӦԪ�ؾ�binary_op������ת����Ŀ�ĵ�ַ
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
		// ����Χ�ڵ����� old_value ���� new_value ȡ��
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
			// ����������ϵ�Ԫ�ص��� old_value���ͷ�new_value���������У�
			// ����ͽ�Ԫ�ؿ���һ�ݷŽ��������С�
			*result = *first == old_value ? new_value : *first;
		return result;
	}

	template <class _Iterator, class _OutputIterator, class _Predicate, class _T>
	_OutputIterator replace_copy_if(_Iterator first, _Iterator last,
		_OutputIterator result, _Predicate pred,
		const _T& new_value) {
		for (; first != last; ++first, ++result)
			// ����������ϵ�Ԫ�ر� pred ����Ϊtrue���ͷ�new_value���������У�
			// ����ͽ�Ԫ�ؿ���һ�ݷŽ��������С�
			*result = pred(*first) ? new_value : *first;
		return result;
	}

	template <class _ForwardIterator, class _Generator>
	void generate(_ForwardIterator first, _ForwardIterator last, _Generator gen) {
		for (; first != last; ++first)	// �������з�Χ
			*first = gen();
	}

	template <class _OutputIterator, class _Size, class _Generator>
	_OutputIterator generate_n(_OutputIterator first, _Size n, _Generator gen) {
		for (; n > 0; --n, ++first)	// ֻ�� n ��Ԫ��
			*first = gen();
		return first;
	}

	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator remove_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, const _T& value) {
		for (; first != last; ++first)
			if (*first != value) {		//   ��������
				*result = *first;		//   ��ָ�ɸ�������
				++result;				//   ������ǰ��һ��λ��
			}                           //   �������������������ԭ�����г�ȥvalue�Ĳ���
		return result;
	}

	template <class _InputIterator, class _OutputIterator, class _Predicate>
	_OutputIterator remove_copy_if(_InputIterator first, _InputIterator last,
		_OutputIterator result, _Predicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) {	//   ���pred�˶�Ϊfalse��
				*result = *first;	//   ��ָ�ɸ���������
				++result;			//   ������ǰ��һ��λ�á�
			}
		return result;
	}

	template <class _ForwardIterator, class _T>
	_ForwardIterator remove(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		first = find(first, last, value);   // ����˳���������ҳ���һ�����Ԫ��
		_ForwardIterator next = first;		// �� next ��ʾ����
											// �������á�remove_copy()�����¾������ص��������ʣ����Ƴ�������
											// ��������ŵ�ԭ�����С�
		return first == last ? first : remove_copy(++next, last, first, value);
	}

	template <class _ForwardIterator, class _Predicate>
	_ForwardIterator remove_if(_ForwardIterator first, _ForwardIterator last,
		_Predicate pred) {
		first = find_if(first, last, pred); // ����˳���������ҳ���һ���Ǻ��ߡ�
		_ForwardIterator next = first;		 // �� next ��ǳ�����
											 // �������á�remove_copy_if()�����¾������ص��������ʣ����Ƴ�������
											 // ��������ŵ�ԭ�����С�
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	// �汾һ������ʽ��forward_iterator_tag ��
	template <class _InputIterator, class _ForwardIterator>
	_ForwardIterator _unique_copy(_InputIterator first, _InputIterator last,
		_ForwardIterator result, forward_iterator_tag)
	{
		*result = *first;			// ��¼��һ��Ԫ��
		while (++first != last)		// �߷���������
									// ���£�Ԫ�ز�ͬ�����ٵ�¼������Ԫ����ͬ������������
			if (*result != *first) *++result = *first;
		return ++result;
	}

	// ���� output iterator Ϊ write only���޷��� forward iterator �ǰ���Զ�ȡ��
	// ���Բ��������� *result != *first �������ж϶��������Բ���Ҫ��ƴ�һ�汾��
	// ���磬ostream_iterator ����һ�� output iterator.
	template <class _InputIterator, class _OutputIterator, class _T>
	_OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, _T*) {
		// T Ϊ output iterator �� value type
		_T value = *first;
		*result = value;
		while (++first != last)
			if (value != *first) {
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	// �汾һ������ʽ��output_iterator_tag ��
	template <class _InputIterator, class _OutputIterator>
	inline _OutputIterator _unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		output_iterator_tag) {
		// ���£�output iterator��һЩ�������ƣ����Ա�����֪���� value type. 
		return _unique_copy(first, last, result, value_type(first));
	}

	// �汾һ
	template <class _InputIterator, class _OutputIterator>
	inline _OutputIterator unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result) {
		if (first == last) return result;
		// ���£�����result �� iterator category������ͬ�Ĵ���
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

	// �汾��
	template <class _InputIterator, class _OutputIterator, class _BinaryPredicate>
	inline _OutputIterator unique_copy(_InputIterator first, _InputIterator last,
		_OutputIterator result,
		_BinaryPredicate binary_pred) {
		if (first == last) return result;
		return _unique_copy(first, last, result, binary_pred,
			iterator_category(result));
	}

	// �汾һ
	template <class _ForwardIterator>
	_ForwardIterator unique(_ForwardIterator first, _ForwardIterator last) {
		first = adjacent_find(first, last);		// �����ҵ������ظ�Ԫ�ص����
		return unique_copy(first, last, first);		// ���� unique_copy ��ɡ�
	}

	// �汾��
	template <class _ForwardIterator, class _BinaryPredicate>
	_ForwardIterator unique(_ForwardIterator first, _ForwardIterator last,
		_BinaryPredicate binary_pred) {
		first = adjacent_find(first, last, binary_pred);
		return unique_copy(first, last, first, binary_pred);
	}

	// reverse �� bidirectional iterator ��
	template <class _BidirectionalIterator>
	void _reverse(_BidirectionalIterator first, _BidirectionalIterator last,
		bidirectional_iterator_tag) {
		while (true)
			if (first == last || first == --last)
				return;
			else
				iter_swap(first++, last);
	}

	// reverse �� random access iterator ��
	template <class _RandomAccessIterator>
	void _reverse(_RandomAccessIterator first, _RandomAccessIterator last,
		random_access_iterator_tag) {
		// ���£�ͷβ����������Ȼ��ͷ���۽�һ��λ�ã�β������һ��λ�á����߽���ʱ��ֹͣ��
		// ע�⣬���µ� first < last �ж϶�����ֻ������ random iterators. 
		while (first < last) iter_swap(first++, --last);
	}

	// ���ɺ�ʽ��dispatch function��
	template <class _BidirectionalIterator>
	inline void reverse(_BidirectionalIterator first, _BidirectionalIterator last) {
		_reverse(first, last, iterator_category(first));
	}

	template <class _BidirectionalIterator, class _OutputIterator>
	_OutputIterator reverse_copy(_BidirectionalIterator first,
		_BidirectionalIterator last,
		_OutputIterator result) {
		while (first != last) {	    // ����������һ��
			--last;				    // β��ǰ��һ��λ��
			*result = *last;		// ��β����ָԪ�ظ��Ƶ� result ��ָλ��
			++result;				// result ǰ��һ��λ��
		}
		return result;
	}

	// rotate �� forward iterator ��
	template <class _ForwardIterator, class _Distance>
	void __rotate(_ForwardIterator first, _ForwardIterator middle,
		_ForwardIterator last, _Distance*, forward_iterator_tag) {
		for (_ForwardIterator i = middle; ;) {
			iter_swap(first, i);	// ǰ�Ρ���ε�Ԫ��һһ����
			++first;				// ˫˫ǰ��1
			++i;
			// �����ж���ǰ��[first, middle)�Ƚ������Ǻ��[middle,last)�Ƚ���
			if (first == middle) {		// ǰ�ν�����
				if (i == last) return; 	// ������ͬʱҲ�����������ͽ����ˡ�
				middle = i;				// ������������µ�ǰ���������������
			}
			else if (i == last)	// ����Ƚ���
				i = middle;			// ������׼�����µ�ǰ���������������
		}
	}

	// rotate �� bidirectional iterator ��
	template <class _BidirectionalIterator, class _Distance>
	void __rotate(_BidirectionalIterator first, _BidirectionalIterator middle,
		_BidirectionalIterator last, _Distance*,
		bidirectional_iterator_tag) {
		reverse(first, middle);
		reverse(middle, last);
		reverse(first, last);
	}

	// ������ӣ�����շת�������
	// __gcd() Ӧ���� __rotate() �� random access iterator ��
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

	// rotate �� random access iterator ��
	template <class _RandomAccessIterator, class _Distance>
	void __rotate(_RandomAccessIterator first, _RandomAccessIterator middle,
		_RandomAccessIterator last, _Distance*,
		random_access_iterator_tag) {
		// ���µ����������������ֻ������ random access iterators
		// ȡȫ����ǰ�γ��ȵ�������ӡ�
		_Distance n = __gcd(last - first, middle - first);
		while (n--)
			__rotate_cycle(first, last, first + n, middle - first,
				value_type(first));
	}

	// ���ɺ�ʽ��dispatch function��
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
		RandomNumberGenerator& rand) { // ע�⣬by reference
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

	// ���б� pred �ж�Ϊ true ��Ԫ�أ������ŵ�ǰ�Σ�
	// ��pred �ж�Ϊ falise ��Ԫ�أ������ŵ���Ρ�
	// ����֤����ԭ���λ�á���not stable��
	template <class _BidirectionalIterator, class _Predicate>
	_BidirectionalIterator partition(_BidirectionalIterator first,
		_BidirectionalIterator last,
		_Predicate pred) {
		while (true) {
			while (true)
				if (first == last)		// ͷָ�����βָ��
					return first;			// ���ж���������
				else if (pred(*first))	// ͷָ����ָ��Ԫ�ط��ϲ���������
					++first;				// �����ƣ�ͷָ��ǰ��1
				else					// ͷָ����ָԪ�ط��ϰ�������
					break;				// ����ѭ��
			--last;					// βָ�����1
			while (true)
				if (first == last)		// ͷָ�����βָ��
					return first;			// ���ж���������
				else if (!pred(*last))	// βָ����ָ��Ԫ�ط��ϲ���������
					--last;				// �����ƣ�βָ�����1
				else					// βָ����ָԪ�ط��ϰ�������
					break;				// ����ѭ��
			iter_swap(first, last);		// ͷβָ����ָԪ�ر˴˽���
			++first;					// ͷָ��ǰ��1��׼����һ����ѭ������
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

	// �汾һ
	template <class _RandomAccessIterator, class _T>
	_RandomAccessIterator __unguarded_partition(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T pivot) {
		while (true) {

			while (*first < pivot) ++first;	// first �ҵ� >= pivot ��Ԫ�أ���ͣ����
			--last;						// ����
			while (pivot < *last) --last;	// last �ҵ� <= pivot ��Ԫ�أ���ͣ����
											// ע�⣬����first < last �ж϶�����ֻ������random iterator
			if (!(first < last)) return first;	// ��������ѭ����
			iter_swap(first, last);				// ��Сֵ����
			++first;							// ����
		}
	}

	// �汾��
	template <class _RandomAccessIterator, class _T, class _Compare>
	_RandomAccessIterator __unguarded_partition(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T pivot, _Compare comp) {
		while (1) {
			while (comp(*first, pivot)) ++first;
			--last;
			while (comp(pivot, *last)) --last;
			// ע�⣬���µ�first < last �ж϶�����ֻ������random iterator
			if (!(first < last)) return first;
			iter_swap(first, last);
			++first;
		}
	}

	const int __stl_threshold = 16;


	// �汾һ
	template <class _RandomAccessIterator, class _T>
	void __unguarded_linear_insert(_RandomAccessIterator last, _T value) {
		_RandomAccessIterator next = last;
		--next;
		// insertion sort ����ѭ��
		// ע�⣬һ����������ת�ԣ�inversion����ѭ���Ϳ��Խ����ˡ�
		while (value < *next) {	// ��ת�ԣ�inversion������
			*last = *next;		// ת��
			last = next;			// ����������
			--next;				// ǰ��һ��λ��
		}
		*last = value;
	}

	// �汾��
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

	// �汾һ
	template <class _RandomAccessIterator, class _T>
	inline void __linear_insert(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*) {
		_T value = *last;		// ��¼βԪ��
		if (value < *first) {	// β��ͷ��С���Ǿͱ�һ�����Ƚ��ˣ�һ�����ꡭ��
			copy_backward(first, last, last + 1); // ��������Χ���ҵ���һ��λ��
			*first = value;		// ��ͷԪ�ص���ԭ�ȵ�βԪ��ֵ
		}
		else
			__unguarded_linear_insert(last, value);
	}

	// �汾��
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

	// �汾һ
	template <class _RandomAccessIterator>
	void __insertion_sort(_RandomAccessIterator first, _RandomAccessIterator last) {
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)  // ��ѭ��
			__linear_insert(first, i, value_type(first));	// first,i�γ�һ���ӷ�Χ
	}

	// �汾��
	template <class _RandomAccessIterator, class _Compare>
	void __insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last, _Compare comp) {
		if (first == last) return;
		for (_RandomAccessIterator i = first + 1; i != last; ++i)
			__linear_insert(first, i, value_type(first), comp);
	}

	// �汾һ
	template <class _RandomAccessIterator, class _T>
	void __unguarded_insertion_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*) {
		for (_RandomAccessIterator i = first; i != last; ++i)
			__unguarded_linear_insert(i, _T(*i));
	}

	// �汾һ
	template <class _RandomAccessIterator>
	inline void __unguarded_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last) {
		__unguarded_insertion_sort_aux(first, last, value_type(first));
	}

	// �汾��
	template <class _RandomAccessIterator, class _T, class _Compare>
	void __unguarded_insertion_sort_aux(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_T*, _Compare comp) {
		for (_RandomAccessIterator i = first; i != last; ++i)
			__unguarded_linear_insert(i, _T(*i), comp);
	}

	// �汾��
	template <class _RandomAccessIterator, class _Compare>
	inline void __unguarded_insertion_sort(_RandomAccessIterator first,
		_RandomAccessIterator last,
		_Compare comp) {
		__unguarded_insertion_sort_aux(first, last, value_type(first), comp);
	}

	// �汾һ
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

	// �汾��
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

	// �ҳ� 2^k <= n �����ֵk������n=7����k=2��n=20����k=4��n=8����k=3��
	template <class _Size>
	inline _Size __lg(_Size n) {
		_Size k;
		for (k = 0; n > 1; n >>= 1) ++k;
		return k;
	}

	// �汾һ
	// ע�⣬����ʽ�ڵ������������㶯������ֻ������RandomAccess Iterators.
	template <class _RandomAccessIterator, class _T, class _Size>
	void __introsort_loop(_RandomAccessIterator first,
		_RandomAccessIterator last, _T*,
		_Size depth_limit) {
		// ���£�__stl_threshold �Ǹ�ȫ�ֳ��������綨��Ϊ const int 16��
		while (last - first > __stl_threshold) {
			if (depth_limit == 0) {				// ���ˣ��и��
				partial_sort(first, last, last);	// ���� heapsort
				return;
			}
			--depth_limit;
			// ������ median-of-three partition��ѡ��һ�����õ����Ტ�����и�㡣
			// �и�㽫���ڵ����� cut ���ϡ�
			_RandomAccessIterator cut = __unguarded_partition
			(first, last, _T(_median(*first, *(first + (last - first) / 2),
				*(last - 1))));
			// ���Ұ�εݹ���� sort.
			__introsort_loop(cut, last, value_type(first), depth_limit);
			last = cut;
			// ���ڻص�while ѭ����׼�������εݹ���� sort.
			// ����д���ɶ��ԽϲЧ�ʲ�û�бȽϺá�
			// RW STL ����һ��̿���д����ֱ�۵ض����κ��Ұ�εݹ飩�������Ķ���
		}
	}

	// �汾��
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

	// �汾һ
	// ǧ��ע�⣺sort()ֻ������ RandomAccessIterator
	template <class _RandomAccessIterator>
	inline void sort(_RandomAccessIterator first, _RandomAccessIterator last) {
		if (first != last) {
			__introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
			__final_insertion_sort(first, last);
		}
	}

	// �汾��
	// ǧ��ע�⣺sort()ֻ������ RandomAccessIterator
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
		// ע�⣬���µ�last-first < 15 �ж϶�����ֻ������random iterator
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
		// ע�⣬���µ�last-first < 15 �ж϶�����ֻ������random iterator
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
		// ע�⣬���µ�i < last �ж϶�����ֻ������random iterator
		for (_RandomAccessIterator i = middle; i < last; ++i)
			if (*i < *first)
				__pop_heap(first, middle, i, _T(*i), distance_type(first));
		sort_heap(first, middle);
	}

	// �汾һ
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
		// ע�⣬���µ�i < last �ж϶�����ֻ������random iterator
		for (_RandomAccessIterator i = middle; i < last; ++i)
			if (comp(*i, *first))
				__pop_heap(first, middle, i, _T(*i), comp, distance_type(first));
		sort_heap(first, middle, comp);
	}

	// �汾��
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

	// �汾һ
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

	// �汾��
	template <class _InputIterator, class _RandomAccessIterator, class _Compare>
	inline _RandomAccessIterator
		partial_sort_copy(_InputIterator first, _InputIterator last,
			_RandomAccessIterator result_first,
			_RandomAccessIterator result_last, _Compare comp) {
		return __partial_sort_copy(first, last, result_first, result_last, comp,
			distance_type(result_first), value_type(first));
	}

	// �汾һ������ʽ
	template <class _RandomAccessIterator, class _T>
	void __nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last, _T*) {
		while (last - first > 3) {	// ���ȳ���3
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

	// �汾һ
	template <class _RandomAccessIterator>
	inline void nth_element(_RandomAccessIterator first, _RandomAccessIterator nth,
		_RandomAccessIterator last) {
		__nth_element(first, nth, last, value_type(first));
	}

	// �汾��������ʽ
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

	// ���ǰ汾һ�� forward_iterator �汾
	template <class _ForwardIterator, class _T, class _Distance>
	_ForwardIterator __lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);	// ��ȡ������Χ�ĳ��� len
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;			// ����2
			middle = first;			// ��������middle ָ���м�λ��
			advance(middle, half);
			if (*middle < value) {		// ����м�λ�õ�Ԫ��ֵ < Ŀ��ֵ
				first = middle;			// �������� first ָ�� middle ����һλ��
				++first;
				len = len - half - 1;		// ���� len����ͷ����ѭ���Ľ�������
			}
			else
				len = half;				// ���� len����ͷ����ѭ���Ľ�������
		}
		return first;
	}

	// ���ǰ汾һ�� random_access_iterator �汾
	template <class _RandomAccessIterator, class _T, class _Distance>
	_RandomAccessIterator __lower_bound(_RandomAccessIterator first,
		_RandomAccessIterator last, const _T& value,
		_Distance*, random_access_iterator_tag) {
		_Distance len = last - first;	// ��ȡ������Χ�ĳ��� len
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;			// ����2
			middle = first + half;		// ��middle ָ���м�λ��
			if (*middle < value) {		// ����м�λ�õ�Ԫ��ֵ < Ŀ��ֵ
				first = middle + 1;		// �� first ָ�� middle ����һλ��
				len = len - half - 1;		// ���� len����ͷ����ѭ���Ľ�������
			}
			else
				len = half;				// ���� len����ͷ����ѭ���Ľ�������
		}
		return first;
	}

	// ���ǰ汾һ
	template <class _ForwardIterator, class _T>
	inline _ForwardIterator lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		return __lower_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// ���ǰ汾���� forward_iterator �汾
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

	// ���ǰ汾���� random_access_iterator �汾
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

	// ���ǰ汾��
	template <class _ForwardIterator, class _T, class _Compare>
	inline _ForwardIterator lower_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp) {
		return __lower_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// ���ǰ汾һ�� forward_iterator �汾
	template <class _ForwardIterator, class _T, class _Distance>
	_ForwardIterator __upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Distance*,
		forward_iterator_tag) {
		_Distance len = 0;
		distance(first, last, len);	// ��ȡ������Χ�ĳ��� len
		_Distance half;
		_ForwardIterator middle;

		while (len > 0) {
			half = len >> 1;			// ����2
			middle = first;			// ��������middle ָ���м�λ��
			advance(middle, half);
			if (value < *middle)		// ����м�λ�õ�Ԫ��ֵ > Ŀ��ֵ
				len = half;				// ���� len����ͷ����ѭ���Ľ�������
			else {
				first = middle;			// �������� first ָ�� middle ����һλ��
				++first;
				len = len - half - 1;		// ���� len����ͷ����ѭ���Ľ�������
			}
		}
		return first;
	}

	// ���ǰ汾һ�� random_access_iterator �汾
	template <class _RandomAccessIterator, class _T, class _Distance>
	_RandomAccessIterator __upper_bound(_RandomAccessIterator first,
		_RandomAccessIterator last, const _T& value,
		_Distance*, random_access_iterator_tag) {
		_Distance len = last - first;	// ��ȡ������Χ�ĳ��� len
		_Distance half;
		_RandomAccessIterator middle;

		while (len > 0) {
			half = len >> 1;			// ����2
			middle = first + half;		// ��middle ָ���м�λ��
			if (value < *middle)		// ����м�λ�õ�Ԫ��ֵ > Ŀ��ֵ
				len = half;				// ���� len����ͷ����ѭ���Ľ�������
			else {
				first = middle + 1;		// �� first ָ�� middle ����һλ��
				len = len - half - 1;		// ���� len����ͷ����ѭ���Ľ�������
			}
		}
		return first;
	}

	// ���ǰ汾һ
	template <class _ForwardIterator, class _T>
	inline _ForwardIterator upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		return __upper_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// ���ǰ汾���� forward_iterator �汾
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

	// ���ǰ汾���� random_access_iterator �汾
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

	// ���ǰ汾��
	template <class _ForwardIterator, class _T, class _Compare>
	inline _ForwardIterator upper_bound(_ForwardIterator first, _ForwardIterator last,
		const _T& value, _Compare comp) {
		return __upper_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// �汾һ�� forward_iterator �汾
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

	// �汾һ�� random_access_iterator �汾
	template <class _RandomAccessIterator, class _T, class _Distance>
	pair<_RandomAccessIterator, _RandomAccessIterator>
		__equal_range(_RandomAccessIterator first, _RandomAccessIterator last,
			const _T& value, _Distance*, random_access_iterator_tag) {
		_Distance len = last - first;
		_Distance half;
		_RandomAccessIterator middle, left, right;

		while (len > 0) {		// ����������δ�߷����
			half = len >> 1;		// �ҳ�����λ��
			middle = first + half;	// �趨���������
			if (*middle < value) {	// �������Ԫ�� < ָ��ֵ
				first = middle + 1;	// ������������С���������Σ��������Ч��
				len = len - half - 1;
			}
			else if (value < *middle)	// �������Ԫ�� > ָ��ֵ
				len = half;				// ������������С������ǰ��Σ������Ч��
			else {		// �������Ԫ�� == ָ��ֵ
						// ��ǰ����� lower_bound
				left = lower_bound(first, middle, value);
				// �ں����� lower_bound
				right = upper_bound(++middle, first + len, value);
				return pair<_RandomAccessIterator, _RandomAccessIterator>(left, right);
			}
		}
		// ���������ڶ�û���Ǻϵ�ֵ����ôӦ�ô���һ�Ե�������ָ���һ������value ��Ԫ�ء�
		return pair<_RandomAccessIterator, _RandomAccessIterator>(first, first);
	}

	// �汾һ
	template <class _ForwardIterator, class _T>
	inline pair<_ForwardIterator, _ForwardIterator>
		equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value) {
		// ���ݵ������������ͣ�category�������ò�ͬ�Ĳ��ԡ�
		return __equal_range(first, last, value, distance_type(first),
			iterator_category(first));
	}

	// �汾���� forward_iterator �汾
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

	// �汾���� random_access_iterator �汾
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

	// �汾��
	template <class _ForwardIterator, class _T, class _Compare>
	inline pair<_ForwardIterator, _ForwardIterator>
		equal_range(_ForwardIterator first, _ForwardIterator last, const _T& value,
			_Compare comp) {
		return __equal_range(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}

	// �汾һ
	template <class _ForwardIterator, class _T>
	bool binary_search(_ForwardIterator first, _ForwardIterator last,
		const _T& value) {
		_ForwardIterator i = lower_bound(first, last, value);
		return i != last && !(value < *i);
	}

	// �汾��
	template <class _ForwardIterator, class _T, class _Compare>
	bool binary_search(_ForwardIterator first, _ForwardIterator last, const _T& value,
		_Compare comp) {
		_ForwardIterator i = lower_bound(first, last, value, comp);
		return i != last && !comp(value, *i);
	}

	// �汾һ
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator merge(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		while (first1 != last1 && first2 != last2) { // �������ж���δ����
			if (*first2 < *first1) {	// ���ж���Ԫ�رȽ�С
				*result = *first2;		// �Ǽ����ж���Ԫ��
				++first2;				// ���ж�ǰ��1
			}
			else {					// ���ж���Ԫ�ز��Ƚ�С
				*result = *first1;		// �Ǽ�����һ��Ԫ��
				++first1;				// ����һǰ��1
			}
			++result;
		}
		// ���ʣ��Ԫ���� copy ���Ƶ�Ŀ�Ķˡ�������������һ��������һ��Ϊ�ա�
		return copy(first2, last2, copy(first1, last1, result));
	}

	// �汾��
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator,
		class _Compare>
		_OutputIterator merge(_InputIterator1 first1, _InputIterator1 last1,
			_InputIterator2 first2, _InputIterator2 last2,
			_OutputIterator result, _Compare comp) {
		while (first1 != last1 && first2 != last2) { // �������ж���δ����
			if (comp(*first2, *first1)) {	// �Ƚ������е�Ԫ��
				*result = *first2;			// �Ǽ����ж���Ԫ��
				++first2;					// ���ж�ǰ��1
			}
			else {
				*result = *first1;			// �Ǽ�����һ��Ԫ��
				++first1;					// ����һǰ��1
			}
			++result;
		}
		// ���ʣ��Ԫ���� copy ���Ƶ�Ŀ�Ķˡ�������������һ��������һ��Ϊ�ա�
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
			// �������㹻�������ж����϶̣�
			buffer_end = copy(middle, last, buffer);
			copy_backward(first, middle, last);
			return copy(buffer, buffer_end, first);
		}
		else if (len1 <= buffer_size) {
			// �������㹻��������һ
			buffer_end = copy(first, middle, buffer);
			copy(middle, last, first);
			return copy_backward(buffer, buffer_end, last);
		}
		else {
			// ��������Ȼ����. ���� rotate �㷨�����軺������
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

	// �汾һ�ĸ�����ʽ���л�����������¡�
	template <class _BidirectionalIterator, class _Distance, class _Pointer>
	void __merge_adaptive(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_Distance len1, _Distance len2,
		_Pointer buffer, _Distance buffer_size) {
		if (len1 <= len2 && len1 <= buffer_size) {
			// case1. �������㹻��������һ
			_Pointer end_buffer = copy(first, middle, buffer);
			merge(buffer, end_buffer, middle, last, first);
		}
		else if (len2 <= buffer_size) {
			// case 2. �������㹻�������ж�
			_Pointer end_buffer = copy(middle, last, buffer);
			__merge_backward(first, middle, buffer, end_buffer, last);
		}
		else {		// case3.  �������ռ䲻�㰲���κ�һ������
			_BidirectionalIterator first_cut = first;
			_BidirectionalIterator second_cut = middle;
			_Distance len11 = 0;
			_Distance len22 = 0;
			if (len1 > len2) { 	// ����һ�Ƚϳ�
				len11 = len1 / 2;
				advance(first_cut, len11);
				second_cut = lower_bound(middle, last, *first_cut);
				distance(middle, second_cut, len22);
			}
			else {				// ���ж��Ƚϲ���
				len22 = len2 / 2; 	// �������ж���һ�볤��
				advance(second_cut, len22);
				first_cut = upper_bound(first, middle, *second_cut);
				distance(first, first_cut, len11);
			}
			_BidirectionalIterator new_middle =
				__rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
					len22, buffer, buffer_size);
			// �����Σ��ݹ���á�
			__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
				buffer_size);
			// ����ҶΣ��ݹ���á�
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

	// �汾һ�ĸ�����ʽ
	template <class _BidirectionalIterator, class _T, class _Distance>
	inline void __inplace_merge_aux(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last,
		_T*, _Distance*) {
		_Distance len1 = 0;
		distance(first, middle, len1);	// len1 ��ʾ����һ�ĳ���
		_Distance len2 = 0;
		distance(middle, last, len2);		// len2 ��ʾ���ж��ĳ���

											// ע�⣬���㷨��ʹ�ö�����ڴ�ռ䣨��ʱ��������
		temporary_buffer<_BidirectionalIterator, _T> buf(first, last);
		if (buf.begin() == 0) 	// �ڴ�����ʧ��
			__merge_without_buffer(first, middle, last, len1, len2);
		else		// ������ʱ������������½���
			__merge_adaptive(first, middle, last, len1, len2,
				buf.begin(), _Distance(buf.size()));
	}

	// �汾���ĸ�����ʽ
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

	// �汾һ���ϲ���ȡ������д��
	template <class _BidirectionalIterator>
	inline void inplace_merge(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last) {
		// ֻҪ���κ�һ������Ϊ�գ���ʲô����������
		if (first == middle || middle == last) return;
		__inplace_merge_aux(first, middle, last, value_type(first),
			distance_type(first));
	}

	// �汾�����ϲ���ȡ������д��
	template <class _BidirectionalIterator, class _Compare>
	inline void inplace_merge(_BidirectionalIterator first,
		_BidirectionalIterator middle,
		_BidirectionalIterator last, _Compare comp) {
		if (first == middle || middle == last) return;
		__inplace_merge_aux(first, middle, last, value_type(first),
			distance_type(first), comp);
	}

	// �汾һ���ж��������ÿ��Ԫ��ֵ�Ƿ񶼴���������һ��
	// ǰ�᣺����һ����������� sorted ranges. 
	template <class _InputIterator1, class _InputIterator2>
	bool includes(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2) {
		while (first1 != last1 && first2 != last2) // �������䶼��δ����
			if (*first2 < *first1)		// ���ж���Ԫ��С������һ��Ԫ��
				return false;			  // �����ǡ��������Ȼ������
			else if (*first1 < *first2) 	// ���ж���Ԫ�ش�������һ��Ԫ��
				++first1;				  //����һǰ��1
			else						// *first1 == *first2
				++first1, ++first2;		  // �����и���ǰ��1

		return first2 == last2;	// ��һ�����������ˣ��ж����һ��
	}

	// �汾�����ж�����һ���Ƿ��и������У��������ж���ÿ����ӦԪ�ض������Ԫ���� comp��
	// ǰ�᣺����һ�����ж����� sorted ranges. 
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

	// �������������[first1,last1) ������� [first2,last2) ������Ԫ�ء�
	// ע�⣬set ��һ�� sorted range�����������㷨��ǰ�ᡣ
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_union(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// ���������䶼��Ϊ�հ�����ʱ��ִ�����¶�����
		while (first1 != last1 && first2 != last2) {
			// ���������ڷֱ��ƶ������������Ƚ�Ԫ��ֵ��С�ߣ�����ΪA������¼��Ŀ������
			// Ȼ���ƶ�A��������ʹ֮ǰ����ͬʱ��֮��һ����������������Ȼ���ٽ���
			// ��һ�εıȴ�С����¼Сֵ���������ƶ�����ֱ����������һ��Ϊ�հס�
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

		// ֻҪ��������һ����Ϊ�հף��ͽ��������� while ѭ����
		// ���½�ʣ��ģ��ǿհ׵ģ����������Ԫ�ؿ�����Ŀ�Ķˡ�
		// �˿̵� [first1,last1)��[first2,last2)֮����һ���ǿհ����䡣
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

	// �������������[first1,last1) �Ҵ����� [first2,last2) ������Ԫ�ء�
	// ע�⣬set ��һ�� sorted range�����������㷨��ǰ�ᡣ
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_intersection(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// ���������䶼��Ϊ�հ�����ʱ��ִ�����¶�����
		while (first1 != last1 && first2 != last2)
			// ���������ڷֱ��ƶ���������ֱ������Ԫ��ֵ��ͬ����ͣ������ֵ��¼��Ŀ������
			// �ټ����ƶ�����������ֱ����������һ��Ϊ�հס�
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

	// ����������[first1,last1) �Ҳ������� [first2,last2) ������Ԫ�ء�
	// ע�⣬set ��һ�� sorted range�����������㷨��ǰ�ᡣ
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_difference(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_OutputIterator result) {
		// ���������䶼��Ϊ�հ�����ʱ��ִ�����¶�����
		while (first1 != last1 && first2 != last2)
			// ���������ڷֱ��ƶ�������������һ�����Ԫ�ص��ڵڶ������Ԫ�أ���ʾ��ֵ
			// ͬʱ����������������������ͬʱǰ��������һ�����Ԫ�ش��ڵڶ������Ԫ�أ�
			// ���õڶ�����ǰ�������������ִ����ͱ�֤����һ�����Ԫ��С�ڵڶ������
			// Ԫ��ʱ����һ�����Ԫ��ֻ�����ڵ�һ�����У��������ڵڶ����䡣���ǽ���
			// ��¼��Ŀ������
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

	// �ԳƲ���������[first1,last1) �Ҳ������� [first2,last2) ������Ԫ�أ�
	// �Լ�������[first2,last2) �Ҳ������� [first1,last1) ������Ԫ�ء� 
	// ע�⣬��������ֻ���ڡ�Ԫ��ֵ��һ�޶���������²ų���������� set һ�㻯��
	// ��������ظ�Ԫ�أ���ô set-symmetric-difference �Ķ���Ӧ���ǣ�
	// ���ĳֵ��[first1,last1) ����n�Σ��� [first2,last2) ����m�Σ�
	// ��ô���� result range ��Ӧ�ó��� abs(n-m) �Ρ�
	// ע�⣬set ��һ�� sorted range�����������㷨��ǰ�ᡣ
	template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
	_OutputIterator set_symmetric_difference(_InputIterator1 first1,
		_InputIterator1 last1,
		_InputIterator2 first2,
		_InputIterator2 last2,
		_OutputIterator result) {
		// ���������䶼��Ϊ�հ�����ʱ��ִ�����¶�����
		while (first1 != last1 && first2 != last2)
			// ���������ڷֱ��ƶ������������������ڵĵ�ֵԪ����ȣ���������ͬʱǰ����
			// ���������ڵĵ�ֵԪ�ز��ȣ��ͼ�¼��Сֵ��Ŀ�����������Сֵ��������ǰ����
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

	// �汾һ
	template <class _ForwardIterator>
	_ForwardIterator max_element(_ForwardIterator first, _ForwardIterator last) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (*result < *first) result = first;
		return result;
	}

	// �汾��
	template <class _ForwardIterator, class _Compare>
	_ForwardIterator max_element(_ForwardIterator first, _ForwardIterator last,
		_Compare comp) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (comp(*result, *first)) result = first;
		return result;
	}

	// �汾һ
	template <class _ForwardIterator>
	_ForwardIterator min_element(_ForwardIterator first, _ForwardIterator last) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (*first < *result) result = first;
		return result;
	}

	// �汾��
	template <class _ForwardIterator, class _Compare>
	_ForwardIterator min_element(_ForwardIterator first, _ForwardIterator last,
		_Compare comp) {
		if (first == last) return first;
		_ForwardIterator result = first;
		while (++first != last)
			if (comp(*first, *result)) result = first;
		return result;
	}

	// �汾һ
	template <class _BidirectionalIterator>
	bool next_permutation(_BidirectionalIterator first,
		_BidirectionalIterator last) {
		if (first == last) return false;	// �շ�Χ
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// ֻ��һ��Ԫ��
		i = last;	// i ָ��β��
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// ���ϣ�����һ�飨����������Ԫ��
			if (*i < *ii) {	// ���ǰһ��Ԫ��С�ں�һ��Ԫ��
				_BidirectionalIterator j = last;		// �� jָ��β��
				while (!(*i < *--j));	  	// ��β����ǰ�ң�ֱ�����ϱ� *i ���Ԫ��
				iter_swap(i, j);			// ���� i, j
				reverse(ii, last);		// �� ii ֮���Ԫ��ȫ����������
				return true;
			}
			if (i == first) {			// ��������ǰ����
				reverse(first, last);		// ȫ����������
				return false;
			}
		}
	}

	// �汾��
	template <class _BidirectionalIterator, class _Compare>
	bool next_permutation(_BidirectionalIterator first, _BidirectionalIterator last,
		_Compare comp) {
		if (first == last) return false;	// �շ�Χ
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// ֻ��һ��Ԫ��
		i = last;	// i ָ��β��
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// ���ϣ�����һ�飨����������Ԫ��
			if (comp(*i, *ii)) {	// ���ǰһ��Ԫ�����һ��Ԫ������ comp ����
				_BidirectionalIterator j = last;		// �� jָ��β��
				while (!comp(*i, *--j));	// ��β����ǰ�ң�ֱ�����Ϸ���������Ԫ��
				iter_swap(i, j);			// ���� i, j
				reverse(ii, last);		// �� ii ֮���Ԫ��ȫ����������
				return true;
			}
			if (i == first) {			// ��������ǰ����
				reverse(first, last);		// ȫ����������
				return false;
			}
		}
	}

	// �汾һ
	template <class _BidirectionalIterator>
	bool prev_permutation(_BidirectionalIterator first,
		_BidirectionalIterator last) {
		if (first == last) return false;	// �շ�Χ
		_BidirectionalIterator i = first;
		++i;
		if (i == last) return false;		// ֻ��һ��Ԫ��
		i = last;	// i ָ��β��
		--i;

		for (;;) {
			_BidirectionalIterator ii = i;
			--i;
			// ���ϣ�����һ�飨����������Ԫ��
			if (*ii < *i) {	// ���ǰһ��Ԫ�ش��ں�һ��Ԫ��
				_BidirectionalIterator j = last;		// �� jָ��β��
				while (!(*--j < *i));		// ��β����ǰ�ң�ֱ�����ϱ� *i С��Ԫ��
				iter_swap(i, j);			// ���� i, j
				reverse(ii, last);		// �� ii ֮���Ԫ��ȫ����������
				return true;
			}
			if (i == first) {			// ��������ǰ����
				reverse(first, last);		// ȫ����������
				return false;
			}
		}
	}

	// �汾��
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

	// �汾һ
	template <class _InputIterator, class _ForwardIterator>
	_InputIterator find_first_of(_InputIterator first1, _InputIterator last1,
		_ForwardIterator first2, _ForwardIterator last2)
	{
		for (; first1 != last1; ++first1) // �������һ
										  // ���£��������ж���ÿ��Ԫ��
			for (_ForwardIterator iter = first2; iter != last2; ++iter)
				if (*first1 == *iter)	// �������һ��Ԫ�ص������ж���Ԫ��
					return first1;		// �ҵ��ˣ�������
		return last1;
	}

	// �汾��
	template <class _InputIterator, class _ForwardIterator, class _BinaryPredicate>
	_InputIterator find_first_of(_InputIterator first1, _InputIterator last1,
		_ForwardIterator first2, _ForwardIterator last2,
		_BinaryPredicate comp)
	{
		for (; first1 != last1; ++first1) // �������һ
										  // ���£��������ж���ÿ��Ԫ��
			for (_ForwardIterator iter = first2; iter != last2; ++iter)
				if (comp(*first1, *iter)) // �������һ�����ж���Ԫ������comp ����
					return first1;			// �ҵ��ˣ�������
		return last1;
	}


	// ��Ѱ[first1, last1) �е������� [first2, last2) �������ֵ�
	// ������forward iterators ��
	template <class _ForwardIterator1, class _ForwardIterator2>
	_ForwardIterator1 __find_end(_ForwardIterator1 first1, _ForwardIterator1 last1,
		_ForwardIterator2 first2, _ForwardIterator2 last2,
		forward_iterator_tag, forward_iterator_tag)
	{
		if (first2 == last2)		// �����ѰĿ���ǿյģ�
			return last1;			// ���� last1 ��ʾ�á��������С��������ֵ�
		else {
			_ForwardIterator1 result = last1;
			while (1) {
				// ��������search()��Ѱĳ�������е��״γ��ֵ㡣�Ҳ����Ļ�����last1
				_ForwardIterator1 new_result = search(first1, last1, first2, last2);
				if (new_result == last1)	// û�ҵ�
					return result;
				else {
					result = new_result;		// ����һ�±����׼����һ����Ѱ�ж�
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

	// ������bidirectional iterators �棬���õ�partial specialization.
	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator1
		__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			bidirectional_iterator_tag, bidirectional_iterator_tag)
	{
		// ������Ѱ���ǡ������ֵص㡹����˷�����Ѱ�ȽϿ졣����reverse_iterator.
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter2 rlast2(first2);
		// ��Ѱʱ�����к�������ͳͳ��ת����
		reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);

		if (rresult == rlast1)	// û�ҵ�
			return last1;
		else {					// �ҵ���
			BidirectionalIterator1 result = rresult.base(); // ת�������������򣩵�����
			advance(result, -distance(first2, last2));	 // �����ص������е���ͷ��
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


	// ���ɺ�ʽ��Dispatching functions�� 
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
