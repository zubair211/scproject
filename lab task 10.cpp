#include <iostream>

template <typename key_type>
struct tnode
{
    key_type key;
    tnode<key_type>* left;
    tnode<key_type>* right;
    tnode<key_type>* parent;
    bool is_nill;

    tnode()
    {
        key = key_type();
        left = right = parent = nullptr;
        is_nill = false;
    }
};

template <typename key_type>
class set
{
private:
    int n;
    tnode<key_type>* h; // sentinel

public:
    set()
    {
        h = new tnode<key_type>;
        h->left = h->right = h->parent = h;
        h->is_nill = true;
        n = 0;
    }

    void insert(const key_type& k)
    {
        tnode<key_type>* nn = new tnode<key_type>;
        nn->key = k;
        nn->left = nn->right = nn->parent = h;
        nn->is_nill = false;

        if (h->parent == h) // empty tree
        {
            h->parent = nn;
            h->left = nn;
            h->right = nn;
            nn->parent = h;
            n++;
            return;
        }

        tnode<key_type>* temp = h->parent;
        while (true)
        {
            if (k < temp->key)
            {
                if (temp->left != h)
                    temp = temp->left;
                else
                {
                    temp->left = nn;
                    nn->parent = temp;
                    break;
                }
            }
            else if (k > temp->key)
            {
                if (temp->right != h)
                    temp = temp->right;
                else
                {
                    temp->right = nn;
                    nn->parent = temp;
                    break;
                }
            }
            else // duplicate
            {
                std::cout << "duplicate key: " << k << "\n";
                delete nn;
                return;
            }
        }

        // Update h->left and h->right (min and max)
        if (k < h->left->key)
            h->left = nn;
        if (k > h->right->key)
            h->right = nn;

        n++;
    }

    bool empty() { return h->parent == h; }
    int size() { return n; }

    // ---------- Iterator ----------
    class iterator
    {
    private:
        tnode<key_type>* ptr;
        tnode<key_type>* h; // needed to detect sentinel
        friend class set;

    public:
        iterator(tnode<key_type>* p = nullptr, tnode<key_type>* header = nullptr)
        {
            ptr = p;
            h = header;
        }

        key_type& operator*() { return ptr->key; }
        key_type* operator->() { return &(ptr->key); }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        // Pre-increment
        iterator& operator++()
        {
            if (ptr == h) return *this;

            if (ptr->right != h) // has right subtree
            {
                ptr = ptr->right;
                while (ptr->left != h)
                    ptr = ptr->left;
                return *this;
            }

            // No right child, go up until coming from left
            tnode<key_type>* p = ptr->parent;
            while (p != h && ptr == p->right)
            {
                ptr = p;
                p = p->parent;
            }
            ptr = p; // next node (or h = end)
            return *this;
        }

        // Post-increment
        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    iterator begin() { return iterator(h->left, h); }
    iterator end() { return iterator(h, h); }

    iterator find(const key_type& k)
    {
        tnode<key_type>* temp = h->parent;
        while (temp != h)
        {
            if (k == temp->key) return iterator(temp, h);
            if (k < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return end();
    }

    bool contains(const key_type& k) { return find(k) != end(); }

    tnode<key_type>* successor(tnode<key_type>* node)
    {
        if (node->right != h)
        {
            node = node->right;
            while (node->left != h) node = node->left;
            return node;
        }

        tnode<key_type>* p = node->parent;
        while (p != h && node == p->right)
        {
            node = p;
            p = p->parent;
        }
        return p;
    }

    void erase(iterator pos)
    {
        tnode<key_type>* to_del = pos.ptr;
        if (to_del == h) return;

        if (to_del->left != h && to_del->right != h) // 2 children
        {
            tnode<key_type>* succ = successor(to_del);
            to_del->key = succ->key;
            erase(iterator(succ, h));
            return;
        }

        // 1 child or no child
        tnode<key_type>* child = (to_del->left != h) ? to_del->left : to_del->right;
        if (child != h) child->parent = to_del->parent;

        if (to_del->parent == h)
            h->parent = child;
        else if (to_del == to_del->parent->left)
            to_del->parent->left = child;
        else
            to_del->parent->right = child;

        // update h->left and h->right
        if (to_del == h->left) h->left = (child != h) ? child : h;
        if (to_del == h->right) h->right = (child != h) ? child : h;

        delete to_del;
        n--;
    }

    void inorder(tnode<key_type>* root)
    {
        if (root == h) return;
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }

    void display()
    {
        if (h->parent == h)
        {
            std::cout << "Set is empty\n";
            return;
        }
        std::cout << "Set elements (in-order): ";
        inorder(h->parent);
        std::cout << "\n";
    }
};

// ----------- MAIN -------------
int main()
{
    set<int> s;
    s.insert(2);
    s.insert(8);
    s.insert(4);
    s.insert(1);

    std::cout << "\nSIZE OF SET = " << s.size() << "\n";
    s.display();

    // Traversal using iterator
    std::cout << "\nTraversing set using iterator: ";
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Erase example
    std::cout << "\nErasing 4 from set...\n";
    auto it = s.find(4);
    if (it != s.end())
        s.erase(it);

    s.display();

    std::cout << "\nCheck contain for 4 = " << s.contains(4);
    std::cout << "\nCheck contain for 10 = " << s.contains(10);
    std::cout << "\n";
    return 0;
}
