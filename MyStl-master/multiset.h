/*
* 关联容器multiset
* 键值允许重复
*/

#ifndef MULTISET_H_
#define MULTISET_H_

#include "rb_tree.h"

namespace MyStl
{
	template <class _Key, class _Compare = less<_Key>, class _Alloc= alloc>
	class multiset 
	{
	public:
		typedef _Key        key_type;
		typedef _Key        value_type;
		typedef _Compare    key_compare;
		typedef _Compare    value_compare;
	private:
		typedef rb_tree<key_type, value_type,
			identity<value_type>, key_compare, _Alloc> rep_type;
		rep_type t;  // 底层用一颗红黑树表示
	public:
		typedef typename rep_type::const_pointer    pointer;
		typedef typename rep_type::const_pointer    const_pointer;
		typedef typename rep_type::const_reference  reference;
		typedef typename rep_type::const_reference  const_reference;
		typedef typename rep_type::const_iterator   iterator;
		typedef typename rep_type::const_iterator   const_iterator;
		typedef typename rep_type::size_type        size_type;
		typedef typename rep_type::difference_type  difference_type;

		//构造函数
		// multiset 一定使用 insert_equal() 而不使用 insert_unique()。
		// set 才使用 insert_unique()。
		multiset() : t(_Compare()) {}
		explicit multiset(const _Compare& comp) : t(comp) {}

		template <class _InputIterator>
		multiset(_InputIterator first, _InputIterator last)
			: t(_Compare()) 
		{
			t.insert_equal(first, last);
		}
		template <class _InputIterator>
		multiset(_InputIterator first, _InputIterator last, const _Compare& comp)
			: t(comp) {
			t.insert_equal(first, last);
		}


		multiset(const multiset<_Key, _Compare, _Alloc>& x) : t(x.t) {}
		multiset<_Key, _Compare, _Alloc>&
			operator=(const multiset<_Key, _Compare, _Alloc>& x) {
			t = x.t;
			return *this;
		}

		// 接口

		key_compare key_comp() const { return t.key_comp(); }
		value_compare value_comp() const { return t.key_comp(); }
		iterator begin() const { return t.begin(); }
		iterator end() const { return t.end(); }
		bool empty() const { return t.empty(); }
		size_type size() const { return t.size(); }
		size_type max_size() const { return t.max_size(); }
		void swap(multiset<_Key, _Compare, _Alloc>& x) { t.swap(x.t); }

		// insert/erase
		iterator insert(const value_type& x) {
			return t.insert_equal(x);
		}
		iterator insert(iterator position, const value_type& x) {
			typedef typename rep_type::iterator rep_iterator;
			return t.insert_equal((rep_iterator&)position, x);
		}

		template <class _InputIterator>
		void insert(_InputIterator first, _InputIterator last) {
			t.insert_equal(first, last);
		}

		void erase(iterator position) {
			typedef typename rep_type::iterator rep_iterator;
			t.erase((rep_iterator&)position);
		}
		size_type erase(const key_type& x) {
			return t.erase(x);
		}
		void erase(iterator first, iterator last) {
			typedef typename rep_type::iterator rep_iterator;
			t.erase((rep_iterator&)first, (rep_iterator&)last);
		}
		void clear() { t.clear(); }

		// multiset operations:

		iterator find(const key_type& x) const { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) const {
			return t.lower_bound(x);
		}
		iterator upper_bound(const key_type& x) const {
			return t.upper_bound(x);
		}
		pair<iterator, iterator> equal_range(const key_type& x) const {
			return t.equal_range(x);
		}
		friend bool operator==(const multiset&, const multiset&);
		friend bool operator< (const multiset&, const multiset&);
	};

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator==(const multiset<_Key, _Compare, _Alloc>& x,
		const multiset<_Key, _Compare, _Alloc>& y) {
		return x.t == y.t;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator<(const multiset<_Key, _Compare, _Alloc>& x,
		const multiset<_Key, _Compare, _Alloc>& y) {
		return x.t < y.t;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline void swap(multiset<_Key, _Compare, _Alloc>& x,
		multiset<_Key, _Compare, _Alloc>& y) {
		x.swap(y);
	}
}//end of MyStl
#endif//end of MULTISET_H_

