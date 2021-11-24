/*
 * �����㷨
 */
#ifndef ALGOBASE_H_
#define ALGOBASE_H_

#include "pair.h"
#include "type_traits.h"
#include "iterator.h"
#include <string>
#include <climits>
#include <cstdlib>
#include <cstddef>
#include <new>
#include <iostream>

namespace MyStl
{
	// iter_swap() �ǡ��б�Ҫ���õ�����֮ value type����һ�������ӡ�
	// �ǵģ�������֪���������� value type�����ܹ��ݴ�����һ����������
	// ��ʱ���õ�������ָ�Ķ���
	template <class _ForwardIterator1, class _ForwardIterator2, class _T>
	inline void _iter_swap(_ForwardIterator1 a, _ForwardIterator2 b, _T*) {
		_T tmp = *a;
		*a = *b;
		*b = tmp;
	}
	//����������������ָ�Ķ���
	template <class _ForwardIterator1, class _ForwardIterator2>
	inline void iter_swap(_ForwardIterator1 a, _ForwardIterator2 b) 
	{
		
		_iter_swap(a, b, value_type(a));;
	}

	//������Ԫ��ֵ
	template <class _T>
	inline void swap(_T& a, _T& b)
	{
		_T tmp = a;
		a = b;
		b = tmp;
	}

	//ȡ�������н�С��/�ϴ���
	//���ʱͳһȡǰ��
	template <class _T>
	inline const _T& min(const _T& a, const _T& b)
	{
		return b < a ? b : a;
	}
	template <class _T>
	inline const _T& max(const _T& a, const _T& b)
	{
		return  a < b ? b : a;
	}
	template <class _T, class _Compare>
	inline const _T& min(const _T& a, const _T& b, _Compare comp)
	{
		return comp(b, a) ? b : a;	// �� comp ��������С�Ƚϡ���׼
	}
	template <class _T, class _Compare>
	inline const _T& max(const _T& a, const _T& b, _Compare comp)
	{
		return comp(a, b) ? b : a;	// �� comp ��������С�Ƚϡ���׼
	}

	//������copy��ʵ�֣�

	//���input_iterator��forward_iterator��bidirectional_iterator
	template <class _InputIterator, class _OutputIterator>
	inline
		_OutputIterator _copy(_InputIterator first, _InputIterator last,
		_OutputIterator result, input_iterator_tag)
	{
		//�Ƚϵ���������ѭ���Ƿ�������ٶ���
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	}
	
