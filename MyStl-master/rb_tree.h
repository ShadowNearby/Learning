/*
 * Red-black tree（红-黑树）class，用以实现关系型容器（如set,
 * multiset, map, multimap）
 * (1)： header 不仅指向 root，也指向红黑树的最左节点，以便实作出常数时间之
 * begin()；并且也指向红黑树的最右节点，以便set 相关泛型算法（如set_union
 * 等等）有线性时间之表现。
 * (2)： 当一个即将被删除之节点拥有两个子节点时，它的successor node is
 * relinked into its place, rather than copied, 如此一来唯一失效（invalidated）
 * 的迭代器就只是那些referring to the deleted node.
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include "allocator.h"

namespace MyStl
{
	typedef bool _rb_tree_color_type;
	const _rb_tree_color_type _rb_tree_red = false;	   // 红色为 0
	const _rb_tree_color_type _rb_tree_black = true;   // 黑色为 1

	struct _rb_tree_node_base
	{
		typedef _rb_tree_color_type  _color_type;
		typedef _rb_tree_node_base*  _base_ptr;

		_color_type _color; 	     // 节点颜色，非红即黑。
		_base_ptr   _parent;  	     // 父节点。
		_base_ptr   _lc;	  	     // 左孩子。
		_base_ptr   _rc;   	         // 右孩子。

		static _base_ptr minimum(_base_ptr _x)
		{
			while (_x->_lc != 0) _x = _x->_lc;	   // 一直向左走，就会找到最小值，
			return _x;
		}

		static _base_ptr maximum(_base_ptr _x)
		{
			while (_x->_rc != 0) _x = _x->_rc; 	  // 一直向右走，就会找到最大值，
			return _x;
		}
	};

	template <typename _Value>
	struct _rb_tree_node : public _rb_tree_node_base
	{
		typedef _rb_tree_node<_Value>* _node_ptr;
		_Value _value_field;	      // 节点实值
	};

	struct _rb_tree_base_iterator
	{
		typedef _rb_tree_node_base::_base_ptr         _base_ptr;
		typedef bidirectional_iterator_tag            iterator_category;
		typedef ptrdiff_t                             difference_type;

		_base_ptr _base_node;// 它用来与容器之间产生一个连结关系

		void _increment()                              //找直接后继节点
		{
			if (_base_node->_color == _rb_tree_red &&	        // 如果是红节点，且
				_base_node->_parent->_parent == _base_node)     // 父节点的父节点等于自己
			{
				_base_node = _base_node->_parent;                //父节点即为解答
			} 
			else if (_base_node->_rc)                 // 如果有右子节点
			{		                                  // 后继节点是右子树中的最小者
				_base_node = _base_node->_rc;		  // 向右走
				while (_base_node->_lc)	              // 然后一直往左子树走到底
					_base_node = _base_node->_lc;     // 即是解答
			}
			else                                        // 没有右子节点
			{					                        // 直接后继应是“将当前节点包含于其左子树中的最低祖先”
				while (_base_node->_parent && _base_node->_parent->_rc == _base_node) //为右孩子
					_base_node = _base_node->_parent;   //逆向地沿右向分支，不断朝左上方移动
				_base_node = _base_node->_parent;       //最后再朝右上方移动一步，即抵达直接后继（如果存在）				
			}
		}

		void _decrement()                                       //找直接前驱节点
		{
			if (_base_node->_color == _rb_tree_red &&	        // 如果是红节点，且
				_base_node->_parent->_parent == _base_node)     // 父节点的父节点等于自己，
			{
				_base_node = _base_node->_rc;                   // 右子节点即为解答。
			// 以上情况发生于node为header时（亦即 node 为 end() 时）。
			// 注意，header 之右子节点即 mostright，指向整棵树的 max 节点。
			}
			else if (_base_node->_lc)             // 如果有左子节点
			{			                               //左子树中最右者为直接前驱
				_base_ptr _y = _base_node->_lc;			// 令y指向左子节点，
				while (_y->_rc)				  // 当y有右子节点时
					_y = _y->_rc;					  // 一直往右子节点走到底
				_base_node = _y;						// 最后即为答案
			}
			else                                         // 既非根节点，亦无左子节点。
			{							                //此时当前节点为其前驱节点右子树中最靠左者		
				while (_base_node->_parent && _base_node->_parent->_lc == _base_node)  //为左孩子
					_base_node = _base_node->_parent; //逆向地沿左向分支，不断朝右上方移动
				_base_node = _base_node->_parent;    //最后再朝左上方移动一步，即抵达直接前驱（如果存在）
			}
		}
	};

	template <class _Value, class _Ref, class _Ptr>
	struct _rb_tree_iterator : public _rb_tree_base_iterator
	{
		typedef _Value                                                  value_type;
		typedef _Ref                                                    reference;
		typedef _Ptr                                                    pointer;
		typedef _rb_tree_iterator<_Value, _Value&, _Value*>             iterator;
		typedef _rb_tree_iterator<_Value, const _Value&, const _Value*> const_iterator;
		typedef _rb_tree_iterator<_Value, _Ref, _Ptr>                   _self;
		typedef _rb_tree_node<_Value>*                                  _node_ptr;

		_rb_tree_iterator() {}
		_rb_tree_iterator(_node_ptr _x) { _base_node = _x; }
		_rb_tree_iterator(const iterator& _it) { _base_node = _it._base_node; }

		reference operator*() const { return _node_ptr(_base_node)->_value_field; }
		pointer operator->() const { return &(operator*()); }
		explicit operator bool() const { return _base_node != 0; }

		_self& operator++()
		{
			_increment(); return *this;
		}
		_self operator++(int)
		{
			_self tmp = *this;
			_increment();
			return tmp;
		}

		_self& operator--()
		{
			_decrement(); return *this;
		}
		_self operator--(int)
		{
			_self tmp = *this;
			_decrement();
			return tmp;
		}
	};

	inline
		bool operator==(const _rb_tree_base_iterator& _x, const _rb_tree_base_iterator& _y)
	{
		return _x._base_node == _y._base_node;
		// 两个迭代器相等，意指其所指的节点相等。
	}

	inline
		bool operator!=(const _rb_tree_base_iterator& _x,
			const _rb_tree_base_iterator& _y)
	{
		return !(_x == _y);
		// 两个迭代器不等，意指其所指的节点不等。
	}

	inline
		bidirectional_iterator_tag iterator_category(const _rb_tree_base_iterator&)
	{
		return bidirectional_iterator_tag();
	}

	inline
		typename _rb_tree_base_iterator::difference_type* distance_type(const _rb_tree_base_iterator&)
	{
		return (typename _rb_tree_base_iterator::difference_type*) 0;
	}

	template <class _Value, class _Ref, class _Ptr>
	inline
		_Value* value_type(const _rb_tree_iterator<_Value, _Ref, _Ptr>&)
	{
		return (_Value*)0;
	}


	// 以下都是全局函数：_rb_tree_rotate_left(), _rb_tree_rotate_right(),
	// _rb_tree_rebalance(), _rb_tree_rebalance_for_erase()

	// 新节点必为红节点。如果安插处之父节点亦为红节点，就违反红黑树规则，此时必须
	// 做树形旋转（及颜色改变，在程序它处）。
	inline
		void _rb_tree_rotate_left(_rb_tree_node_base* _x, _rb_tree_node_base*& _root)
	{
		// x 为旋转点
		_rb_tree_node_base* _y = _x->_rc;	 // 令y为旋转点的右子节点
		_x->_rc = _y->_lc;
		if (_y->_lc != 0)
			_y->_lc->_parent = _x;		     // 别忘了回马枪设定父节点
		_y->_parent = _x->_parent;

		// 令 y 完全顶替 x 的地位（必须将 x 对其父节点的关系完全接收过来）
		if (_x == _root)					// x 为根节点
			_root = _y;
		else if (_x == _x->_parent->_lc)	// x 为其父节点的左子节点
			_x->_parent->_lc = _y;
		else							   // x 为其父节点的右子节点
			_x->_parent->_rc = _y;
		_y->_lc = _x;
		_x->_parent = _y;
	}

	// 新节点必为红节点。如果安插处之父节点亦为红节点，就违反红黑树规则，此时必须
	// 做树形旋转（及颜色改变，在程序它处）。
	inline
		void _rb_tree_rotate_right(_rb_tree_node_base* _x, _rb_tree_node_base*& _root)
	{
		// x 为旋转点
		_rb_tree_node_base* _y = _x->_lc;	// y 为旋转点的左子节点
		_x->_lc = _y->_rc;
		if (_y->_rc != 0)
			_y->_rc->_parent = _x; 	// 别忘了回马枪设定父节点
		_y->_parent = _x->_parent;

		// 令 y 完全顶替 x 的地位（必须将 x 对其父节点的关系完全接收过来）
		if (_x == _root)					// x 为根节点
			_root = _y;
		else if (_x == _x->_parent->_rc)	// x 为其父节点的右子节点
			_x->_parent->_rc = _y;
		else							// x 为其父节点的左子节点
			_x->_parent->_lc = _y;
		_y->_rc = _x;
		_x->_parent = _y;
	}

	// 重新令树形平衡（改变颜色及旋转树形）
	// 参数一为新增节点，参数二为 root
	inline
		void _rb_tree_rebalance(_rb_tree_node_base* _x, _rb_tree_node_base*& _root)
	{
		_x->_color = _rb_tree_red;		// 新节点必为红
		while (_x != _root && _x->_parent->_color == _rb_tree_red) { // 父节点为红
			if (_x->_parent == _x->_parent->_parent->_lc) { // 父节点为祖父节点之左子节点
				_rb_tree_node_base* _y = _x->_parent->_parent->_rc;	// 令y 为伯父节点
				if (_y && _y->_color == _rb_tree_red) { 		// 伯父节点存在，且为红
					_x->_parent->_color = _rb_tree_black;  		// 更改父节点为黑
					_y->_color = _rb_tree_black;				// 更改伯父节点为黑
					_x->_parent->_parent->_color = _rb_tree_red; 	// 更改祖父节点为红
					_x = _x->_parent->_parent;
				}
				else {	// 无伯父节点，或伯父节点为黑
					if (_x == _x->_parent->_rc) { // 如果新节点为父节点之右子节点
						_x = _x->_parent;
						_rb_tree_rotate_left(_x, _root); // 第一参数为左旋点
					}
					_x->_parent->_color = _rb_tree_black;	// 改变颜色
					_x->_parent->_parent->_color = _rb_tree_red;
					_rb_tree_rotate_right(_x->_parent->_parent, _root); // 第一参数为右旋点
				}
			}
			else {	// 父节点为祖父节点之右子节点
				_rb_tree_node_base* y = _x->_parent->_parent->_lc; // 令y 为伯父节点
				if (y && y->_color == _rb_tree_red) {		// 有伯父节点，且为红
					_x->_parent->_color = _rb_tree_black;		// 更改父节点为黑
					y->_color = _rb_tree_black; 				// 更改伯父节点为黑
					_x->_parent->_parent->_color = _rb_tree_red; 	// 更改祖父节点为红
					_x = _x->_parent->_parent;	// 准备继续往上层检查...
				}
				else {	// 无伯父节点，或伯父节点为黑
					if (_x == _x->_parent->_lc) {	// 如果新节点为父节点之左子节点
						_x = _x->_parent;
						_rb_tree_rotate_right(_x, _root); 	// 第一参数为右旋点
					}
					_x->_parent->_color = _rb_tree_black;	// 改变颜色
					_x->_parent->_parent->_color = _rb_tree_red;
					_rb_tree_rotate_left(_x->_parent->_parent, _root); // 第一参数为左旋点
				}
			}
		}	// while 结束
		_root->_color = _rb_tree_black;	// 根节点永远为黑
	}

	inline
		_rb_tree_node_base* _rb_tree_rebalance_for_erase(_rb_tree_node_base* _z, _rb_tree_node_base*& _root,
			_rb_tree_node_base*& _leftmost, _rb_tree_node_base*& _rightmost)
	{
		_rb_tree_node_base* y = _z;
		_rb_tree_node_base* _x = 0;
		_rb_tree_node_base* _x_parent = 0;
		if (y->_lc == 0)               // z has at most one non-null child. y == z.
			_x = y->_rc;               // x might be null.
		else
			if (y->_rc == 0)           // z has exactly one non-null child.  y == z.
				_x = y->_lc;              // x is not null.
			else {                      // z has two non-null children.  Set y to
				y = y->_rc;             //   z's successor.  x might be null.
				while (y->_lc != 0)
					y = y->_lc;
				_x = y->_rc;
			}
			if (y != _z) {                 // relink y in place of z.  y is z's successor
				_z->_lc->_parent = y;
				y->_lc = _z->_lc;
				if (y != _z->_rc) {
					_x_parent = y->_parent;
					if (_x) _x->_parent = y->_parent;
					y->_parent->_lc = _x;      // y must be a left child
					y->_rc = _z->_rc;
					_z->_rc->_parent = y;
				}
				else
					_x_parent = y;
				if (_root == _z)
					_root = y;
				else if (_z->_parent->_lc == _z)
					_z->_parent->_lc = y;
				else
					_z->_parent->_rc = y;
				y->_parent = _z->_parent;
				std::swap(y->_color, _z->_color);
				y = _z;
				// y now points to node to be actually deleted
			}
			else {                        // y == z
				_x_parent = y->_parent;
				if (_x) _x->_parent = y->_parent;
				if (_root == _z)
					_root = _x;
				else
					if (_z->_parent->_lc == _z)
						_z->_parent->_lc = _x;
					else
						_z->_parent->_rc = _x;
				if (_leftmost == _z)
					if (_z->_rc == 0)        // z->left must be null also
						_leftmost = _z->_parent;
				// makes leftmost == header if z == root
					else
						_leftmost = _rb_tree_node_base::minimum(_x);
				if (_rightmost == _z)
					if (_z->_lc == 0)         // z->right must be null also
						_rightmost = _z->_parent;
				// makes rightmost == header if z == root
					else                      // x == z->left
						_rightmost = _rb_tree_node_base::maximum(_x);
			}
			if (y->_color != _rb_tree_red) {
				while (_x != _root && (_x == 0 || _x->_color == _rb_tree_black))
					if (_x == _x_parent->_lc) {
						_rb_tree_node_base* w = _x_parent->_rc;
						if (w->_color == _rb_tree_red) {
							w->_color = _rb_tree_black;
							_x_parent->_color = _rb_tree_red;
							_rb_tree_rotate_left(_x_parent, _root);
							w = _x_parent->_rc;
						}
						if ((w->_lc == 0 || w->_lc->_color == _rb_tree_black) &&
							(w->_rc == 0 || w->_rc->_color == _rb_tree_black)) {
							w->_color = _rb_tree_red;
							_x = _x_parent;
							_x_parent = _x_parent->_parent;
						}
						else {
							if (w->_rc == 0 || w->_rc->_color == _rb_tree_black) {
								if (w->_lc) w->_lc->_color = _rb_tree_black;
								w->_color = _rb_tree_red;
								_rb_tree_rotate_right(w, _root);
								w = _x_parent->_rc;
							}
							w->_color = _x_parent->_color;
							_x_parent->_color = _rb_tree_black;
							if (w->_rc) w->_rc->_color = _rb_tree_black;
							_rb_tree_rotate_left(_x_parent, _root);
							break;
						}
					}
					else {                  // same as above, with right <-> left.
						_rb_tree_node_base* w = _x_parent->_lc;
						if (w->_color == _rb_tree_red) {
							w->_color = _rb_tree_black;
							_x_parent->_color = _rb_tree_red;
							_rb_tree_rotate_right(_x_parent, _root);
							w = _x_parent->_lc;
						}
						if ((w->_rc == 0 || w->_rc->_color == _rb_tree_black) &&
							(w->_lc == 0 || w->_lc->_color == _rb_tree_black)) {
							w->_color = _rb_tree_red;
							_x = _x_parent;
							_x_parent = _x_parent->_parent;
						}
						else {
							if (w->_lc == 0 || w->_lc->_color == _rb_tree_black) {
								if (w->_rc) w->_rc->_color = _rb_tree_black;
								w->_color = _rb_tree_red;
								_rb_tree_rotate_left(w, _root);
								w = _x_parent->_lc;
							}
							w->_color = _x_parent->_color;
							_x_parent->_color = _rb_tree_black;
							if (w->_lc) w->_lc->_color = _rb_tree_black;
							_rb_tree_rotate_right(_x_parent, _root);
							break;
						}
					}
					if (_x) _x->_color = _rb_tree_black;
			}
			return y;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc = alloc>
	class rb_tree
	{
	protected:
		typedef void*                                 void_pointer;
		typedef _rb_tree_node_base*                   _base_ptr;
		typedef _rb_tree_node<_Value>                 _rb_tree_node;
		typedef simple_alloc<_rb_tree_node, _Alloc>   _rb_tree_node_allocator;
		typedef _rb_tree_color_type                   _color_type;
	public:
		//iterator定义在后面
		typedef _Key                key_type;
		typedef _Value              value_type;
		typedef value_type*         pointer;
		typedef const value_type*   const_pointer;
		typedef value_type&         reference;
		typedef const value_type&   const_reference;
		typedef _rb_tree_node*      _node_ptr;
		typedef size_t              size_type;
		typedef ptrdiff_t           difference_type;

	protected:
		_node_ptr _get_node() { return _rb_tree_node_allocator::allocate(); }
		void _put_node(_node_ptr _p) { _rb_tree_node_allocator::deallocate(_p); }

		_node_ptr _create_node(const value_type& _x)
		{
			_node_ptr _tmp = _get_node();			// 配置空间
			try
			{
				construct(&_tmp->_value_field, _x);	// 建构内容
			}
			catch (...)
			{
				_put_node(_tmp);
			}
			return _tmp;
		}

		_node_ptr _clone_node(_node_ptr _x)
		{	// 复制一个节点（值和色）
			_node_ptr _tmp = _create_node(_x->_value_field);
			_tmp->_color = _x->_color;
			_tmp->_lc = 0;
			_tmp->_rc = 0;
			return _tmp;
		}

		void _destroy_node(_node_ptr _p)
		{
			destroy(&_p->_value_field);		// 解构内容
			_put_node(_p);					// 释还内存
		}

	protected:
		// RB-tree 只以三笔数据表现。
		size_type _node_count;   // 追踪记录树的大小（节点数量）
		_node_ptr _header;
		_Compare _key_compare;	 // 节点间的键值大小比较准则

		// 以下三个函数用来方便取得 header 的成员
		_node_ptr& root() const { return (_node_ptr&)_header->_parent; }
		_node_ptr& leftmost() const { return (_node_ptr&)_header->_lc; }
		_node_ptr& rightmost() const { return (_node_ptr&)_header->_rc; }

		// 以下六个函数用来方便取得节点 x 的成员
		static _node_ptr& left(_node_ptr x) { return (_node_ptr&)(x->_lc); }
		static _node_ptr& right(_node_ptr x) { return (_node_ptr&)(x->_rc); }
		static _node_ptr& parent(_node_ptr x) { return (_node_ptr&)(x->_parent); }
		static reference value(_node_ptr x) { return x->_value_field; }
		static const _Key& key(_node_ptr x) { return _KeyOfValue()(value(x)); }
		static _color_type& color(_node_ptr x) { return (_color_type&)(x->_color); }

		// 以下六个函数用来方便取得节点 x 的成员
		static _node_ptr& left(_base_ptr x) { return (_node_ptr&)(x->_lc); }
		static _node_ptr& right(_base_ptr x) { return (_node_ptr&)(x->_rc); }
		static _node_ptr& parent(_base_ptr x) { return (_node_ptr&)(x->_parent); }
		static reference value(_base_ptr x) { return ((_node_ptr)x)->_value_field; }
		static const _Key& key(_base_ptr x) { return _KeyOfValue()(value(_node_ptr(x))); }
		static _color_type& color(_base_ptr x) { return (_color_type&)(_node_ptr(x)->_color); }

		// 求取极大值和极小值。node class 有实作此功能，交给它们完成即可。
		static _node_ptr minimum(_node_ptr x)
		{
			return (_node_ptr)_rb_tree_node_base::minimum(x);
		}
		static _node_ptr maximum(_node_ptr x)
		{
			return (_node_ptr)_rb_tree_node_base::maximum(x);
		}

	public:
		typedef _rb_tree_iterator<value_type, reference, pointer>             iterator;
		typedef _rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
	private:
		iterator _insert(_base_ptr x_, _base_ptr y_, const _Value& v);
		_node_ptr _copy(_node_ptr x, _node_ptr p);
		void _erase(_node_ptr x);
		void init()
		{
			_header = _get_node();	       // 产生一个节点空间，令 header 指向它
			color(_header) = _rb_tree_red; // 令 header 为红色，用来区分 header  
										   // 和 root(黑色)（在 iterator.operator++ 中）
			root() = 0;
			leftmost() = _header;	      // 令 header 的左子节点为自己。
			rightmost() = _header;	      // 令 header 的右子节点为自己。
		}

	public:
		//构造函数
		rb_tree(const _Compare& comp = _Compare()) : _node_count(0), _key_compare(comp)
		{
			init();
		}

		// 以另一个 rb_tree 物件 x 为初值
		rb_tree(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& x) : _node_count(0), _key_compare(x._key_compare)
		{
			_header = _get_node();	// 产生一个节点空间，令 header 指向它
			color(_header) = _rb_tree_red;	// 令 header 为红色，注意color()返回的引用
			if (x.root() == 0)          //  如果 x 是个空白树
			{
				root() = 0;
				leftmost() = _header; 	// 令 header 的左子节点为自己。
				rightmost() = _header; // 令 header 的右子节点为自己。
			}
			else               //  x 不是一个空白树
			{
				try
				{
					root() = _copy(x.root(), _header);
				}
				catch (...)
				{
					_put_node(_header);
				}
				leftmost() = minimum(root());	// 令 header 的左子节点为最小节点
				rightmost() = maximum(root());	// 令 header 的右子节点为最大节点
			}
			_node_count = x._node_count;
		}
		//析构函数
		~rb_tree()
		{
			clear();
			_put_node(_header);
		}

		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& operator=(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& x);

	public:
		// accessors:
		_Compare key_comp() const { return _key_compare; }
		iterator begin() { return leftmost(); }		// RB 树的起头为最左（最小）节点处
		const_iterator begin() const { return leftmost(); }
		iterator end() { return _header; }	// RB 树的终点为 header所指处
		const_iterator end() const { return _header; }
		bool empty() const { return _node_count == 0; }
		size_type size() const { return _node_count; }
		size_type max_size() const { return size_type(-1); }

		void swap(rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& t)
		{
			// RB-tree 只以三个资料成员表现。所以互换两个 RB-trees时，
			// 只需将这三个成员互换即可。
			std::swap(_header, t._header);
			std::swap(_node_count, t._node_count);
			std::swap(_key_compare, t._key_compare);
		}

	public:
		// insert/erase
		// 将 x 安插到 RB-tree 中（保持节点值独一无二）。
		pair<iterator, bool> insert_unique(const _Value & v);
		// 将 x 安插到 RB-tree 中（允许节点值重复）。
		iterator insert_equal(const _Value & v);

		iterator insert_unique(iterator position, const _Value & v);
		iterator insert_equal(iterator position, const _Value & v);

		template<class _Iterator>
		void insert_equal(_Iterator first, _Iterator last);
		template<class _Iterator>
		void insert_unique(_Iterator first, _Iterator last);

		void erase(iterator position);
		size_type erase(const _Key & x);
		void erase(iterator first, iterator last);
		void clear()
		{
			if (_node_count != 0)
			{
				_erase(root());
				leftmost() = _header;
				root() = 0;
				rightmost() = _header;
				_node_count = 0;
			}
		}

	public:
		// 集合（set）的各种操作行为:
		iterator find(const _Key & k);
		const_iterator find(const _Key & k) const;
		size_type count(const _Key & k) const;
		iterator lower_bound(const _Key & k);
		const_iterator lower_bound(const _Key & k) const;
		iterator upper_bound(const _Key & k);
		const_iterator upper_bound(const _Key & k) const;
		pair<iterator, iterator> equal_range(const _Key & k);
		pair<const_iterator, const_iterator> equal_range(const _Key & k) const;
	public:
		// Debugging.
		bool _rb_verify() const;
	};//end of rb_tree

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	inline
		bool operator==(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& x,
			const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& y)
	{
		return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	inline
		bool operator<(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& x,
			const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& y)
	{
		return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class _Key, class _Value, class KeyOfValue, class _Compare, class _Alloc>
	inline
		void swap(rb_tree<_Key, _Value, KeyOfValue, _Compare, _Alloc>& x,
			rb_tree<_Key, _Value, KeyOfValue, _Compare, _Alloc>& y)
	{
		x.swap(y);
	}


	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>&
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::
		operator=(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& x)
	{
		if (this != &x)
		{
			// Note that Key may be a constant type.
			clear();
			_node_count = 0;
			_key_compare = x._key_compare;
			if (x.root() == 0)
			{
				root() = 0;
				leftmost() = _header;
				rightmost() = _header;
			}
			else
			{
				root() = _copy(x.root(), _header);
				leftmost() = minimum(root());
				rightmost() = maximum(root());
				_node_count = x._node_count;
			}
		}
		return *this;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::
		_insert(_base_ptr x_, _base_ptr y_, const _Value& v)
	{
		// 参数x_ 为新值安插点，参数y_ 为安插点之父节点，参数v为新值。
		_node_ptr x = (_node_ptr)x_;
		_node_ptr y = (_node_ptr)y_;
		_node_ptr z;

		// key_compare 是键值大小比较准则。应该会是个 function object。
		if (y == _header || x != 0 || _key_compare(_KeyOfValue()(v), key(y))) {
			z = _create_node(v);  // 产生一个新节点
			left(y) = z;          // 这使得当 y 即为 header时，leftmost() = z
			if (y == _header) {
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())	// 如果y为最左节点
				leftmost() = z;           	// 维护leftmost()，使它永远指向最左节点
		}
		else {
			z = _create_node(v);		// 产生一个新节点
			right(y) = z;				// 令新节点成为安插点之父节点 y 的右子节点
			if (y == rightmost())
				rightmost() = z;          	// 维护rightmost()，使它永远指向最右节点
		}
		parent(z) = y;		// 设定新节点的父节点
		left(z) = 0;		// 设定新节点的左子节点
		right(z) = 0; 		// 设定新节点的右子节点
							// 新节点的颜色将在 __rb_tree_rebalance() 设定（并调整）
		_rb_tree_rebalance(z, _header->_parent);	// 参数一为新增节点，参数二为 root
		++_node_count;		// 节点数累加
		return iterator(z);	// 传回一个迭代器，指向新增节点
	}

	// 安插新值；节点键值允许重复。
	// 注意，传回值是一个 RB-tree 迭代器，指向新增节点
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_equal(const _Value& v)
	{
		_node_ptr y = _header;
		_node_ptr x = root();	// 从根节点开始
		while (x != 0) {		// 从根节点开始，往下寻找适当的安插点
			y = x;
			x = _key_compare(_KeyOfValue()(v), key(x)) ? left(x) : right(x);
			// 以上，遇「大」则往左，遇「小于或等于」则往右
		}
		return _insert(x, y, v);
	}

	// 安插新值；节点键值不允许重复，若重复则安插无效。
	// 注意，传回值是个pair，第一元素是个 RB-tree 迭代器，指向新增节点，
	// 第二元素表示安插成功与否。
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	pair<typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(const _Value& _v)
	{
		_node_ptr _y = _header;
		_node_ptr _x = root();	// 从根节点开始
		bool _comp = true;
		while (_x != 0)
		{ 		// 从根节点开始，往下寻找适当的安插点
			_y = _x;
			_comp = _key_compare(_KeyOfValue()(_v), key(_x)); // v 键值小于目前节点之键值？
			_x = _comp ? left(_x) : right(_x);	// 遇「大」则往左，遇「小于或等于」则往右
		}
		// 离开 while 循环之后，y 所指即安插点之父节点（此时的它必为叶节点）

		iterator _j = iterator(_y);   // 令迭代器j指向安插点之父节点 y
		if (_comp)	// 如果离开 while 循环时 comp 为真（表示遇「大」，将安插于左侧）
			if (_j == begin())   // 如果安插点之父节点为最左节点
				return pair<iterator, bool>(_insert(_x, _y, _v), true);
		// 以上，x 为安插点，y 为安插点之父节点，v 为新值。
			else	// 否则（安插点之父节点不为最左节点）
				--_j;	// 调整 j，回头准备测试...
		if (_key_compare(key(_j._base_node), _KeyOfValue()(_v)))
			// 小于新值（表示遇「小」，将安插于右侧）
			return pair<iterator, bool>(_insert(_x, _y, _v), true);

		// 进行至此，表示新值一定与树中键值重复，那么就不该插入新值。
		return pair<iterator, bool>(_j, false);
	}


	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(iterator position,
			const _Value& v)
	{
		if (position._base_node == _header->_lc) // begin()
			if (size() > 0 && _key_compare(_KeyOfValue()(v), key(position._base_node)))
				return _insert(position._base_node, position._base_node, v);
		// first argument just needs to be non-null 
			else
				return insert_unique(v).first;
		else if (position._base_node == _header) // end()
			if (_key_compare(key(rightmost()), _KeyOfValue()(v)))
				return _insert(0, rightmost(), v);
			else
				return insert_unique(v).first;
		else {
			iterator before = position;
			--before;
			if (_key_compare(key(before._base_node), _KeyOfValue()(v))
				&& _key_compare(_KeyOfValue()(v), key(position._base_node)))
				if (right(before._base_node) == 0)
					return _insert(0, before._base_node, v);
				else
					return _insert(position._base_node, position._base_node, v);
			// first argument just needs to be non-null 
			else
				return insert_unique(v).first;
		}
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_equal(iterator position,
			const _Value& v) {
		if (position._base_node == _header->_lc) // begin()
			if (size() > 0 && _key_compare(_KeyOfValue()(v), key(position._base_node)))
				return _insert(position._base_node, position._base_node, v);
		// first argument just needs to be non-null 
			else
				return insert_equal(v);
		else if (position._base_node == _header) // end()
			if (!_key_compare(_KeyOfValue()(v), key(rightmost())))
				return _insert(0, rightmost(), v);
			else
				return insert_equal(v);
		else {
			iterator before = position;
			--before;
			if (!_key_compare(_KeyOfValue()(v), key(before._base_node))
				&& !_key_compare(key(position._base_node), _KeyOfValue()(v)))
				if (right(before._base_node) == 0)
					return _insert(0, before._base_node, v);
				else
					return _insert(position._base_node, position._base_node, v);
			// first argument just needs to be non-null 
			else
				return insert_equal(v);
		}
	}

	template <class _Key, class _Value, class _Key_of_Value, class _Compare, class _Alloc>
	template<class _Iterator>
	void rb_tree<_Key, _Value, _Key_of_Value, _Compare, _Alloc>::insert_equal(_Iterator first, _Iterator last)
	{
		for (; first != last; ++first)
			insert_equal(*first);
	}

	template <class _Key, class _Value, class _Key_of_Value, class _Compare, class _Alloc>
	template<class _Iterator>
	void rb_tree<_Key, _Value, _Key_of_Value, _Compare, _Alloc>::insert_unique(_Iterator first, _Iterator last)
	{
		for (; first != last; ++first)
			insert_unique(*first);
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	inline
		void rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(iterator position)
	{
		_node_ptr y = (_node_ptr)_rb_tree_rebalance_for_erase(position._base_node,
			_header->_parent,
			_header->_lc,
			_header->_rc);
		_destroy_node(y);
		--_node_count;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(const _Key& x)
	{
		pair<iterator, iterator> p = equal_range(x);
		size_type n = 0;
		distance(p.first, p.second, n);
		erase(p.first, p.second);
		return n;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_node_ptr
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_copy(_node_ptr x, _node_ptr p)
	{
		// structural copy.  x and p must be non-null.
		_node_ptr top = _clone_node(x);
		top->_parent = p;

		try
		{
			if (x->_rc)
				top->_rc = _copy(right(x), top);
			p = top;
			x = left(x);

			while (x != 0)
			{
				_node_ptr y = _clone_node(x);
				p->_lc = y;
				y->_parent = p;
				if (x->_rc)
					y->_rc = _copy(right(x), y);
				p = y;
				x = left(x);
			}
		}
		catch (...)
		{
			_erase(top);
		}

		return top;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	void rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_erase(_node_ptr x) {
		// erase without rebalancing
		while (x != 0) {
			_erase(right(x));
			_node_ptr y = left(x);
			_destroy_node(x);
			x = y;
		}
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	void rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(iterator first,
		iterator last) {
		if (first == begin() && last == end())
			clear();
		else
			while (first != last) erase(first++);
	}


	// 寻找 RB 树中是否有键值为 k 的节点
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(const _Key& k) {
		_node_ptr y = _header;        // Last node which is not less than k. 
		_node_ptr x = root();        // Current node. 

		while (x != 0)
			// 以下，key_compare 是节点键值大小比较准则。应该会是个 function object。
			if (!_key_compare(key(x), k))
				// 进行到这里，表示 x 键值大于 k。遇到大值就向左走。
				y = x, x = left(x);	// 注意语法!
			else
				// 进行到这里，表示 x 键值小于 k。遇到小值就向右走。
				x = right(x);

		iterator j = iterator(y);
		return (j == end() || _key_compare(k, key(j._base_node))) ? end() : j;
	}

	// 寻找 RB 树中是否有键值为 k 的节点
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(const _Key& k) const {
		_node_ptr y = _header; /* Last node which is not less than k. */
		_node_ptr x = root(); /* Current node. */

		while (x != 0) {
			// 以下，key_compare 是节点键值大小比较准则。应该会是个 function object。
			if (!_key_compare(key(x), k))
				// 进行到这里，表示 x 键值大于 k。遇到大值就向左走。
				y = x, x = left(x);	// 注意语法!
			else
				// 进行到这里，表示 x 键值小于 k。遇到小值就向右走。
				x = right(x);
		}
		const_iterator j = const_iterator(y);
		return (j == end() || _key_compare(k, key(j._base_node))) ? end() : j;
	}

	// 计算 RB 树中键值为 k 的节点个数
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::count(const _Key& k) const {
		pair<const_iterator, const_iterator> p = equal_range(k);
		size_type n = 0;
		distance(p.first, p.second, n);
		return n;
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::lower_bound(const _Key& k) {
		_node_ptr y = _header; /* Last node which is not less than k. */
		_node_ptr x = root(); /* Current node. */

		while (x != 0)
			if (!_key_compare(key(x), k))
				y = x, x = left(x);
			else
				x = right(x);

		return iterator(y);
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::lower_bound(const _Key& k) const {
		_node_ptr y = _header; /* Last node which is not less than k. */
		_node_ptr x = root(); /* Current node. */

		while (x != 0)
			if (!_key_compare(key(x), k))
				y = x, x = left(x);
			else
				x = right(x);

		return const_iterator(y);
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::upper_bound(const _Key& k) {
		_node_ptr y = _header; /* Last node which is greater than k. */
		_node_ptr x = root(); /* Current node. */

		while (x != 0)
			if (_key_compare(k, key(x)))
				y = x, x = left(x);
			else
				x = right(x);

		return iterator(y);
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::upper_bound(const _Key& k) const {
		_node_ptr y = _header; /* Last node which is greater than k. */
		_node_ptr x = root(); /* Current node. */

		while (x != 0)
			if (_key_compare(k, key(x)))
				y = x, x = left(x);
			else
				x = right(x);

		return const_iterator(y);
	}

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	inline
		pair<typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator,
		typename rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator>
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::equal_range(const _Key& k) {
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	template <class _Key, class _Value, class _Key_of_Value, class _Compare, class _Alloc>
	inline
		pair<typename rb_tree<_Key, _Value, _Key_of_Value, _Compare, _Alloc>::const_iterator,
		typename rb_tree<_Key, _Value, _Key_of_Value, _Compare, _Alloc>::const_iterator>
		rb_tree<_Key, _Value, _Key_of_Value, _Compare, _Alloc>::equal_range(const _Key& k) const {
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

	// 计算从 node 至 root 路径中的黑节点数量。
	inline int _black_count(_rb_tree_node_base* node, _rb_tree_node_base* root)
	{
		if (node == 0)
			return 0;
		else {
			int bc = node->_color == _rb_tree_black ? 1 : 0;
			if (node == root)
				return bc;
			else
				return bc + _black_count(node->_parent, root); // 累加
		}
	}

	// 验证己身这棵树是否符合 RB 树的条件
	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	bool
		rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_rb_verify() const
	{
		// 空树，符合RB树标准
		if (_node_count == 0 || begin() == end())
			return _node_count == 0 && begin() == end() &&
			_header->_lc == _header && _header->_rc == _header;

		// 最左（叶）节点至 root 路径内的黑节点数
		int len = _black_count(leftmost(), root());
		// 以下走访整个RB树，针对每个节点（从最小到最大）...
		for (const_iterator it = begin(); it != end(); ++it) {
			_node_ptr x = (_node_ptr)it._base_node; // __rb_tree_base_iterator::node
			_node_ptr L = left(x);		// 这是左子节点
			_node_ptr R = right(x); 	// 这是右子节点

			if (x->_color == _rb_tree_red)
				if ((L && L->_color == _rb_tree_red) ||
					(R && R->_color == _rb_tree_red))
					return false;	// 父子节点同为红色，不符合 RB 树的要求。

			if (L && _key_compare(key(x), key(L))) // 目前节点的键值小于左子节点键值
				return false;         	// 不符合二元搜索树的要求。
			if (R && _key_compare(key(R), key(x))) // 目前节点的键值大于右子节点键值
				return false;		// 不符合二元搜索树的要求。

									// 「叶节点至 root」路径内的黑节点数，与「最左节点至 root」路径内的黑节点数不同。
									// 这不符合 RB 树的要求。
			if (!L && !R && _black_count(x, root()) != len)
				return false;
		}

		if (leftmost() != _rb_tree_node_base::minimum(root()))
			return false;	// 最左节点不为最小节点，不符合二元搜索树的要求。
		if (rightmost() != _rb_tree_node_base::maximum(root()))
			return false;	// 最右节点不为最大节点，不符合二元搜索树的要求。
		return true;
	}
}//end of MyStl
#endif // end of RB_TREE_H_
