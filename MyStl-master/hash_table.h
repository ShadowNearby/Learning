/*
 * 采用“挂链”的hash_table解决冲突问题，
 * hash_table中元素的数目不多于buckets数，
 * 否则就重建表，这样做可保持适度的装填因子，
 * 以减少因hash_function设计不合理引入的元素
 * 聚集现象。
 *
 * 用于实现unordered_set,
 * unordered_map, unordered_multiset,
 * unordered_multimap
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "vector.h"
#include "hash_func.h"

namespace MyStl
{
	template <class _Value>
	struct _hashtable_node
	{
		//  separate chaining 
		// 自行管理分离链表
		_hashtable_node* next;
		_Value val;
	};

	//前置声明：
	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey, class _EqualKey, class _Alloc = alloc>
		class hashtable;

	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey, class _EqualKey, class _Alloc>
		struct _hashtable_iterator;

	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey, class _EqualKey, class _Alloc>
		struct _hashtable_const_iterator;

	//hash_table的迭代器
	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey/*提取键值的方法*/, class _EqualKey/*判断键值相等的方法*/, class _Alloc>
		struct _hashtable_iterator
	{
		typedef hashtable<_Value, _Key,
			_HashFcn, _ExtractKey, _EqualKey, _Alloc>       hashtable;

		typedef _hashtable_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                 iterator;

		typedef _hashtable_const_iterator<_Value, _Key,
			_HashFcn, _ExtractKey, _EqualKey, _Alloc>        const_iterator;

		typedef _hashtable_node<_Value>                     node;

		typedef forward_iterator_tag                        iterator_category;
		typedef _Value                                      value_type;
		typedef ptrdiff_t                                   difference_type;
		typedef size_t                                      size_type;
		typedef _Value&                                     reference;
		typedef _Value*                                     pointer;

		node* cur;		// 迭代器目前所指之节点
		hashtable* ht;	// 保持对容器的连结关系（方便bucket之间的跳跃）

		_hashtable_iterator(node* n, hashtable* tab) : cur(n), ht(tab) {}
		_hashtable_iterator() {}
		reference operator*() const { return cur->val; }
		pointer operator->() const { return &(operator*()); }
		explicit operator bool() const { return cur != 0; }

		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& it) const { return cur == it.cur; }
		bool operator!=(const iterator& it) const { return cur != it.cur; }
	};


	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey, class _EqualKey, class _Alloc>
		struct _hashtable_const_iterator
	{
		typedef hashtable<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                       hashtable;

		typedef _hashtable_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                       iterator;

		typedef _hashtable_const_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                       const_iterator;

		typedef _hashtable_node<_Value>                           node;

		typedef forward_iterator_tag                              iterator_category;
		typedef _Value                                            value_type;
		typedef ptrdiff_t                                         difference_type;
		typedef size_t                                            size_type;
		typedef const _Value&                                     reference;
		typedef const _Value*                                     pointer;

		const node* cur;
		const hashtable* ht;

		_hashtable_const_iterator(const node* n, const hashtable* tab)
			: cur(n), ht(tab) {}
		_hashtable_const_iterator() {}
		_hashtable_const_iterator(const iterator& it) : cur(it.cur), ht(it.ht) {}
		reference operator*() const { return cur->val; }
		pointer operator->() const { return &(operator*()); }
		explicit operator bool() const { return cur != 0; }

		const_iterator& operator++();
		const_iterator operator++(int);
		bool operator==(const const_iterator& it) const { return cur == it.cur; }
		bool operator!=(const const_iterator& it) const { return cur != it.cur; }
	};

	// 注意：假设 long 至少有 32 bits。
	// 用于设计表长的质数
	static const int _stl_num_primes = 28;
	static const unsigned long _stl_prime_list[_stl_num_primes] =
	{
		53,         97,           193,         389,       769,
		1543,       3079,         6151,        12289,     24593,
		49157,      98317,        196613,      393241,    786433,
		1572869,    3145739,      6291469,     12582917,  25165843,
		50331653,   100663319,    201326611,   402653189, 805306457,
		1610612741, 3221225473ul, 4294967291ul
	};

	// 以下找出上述28个质数之中，最接近并大于n的那个质数
	inline unsigned long _stl_next_prime(unsigned long n)
	{
		const unsigned long* first = _stl_prime_list;
		const unsigned long* last = _stl_prime_list + _stl_num_primes;
		const unsigned long* pos = lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}


	template <class _Value, class _Key, class _HashFcn,
		class _ExtractKey, class _EqualKey, class _Alloc>
		class hashtable
	{
		friend bool operator==(const hashtable&, const hashtable&);
		friend struct _hashtable_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>;
		friend struct _hashtable_const_iterator<_Value, _Key,
			_HashFcn, _ExtractKey, _EqualKey, _Alloc>;

	public:
		typedef _Key        key_type;
		typedef _Value      value_type;
		typedef _HashFcn    hasher;
		typedef _EqualKey   key_equal;

		typedef size_t            size_type;
		typedef ptrdiff_t         difference_type;
		typedef value_type*       pointer;
		typedef const value_type* const_pointer;
		typedef value_type&       reference;
		typedef const value_type& const_reference;

		hasher hash_funct() const { return hash; }
		key_equal key_eq() const { return equals; }

	private:
		//都是可调用对象
		hasher      hash;
		key_equal   equals;
		_ExtractKey get_key;

		typedef _hashtable_node<_Value>     node;
		//专属配置器，每次配置一个node
		typedef simple_alloc<node, _Alloc>  node_allocator;

		vector<node*, _Alloc> buckets;	// 以 vector 完成
		size_type num_elements;

	public:
		typedef _hashtable_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                         iterator;

		typedef _hashtable_const_iterator<_Value, _Key, _HashFcn,
			_ExtractKey, _EqualKey, _Alloc>                        const_iterator;



	public:
		// 构造函数
		// 没有默认构造函数
		hashtable(size_type n, const _HashFcn&hf, const _EqualKey& eql,
			const _ExtractKey& ext)
			: hash(hf), equals(eql), get_key(ext), num_elements(0)
		{
			initialize_buckets(n);
		}

		hashtable(size_type n, const _HashFcn& hf,
			const _EqualKey& eql)
			: hash(hf), equals(eql), get_key(_ExtractKey()), num_elements(0)
		{
			initialize_buckets(n);
		}

		hashtable(const hashtable& ht)
			: hash(ht.hash), equals(ht.equals), get_key(ht.get_key), num_elements(0)
		{
			copy_from(ht);
		}

		hashtable& operator= (const hashtable& ht)
		{
			if (&ht != this)    //不是自赋值
			{
				clear();		// 先清除自己
				// 以下三个动作，将三份data members 复制过来
				hash = ht.hash;
				equals = ht.equals;
				get_key = ht.get_key;
				copy_from(ht);	// 完整复制整个 hash table 的内容。
			}
			return *this;
		}

		// 析构函数
		~hashtable() { clear(); }

		size_type size() const { return num_elements; }
		size_type max_size() const { return size_type(-1); }
		bool empty() const { return size() == 0; }

		void swap(hashtable& ht)
		{
			std::swap(hash, ht.hash);
			std::swap(equals, ht.equals);
			std::swap(get_key, ht.get_key);
			buckets.swap(ht.buckets);
			std::swap(num_elements, ht.num_elements);
		}

		iterator begin()
		{
			for (size_type n = 0; n < buckets.size(); ++n)
				// 找出第一个被使用的节点，此即 begin iterator。
				if (buckets[n])
					return iterator(buckets[n], this);
			return end();
		}

		iterator end() { return iterator(0, this); }

		const_iterator begin() const
		{
			for (size_type n = 0; n < buckets.size(); ++n)
				if (buckets[n])
					return const_iterator(buckets[n], this);
			return end();
		}

		const_iterator end() const { return const_iterator(0, this); }



	public:

		// bucket 个数即 buckets vector 的大小
		size_type bucket_count() const { return buckets.size(); }

		// 以目前情况（不重建表格），总共可以有多少 buckets
		size_type max_bucket_count() const
		{
			return _stl_prime_list[_stl_num_primes - 1];
		}

		// 探知某个bucket（内含一个list）容纳多少元素。
		size_type elems_in_bucket(size_type bucket) const
		{
			size_type result = 0;
			for (node* cur = buckets[bucket]; cur; cur = cur->next)
				result += 1;
			return result;
		}

		// 安插元素，不允许重复
		pair<iterator, bool> insert_unique(const value_type& obj)
		{
			resize(num_elements + 1); 	// 判断是否需要重建表格，如需要就扩充
			return insert_unique_no_resize(obj);
		}

		// 安插元素，允许重复
		iterator insert_equal(const value_type& obj)
		{
			resize(num_elements + 1);	// 判断是否需要重建表格，如需要就扩充
			return insert_equal_no_resize(obj);
		}

		pair<iterator, bool> insert_unique_no_resize(const value_type& obj);
		iterator insert_equal_no_resize(const value_type& obj);


		template <class _InputIterator>
		void insert_unique(_InputIterator f, _InputIterator l)
		{
			insert_unique(f, l, iterator_category(f));
		}

		template <class _InputIterator>
		void insert_equal(_InputIterator f, _InputIterator l)
		{
			insert_equal(f, l, iterator_category(f));
		}

		template <class _InputIterator>
		void insert_unique(_InputIterator f, _InputIterator l,
			input_iterator_tag)
		{
			for (; f != l; ++f)
				insert_unique(*f);
		}

		template <class _InputIterator>
		void insert_equal(_InputIterator f, _InputIterator l,
			input_iterator_tag)
		{
			for (; f != l; ++f)
				insert_equal(*f);
		}

		template <class _ForwardIterator>
		void insert_unique(_ForwardIterator f, _ForwardIterator l,
			forward_iterator_tag)
		{
			size_type n = MyStl::distance(f, l);
			resize(num_elements + n);		// 判断（并实施）表格的重建
			for (; n > 0; --n, ++f)
				insert_unique_no_resize(*f);	// 一一安插新元素
		}

		template <class _ForwardIterator>
		void insert_equal(_ForwardIterator f, _ForwardIterator l,
			forward_iterator_tag)
		{
			size_type n = MyStl::distance(f, l);
			resize(num_elements + n);		   // 判断（并实施）表格的重建
			for (; n > 0; --n, ++f)
				insert_equal_no_resize(*f);		// 一一安插新元素
		}



		reference find_or_insert(const value_type& obj);

		iterator find(const key_type& key)
		{
			size_type n = bkt_num_key(key);	// 首先寻找落在哪一个 bucket 内
			node* first;
			// 以下，从bucket list 的头开始，一一比对每个元素的键值。比对成功就跳出。
			for (first = buckets[n]; first && !equals(get_key(first->val), key);
				first = first->next) {
			}
			return iterator(first, this);
		}

		const_iterator find(const key_type& key) const
		{
			size_type n = bkt_num_key(key);
			const node* first;
			for (first = buckets[n]; first && !equals(get_key(first->val), key);
				first = first->next) {
			}
			return const_iterator(first, this);
		}

		size_type count(const key_type& key) const
		{
			const size_type n = bkt_num_key(key); // 首先寻找落在哪一个 bucket 内
			size_type result = 0;

			// 以下，从bucket list 的头开始，一一比对每个元素的键值。比对成功就累加1。
			for (const node* cur = buckets[n]; cur; cur = cur->next)
				if (equals(get_key(cur->val), key))
					++result;
			return result;
		}

		pair<iterator, iterator> equal_range(const key_type& key);
		pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

		size_type erase(const key_type& key);
		void erase(const iterator& it);
		void erase(iterator first, iterator last);

		void erase(const const_iterator& it);
		void erase(const_iterator first, const_iterator last);

		void resize(size_type num_elements_hint);
		void clear();

	private:
		// 寻找下一个质数
		size_type next_size(size_type n) const { return (size_type)(_stl_next_prime(unsigned long(n))); }

		// unordered_set 和 unordered_map 都将其底层的 hash_table 的初始大小预设为100
		void initialize_buckets(size_type n)
		{
			const size_type n_buckets = next_size(n);
			buckets.reserve(n_buckets);
			buckets.insert(buckets.end(), n_buckets, (node*)0);
			num_elements = 0;
		}

		size_type bkt_num_key(const key_type& key) const
		{
			return bkt_num_key(key, buckets.size());
		}

		size_type bkt_num(const value_type& obj) const
		{
			return bkt_num_key(get_key(obj));
		}

		size_type bkt_num_key(const key_type& key, size_t n) const
		{
			return hash(key) % n;
		}

		size_type bkt_num(const value_type& obj, size_t n) const
		{
			return bkt_num_key(get_key(obj), n);
		}

		node* new_node(const value_type& obj)
		{
			node* n = node_allocator::allocate();
			n->next = 0;
			try
			{
				construct(&n->val, obj);
				return n;
			}
			catch (...)
			{
				node_allocator::deallocate(n);
				throw;
			}
		}

		void delete_node(node* n)
		{
			destroy(&n->val);
			node_allocator::deallocate(n);
		}

		void erase_bucket(const size_type n, node* first, node* last);
		void erase_bucket(const size_type n, node* last);

		void copy_from(const hashtable& ht);

	}; //end of hashtable

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class _A>
	_hashtable_iterator<_V, _K, _HF, _ExK, _EqK, _A>&
		_hashtable_iterator<_V, _K, _HF, _ExK, _EqK, _A>::operator++() //前置
	{
		const node* old = cur;
		cur = cur->next; // 如果存在，就是它。否则进入以下 if 流程
		if (!cur)
		{
			// 根据原值，重新定位。从该位置（bucket）的下一位置找起。
			size_type bucket = ht->bkt_num(old->val);
			while (!cur && ++bucket < ht->buckets.size())
				cur = ht->buckets[bucket];
		}
		return *this;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class _A>
	inline _hashtable_iterator<_V, _K, _HF, _ExK, _EqK, _A>
		_hashtable_iterator<_V, _K, _HF, _ExK, _EqK, _A>::operator++(int)
	{
		iterator tmp = *this;
		++*this;	// 唤起 operator++()
		return tmp;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class _A>
	_hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, _A>&
		_hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, _A>::operator++()
	{
		const node* old = cur;
		cur = cur->next;
		if (!cur)
		{
			size_type bucket = ht->bkt_num(old->val);
			while (!cur && ++bucket < ht->buckets.size())
				cur = ht->buckets[bucket];
		}
		return *this;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class _A>
	inline _hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, _A>
		_hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, _A>::operator++(int)
	{
		const_iterator tmp = *this;
		++*this;
		return tmp;
	}



	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline forward_iterator_tag
		iterator_category(const _hashtable_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return forward_iterator_tag();
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline _V* value_type(const _hashtable_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return (_V*)0;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline 
		typename hashtable<_V, _K, _HF, _ExK, _EqK, All>::difference_type*
		distance_type(const _hashtable_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return (hashtable<_V, _K, _HF, _ExK, _EqK, All>::difference_type*) 0;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline forward_iterator_tag
		iterator_category(const _hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return forward_iterator_tag();
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline _V*
		value_type(const _hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return (_V*)0;
	}

	template <class _V, class _K, class _HF, class _ExK, class _EqK, class All>
	inline
		typename hashtable<_V, _K, _HF, _ExK, _EqK, All>::difference_type*
		distance_type(const _hashtable_const_iterator<_V, _K, _HF, _ExK, _EqK, All>&)
	{
		return (hashtable<_V, _K, _HF, _ExK, _EqK, All>::difference_type*) 0;
	}


	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	bool operator==(const hashtable<_V, _K, _HF, _Ex, _Eq, _A>& ht1,
		const hashtable<_V, _K, _HF, _Ex, _Eq, _A>& ht2)
	{
		typedef typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::node node;
		if (ht1.buckets.size() != ht2.buckets.size())
			return false;
		for (int n = 0; n < ht1.buckets.size(); ++n)
		{
			node* cur1 = ht1.buckets[n];
			node* cur2 = ht2.buckets[n];
			for (; cur1 && cur2 && cur1->val == cur2->val;
				cur1 = cur1->next, cur2 = cur2->next)
			{
			}
			if (cur1 || cur2)
				return false;
		}
		return true;
	}



	template <class _Val, class _Key, class _HF, class _Extract, class _EqKey, class _A>
	inline void swap(hashtable<_Val, _Key, _HF, _Extract, _EqKey, _A>& ht1,
		hashtable<_Val, _Key, _HF, _Extract, _EqKey, _A>& ht2) 
	{
		ht1.swap(ht2);
	}


	// 在不需重建表格的情况下安插新节点。键值不允许重复。
	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	pair<typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::iterator, bool>
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::insert_unique_no_resize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);	// 决定obj应位于 #n bucket
		node* first = buckets[n];	        // 令 first 指向 bucket 对应之链表头部

		// 如果 buckets[n] 已被占用，此时first 将不为0，于是进入以下循环，
		// 走过 bucket 所对应的整个链表。
		for (node* cur = first; cur; cur = cur->next)
			if (equals(get_key(cur->val), get_key(obj)))
				// 如果发现与链表中的某键值相同，就不安插，立刻回返。
				return pair<iterator, bool>(iterator(cur, this), false);

		// 离开以上循环（或根本未进入循环）时，first 指向bucket所指链表的头部节点。
		node* tmp = new_node(obj);	// 产生新节点
		tmp->next = first;
		buckets[n] = tmp; 			// 令新节点成为链表的第一个节点
		++num_elements;				// 节点个数累加1
		return pair<iterator, bool>(iterator(tmp, this), true);
	}

	// 在不需重建表格的情况下安插新节点。键值允许重复。
	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::iterator
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::insert_equal_no_resize(const value_type& obj)
	{
		const size_type n = bkt_num(obj); // 决定obj应位于 第n号 bucket
		node* first = buckets[n]; // 令first指向bucket对应之链表头部

								  // 如果 buckets[n] 已被占用，此时first 将不为0，于是进入以下循环，
								  // 走过 bucket 所对应的整个串行。
		for (node* cur = first; cur; cur = cur->next)
			if (equals(get_key(cur->val), get_key(obj)))
			{
				// 如果发现与串行中的某键值相同，就马上安插，然后回返。
				node* tmp = new_node(obj);		// 产生新节点
				tmp->next = cur->next;		// 将新节点安插于目前位置
				cur->next = tmp;
				++num_elements;				// 节点个数累加1
				return iterator(tmp, this);	// 传回一个迭代器，指向新增节点
			}

		// 进行至此，表示没有发现重复的键值
		node* tmp = new_node(obj);	// 产生新节点
		tmp->next = first;			// 将新节点安插于串行头部
		buckets[n] = tmp;
		++num_elements;				// 节点个数累加1
		return iterator(tmp, this);	// 传回一个迭代器，指向新增节点
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::reference
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::find_or_insert(const value_type& obj)
	{
		resize(num_elements + 1);

		size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
			if (equals(get_key(cur->val), get_key(obj)))
				return cur->val;

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return tmp->val;
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	pair<typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::iterator,
		typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::iterator>
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::equal_range(const key_type& key)
	{
		typedef pair<iterator, iterator> pii;
		const size_type n = bkt_num_key(key);

		for (node* first = buckets[n]; first; first = first->next) {
			if (equals(get_key(first->val), key)) {
				for (node* cur = first->next; cur; cur = cur->next)
					if (!equals(get_key(cur->val), key))
						return pii(iterator(first, this), iterator(cur, this));
				for (size_type m = n + 1; m < buckets.size(); ++m)
					if (buckets[m])
						return pii(iterator(first, this),
							iterator(buckets[m], this));
				return pii(iterator(first, this), end());
			}
		}
		return pii(end(), end());
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	pair<typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::const_iterator,
		typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::const_iterator>
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::equal_range(const key_type& key) const
	{
		typedef pair<const_iterator, const_iterator> pii;
		const size_type n = bkt_num_key(key);

		for (const node* first = buckets[n]; first; first = first->next) {
			if (equals(get_key(first->val), key)) {
				for (const node* cur = first->next; cur; cur = cur->next)
					if (!equals(get_key(cur->val), key))
						return pii(const_iterator(first, this),
							const_iterator(cur, this));
				for (size_type m = n + 1; m < buckets.size(); ++m)
					if (buckets[m])
						return pii(const_iterator(first, this),
							const_iterator(buckets[m], this));
				return pii(const_iterator(first, this), end());
			}
		}
		return pii(end(), end());
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	typename hashtable<_V, _K, _HF, _Ex, _Eq, _A>::size_type
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase(const key_type& key)
	{
		const size_type n = bkt_num_key(key);
		node* first = buckets[n];
		size_type erased = 0;

		if (first) {
			node* cur = first;
			node* next = cur->next;
			while (next) {
				if (equals(get_key(next->val), key)) {
					cur->next = next->next;
					delete_node(next);
					next = cur->next;
					++erased;
					--num_elements;
				}
				else {
					cur = next;
					next = cur->next;
				}
			}
			if (equals(get_key(first->val), key)) {
				buckets[n] = first->next;
				delete_node(first);
				++erased;
				--num_elements;
			}
		}
		return erased;
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase(const iterator& it)
	{
		if (node* const p = it.cur) {
			const size_type n = bkt_num(p->val);
			node* cur = buckets[n];

			if (cur == p) {
				buckets[n] = cur->next;
				delete_node(cur);
				--num_elements;
			}
			else {
				node* next = cur->next;
				while (next) {
					if (next == p) {
						cur->next = next->next;
						delete_node(next);
						--num_elements;
						break;
					}
					else {
						cur = next;
						next = cur->next;
					}
				}
			}
		}
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase(iterator first, iterator last)
	{
		size_type f_bucket = first.cur ? bkt_num(first.cur->val) : buckets.size();
		size_type l_bucket = last.cur ? bkt_num(last.cur->val) : buckets.size();

		if (first.cur == last.cur)
			return;
		else if (f_bucket == l_bucket)
			erase_bucket(f_bucket, first.cur, last.cur);
		else {
			erase_bucket(f_bucket, first.cur, 0);
			for (size_type n = f_bucket + 1; n < l_bucket; ++n)
				erase_bucket(n, 0);
			if (l_bucket != buckets.size())
				erase_bucket(l_bucket, last.cur);
		}
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	inline void
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase(const_iterator first,
			const_iterator last)
	{
		erase(iterator(const_cast<node*>(first.cur),
			const_cast<hashtable*>(first.ht)),
			iterator(const_cast<node*>(last.cur),
				const_cast<hashtable*>(last.ht)));
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	inline void
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase(const const_iterator& it)
	{
		erase(iterator(const_cast<node*>(it.cur),
			const_cast<hashtable*>(it.ht)));
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::resize(size_type num_elements_hint)
	{
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n) // 确定真的需要重新配置
		{
			const size_type n = next_size(num_elements_hint);	// 找出下一个质数
			if (n > old_n)
			{
				vector<node*, _A> tmp(n, (node*)0);	// 设立新的 buckets
				try
				{
					// 以下处理每一个旧的bucket
					for (size_type bucket = 0; bucket < old_n; ++bucket)
					{
						node* first = buckets[bucket]; // 指向节点所对应之链表的起始节点
						// 以下处理每一个旧bucket 所含（链表）的每一个节点
						while (first)
						{	// 链表还没结束时
							// 以下找出节点落在哪一个新bucket 内
							size_type new_bucket = bkt_num(first->val, n);
							// 令旧 bucket 指向其所对应链表的下一个节点（以便迭代处理）
							buckets[bucket] = first->next;
							// 将当前节点安插到新bucket内，成为其对应链表的第一个节点。
							first->next = tmp[new_bucket];
							tmp[new_bucket] = first;
							// 回到旧bucket所指的待处理链表，准备处理下一个节点
							first = buckets[bucket];
						}
					}
					// vector::swap。新旧 buckets 对调。
					// 注意，对调两方如果大小不同，大的会变小，小的会变大。
					buckets.swap(tmp);
				}
				catch (...)
				{
					for (size_type bucket = 0; bucket < tmp.size(); ++bucket)
					{
						while (tmp[bucket])
						{
							node* next = tmp[bucket]->next;
							delete_node(tmp[bucket]);
							tmp[bucket] = next;
						}
					}
					throw;
				}
			}
		}
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase_bucket(const size_type n,
		node* first, node* last)
	{
		node* cur = buckets[n];
		if (cur == first)
			erase_bucket(n, last);
		else {
			node* next;
			for (next = cur->next; next != first; cur = next, next = cur->next)
				;
			while (next) {
				cur->next = next->next;
				delete_node(next);
				next = cur->next;
				--num_elements;
			}
		}
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void
		hashtable<_V, _K, _HF, _Ex, _Eq, _A>::erase_bucket(const size_type n, node* last)
	{
		node* cur = buckets[n];
		while (cur != last) {
			node* next = cur->next;
			delete_node(cur);
			cur = next;
			buckets[n] = cur;
			--num_elements;
		}
	}

	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::clear()
	{
		// 针对每一个 bucket.
		for (size_type i = 0; i < buckets.size(); ++i) {
			node* cur = buckets[i];
			// 将 bucket list 中的每一个节点删除掉
			while (cur != 0) {
				node* next = cur->next;
				delete_node(cur);
				cur = next;
			}
			buckets[i] = 0; 	// 令bucket 内容为 null 指标
		}
		num_elements = 0; 	// 令总节点个数为0

							// 注意，buckets vector 并未释放掉空间，仍保有原来大小。
	}


	template <class _V, class _K, class _HF, class _Ex, class _Eq, class _A>
	void hashtable<_V, _K, _HF, _Ex, _Eq, _A>::copy_from(const hashtable& ht)
	{
		// 先清除己方的buckets vector，调用vector::clear.
		buckets.clear();
		// 为己方的buckets vector 保留空间，使与对方相同
		// 如果己方空间大于对方，就不动，如果己方空间小于对方，就会增大。
		buckets.reserve(ht.buckets.size());
		// 从己方的 buckets vector 尾端开始，安插n个元素，其值为 null 。
		// 注意，此时buckets vector 为空，所以所谓尾端，就是起头处。
		buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
		try
		{
			// 针对 buckets vector 
			for (size_type i = 0; i < ht.buckets.size(); ++i)
			{
				// 复制 vector 的每一个元素（是个指针，指向 hashtable节点）
				if (const node* cur = ht.buckets[i])
				{
					node* copy = new_node(cur->val);
					buckets[i] = copy;

					// 针对同一个 bucket list，复制每一个节点
					for (node* next = cur->next; next; cur = next, next = cur->next)
					{
						copy->next = new_node(next->val);
						copy = copy->next;
					}
				}
			}
			num_elements = ht.num_elements;	// 重新登录节点个数（hashtable 的大小）
		}
		catch (...)
		{
			clear();
			throw;
		}
	}
} //end of MyStl
#endif //end of HASH_TABLE_H_