	template <class _RandomAccessIterator, class _OutputIterator, class _Distance>
	inline
		_OutputIterator _copy_d(_RandomAccessIterator first, _RandomAccessIterator last, 
			_OutputIterator result, _Distance*)
	{
		//�Ե���������n����ѭ���Ƿ����ִ�У��ٶȿ�
		for (_Distance n = last - first; n > 0; --n, ++result, ++first)
			*result = *first;
		return result;
	}
	//���random_access_iterator
    //�������溯��
	template <class _RandomAccessIterator, class _OutputIterator>
	inline 
		_OutputIterator _copy(_RandomAccessIterator first, _RandomAccessIterator last,
			_OutputIterator result, random_access_iterator_tag)
	{
		return _copy_d(first, last, result, distance_type(first));
	}
	//������_copy_dispatch
	template <class _InputIterator, class _OutputIterator>
	struct _copy_dispatch
	{
		_OutputIterator operator()(_InputIterator first, _InputIterator last,
			_OutputIterator result) 
		{
			return _copy(first, last, result, iterator_category(first));
		}
	};
	//�ػ��汾һ��ָ����ָ������ ƽ����ֵ�����
	template <class _T>
	inline 
		_T* _copy_t(const _T* first, const _T* last, _T* result, __true_type)
	{
		memmove(result, first, sizeof(_T) * (last - first));
		return result + (last - first);
	}
	//�ػ��汾����ָ����ָ������ ��ƽ����ֵ�����
	template <class _T>
	inline 
		_T* _copy_t(const _T* first, const _T* last, _T* result, __false_type)
	{
		return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	template <class _T>
	struct _copy_dispatch<_T*, _T*>
	{
		_T* operator()(_T* first, _T* last, _T* result) 
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};

	template <class _T>
	struct _copy_dispatch<const _T*, _T*>
	{
		_T* operator()(const _T* first, const _T* last, _T* result)
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};


	// copy ��ʽ������ function overloading, type traits, partial 
	// specialization, ���������伫�ظ���Ч�ʡ�
	//�����ӿڣ�
	template <class _InputIterator, class _OutputIterator>
	inline 
		_OutputIterator copy(_InputIterator first, _InputIterator last,
		_OutputIterator result)
	{
		return _copy_dispatch<_InputIterator, _OutputIterator>()(first, last, result);
	}
	//�ػ��ӿڣ�����memmove()����ʵ��copy
	inline 
		char* copy(const char* first, const char* last, char* result) 
	{
		memmove(result, first, last - first);
		return result + (last - first);
	}
	//�ػ��ӿڣ�����memmove()����ʵ��copy
	inline
		wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last - first);
	}

	//������copy_backward��ʵ�֣�
	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	inline _BidirectionalIterator2 _copy_backward(_BidirectionalIterator1 first,
		_BidirectionalIterator1 last,
		_BidirectionalIterator2 result) {
		while (first != last) *--result = *--last;
		return result;
	}

	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	struct _copy_backward_dispatch
	{
		_BidirectionalIterator2 operator()(_BidirectionalIterator1 first,
			_BidirectionalIterator1 last,
			_BidirectionalIterator2 result) {
			return _copy_backward(first, last, result);
		}
	};

	template <class _T>
	inline 
		_T* _copy_backward_t(const _T* first, const _T* last, _T* result,
		__true_type)
	{
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(_T) * N);
		return result - N;
	}

	template <class _T>
	inline
		_T* _copy_backward_t(const _T* first, const _T* last, _T* result,
		__false_type)
	{
		return _copy_backward(first, last, result);
	}

	template <class _T>
	struct _copy_backward_dispatch<_T*, _T*>
	{
		_T* operator()(_T* first, _T* last, _T* result)
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	template <class _T>
	struct _copy_backward_dispatch<const _T*, _T*>
	{
		_T* operator()(const _T* first, const _T* last, _T* result) 
		{
			typedef typename __type_traits<_T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//copy_backward�ӿڣ�
	template <class _BidirectionalIterator1, class _BidirectionalIterator2>
	inline _BidirectionalIterator2 copy_backward(_BidirectionalIterator1 first,
		_BidirectionalIterator1 last,
		_BidirectionalIterator2 result)
	{
		return _copy_backward_dispatch<_BidirectionalIterator1,
			_BidirectionalIterator2>()(first, last, result);
	}

	//������copy_n��ʵ�֣�
	template <class _InputIterator, class _Size, class _OutputIterator>
	pair<_InputIterator, _OutputIterator> _copy_n(_InputIterator first, _Size count,
		_OutputIterator result,
		input_iterator_tag)
	{
		for (; count > 0; --count, ++first, ++result)
			*result = *first;
		return pair<_InputIterator, _OutputIterator>(first, result);
	}

	template <class _RandomAccessIterator, class _Size, class _OutputIterator>
	inline pair<_RandomAccessIterator, _OutputIterator>
		_copy_n(_RandomAccessIterator first, _Size count,
			_OutputIterator result,
			random_access_iterator_tag)
	{
		_RandomAccessIterator last = first + count;
		return pair<_RandomAccessIterator, _OutputIterator>
			(last, copy(first, last, result));
	}

	//copy_n�ӿڣ�
	//�� first ��ʼ���� count ��Ԫ�ص� result �Ժ�Ŀռ䡣
	template <class _InputIterator, class _Size, class _OutputIterator>
	inline pair<_InputIterator, _OutputIterator>
		copy_n(_InputIterator first, _Size count,
			_OutputIterator result)
	{
		return _copy_n(first, count, result, iterator_category(first));
	}

	//������Ԫ�ظ�����ֵ
	template <class _ForwardIterator, class _T>
	void fill(_ForwardIterator first, _ForwardIterator last, const _T& value)
	{
		for (; first != last; ++first)	//�����߹�������Χ
			*first = value;
	}

	//������ǰn��Ԫ�ظ�����ֵ���������һ��������Ԫ�ص���һԪ�ؤε�����
	template <class _OutputIterator, class _Size, class _T>
	_OutputIterator fill_n(_OutputIterator first, _Size n, const _T& value) 
	{
		for (; n > 0; --n, ++first)		// ����n��Ԫ��
			*first = value;	// ע�⣬assignment �Ǹ�д��overwrite�������ǰ��壨insert��
		return first;
	}

	//ƽ�бȽ������У�����һ�Ե�������ָ���������е�һ�β�ƥ��λ��
	// ���£��������һ���꣬�ͽ�����
	// ���£��������һ�����ж��Ķ�ӦԪ����ȣ��ͽ�����
	// ��Ȼ�����ж���Ԫ�ظ������벻��������һ��Ԫ�ظ������������޿�Ԥ�ڡ�
	template <class _InputIterator1, class _InputIterator2>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 first1,
		_InputIterator1 last1, _InputIterator2 first2) 
	{
		while (first1 != last1 && *first1 == *first2) 
		{
			++first1;
			++first2;
		}
		return pair<_InputIterator1, _InputIterator2>(first1, first2);
	}

	template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _BinaryPredicate binary_pred)
	{
		while (first1 != last1 && binary_pred(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return pair<_InputIterator1, _InputIterator2>(first1, first2);
	}


	//������Ⱥ�����
	//ֻ��֤�����Ƚ�������Ԫ����ȣ����ж��������Ա�����һ��
	//Ҫ�ж����������Ƿ���ȫ��ȣ���Ҫ���ж���size()�Ƿ�һ��
	template <class _InputIterator1, class _InputIterator2>
	inline 
		bool equal(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2) 
	{
		// ���£�������һ�߹�һ�顣���ж��ಽ������
		// �ٶ����ж�Ԫ�ز���������һԪ�ظ���
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)		// ֻҪ��ӦԪ�ز���ȣ�
				return false;			// �ͽ��������� false��
		return true;				   // ���ˣ�ȫ����ȣ�����true��
	}

	template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
	inline 
		bool equal(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _BinaryPredicate binary_pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!binary_pred(*first1, *first2))
				return false;
		return true;
	}

	//�����������ֵ���Ƚϣ���һ������С�ڵڶ������У�����true�����ڵ��ڶ�����false
	template <class _InputIterator1, class _InputIterator2>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2)
	{
		// ���£��κ�һ�����е���β�ˣ��ͽ��������������о���ӦԪ��һһ���бȶԡ�
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)	// ��һ����Ԫ��ֵС�ڵڶ����е���ӦԪ��ֵ
				return true;
			if (*first2 < *first1) // �ڶ�����Ԫ��ֵС�ڵ�һ���е���ӦԪ��ֵ
				return false;
			// �����������������������ʾ��ֵ��ȣ��Ǿͽ�����һ����ӦԪ��ֵ�ıȶԡ�
		}
		// ���е���������һ���е���β�˶��ڶ�������������ô��һ����С�ڵڶ����С�
		return first1 == last1 && first2 != last2;
	}

	template <class _InputIterator1, class _InputIterator2, class _Compare>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2,
		_Compare comp) 
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}
    //���ԭ��ָ��unsigned char*���ػ�
	inline
		bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, 
			const unsigned char* first2, const unsigned char* last2)
	{
		const size_t len1 = last1 - first1; 	// ��һ���г���
		const size_t len2 = last2 - first2; 	// �ڶ����г���
		// �ȱȽ���ͬ���ȵ�һ�ء�memcmp() �ٶȼ��졣
		const int result = memcmp(first1, first2, min(len1, len2));
		// ����������£��򳤶Ƚϳ��߱���Ϊ�Ƚϴ�
		return result != 0 ? result < 0 : len1 < len2;
	}
	inline 
		bool lexicographical_compare(const char* first1, const char* last1,
		const char* first2, const char* last2)
	{
		// ת��Ϊ const signed char*
		return lexicographical_compare((const signed char*)first1,
			(const signed char*)last1,
			(const signed char*)first2,
			(const signed char*)last2);
	}
	//�����һ����Χ���ֵ�˳��С�ڵڶ�����Χ����˺�������һ������
	//�����һ����Χ���ֵ�˳����ڵڶ�����Χ���򷵻�����
	//���������Χ���ֵ��϶���������һ����Χ���򷵻���
	template <class _InputIterator1, class _InputIterator2>
	int lexicographical_compare_3way(_InputIterator1 first1, _InputIterator1 last1,
		_InputIterator2 first2, _InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2) 
		{
			if (*first1 < *first2) return -1;
			if (*first2 < *first1) return 1;
			++first1; ++first2;
		}
		if (first2 == last2) 
		{
			return !(first1 == last1);
		}
		else 
		{
			return -1;
		}
	}

	inline int
		lexicographical_compare_3way(const unsigned char* first1,
			const unsigned char* last1,
			const unsigned char* first2,
			const unsigned char* last2)
	{
		const ptrdiff_t len1 = last1 - first1;
		const ptrdiff_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return result != 0 ? result : (len1 == len2 ? 0 : (len1 < len2 ? -1 : 1));
	}

	inline int lexicographical_compare_3way(const char* first1, const char* last1,
		const char* first2, const char* last2)
	{
		return lexicographical_compare_3way(
			(const signed char*)first1,
			(const signed char*)last1,
			(const signed char*)first2,
			(const signed char*)last2);
	}
} //end of MyStl
#endif //end of ALGOBASE_H_

