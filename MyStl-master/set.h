/*
 * 关联容器set
 * 键值不允许重复
 */

#ifndef SET_H_
#define SET_H_

#include "rb_tree.h"
#include <initializer_list>

namespace MyStl
{

	template <class _Key, class _Compare = less<_Key>, class _Alloc = alloc>
	class set
	{
	public:
		//key_type 与 value_type相同
		typedef _Key key_type;
		typedef _Key value_type;
		// 注意，以下 key_compare 和 value_compare 使用相同的比较函数
		typedef _Compare key_compare;
		typedef _Compare value_compare;

	private:
		typedef rb_tree<key_type, value_type,
			identity<value_type>, key_compare, _Alloc> rep_type;
		rep_type t;  // 采用红黑树（RB-tree）来表现 set
	public:
		typedef typename rep_type::const_pointer      pointer;
		typedef typename rep_type::const_pointer      const_pointer;
		typedef typename rep_type::const_reference    reference;
		typedef typename rep_type::const_reference    const_reference;
		//下句iterator定义为RB-tree的const_iterator,set的迭代器无法执行写入动作
		typedef typename rep_type::const_iterator     iterator;
		typedef typename rep_type::const_iterator     const_iterator;
		typedef typename rep_type::size_type          size_type;
		typedef typename rep_type::difference_type    difference_type;

		//构造函数：
		// 注意， set 一定使用 insert_unique() 而不使用 insert_equal()。
		// multiset 才使用 insert_equal()。
		set() : t(_Compare()) {}
		explicit set(const _Compare& comp) : t(comp) {}

		template <class _InputIterator>
		set(_InputIterator first, _InputIterator last)
			: t(_Compare())
		{
			t.insert_unique(first, last);
		}

		template <class _InputIterator>
		set(_InputIterator first, _InputIterator last, const _Compare& comp)
			: t(comp)
		{
			t.insert_unique(first, last);
		}

		set(const std::initializer_list<_Key>& il):t(_Compare())
		{
			t.insert_unique(il.begin(), il.end());
		}

		set(const std::initializer_list<_Key>& il,const _Compare& comp) :t(comp)
		{
			t.insert_unique(il.begin(), il.end());
		}

		set(const set<_Key, _Compare, _Alloc>& x) : t(x.t) {}

		set<_Key, _Compare, _Alloc>& operator=(const set<_Key, _Compare, _Alloc>& x)
		{
			t = x.t;
			return *this;
		}

		// 接口：
		key_compare key_comp() const { return t.key_comp(); }
		//下句set的value_comp() 事实上为RB-tree 的key_comp()
		value_compare value_comp() const { return t.key_comp(); }
		iterator begin() const { return t.begin(); }
		iterator end() const { return t.end(); }
		bool empty() const { return t.empty(); }
		size_type size() const { return t.size(); }
		size_type max_size() const { return t.max_size(); }
		void swap(set<_Key, _Compare, _Alloc>& x) { t.swap(x.t); }

		// insert/erase
		typedef  pair<iterator, bool> pair_iterator_bool;
		pair<iterator, bool> insert(const value_type& x)
		{
			pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
			return pair<iterator, bool>(p.first, p.second);
		}
		iterator insert(iterator position, const value_type& x)
		{
			typedef typename rep_type::iterator rep_iterator;
			return t.insert_unique((rep_iterator&)position, x);
		}

		template <class _InputIterator>
		void insert(_InputIterator first, _InputIterator last)
		{
			t.insert_unique(first, last);
		}
		void erase(iterator position)
		{
			typedef typename rep_type::iterator rep_iterator;
			t.erase((rep_iterator&)position);
		}
		size_type erase(const key_type& x)
		{
			return t.erase(x);
		}
		void erase(iterator first, iterator last)
		{
			typedef typename rep_type::iterator rep_iterator;
			t.erase((rep_iterator&)first, (rep_iterator&)last);
		}
		void clear() { t.clear(); }

		iterator find(const key_type& x) const { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) const
		{
			return t.lower_bound(x);
		}
		iterator upper_bound(const key_type& x) const
		{
			return t.upper_bound(x);
		}
		pair<iterator, iterator> equal_range(const key_type& x) const
		{
			return t.equal_range(x);
		}
		friend bool operator==(const set&, const set&);
		friend bool operator<(const set&, const set&);
	};

	template <class _Key, class _Compare, class _Alloc>
	inline
		bool operator==(const set<_Key, _Compare, _Alloc>& x,
			const set<_Key, _Compare, _Alloc>& y)
	{
		return x.t == y.t;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline
		bool operator<(const set<_Key, _Compare, _Alloc>& x,
			const set<_Key, _Compare, _Alloc>& y)
	{
		return x.t < y.t;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline
		void swap(set<_Key, _Compare, _Alloc>& x,
			set<_Key, _Compare, _Alloc>& y)
	{
		x.swap(y);
	}
}//end of MyStl
#endif //end of SET_H_
