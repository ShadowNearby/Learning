/*
 * 关联容器multimap
 * 键值允许重复
*/
#ifndef MULTIMAP_H_
#define MULTIMAP_H_

#include "rb_tree.h"

namespace MyStl
{
	template <class _Key, class _T, class _Compare = less<_Key>, class _Alloc = alloc>
	class multimap
	{
	public:
		typedef _Key                   key_type;     // 键值型别
		typedef _T                     data_type;    // 真值型别
		typedef _T                     mapped_type;  // map独有,等同于真值型别
		typedef pair<const _Key, _T>   value_type;   // 元素型别（键值/真值）
		typedef _Compare               key_compare;  // 键值比较函数

		class value_compare : public binary_function<value_type, value_type, bool> {
			friend class multimap<_Key, _T, _Compare, _Alloc>;
		protected:
			_Compare comp;
			value_compare(_Compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

	private:
		typedef rb_tree<key_type, value_type,
			select1st<value_type>, key_compare, _Alloc> rep_type;
		rep_type t;  // red-black tree representing multimap
	public:
		typedef typename rep_type::pointer           pointer;
		typedef typename rep_type::const_pointer     const_pointer;
		typedef typename rep_type::reference         reference;
		typedef typename rep_type::const_reference   const_reference;
		typedef typename rep_type::iterator          iterator;
		typedef typename rep_type::const_iterator    const_iterator;
		typedef typename rep_type::size_type         size_type;
		typedef typename rep_type::difference_type   difference_type;

		//构造函数
		//使用nsert_equal()
		multimap() : t(_Compare()) { }
		explicit multimap(const _Compare& comp) : t(comp) { }

		template <class _InputIterator>
		multimap(_InputIterator first, _InputIterator last)
			: t(_Compare()) {
			t.insert_equal(first, last);
		}

		template <class _InputIterator>
		multimap(_InputIterator first, _InputIterator last, const _Compare& comp)
			: t(comp) {
			t.insert_equal(first, last);
		}

		multimap(const multimap<_Key, _T, _Compare, _Alloc>& x) : t(x.t) { }
		multimap<_Key, _T, _Compare, _Alloc>&
			operator=(const multimap<_Key, _T, _Compare, _Alloc>& x) {
			t = x.t;
			return *this;
		}

		// 接口：
		key_compare key_comp() const { return t.key_comp(); }
		value_compare value_comp() const { return value_compare(t.key_comp()); }
		iterator begin() { return t.begin(); }
		const_iterator begin() const { return t.begin(); }
		iterator end() { return t.end(); }
		const_iterator end() const { return t.end(); }
		bool empty() const { return t.empty(); }
		size_type size() const { return t.size(); }
		size_type max_size() const { return t.max_size(); }
		void swap(multimap<_Key, _T, _Compare, _Alloc>& x) { t.swap(x.t); }

		// insert/erase

		iterator insert(const value_type& x) { return t.insert_equal(x); }
		iterator insert(iterator position, const value_type& x) {
			return t.insert_equal(position, x);
		}
		template <class _InputIterator>
		void insert(_InputIterator first, _InputIterator last) {
			t.insert_equal(first, last);
		}

		void erase(iterator position) { t.erase(position); }
		size_type erase(const key_type& x) { return t.erase(x); }
		void erase(iterator first, iterator last) { t.erase(first, last); }
		void clear() { t.clear(); }

		// multimap operations:

		iterator find(const key_type& x) { return t.find(x); }
		const_iterator find(const key_type& x) const { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
		const_iterator lower_bound(const key_type& x) const {
			return t.lower_bound(x);
		}
		iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
		const_iterator upper_bound(const key_type& x) const {
			return t.upper_bound(x);
		}
		pair<iterator, iterator> equal_range(const key_type& x) {
			return t.equal_range(x);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
			return t.equal_range(x);
		}
		friend bool operator==(const multimap&, const multimap&);
		friend bool operator<(const multimap&, const multimap&);
	};

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline bool operator==(const multimap<_Key, _T, _Compare, _Alloc>& x,
		const multimap<_Key, _T, _Compare, _Alloc>& y) {
		return x.t == y.t;
	}

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline bool operator<(const multimap<_Key, _T, _Compare, _Alloc>& x,
		const multimap<_Key, _T, _Compare, _Alloc>& y) {
		return x.t < y.t;
	}

	template <class _Key, class _T, class _Compare, class _Alloc>
	inline void swap(multimap<_Key, _T, _Compare, _Alloc>& x,
		multimap<_Key, _T, _Compare, _Alloc>& y) {
		x.swap(y);
	}

}//end of MyStl
#endif //end of MULTIMAP_H_
