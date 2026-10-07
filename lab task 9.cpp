#include <iostream>
template<typename key_type>
struct tnode
{
	key_type key;
	tnode<key_type>* left, *right, *parent;
	bool is_nill;

	tnode()
	{
		key = key_type();
		left = right = parent = nullptr;
		is_nill = false;
	}
};
template<typename key_type>
class set
{
private:
	int n;
	tnode<key_type>* H;

public:
	set()
	{
		H = new tnode<key_type>;
		H->left = H->right = H->parent = H;
		H->is_nill = true;
		n = 0;
	}
	void insert(const key_type& k)
	{
		tnode<key_type>* nn, *temp;
		nn = new tnode<key_type>;
		nn->left = H;
		nn->right = H;
		nn->parent = H;
		nn->is_nill = false;
		n++;
		nn->key = k;
		if (H->parent == H)
		{
			H->parent = nn;
			H->left = nn;
			H->right = nn;
			nn->parent = H;
		}
		temp = H->parent;
		while (1)
		{
			if (k < temp->key)
			{
				if (temp->left != H)
				{
					temp = temp->left;
				}
				else
				{
					temp->left = nn;
					nn->parent = temp;
					break;
				}
			}
			else if (k > temp->key)
			{
				if (temp->right != H)
				{
					temp = temp->right;
				}
				else
				{
					temp->right = nn;
					nn->parent = temp;
					break;
				}
			}
			else
			{
				std::cout << "duplicate keys";
				break;
			}
		}
		if (k < H->left->key)
		{
			H->left = nn;
		}
		else if (k > H->right->key)
		{
			H->right = nn;
		}
	}

	bool empty()
	{
		return H->parent == H;
	}
	int size()
	{
		return n;
	}
	class iterator
	{
	private:
		tnode<key_type>* ptr;
		friend class set;

	public:
		iterator(tnode<key_type>* p = nullptr)
		{
			ptr = p;
		}
		key_type& operator *()
		{
			return ptr->key;
		}
		bool operator ==(const iterator&other)const
		{
			return this->ptr == other.ptr;

		}
		bool operator !=(const iterator&other)const
		{
			return this->ptr != other.ptr;

		}
		key_type* operator->()
		{
			return &(ptr->key);
		}
		iterator& operator --() {

			if (ptr->is_nill) {
				ptr = ptr->parent;
				while (!ptr->right->is_nill) {
					ptr = ptr->right;
				}
				return *this;
			}
			else if (!ptr->left -> is_nill) {
				ptr = ptr->left;
				if (!ptr->right -> is_nill) {
					while (!ptr->right -> is_nill) {
						ptr = ptr->right;
					}
					return*this;
				}
				return*this;
			}
				else {
					tnode<key_type>*parent = ptr->parent;
					while (!parent-> is_nill && ptr == parent->left) {
						ptr = parent;
						parent = parent->parent;
					}
					ptr = parent;
					return*this;
				}
		
			}
		
		
	};
	tnode<key_type>* insert_r(tnode<key_type>*rootnode, int key) {
		
		if (key > rootnode->key) {
			rootnode->right = insert(rootnode->right, key);
		}
		else if (key < rootnode->key) {
			rootnode->left = insert(rootnode->left, key);
		}
		else if (key == rootnode->key) {
			return rootnode;
		}
		return rootnode;
	}
	
	iterator find(const key_type& k1)
	{
		iterator it;

		tnode<key_type>* temp;
		temp = H->parent;
		while (temp != H)
		{
			if (k1 == temp->key)
			{
				it.ptr = temp;
				return it;
			}
			else if (k1 < temp->key)
			{
				temp = temp->left;
			}
			else if (k1 > temp->key)
			{
				temp = temp->right;
			}
		}
		it.ptr = H;
		return it;
	}
	int count(const key_type& k)
	{
		return find(k) != end();
	}
	int contains(const key_type& k)
	{
		return find(k) != end();
	}

	iterator begin()
	{
		return iterator(H->left);
	}
	iterator end()
	{
		return iterator(H);
	}
	void inorder(tnode<key_type>* root)
	{
		if (root == H) return;
		inorder(root->left);
		std::cout << root->key << " ";
		inorder(root->right);
	}
	void erase(iterator pos)
	{
		tnode<key_type>* to_del, *lc;
		to_del = pos.ptr;
		if (to_del->left == H && to_del->right == H)
		{
			if (to_del == to_del->parent->right)
			{
				to_del->parent->right = H;
			}
			else
			{
				to_del->parent->left = H;
			}
			delete to_del;
			--n;
		}
		else if (to_del->left != H && to_del->right == H)
		{
			lc = to_del->left;
			if (to_del == to_del->parent->right)
			{
				to_del->parent->right = lc;
			}
			else
			{
				to_del->parent->left = lc;
			}
			delete to_del;
			--n;
		}
		else if (to_del->left == H && to_del->right != H)
		{
			lc = to_del->right;
			if (to_del == to_del->parent->right)
			{
				to_del->parent->right = lc;
			}
			else
			{
				to_del->parent->left = lc;
			}
			delete to_del;
			--n;
		}

	}
	void display()
	{
		if (H->parent == H)
		{
			std::cout << "\nSet is empty\n";
			return;
		}
		std::cout << "\nSet elements (in-order): ";
		inorder(H->parent);
		std::cout << "\n";
	}
};
int main()
{
	set<int> s;
	tnode<int>*rootnode;
//	rootnode = s.insert_r(rootnode, 50);

	s.insert(2);
	s.insert(8);
	s.insert(4);
	s.insert(1);
	s.display();
	std::cout << "\nReverse display of tree\n";

	set<int>::iterator it = s.end();
	--it;

	while (true) {
		std::cout << *it << " ";
		if (it == s.begin()) break;
		--it;
	}

	std::cout << "\n SIZE OF SET  =" << s.size();
	set<int>::iterator itr = s.find(10);
	if (itr != s.end())
	{
		std::cout << "\n key is " << *itr << std::endl;
	}
	else
	{
		std::cout << "\n Key not found" << std::endl;

	}

	/*set<int>::iterator it;
	it = s.end();
	std::cout << "\n cout with -- operator\n ";
	while (it != s.begin()) {
		std::cout << *it << " ";
		--it;
	}*/
	s.display();
	std::cout << "\nErasing 4 from set...\n";
	set<int>::iterator itr1 = s.find(4);
	if (itr1 != s.end())
		s.erase(itr1);

	s.display();

	std::cout << "\ncheck contain for 4   " << s.contains(4);
	std::cout << "\n check contain for 10  " << s.contains(10);
	return 0;
}